// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/ErrorInfo.h"
#include "../Core/Releasable.h"
#include "../Core/ReleasablePtr.h"
#include "../Core/Strings.h"
#include "../Interfaces/IDbMigration.h"
#include "../Interfaces/IDbMigrationKey.h"
#include "../Interfaces/IErrorListener.h"
#include <limits>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IDbConnection;
	class IDbMigrationColumn;
	class IDbQueryBuilder;
	class IDbStatement;
	class IErrorListener;

	class CDbMigration :public virtual IDbMigration, public CReleasable
	{
	private:
		class CErrorListener :public virtual IErrorListener
		{
		public:
			String Error;

			void NotifyOnError(const AnsiString& function, const int line, const ErrorInfo& info, const StringKeyValueArray& args = EmptyStringKeyValueArray) override;
		};

		class CConnectionErrorListenerLock
		{
		private:
			IDbConnection* m_pConnection;
			IErrorListener* m_pOld;
		public:
			CConnectionErrorListenerLock(IDbConnection* connection, IErrorListener* listener);
			~CConnectionErrorListenerLock();
		};

		class CStatementErrorListenerLock
		{
		private:
			IDbStatement *m_pStatement;
			IErrorListener *m_pOld;
		public:
			CStatementErrorListenerLock(IDbStatement *statement, IErrorListener *listener);
			~CStatementErrorListenerLock();
		};
	private:
		CErrorListener m_cErrorListener;
	protected:
		IDbConnection* m_pConnection; // Connection instance. Ignored if statement is provided
		IDbStatement* m_pStatement; // Statement instance
		IDbQueryBuilder* m_pQueryBuilder; // Query Builder instance

		// IDbMigration database methods
		void CreateDatabase(const String& name, const String& charset = L"", const String& collation = L"", const bool if_not_exists = false) override; // Throw exceptions in case of error
		void AlterDatabase(const String& name, const String& charset, const String& collation) override; // Throw exceptions in case of error
		void DropDatabase(const String& name, const bool if_exists = false) override; // Throw exceptions in case of error

		// IDbMigration column creation methods
		MigrationColumn Column(const String& name) override; // Create column description object

		// IDbMigration key creation methods
		MigrationKey Index(const String& column, const String& name = L"", const bool& fulltext = false) override; // Create index description object
		MigrationKey Index(const StringArray& columns, const String& name = L"", const bool& fulltext = false) override; // Create index description object
		MigrationKey Unique(const String& column, const String& name = L"") override; // Create unique index description object
		MigrationKey Unique(const StringArray& columns, const String& name = L"") override; // Create unique index description object
		MigrationKey PrimaryKey(const String& column, const String& name = L"") override; // Create primary key description object
		MigrationKey PrimaryKey(const StringArray& columns, const String& name = L"") override; // Create primary key description object
		MigrationKey ForeignKey( // Create foreign key description object
			const String& column,
			const String& ref_table,
			const String& ref_column,
			const String& name = L"",
			const IDbMigrationKey::RefOption& on_delete = IDbMigrationKey::RefOption::None,
			const IDbMigrationKey::RefOption& on_update = IDbMigrationKey::RefOption::None) override;
		MigrationKey ForeignKey( // Create foreign key description object
			const StringArray& columns,
			const String& ref_table,
			const StringArray& ref_columns,
			const String& name = L"",
			const IDbMigrationKey::RefOption& on_delete = IDbMigrationKey::RefOption::None,
			const IDbMigrationKey::RefOption& on_update = IDbMigrationKey::RefOption::None) override;

		// IDbMigration table methods. All methods throw exceptions in case of error
		void CreateTable(
			const String& name,
			const MigrationColumns& columns,
			const MigrationKeys& keys,
			const bool& if_not_exists = false,
			const String& comment = L"",
			const int64& auto_increment = std::numeric_limits<int64>::min(),
			const String& charset = L"",
			const String& collation = L"",
			const String& engine = L"") override;
		void AlterTable(const String& name, const String& charset, const String& collation = L"", const bool& convert = false) override;
		void RenameTable(const String& old_name, const String& new_name) override;
		void TruncateTable(const String& name) override;
		void DropTable(const String& name, const bool if_exists = false) override;
		void DisableKeys(const String& table) override;
		void EnableKeys(const String& table) override;

		// IDbMigration column methods. All methods throw exceptions in case of error
		void AddColumn(const String& table, const MigrationColumn& column, const String& after = L"") override;
		void AlterColumn(const String& table, const MigrationColumn& column, const String& after = L"") override;
		void AlterColumn(const String& table, const String& old_name, const MigrationColumn& column, const String& after = L"") override;
		void RenameColumn(const String& table, const String& old_name, const String& new_name) override;
		void DropColumn(const String& table, const String& name) override;

		// IDbMigration index methods. All methods throw exceptions in case of error
		void AddKey(const String& table, const MigrationKey& key) override;
		void RenameKey(const String& table, const String& old_name, const String& new_name) override;
		void DropKey(const String& table, const String& name) override;
		void DropPrimaryKey(const String& table, const String& name = L"") override;
	public:
		// IDbMigration setters
		IDbMigration* setConnection(IDbConnection* value) override;
		IDbMigration* setStatement(IDbStatement* value) override;
		IDbMigration* setQueryBuilder(IDbQueryBuilder* value) override;

		// IDbMigration execute methods
		void Revert() override;

		CDbMigration(const String& name);
		CDbMigration(const String& name, IDbConnection* connection, IDbStatement *statement, IDbQueryBuilder* query_builder);
	};
}