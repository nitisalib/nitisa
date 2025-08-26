// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region CErrorListener
	void CDbDelete::CErrorListener::NotifyOnError(const AnsiString& function, const int line, const ErrorInfo& info, const StringKeyValueArray& args)
	{
		Error = L"ERROR " + ToString(info.Code) + L" in " + AnsiToString(function) + L":" + ToString(line) + L": " + ReplaceAll(info.Message, args);
	}
#pragma endregion

#pragma region CConnectionErrorListenerLock
	CDbDelete::CConnectionErrorListenerLock::CConnectionErrorListenerLock(IDbConnection* connection, IErrorListener* listener) :
		m_pConnection{ connection },
		m_pOld{ connection->ErrorListener }
	{
		m_pConnection->setErrorListener(listener);
	}

	CDbDelete::CConnectionErrorListenerLock::~CConnectionErrorListenerLock()
	{
		m_pConnection->setErrorListener(m_pOld);
	}
#pragma endregion

#pragma region CStatementErrorListenerLock
	CDbDelete::CStatementErrorListenerLock::CStatementErrorListenerLock(IDbStatement *statement, IErrorListener *listener) :
		m_pStatement{ statement },
		m_pOld{ statement->ErrorListener }
	{
		m_pStatement->setErrorListener(listener);
	}

	CDbDelete::CStatementErrorListenerLock::~CStatementErrorListenerLock()
	{
		m_pStatement->setErrorListener(m_pOld);
	}
#pragma endregion

#pragma region Constructor & destructor
	CDbDelete::CDbDelete(IDbConnection* connection, IDbStatement *statement, IDbQueryBuilder* qb) :
		CReleasable(),
		m_pConnection{ connection },
		m_pStatement{ statement },
		m_pQueryBuilder{ qb }
	{
		m_bDistinct = false;
		m_iLimit = -1;
		m_iOffset = -1;
	}
#pragma endregion

#pragma region Query building
	CDbDelete* CDbDelete::From(const String& table)
	{
		if (!table.empty())
		{
			m_aFrom.clear();
			m_aFrom.push_back(StringKeyValue{ table, L"" });
		}
		return this;
	}

	CDbDelete* CDbDelete::From(const String& table, const String& alias)
	{
		if (!table.empty())
		{
			m_aFrom.clear();
			m_aFrom.push_back(StringKeyValue{ table, alias });
		}
		return this;
	}

	CDbDelete* CDbDelete::Where(DbCondition condition)
	{
		m_pWhere = condition;
		return this;
	}

	CDbDelete* CDbDelete::Where(const DbConditions &conditions)
	{
		m_pWhere = nullptr;
		for (auto condition : conditions)
			AndWhere(condition);
		return this;
	}

	CDbDelete* CDbDelete::AndWhere(DbCondition condition)
	{
		if (m_pWhere)
		{
			if (condition)
				m_pWhere = db::And(m_pWhere, condition);
		}
		else
			m_pWhere = condition;
		return this;
	}

	CDbDelete* CDbDelete::OrWhere(DbCondition condition)
	{
		if (m_pWhere)
		{
			if (condition)
				m_pWhere = db::Or(m_pWhere, condition);
		}
		else
			m_pWhere = condition;
		return this;
	}

	CDbDelete* CDbDelete::OrderBy(const String& column, const DbOrder& order)
	{
		if (!column.empty())
			m_aOrderBy.push_back(DbOrderBy{ column, order });
		return this;
	}

	CDbDelete* CDbDelete::OrderBy(const DbOrderByArray& columns)
	{
		for (auto const& column : columns)
			if (!column.first.empty())
				m_aOrderBy.push_back(column);
		return this;
	}

	CDbDelete* CDbDelete::Limit(const int64& limit)
	{
		m_iLimit = limit;
		return this;
	}
#pragma endregion

#pragma region Execute
	void CDbDelete::Execute()
	{
		// Check connection
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();

		// Check query builder
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		// Prepare raw query
		String query;
		if (!m_pQueryBuilder->Delete(this, query))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

		// Prepare statement
		ReleasablePtr<IDbStatement> statement;
		if (!m_pStatement)
		{
			CConnectionErrorListenerLock e_lock{ m_pConnection, &m_cErrorListener };
			statement = m_pConnection->CreateStatement();
			if (!statement)
				throw DbExceptionCreateStatement(m_cErrorListener.Error);
		}
		else
		{
			statement = m_pStatement;
			statement->AddRef();
		}
		CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };

		// Execute statement
		DbResult result{ statement->Execute(query) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}
#pragma endregion
}