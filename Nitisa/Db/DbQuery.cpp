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
	void CDbQuery::CErrorListener::NotifyOnError(const AnsiString& function, const int line, const ErrorInfo& info, const StringKeyValueArray& args)
	{
		Error = L"ERROR " + ToString(info.Code) + L" in " + AnsiToString(function) + L":" + ToString(line) + L": " + ReplaceAll(info.Message, args);
	}
#pragma endregion

#pragma region CConnectionErrorListenerLock
	CDbQuery::CConnectionErrorListenerLock::CConnectionErrorListenerLock(IDbConnection* connection, IErrorListener* listener) :
		m_pConnection{ connection },
		m_pOld{ connection->ErrorListener }
	{
		m_pConnection->setErrorListener(listener);
	}

	CDbQuery::CConnectionErrorListenerLock::~CConnectionErrorListenerLock()
	{
		m_pConnection->setErrorListener(m_pOld);
	}
#pragma endregion

#pragma region CStatementErrorListenerLock
	CDbQuery::CStatementErrorListenerLock::CStatementErrorListenerLock(IDbStatement *statement, IErrorListener *listener) :
		m_pStatement{ statement },
		m_pOld{ statement->ErrorListener }
	{
		m_pStatement->setErrorListener(listener);
	}

	CDbQuery::CStatementErrorListenerLock::~CStatementErrorListenerLock()
	{
		m_pStatement->setErrorListener(m_pOld);
	}
#pragma endregion

#pragma region Constructor & destructor
	CDbQuery::CDbQuery(const String& table, IDbConnection* connection, IDbStatement *statement, IDbQueryBuilder* qb) :
		CReleasable(),
		m_pConnection{ connection },
		m_pStatement{ statement },
		m_pQueryBuilder{ qb }
	{
		m_sTable = table;
		m_bDistinct = false;
		m_iLimit = -1;
		m_iOffset = -1;
	}
#pragma endregion

#pragma region Query building
	CDbQuery* CDbQuery::Select(const String& column)
	{
		if (!column.empty())
			m_aSelect.push_back(StringKeyValue{ column, L"" });
		return this;
	}

	CDbQuery* CDbQuery::Select(const String& column, const String& alias)
	{
		if (!column.empty())
			m_aSelect.push_back(StringKeyValue{ column, alias });
		return this;
	}

	CDbQuery* CDbQuery::Select(const StringKeyValue& column)
	{
		if (!column.first.empty())
			m_aSelect.push_back(column);
		return this;
	}

	CDbQuery* CDbQuery::Select(const StringArray& columns)
	{
		for (auto const& column : columns)
			if (!column.empty())
				m_aSelect.push_back(StringKeyValue{ column, L"" });
		return this;
	}

	CDbQuery* CDbQuery::Select(const StringKeyValueArray& columns)
	{
		for (auto const& column : columns)
			if (!column.first.empty())
				m_aSelect.push_back(column);
		return this;
	}

	CDbQuery* CDbQuery::Distinct(const bool& value)
	{
		m_bDistinct = value;
		return this;
	}

	CDbQuery* CDbQuery::From(const String& table)
	{
		if (!table.empty())
			m_aFrom.push_back(StringKeyValue{ table, L"" });
		return this;
	}

	CDbQuery* CDbQuery::From(const String& table, const String& alias)
	{
		if (!table.empty())
			m_aFrom.push_back(StringKeyValue{ table, alias });
		return this;
	}

	CDbQuery* CDbQuery::From(const StringArray& tables)
	{
		for (auto const& table : tables)
			if (!table.empty())
				m_aFrom.push_back(StringKeyValue{ table, L"" });
		return this;
	}

	CDbQuery* CDbQuery::From(const StringKeyValueArray& tables)
	{
		for (auto const& table : tables)
			if (!table.first.empty())
				m_aFrom.push_back(table);
		return this;
	}

	CDbQuery* CDbQuery::InnerJoin(const String& table, DbCondition on)
	{
		if (!table.empty())
			m_aInnerJoins.push_back(DbJoin{ table, L"", on });
		return this;
	}

	CDbQuery* CDbQuery::InnerJoin(const String& table, const String& alias, DbCondition on)
	{
		if (!table.empty())
			m_aInnerJoins.push_back(DbJoin{ table, alias, on });
		return this;
	}

	CDbQuery* CDbQuery::InnerJoin(const DbJoin& table)
	{
		m_aInnerJoins.push_back(table);
		return this;
	}

	CDbQuery* CDbQuery::LeftJoin(const String& table, DbCondition on)
	{
		if (!table.empty())
			m_aLeftJoins.push_back(DbJoin{ table, L"", on });
		return this;
	}

	CDbQuery* CDbQuery::LeftJoin(const String& table, const String& alias, DbCondition on)
	{
		if (!table.empty())
			m_aLeftJoins.push_back(DbJoin{ table, alias, on });
		return this;
	}

	CDbQuery* CDbQuery::LeftJoin(const DbJoin& table)
	{
		m_aLeftJoins.push_back(table);
		return this;
	}

	CDbQuery* CDbQuery::RightJoin(const String& table, DbCondition on)
	{
		if (!table.empty())
			m_aRightJoins.push_back(DbJoin{ table, L"", on });
		return this;
	}

	CDbQuery* CDbQuery::RightJoin(const String& table, const String& alias, DbCondition on)
	{
		if (!table.empty())
			m_aRightJoins.push_back(DbJoin{ table, alias, on });
		return this;
	}

	CDbQuery* CDbQuery::RightJoin(const DbJoin& table)
	{
		m_aRightJoins.push_back(table);
		return this;
	}

	CDbQuery* CDbQuery::Where(DbCondition condition)
	{
		m_pWhere = condition;
		return this;
	}

	CDbQuery* CDbQuery::Where(const DbConditions &conditions)
	{
		m_pWhere = nullptr;
		for (auto condition : conditions)
			AndWhere(condition);
		return this;
	}

	CDbQuery* CDbQuery::AndWhere(DbCondition condition)
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

	CDbQuery* CDbQuery::OrWhere(DbCondition condition)
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

	CDbQuery* CDbQuery::GroupBy(const String& column)
	{
		if (!column.empty())
			m_aGroupBy.push_back(column);
		return this;
	}

	CDbQuery* CDbQuery::GroupBy(const StringArray& columns)
	{
		for (auto const& column : columns)
			if (!column.empty())
				m_aGroupBy.push_back(column);
		return this;
	}

	CDbQuery* CDbQuery::Having(DbCondition condition)
	{
		m_pHaving = condition;
		return this;
	}

	CDbQuery* CDbQuery::Having(const DbConditions &conditions)
	{
		m_pHaving = nullptr;
		for (auto condition : conditions)
			AndHaving(condition);
		return this;
	}

	CDbQuery* CDbQuery::AndHaving(DbCondition condition)
	{
		if (m_pHaving)
		{
			if (condition)
				m_pHaving = db::And(m_pHaving, condition);
		}
		else
			m_pHaving = condition;
		return this;
	}

	CDbQuery* CDbQuery::OrHaving(DbCondition condition)
	{
		if (m_pHaving)
		{
			if (condition)
				m_pHaving = db::Or(m_pHaving, condition);
		}
		else
			m_pHaving = condition;
		return this;
	}

	CDbQuery* CDbQuery::OrderBy(const String& column, const DbOrder& order)
	{
		if (!column.empty())
			m_aOrderBy.push_back(DbOrderBy{ column, order });
		return this;
	}

	CDbQuery* CDbQuery::OrderBy(const DbOrderByArray& columns)
	{
		for (auto const& column : columns)
			if (!column.first.empty())
				m_aOrderBy.push_back(column);
		return this;
	}

	CDbQuery* CDbQuery::Limit(const int64& limit)
	{
		m_iLimit = limit;
		return this;
	}

	CDbQuery* CDbQuery::Offset(const int64& offset)
	{
		m_iOffset = offset;
		return this;
	}

	CDbQuery* CDbQuery::Union(ReleasablePtr<IDbQuery> query, const bool all)
	{
		if (query)
			m_aUnions.push_back(DbUnion{ query, all });
		return this;
	}
#pragma endregion

#pragma region Query result
	DbValue CDbQuery::Column()
	{
		// Check connection
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();

		// Check query builder
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		// Prepare raw query
		if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
			From(m_sTable);
		String query;
		int64 old_limit{ m_iLimit };
		m_iLimit = 1;
		if (!m_pQueryBuilder->Select(this, query))
		{
			m_iLimit = old_limit;
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);
		}
		m_iLimit = old_limit;

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
		if (result.Rows.empty() || result.Rows[0].empty())
			return DbValue{ };

		return result.Rows[0][0];
	}

	int64 CDbQuery::Count(const String& column)
	{
		// Check connection
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();

		// Check query builder
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		// Prepare raw query
		if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
			From(m_sTable);
		String query;
		if (!m_pQueryBuilder->Count(this, column, query))
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
		if (result.Rows.empty() || result.Rows[0].empty())
			throw DbExceptionNoResult();

		return (int64)result.Rows[0][0];
	}

	DbRows CDbQuery::Rows()
	{
		// Check connection
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();

		// Check query builder
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		// Prepare raw query
		if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
			From(m_sTable);
		String query;
		if (!m_pQueryBuilder->Select(this, query))
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

		// Prepare and execute statement
		DbResult result{ statement->Execute(query) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);

		return result.Rows;
	}

	DbRow CDbQuery::Row()
	{
		// Check connection
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();

		// Check query builder
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		// Prepare raw query
		if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
			From(m_sTable);
		int64 old_limit{ m_iLimit };
		m_iLimit = 1;
		String query;
		if (!m_pQueryBuilder->Select(this, query))
		{
			m_iLimit = old_limit;
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);
		}
		m_iLimit = old_limit;

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

		// Prepare and execute statement
		DbResult result{ statement->Execute(query) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
		if (result.Rows.empty())
			return DbRow{ };

		return result.Rows[0];
	}

	bool CDbQuery::Exists()
	{
		// Check connection
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();

		// Check query builder
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		// Prepare raw query
		if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
			From(m_sTable);
		String query;
		if (!m_pQueryBuilder->Exists(this, query))
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

		// Prepare and execute statement
		DbResult result{ statement->Execute(query) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
		if (result.Rows.empty() || result.Rows[0].empty())
			throw DbExceptionNoResult();

		return (bool)result.Rows[0][0];
	}
#pragma endregion
}