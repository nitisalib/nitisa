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
	void CDbMigration::CErrorListener::NotifyOnError(const AnsiString& function, const int line, const ErrorInfo& info, const StringKeyValueArray& args)
	{
		Error = L"ERROR " + ToString(info.Code) + L" in " + AnsiToString(function) + L":" + ToString(line) + L": " + ReplaceAll(info.Message, args);
	}
#pragma endregion

#pragma region CConnectionErrorListenerLock
	CDbMigration::CConnectionErrorListenerLock::CConnectionErrorListenerLock(IDbConnection* connection, IErrorListener* listener) :
		m_pConnection{ connection },
		m_pOld{ connection->ErrorListener }
	{
		m_pConnection->setErrorListener(listener);
	}

	CDbMigration::CConnectionErrorListenerLock::~CConnectionErrorListenerLock()
	{
		m_pConnection->setErrorListener(m_pOld);
	}
#pragma endregion

#pragma region CStatementErrorListenerLock
	CDbMigration::CStatementErrorListenerLock::CStatementErrorListenerLock(IDbStatement *statement, IErrorListener *listener) :
		m_pStatement{ statement },
		m_pOld{ statement->ErrorListener }
	{
		m_pStatement->setErrorListener(listener);
	}

	CDbMigration::CStatementErrorListenerLock::~CStatementErrorListenerLock()
	{
		m_pStatement->setErrorListener(m_pOld);
	}
#pragma endregion

#pragma region Constructor & destructor
	CDbMigration::CDbMigration(const String& name) :
		CReleasable(),
		m_pConnection{ nullptr },
		m_pStatement{ nullptr },
		m_pQueryBuilder{ nullptr }
	{
		m_sName = name;
	}

	CDbMigration::CDbMigration(const String& name, IDbConnection* connection, IDbStatement *statement, IDbQueryBuilder* query_builder) :
		CReleasable(),
		m_pConnection{ connection },
		m_pStatement{ statement },
		m_pQueryBuilder{ query_builder }
	{
		m_sName = name;
	}
#pragma endregion

#pragma region IDbMigration setters
	IDbMigration* CDbMigration::setConnection(IDbConnection* value)
	{
		m_pConnection = value;
		return this;
	}

	IDbMigration *CDbMigration::setStatement(IDbStatement *value)
	{
		m_pStatement = value;
		return this;
	}

	IDbMigration* CDbMigration::setQueryBuilder(IDbQueryBuilder* value)
	{
		m_pQueryBuilder = value;
		return this;
	}
#pragma endregion

#pragma region IDbMigration database methods
	void CDbMigration::CreateDatabase(const String& name, const String& charset, const String& collation, const bool if_not_exists)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->CreateDatabase(name, charset, collation, if_not_exists, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}

	void CDbMigration::AlterDatabase(const String& name, const String& charset, const String& collation)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->AlterDatabase(name, charset, collation, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}

	void CDbMigration::DropDatabase(const String& name, const bool if_exists)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->DropDatabase(name, if_exists, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}
#pragma endregion

#pragma region IDbMigration column creation methods
	IDbMigration::MigrationColumn CDbMigration::Column(const String& name)
	{
		return new CDbMigrationColumn(name);
	}
#pragma endregion

#pragma region IDbMigration key creation methods
	IDbMigration::MigrationKey CDbMigration::Index(const String& column, const String& name, const bool& fulltext)
	{
		return new CDbMigrationKey(name, StringArray{ column }, fulltext);
	}

	IDbMigration::MigrationKey CDbMigration::Index(const StringArray& columns, const String& name, const bool& fulltext)
	{
		return new CDbMigrationKey(name, columns, fulltext);
	}

	IDbMigration::MigrationKey CDbMigration::Unique(const String& column, const String& name)
	{
		return new CDbMigrationKey(name, L"", StringArray{column});
	}

	IDbMigration::MigrationKey CDbMigration::Unique(const StringArray& columns, const String& name)
	{
		return new CDbMigrationKey(name, L"", columns);
	}

	IDbMigration::MigrationKey CDbMigration::PrimaryKey(const String& column, const String& name)
	{
		return new CDbMigrationKey(name, StringArray{ column });
	}

	IDbMigration::MigrationKey CDbMigration::PrimaryKey(const StringArray& columns, const String& name)
	{
		return new CDbMigrationKey(name, columns);
	}

	IDbMigration::MigrationKey CDbMigration::ForeignKey(
		const String& column,
		const String& ref_table,
		const String& ref_column,
		const String& name,
		const IDbMigrationKey::RefOption& on_delete,
		const IDbMigrationKey::RefOption& on_update)
	{
		return new CDbMigrationKey(name, L"", StringArray{ column }, ref_table, StringArray{ ref_column }, on_delete, on_update);
	}

	IDbMigration::MigrationKey CDbMigration::ForeignKey(
		const StringArray& columns,
		const String& ref_table,
		const StringArray& ref_columns,
		const String& name,
		const IDbMigrationKey::RefOption& on_delete,
		const IDbMigrationKey::RefOption& on_update)
	{
		return new CDbMigrationKey(name, L"", columns, ref_table, ref_columns, on_delete, on_update);
	}
#pragma endregion

#pragma region IDbMigration table methods
	void CDbMigration::CreateTable(
		const String& name,
		const MigrationColumns& columns,
		const MigrationKeys& keys,
		const bool& if_not_exists,
		const String& comment,
		const int64& auto_increment,
		const String& charset,
		const String& collation,
		const String& engine)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->CreateTable(name, columns, keys, if_not_exists, comment, auto_increment, charset, collation, engine, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}

	void CDbMigration::AlterTable(const String& name, const String& charset, const String& collation, const bool& convert)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->AlterTable(name, charset, collation, convert, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}

	void CDbMigration::RenameTable(const String& old_name, const String& new_name)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->RenameTable(old_name, new_name, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}

	void CDbMigration::TruncateTable(const String& name)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->TruncateTable(name, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}

	void CDbMigration::DropTable(const String& name, const bool if_exists)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->DropTable(name, if_exists, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}

	void CDbMigration::DisableKeys(const String& table)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->DisableKeys(table, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}

	void CDbMigration::EnableKeys(const String& table)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->EnableKeys(table, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}
#pragma endregion

#pragma region IDbMigration column methods
	void CDbMigration::AddColumn(const String& table, const MigrationColumn& column, const String& after)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->AddColumn(table, column, after, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}

	void CDbMigration::AlterColumn(const String& table, const MigrationColumn& column, const String& after)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->AlterColumn(table, column, after, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}

	void CDbMigration::AlterColumn(const String& table, const String& old_name, const MigrationColumn& column, const String& after)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->AlterColumn(table, old_name, column, after, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}

	void CDbMigration::RenameColumn(const String& table, const String& old_name, const String& new_name)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->RenameColumn(table, old_name, new_name, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}

	void CDbMigration::DropColumn(const String& table, const String& name)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->DropColumn(table, name, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}
#pragma endregion

#pragma region IDbMigration index methods
	void CDbMigration::AddKey(const String& table, const MigrationKey& key)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->AddKey(table, key, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}

	void CDbMigration::RenameKey(const String& table, const String& old_name, const String& new_name)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->RenameKey(table, old_name, new_name, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}

	void CDbMigration::DropKey(const String& table, const String& name)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->DropKey(table, name, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}

	void CDbMigration::DropPrimaryKey(const String& table, const String& name)
	{
		if (!m_pStatement && !m_pConnection)
			throw DbExceptionNoConnection();
		if (!m_pQueryBuilder)
			throw DbExceptionNoQueryBuilder();

		String sql;
		if (!m_pQueryBuilder->DropPrimaryKey(table, name, sql))
			throw DbExceptionBuildQuery(m_pQueryBuilder->LastError);

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

		DbResult result{ statement->Execute(sql) };
		if (!result.Successful)
			throw DbExceptionExecuteStatement(m_cErrorListener.Error);
	}
#pragma endregion

#pragma region IDbMigration execute methods
	void CDbMigration::Revert()
	{
		throw DbExceptionRevertNotImplemented();
	}
#pragma endregion
}