// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "../Core/Releasable.h"
#include "../Core/ReleasablePtr.h"
#include "../Core/Strings.h"
#include "../Interfaces/IDbMigration.h"
#include "../Interfaces/IDbQuery.h"
#include "../Interfaces/IDbQueryBuilder.h"
#include "DbOrderByArray.h"
#include "DbRow.h"
#include "DbRows.h"
#include "DbValue.h"
#include <map>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IDbMigrationColumn;
	class IDbMigrationKey;

	class CDbCondition;

	class CDbQueryBuilderMySql :public virtual IDbQueryBuilder, public CReleasable
	{
	protected: // To be accessible in tests
		String PrepareColumnName(const String &name) const;
		bool ValueToString(const DbValue &value, String &target);
		bool BuildConditionOperand1(const CDbCondition *condition, String &target);
		bool BuildConditionOperand2(const CDbCondition *condition, String &target);
		bool BuildConditionOperand3(const CDbCondition *condition, String &target);
		bool BuildConditionExpression(const CDbCondition *condition, String &target);
		bool BuildConditionEquals(const CDbCondition *condition, String &target);
		bool BuildConditionNotEquals(const CDbCondition *condition, String &target);
		bool BuildConditionGreater(const CDbCondition *condition, String &target);
		bool BuildConditionGreaterEquals(const CDbCondition *condition, String &target);
		bool BuildConditionLess(const CDbCondition *condition, String &target);
		bool BuildConditionLessEquals(const CDbCondition *condition, String &target);
		bool BuildConditionAnd(const CDbCondition *condition, String &target);
		bool BuildConditionOr(const CDbCondition *condition, String &target);
		bool BuildConditionNot(const CDbCondition *condition, String &target);
		bool BuildConditionBetween(const CDbCondition *condition, String &target);
		bool BuildConditionNotBetween(const CDbCondition *condition, String &target);
		bool BuildConditionIn(const CDbCondition *condition, String &target);
		bool BuildConditionNotIn(const CDbCondition *condition, String &target);
		bool BuildConditionLike(const CDbCondition *condition, String &target);
		bool BuildConditionNotLike(const CDbCondition *condition, String &target);
		bool BuildConditionExists(const CDbCondition *condition, String &target);
		bool BuildConditionNotExists(const CDbCondition *condition, String &target);
		bool BuildCondition(const CDbCondition *condition, String &target);
		bool BuildSelect(const StringKeyValueArray &selects, const bool distinct, String &sql);
		bool BuildFrom(const StringKeyValueArray &froms, String &sql);
		bool BuildJoin(const String &prefix, const IDbQuery::DbJoins &joins, String &sql);
		bool BuildWhere(const CDbCondition *condition, String &sql);
		bool BuildGroupBy(const StringArray &group_by, String &sql);
		bool BuildHaving(const CDbCondition *condition, String &sql);
		bool BuildOrderBy(const DbOrderByArray &orders, String &sql);
		bool BuildLimit(const int64 &limit, const int64 &offset, String &sql);
		bool BuildUnion(const IDbQuery::DbUnions &unions, String &sql);
		bool BuildColumnType(const IDbMigrationColumn *column, String &sql);
		bool BuildColumnDefault(const IDbMigrationColumn *column, String &sql);
		bool BuildColumn(const IDbMigrationColumn *column, String &sql);
		bool BuildKeyIndex(const IDbMigrationKey *key, String &sql);
		bool BuildKeyPrimary(const IDbMigrationKey *key, String &sql);
		bool BuildKeyUnique(const IDbMigrationKey *key, String &sql);
		bool BuildKeyForeign(const IDbMigrationKey *key, String &sql);
		bool BuildKey(const IDbMigrationKey *key, String &sql);
	public:
		static const String Name;

		// IDbQueryBuilder database manipulation queries
		bool CreateDatabase(const String &name, const String &charset, const String &collation, const bool if_not_exists, String &target) override;
		bool AlterDatabase(const String &name, const String &charset, const String &collation, String &target) override;
		bool DropDatabase(const String &name, const bool if_exists, String &target) override;

		// IDbQueryBuilder table manipulation queries
		bool CreateTable(
			const String &name,
			const IDbMigration::MigrationColumns &columns,
			const IDbMigration::MigrationKeys &keys,
			const bool &if_not_exists,
			const String &comment,
			const int64 &auto_increment,
			const String &charset,
			const String &collation,
			const String &engine,
			String &target) override;
		bool AlterTable(const String &name, const String &charset, const String &collation, const bool &convert, String &target) override;
		bool RenameTable(const String &old_name, const String &new_name, String &target) override;
		bool TruncateTable(const String &name, String &target) override;
		bool DropTable(const String &name, const bool if_exists, String &target) override;
		bool DisableKeys(const String &table, String &target) override;
		bool EnableKeys(const String &table, String &target) override;

		// IDbQueryBuilder column manipulation options
		bool AddColumn(const String &table, const IDbMigrationColumn *column, const String &after, String &target) override;
		bool AlterColumn(const String &table, const IDbMigrationColumn *column, const String &after, String &target) override;
		bool AlterColumn(const String &table, const String &old_name, const IDbMigrationColumn *column, const String &after, String &target) override;
		bool RenameColumn(const String &table, const String &old_name, const String &new_name, String &target) override;
		bool DropColumn(const String &table, const String &name, String &target) override;

		// IDbQueryBuilder key manipulation queries
		bool AddKey(const String &table, const IDbMigrationKey *key, String &target) override;
		bool RenameKey(const String &table, const String &old_name, const String &new_name, String &target) override;
		bool DropKey(const String &table, const String &name, String &target) override;
		bool DropPrimaryKey(const String &table, const String &name, String &target) override;

		// IDbQueryBuilder select queries
		bool Select(const IDbQuery *query, String &target) override;
		bool Exists(const IDbQuery *query, String &target) override;
		bool Scalar(const IDbQuery *query, const String &column, String &target) override;
		bool Count(const IDbQuery *query, const String &column, String &target) override;
		bool Sum(const IDbQuery *query, const String &column, String &target) override;
		bool Average(const IDbQuery *query, const String &column, String &target) override;
		bool Min(const IDbQuery *query, const String &column, String &target) override;
		bool Max(const IDbQuery *query, const String &column, String &target) override;

		// IDbQueryBuilder delete queries
		bool Delete(const IDbQuery *query, String &target) override;

		// IDbQueryBuilder insert queries
		bool Insert(const IDbQuery *query, const StringArray &columns, const DbRow &row, const String &on_duplicate_update, String &target) override;
		bool Insert(const IDbQuery *query, const StringArray &columns, const DbRows &rows, const String &on_duplicate_update, String &target) override;
		bool Insert(const IDbQuery *query, const DbSet &data, const String &on_duplicate_update, String &target) override;

		// IDbQueryBuilder update queries
		bool Update(const IDbQuery *query, const StringArray &columns, const DbRow &row, String &target) override;
		bool Update(const IDbQuery *query, const DbSet &data, String &target) override;

		// IDbQueryBuilder transaction queries
		bool StartTransaction(const String &options, String &target) override;
		bool Commit(String &target) override;
		bool RollBack(String &target) override;

		// IDbQueryBuilder information queries
		bool LastInsertId(String &target) override;
		bool AutoIncrementColumn(const String &table, String &target) override;
	};
}