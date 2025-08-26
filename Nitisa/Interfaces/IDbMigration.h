// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/ReleasablePtr.h"
#include "../Core/Strings.h"
#include "IDbMigrationKey.h"
#include "IReleasable.h"
#include <limits>
#include <vector>

#ifdef min
#undef min
#endif

namespace nitisa
{
	class IDbConnection;
	class IDbMigrationColumn;
	class IDbQueryBuilder;
	class IDbStatement;

	class IDbMigration :public virtual IReleasable
	{
	public:
		using MigrationColumn = ReleasablePtr<IDbMigrationColumn>;
		using MigrationColumns = std::vector<MigrationColumn>;
		using MigrationKey = ReleasablePtr<IDbMigrationKey>;
		using MigrationKeys = std::vector<MigrationKey>;
	protected:
		IDbMigration() = default;
		~IDbMigration() = default;
		IDbMigration(const IDbMigration &other) = delete;
		IDbMigration(IDbMigration &&other) = delete;
		IDbMigration &operator=(const IDbMigration &other) = delete;
		IDbMigration &operator=(IDbMigration &&other) = delete;
	protected:
		String m_sName;

		// Database methods
		virtual void CreateDatabase(const String &name, const String &charset = L"", const String &collation = L"", const bool if_not_exists = false) = 0;
		virtual void AlterDatabase(const String &name, const String &charset, const String &collation) = 0;
		virtual void DropDatabase(const String &name, const bool if_exists = false) = 0;

		// Column creation methods
		virtual MigrationColumn Column(const String &name) = 0;

		// Key creation methods
		virtual MigrationKey Index(const String &column, const String &name = L"", const bool &fulltext = false) = 0;
		virtual MigrationKey Index(const StringArray &columns, const String &name = L"", const bool &fulltext = false) = 0;
		virtual MigrationKey Unique(const String &column, const String &name = L"") = 0;
		virtual MigrationKey Unique(const StringArray &columns, const String &name = L"") = 0;
		virtual MigrationKey PrimaryKey(const String &column, const String &name = L"") = 0;
		virtual MigrationKey PrimaryKey(const StringArray &columns, const String &name = L"") = 0;
		virtual MigrationKey ForeignKey(
			const String &column,
			const String &ref_table,
			const String &ref_column,
			const String &name = L"",
			const IDbMigrationKey::RefOption &on_delete = IDbMigrationKey::RefOption::None,
			const IDbMigrationKey::RefOption &on_update = IDbMigrationKey::RefOption::None
		) = 0;
		virtual MigrationKey ForeignKey(
			const StringArray &columns,
			const String &ref_table,
			const StringArray &ref_columns,
			const String &name = L"",
			const IDbMigrationKey::RefOption &on_delete = IDbMigrationKey::RefOption::None,
			const IDbMigrationKey::RefOption &on_update = IDbMigrationKey::RefOption::None
		) = 0;

		// Table methods
		virtual void CreateTable(
			const String &name,
			const MigrationColumns &columns,
			const MigrationKeys &keys,
			const bool &if_not_exists = false,
			const String &comment = L"",
			const int64 &auto_increment = std::numeric_limits<int64>::min(),
			const String &charset = L"",
			const String &collation = L"",
			const String &engine = L"") = 0;
		virtual void AlterTable(const String &name, const String &charset, const String &collation = L"", const bool &convert = false) = 0;
		virtual void RenameTable(const String &old_name, const String &new_name) = 0;
		virtual void TruncateTable(const String &name) = 0;
		virtual void DropTable(const String &name, const bool if_exists = false) = 0;
		virtual void DisableKeys(const String &table) = 0;
		virtual void EnableKeys(const String &table) = 0;

		// Column methods
		virtual void AddColumn(const String &table, const MigrationColumn &column, const String &after = L"") = 0;
		virtual void AlterColumn(const String &table, const MigrationColumn &column, const String &after = L"") = 0;
		virtual void AlterColumn(const String &table, const String &old_name, const MigrationColumn &column, const String &after = L"") = 0;
		virtual void RenameColumn(const String &table, const String &old_name, const String &new_name) = 0;
		virtual void DropColumn(const String &table, const String &name) = 0;

		// Index methods
		virtual void AddKey(const String &table, const MigrationKey &key) = 0;
		virtual void RenameKey(const String &table, const String &old_name, const String &new_name) = 0;
		virtual void DropKey(const String &table, const String &name) = 0;
		virtual void DropPrimaryKey(const String &table, const String &name = L"") = 0;
	public:
		String const &sName{ m_sName };

		virtual IDbMigration *setConnection(IDbConnection *value) = 0;
		virtual IDbMigration *setStatement(IDbStatement *value) = 0;
		virtual IDbMigration *setQueryBuilder(IDbQueryBuilder *value) = 0;

		// Execute methods
		virtual void Run() = 0;
		virtual void Revert() = 0;
	};
}