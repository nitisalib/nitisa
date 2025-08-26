// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Db/DbOrderByArray.h"
#include "../Db/DbRow.h"
#include "../Db/DbRows.h"
#include "../Db/DbSet.h"
#include "../Db/DbValue.h"
#include "../Core/Aliases.h"
#include "../Core/ReleasablePtr.h"
#include "../Core/Strings.h"
#include "IDbMigration.h"
#include "IReleasable.h"
#include <map>
#include <vector>

namespace nitisa
{
	class IDbMigrationColumn;
	class IDbMigrationKey;
	class IDbQuery;

	class CDbCondition;

	class IDbQueryBuilder : public virtual IReleasable
	{
	protected:
		IDbQueryBuilder() = default;
		~IDbQueryBuilder() = default;
		IDbQueryBuilder(const IDbQueryBuilder &other) = delete;
		IDbQueryBuilder(IDbQueryBuilder &&other) = delete;
		IDbQueryBuilder &operator=(const IDbQueryBuilder &other) = delete;
		IDbQueryBuilder &operator=(IDbQueryBuilder &&other) = delete;
	protected:
		String m_sLastError; // Last error
	public:
		// Read-only references to the protected members
		String const &LastError{ m_sLastError }; // Last error

		// Database manipulation queries
		virtual bool CreateDatabase(const String &name, const String &charset, const String &collation, const bool if_not_exists, String &target) = 0;
		virtual bool AlterDatabase(const String &name, const String &charset, const String &collation, String &target) = 0;
		virtual bool DropDatabase(const String &name, const bool if_exists, String &target) = 0;

		// Table manipulation queries
		virtual bool CreateTable(
			const String &name,
			const IDbMigration::MigrationColumns &columns,
			const IDbMigration::MigrationKeys &keys,
			const bool &if_not_exists,
			const String &comment,
			const int64 &auto_increment, // std::numeric_limits<int64>::min() means no auto_increment option is needed
			const String &charset,
			const String &collation,
			const String &engine,
			String &target) = 0;
		virtual bool AlterTable(const String &name, const String &charset, const String &collation, const bool &convert, String &target) = 0;
		virtual bool RenameTable(const String &old_name, const String &new_name, String &target) = 0;
		virtual bool TruncateTable(const String &name, String &target) = 0;
		virtual bool DropTable(const String &name, const bool if_exists, String &target) = 0;
		virtual bool DisableKeys(const String &table, String &target) = 0;
		virtual bool EnableKeys(const String &table, String &target) = 0;

		// Column manipulation queries
		virtual bool AddColumn(const String &table, const IDbMigrationColumn *column, const String &after, String &target) = 0; // "FIRST" has special meaning for after. If the column need to be added after the column called FIRST, just use "`FIRST`" in after
		virtual bool AlterColumn(const String &table, const IDbMigrationColumn *column, const String &after, String &target) = 0;
		virtual bool AlterColumn(const String &table, const String &old_name, const IDbMigrationColumn *column, const String &after, String &target) = 0;
		virtual bool RenameColumn(const String &table, const String &old_name, const String &new_name, String &target) = 0;
		virtual bool DropColumn(const String &table, const String &name, String &target) = 0;

		// Key manipulation queries
		virtual bool AddKey(const String &table, const IDbMigrationKey *key, String &target) = 0;
		virtual bool RenameKey(const String &table, const String &old_name, const String &new_name, String &target) = 0;
		virtual bool DropKey(const String &table, const String &name, String &target) = 0;
		virtual bool DropPrimaryKey(const String &table, const String &name, String &target) = 0;

		// Select queries
		virtual bool Select(const IDbQuery *query, String &target) = 0;
		virtual bool Exists(const IDbQuery *query, String &target) = 0;
		virtual bool Scalar(const IDbQuery *query, const String &column, String &target) = 0;
		virtual bool Count(const IDbQuery *query, const String &column, String &target) = 0;
		virtual bool Sum(const IDbQuery *query, const String &column, String &target) = 0;
		virtual bool Average(const IDbQuery *query, const String &column, String &target) = 0;
		virtual bool Min(const IDbQuery *query, const String &column, String &target) = 0;
		virtual bool Max(const IDbQuery *query, const String &column, String &target) = 0;

		// Delete queries
		virtual bool Delete(const IDbQuery *query, String &target) = 0;

		// Insert queries
		virtual bool Insert(const IDbQuery *query, const StringArray &columns, const DbRow &row, const String &on_duplicate_update, String &target) = 0;
		virtual bool Insert(const IDbQuery *query, const StringArray &columns, const DbRows &rows, const String &on_duplicate_update, String &target) = 0;
		virtual bool Insert(const IDbQuery *query, const DbSet &data, const String &on_duplicate_update, String &target) = 0; // [ name => value, ...] format

		// Update queries
		virtual bool Update(const IDbQuery *query, const StringArray &columns, const DbRow &row, String &target) = 0;
		virtual bool Update(const IDbQuery *query, const DbSet &data, String &target) = 0; // [ name => value, ...] format

		// Transaction queries
		virtual bool StartTransaction(const String &options, String &target) = 0;
		virtual bool Commit(String &target) = 0;
		virtual bool RollBack(String &target) = 0;

		// Information queries
		virtual bool LastInsertId(String &target) = 0;
		virtual bool AutoIncrementColumn(const String &table, String &target) = 0;
	};
}