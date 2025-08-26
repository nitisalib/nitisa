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
	DbSchema::CErrorListener DbSchema::m_cErrorListener;
	std::map<String, DbSchema::PrimaryKey> DbSchema::m_aPrimaryKeys;
	std::map<String, String> DbSchema::m_aAutoIncrementColumns;
	std::map<String, std::map<String, DbSchema::Column>> DbSchema::m_aColumns;

#pragma region CErrorListener
	void DbSchema::CErrorListener::NotifyOnError(const AnsiString &function, const int line, const ErrorInfo &info, const StringKeyValueArray &args)
	{
		Error = L"ERROR " + ToString(info.Code) + L" in " + AnsiToString(function) + L":" + ToString(line) + L": " + ReplaceAll(info.Message, args);
	}
#pragma endregion

#pragma region CConnectionErrorListenerLock
	DbSchema::CConnectionErrorListenerLock::CConnectionErrorListenerLock(IDbConnection *connection, IErrorListener *listener) :
		m_pConnection{ connection },
		m_pOld{ connection->ErrorListener }
	{
		m_pConnection->setErrorListener(listener);
	}

	DbSchema::CConnectionErrorListenerLock::~CConnectionErrorListenerLock()
	{
		m_pConnection->setErrorListener(m_pOld);
	}
#pragma endregion

#pragma region CStatementErrorListenerLock
	DbSchema::CStatementErrorListenerLock::CStatementErrorListenerLock(IDbStatement *statement, IErrorListener *listener) :
		m_pStatement{ statement },
		m_pOld{ statement->ErrorListener }
	{
		m_pStatement->setErrorListener(listener);
	}

	DbSchema::CStatementErrorListenerLock::~CStatementErrorListenerLock()
	{
		m_pStatement->setErrorListener(m_pOld);
	}
#pragma endregion

	bool DbSchema::getPrimaryKey(const String& table, IDbStatement* statement, IDbQueryBuilder* qb, PrimaryKey& target, const bool& refresh)
	{
		if (!refresh)
		{
			auto pos{ m_aPrimaryKeys.find(table) };
			if (pos != m_aPrimaryKeys.end())
			{
				target = pos->second;
				return true;
			}
		}
		if (!statement)
			throw DbExceptionNoStatement();
		if (!qb)
			throw DbExceptionNoQueryBuilder();
		if (table.empty())
			throw DbExceptionNoTableName();
		CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };
		DbResult result{ statement->QueryPrimaryKeys(L"", table, L"") };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
		PrimaryKey primary_key;
		if (!result.Rows.empty())
		{
			if (result.Rows[0][5].Type != DbValueType::Null)
				primary_key.Name = (String)result.Rows[0][5];
			for (auto const& row : result.Rows)
				primary_key.Columns.push_back((String)row[3]);
		}
		m_aPrimaryKeys[table] = primary_key;
		target = primary_key;
		return true;
	}

	bool DbSchema::getPrimaryKey(const String& table, IDbConnection* connection, IDbQueryBuilder* qb, PrimaryKey& target, const bool& refresh)
	{
		if (!refresh)
		{
			auto pos{ m_aPrimaryKeys.find(table) };
			if (pos != m_aPrimaryKeys.end())
			{
				target = pos->second;
				return true;
			}
		}
		if (!connection)
			throw DbExceptionNoConnection();
		if (!qb)
			throw DbExceptionNoQueryBuilder();
		if (table.empty())
			throw DbExceptionNoTableName();
		CConnectionErrorListenerLock e_lock{ connection, &m_cErrorListener };
		ReleasablePtr<IDbStatement> statement{ connection->CreateStatement() };
		if (!statement)
			throw DbExceptionCreateStatement(m_cErrorListener.Error);
		return getPrimaryKey(table, statement, qb, target, true);
	}

	bool DbSchema::getAutoIncrementColumn(const String& table, IDbStatement* statement, IDbQueryBuilder* qb, String& target, const bool& refresh)
	{
		if (!refresh)
		{
			auto pos{ m_aAutoIncrementColumns.find(table) };
			if (pos != m_aAutoIncrementColumns.end())
			{
				target = pos->second;
				return true;
			}
		}
		if (!statement)
			throw DbExceptionNoStatement();
		if (!qb)
			throw DbExceptionNoQueryBuilder();
		if (table.empty())
			throw DbExceptionNoTableName();
		String sql;
		if (!qb->AutoIncrementColumn(table, sql))
			throw DbExceptionBuildQuery(qb->LastError);
		CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };
		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
		String column;
		if (!result.Rows.empty() && !result.Rows[0].empty())
			column = (String)result.Rows[0][0];
		m_aAutoIncrementColumns[table] = column;
		target = column;
		return true;
	}

	bool DbSchema::getAutoIncrementColumn(const String& table, IDbConnection* connection, IDbQueryBuilder* qb, String& target, const bool& refresh)
	{
		if (!refresh)
		{
			auto pos{ m_aAutoIncrementColumns.find(table) };
			if (pos != m_aAutoIncrementColumns.end())
			{
				target = pos->second;
				return true;
			}
		}
		if (!connection)
			throw DbExceptionNoConnection();
		if (!qb)
			throw DbExceptionNoQueryBuilder();
		if (table.empty())
			throw DbExceptionNoTableName();
		CConnectionErrorListenerLock e_lock{ connection, &m_cErrorListener };
		ReleasablePtr<IDbStatement> statement{ connection->CreateStatement() };
		if (!statement)
			throw DbExceptionCreateStatement(m_cErrorListener.Error);
		return getAutoIncrementColumn(table, statement, qb, target, true);
	}

	bool DbSchema::getColumn(const String &table, const String &column, IDbStatement *statement, Column &target, const bool &refresh)
	{
		if (!refresh)
		{
			auto pos_table{ m_aColumns.find(table) };
			if (pos_table != m_aColumns.end())
			{
				auto pos_column{ pos_table->second.find(column) };
				if (pos_column != pos_table->second.end())
				{
					target = pos_column->second;
					return true;
				}
			}
		}
		if (!statement)
			throw DbExceptionNoStatement();
		if (table.empty())
			throw DbExceptionNoTableName();
		if (column.empty())
			throw DbExceptionNoColumnName();
		CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };
		DbResult result{ statement->QueryColumns(L"", table, L"", column) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
		if (result.Rows.empty() || result.Rows[0].size() < 13)
			return false;
		Column info{ result.Rows[0][12] };
		if ((String)info.DefaultValue == L"NULL")
			info.DefaultValue = DbValue{ };
		else if (String(info.DefaultValue).length() >= 2 && in(String(info.DefaultValue)[0], { L'"', L'\'' }))
			info.DefaultValue = String(info.DefaultValue).substr(1, String(info.DefaultValue).length() - 2);
		else
		{
			int64 i;
			if (TryStringToInt64((String)info.DefaultValue, i))
				info.DefaultValue = i;
			else
			{
				double f;
				if (TryStringToDouble((String)info.DefaultValue, f))
					info.DefaultValue = f;
			}
		}
		m_aColumns[table][column] = info;
		target = info;
		return true;
	}

	bool DbSchema::getColumn(const String &table, const String &column, IDbConnection *connection, Column &target, const bool &refresh)
	{
		if (!refresh)
		{
			auto pos_table{ m_aColumns.find(table) };
			if (pos_table != m_aColumns.end())
			{
				auto pos_column{ pos_table->second.find(column) };
				if (pos_column != pos_table->second.end())
				{
					target = pos_column->second;
					return true;
				}
			}
		}
		if (!connection)
			throw DbExceptionNoConnection();
		if (table.empty())
			throw DbExceptionNoTableName();
		if (column.empty())
			throw DbExceptionNoColumnName();
		CConnectionErrorListenerLock e_lock{ connection, &m_cErrorListener };
		ReleasablePtr<IDbStatement> statement{ connection->CreateStatement() };
		if (!statement)
			throw DbExceptionCreateStatement(m_cErrorListener.Error);
		return getColumn(table, column, statement, target, true);
	}
}