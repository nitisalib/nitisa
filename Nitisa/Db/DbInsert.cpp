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
	void CDbInsert::CErrorListener::NotifyOnError(const AnsiString &function, const int line, const ErrorInfo &info, const StringKeyValueArray &args)
	{
		Error = L"ERROR " + ToString(info.Code) + L" in " + AnsiToString(function) + L":" + ToString(line) + L": " + ReplaceAll(info.Message, args);
	}
#pragma endregion

#pragma region CConnectionErrorListenerLock
	CDbInsert::CConnectionErrorListenerLock::CConnectionErrorListenerLock(IDbConnection *connection, IErrorListener *listener) :
		m_pConnection{ connection },
		m_pOld{ connection->ErrorListener }
	{
		m_pConnection->setErrorListener(listener);
	}

	CDbInsert::CConnectionErrorListenerLock::~CConnectionErrorListenerLock()
	{
		m_pConnection->setErrorListener(m_pOld);
	}
#pragma endregion

#pragma region CStatementErrorListenerLock
	CDbInsert::CStatementErrorListenerLock::CStatementErrorListenerLock(IDbStatement *statement, IErrorListener *listener) :
		m_pStatement{ statement },
		m_pOld{ statement->ErrorListener }
	{
		m_pStatement->setErrorListener(listener);
	}

	CDbInsert::CStatementErrorListenerLock::~CStatementErrorListenerLock()
	{
		m_pStatement->setErrorListener(m_pOld);
	}
#pragma endregion

#pragma region Constructor & destructor
	CDbInsert::CDbInsert(IDbConnection *connection, IDbStatement *statement, IDbQueryBuilder *qb) :
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
	CDbInsert *CDbInsert::Into(const String &table)
	{
		if (!table.empty())
			m_sInto = table;
		return this;
	}
#pragma endregion

#pragma region Execute
	CDbInsert *CDbInsert::Execute(const StringArray &columns, const DbRow &row, const String &on_duplicate_update)
	{
		// Check connection
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();

		// Check query builder
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		// Prepare raw query
		String query;
		if (!m_pQueryBuilder->Insert(this, columns, row, on_duplicate_update, query))
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

		return this;
	}

	CDbInsert *CDbInsert::Execute(const StringArray &columns, const DbRows &rows, const String &on_duplicate_update)
	{
		// Check connection
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();

		// Check query builder
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		// Prepare raw query
		String query;
		if (!m_pQueryBuilder->Insert(this, columns, rows, on_duplicate_update, query))
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

		return this;
	}

	CDbInsert *CDbInsert::Execute(const DbSet &data, const String &on_duplicate_update)
	{
		// Check connection
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();

		// Check query builder
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		// Prepare raw query
		String query;
		if (!m_pQueryBuilder->Insert(this, data, on_duplicate_update, query))
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

		return this;
	}

	DbValue CDbInsert::Id()
	{
		// Check connection
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();

		// Check query builder
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		// Prepare raw query
		String query;
		if (!m_pQueryBuilder->LastInsertId(query))
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
		if (result.Rows.empty())
			DbValue{ };
		if (result.Rows[0].empty())
			DbValue{ };

		return result.Rows[0][0];
	}
#pragma endregion
}