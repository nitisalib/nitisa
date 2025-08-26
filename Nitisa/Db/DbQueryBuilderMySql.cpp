// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	const String CDbQueryBuilderMySql::Name{ L"MySql" };

#pragma region IDbQueryBuilder database manipulation queries
	bool CDbQueryBuilderMySql::CreateDatabase(const String &name, const String &charset, const String &collation, const bool if_not_exists, String &target)
	{
		if (name.empty())
		{
			m_sLastError = L"Database name is required";
			return false;
		}
		target = L"CREATE DATABASE ";
		if (if_not_exists)
			target += L"IF NOT EXISTS ";
		target += PrepareColumnName(name);
		if (!charset.empty())
			target += L" CHARACTER SET " + charset;
		if (!collation.empty())
			target += L" COLLATE " + collation;
		return true;
	}

	bool CDbQueryBuilderMySql::AlterDatabase(const String &name, const String &charset, const String &collation, String &target)
	{
		if (name.empty())
		{
			m_sLastError = L"Database name is required";
			return false;
		}
		if (charset.empty() && collation.empty())
		{
			m_sLastError = L"Charset of collation is required";
			return false;
		}
		target = L"ALTER DATABASE " + PrepareColumnName(name);
		if (!charset.empty())
			target += L" CHARACTER SET " + charset;
		if (!collation.empty())
			target += L" COLLATE " + collation;
		return true;
	}

	bool CDbQueryBuilderMySql::DropDatabase(const String &name, const bool if_exists, String &target)
	{
		if (name.empty())
		{
			m_sLastError = L"Database name is required";
			return false;
		}
		target = L"DROP DATABASE ";
		if (if_exists)
			target += L"IF EXISTS ";
		target += PrepareColumnName(name);
		return true;
	}
#pragma endregion

#pragma region IDbQueryBuilder table manipulation queries
	bool CDbQueryBuilderMySql::CreateTable(
		const String &name,
		const IDbMigration::MigrationColumns &columns,
		const IDbMigration::MigrationKeys &keys,
		const bool &if_not_exists,
		const String &comment,
		const int64 &auto_increment,
		const String &charset,
		const String &collation,
		const String &engine,
		String &target)
	{
		if (name.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		if (columns.empty())
		{
			m_sLastError = L"Columns are required";
			return false;
		}
		target = L"CREATE TABLE ";
		if (if_not_exists)
			target += L"IF NOT EXISTS ";
		target += PrepareColumnName(name) + L" (";
		for (size_t i = 0; i < columns.size(); i++)
		{
			if (i > 0)
				target += L", ";
			String sql;
			if (!BuildColumn(columns[i], sql))
				return false;
			target += sql;
		}
		for (size_t i = 0; i < keys.size(); i++)
		{
			String sql;
			if (!BuildKey(keys[i], sql))
				return false;
			target += L", " + sql;
		}
		target += L")";
		if (auto_increment != std::numeric_limits<long long>::min())
			target += L" AUTO_INCREMENT " + ToString(auto_increment);
		if (!charset.empty())
			target += L" CHARACTER SET " + charset;
		if (!collation.empty())
			target += L" COLLATE " + collation;
		if (!engine.empty())
			target += L" ENGINE " + engine;
		if (!comment.empty())
			target += L" COMMENT '" + ReplaceAll(comment, L"'", L"\\'") + L"'";
		return true;
	}

	bool CDbQueryBuilderMySql::AlterTable(const String &name, const String &charset, const String &collation, const bool &convert, String &target)
	{
		if (name.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		if (charset.empty())
		{
			m_sLastError = L"Character set is required";
			return false;
		}
		target = L"ALTER TABLE " + PrepareColumnName(name) + L" ";
		if (convert)
			target += L"CONVERT TO ";
		target += L"CHARACTER SET " + charset;
		if (!collation.empty())
			target += L" COLLATE " + collation;
		return true;
	}

	bool CDbQueryBuilderMySql::RenameTable(const String &old_name, const String &new_name, String &target)
	{
		if (old_name.empty())
		{
			m_sLastError = L"Table old name is required";
			return false;
		}
		if (new_name.empty())
		{
			m_sLastError = L"Table new name is required";
			return false;
		}
		target = L"RENAME TABLE " + PrepareColumnName(old_name) + L" TO " + PrepareColumnName(new_name);
		return true;
	}

	bool CDbQueryBuilderMySql::TruncateTable(const String &name, String &target)
	{
		if (name.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		target = L"TRUNCATE TABLE " + PrepareColumnName(name);
		return true;
	}

	bool CDbQueryBuilderMySql::DropTable(const String &name, const bool if_exists, String &target)
	{
		if (name.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		target = L"DROP TABLE ";
		if (if_exists)
			target += L"IF EXISTS ";
		target += PrepareColumnName(name);
		return true;
	}

	bool CDbQueryBuilderMySql::DisableKeys(const String &table, String &target)
	{
		if (table.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		target = L"ALTER TABLE " + PrepareColumnName(table) + L" DISABLE KEYS";
		return true;
	}

	bool CDbQueryBuilderMySql::EnableKeys(const String &table, String &target)
	{
		if (table.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		target = L"ALTER TABLE " + PrepareColumnName(table) + L" ENABLE KEYS";
		return true;
	}
#pragma endregion

#pragma region IDbQueryBuilder column manipulation options
	bool CDbQueryBuilderMySql::AddColumn(const String &table, const IDbMigrationColumn *column, const String &after, String &target)
	{
		if (table.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		if (!column)
		{
			m_sLastError = L"Column definition is required";
			return false;
		}
		String sql;
		if (!BuildColumn(column, sql))
			return false;
		target = L"ALTER TABLE " + PrepareColumnName(table) + L" ADD COLUMN " + sql;
		if (!after.empty())
		{
			if (after == L"FIRST")
				target += L" FIRST";
			else
				target += L" AFTER " + PrepareColumnName(after);
		}
		return true;
	}

	bool CDbQueryBuilderMySql::AlterColumn(const String &table, const IDbMigrationColumn *column, const String &after, String &target)
	{
		if (table.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		if (!column)
		{
			m_sLastError = L"Column definition is required";
			return false;
		}
		String sql;
		if (!BuildColumn(column, sql))
			return false;
		target = L"ALTER TABLE " + PrepareColumnName(table) + L" MODIFY COLUMN " + sql;
		if (!after.empty())
		{
			if (after == L"FIRST")
				target += L" FIRST";
			else
				target += L" AFTER " + PrepareColumnName(after);
		}
		return true;
	}

	bool CDbQueryBuilderMySql::AlterColumn(const String &table, const String &old_name, const IDbMigrationColumn *column, const String &after, String &target)
	{
		if (table.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		if (old_name.empty())
		{
			m_sLastError = L"Column old name is required";
			return false;
		}
		if (!column)
		{
			m_sLastError = L"Column definition is required";
			return false;
		}
		String sql;
		if (!BuildColumn(column, sql))
			return false;
		target = L"ALTER TABLE " + PrepareColumnName(table) + L" CHANGE COLUMN " + PrepareColumnName(old_name) + L" " + sql;
		if (!after.empty())
		{
			if (after == L"FIRST")
				target += L" FIRST";
			else
				target += L" AFTER " + PrepareColumnName(after);
		}
		return true;
	}

	bool CDbQueryBuilderMySql::RenameColumn(const String &table, const String &old_name, const String &new_name, String &target)
	{
		if (table.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		if (old_name.empty())
		{
			m_sLastError = L"Column old name is required";
			return false;
		}
		if (new_name.empty())
		{
			m_sLastError = L"Column new name is required";
			return false;
		}
		target = L"ALTER TABLE " + PrepareColumnName(table) + L" RENAME COLUMN " + PrepareColumnName(old_name) + L" TO " + PrepareColumnName(new_name);
		return true;
	}

	bool CDbQueryBuilderMySql::DropColumn(const String &table, const String &name, String &target)
	{
		if (table.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		if (name.empty())
		{
			m_sLastError = L"Column name is required";
			return false;
		}
		target = L"ALTER TABLE " + PrepareColumnName(table) + L" DROP COLUMN " + PrepareColumnName(name);
		return true;
	}
#pragma endregion

#pragma region IDbQueryBuilder key manipulation queries
	bool CDbQueryBuilderMySql::AddKey(const String &table, const IDbMigrationKey *key, String &target)
	{
		if (table.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		if (!key)
		{
			m_sLastError = L"Key definition is required";
			return false;
		}
		String sql;
		if (!BuildKey(key, sql))
			return false;
		target = L"ALTER TABLE " + PrepareColumnName(table) + L" ADD " + sql;
		return true;
	}

	bool CDbQueryBuilderMySql::RenameKey(const String &table, const String &old_name, const String &new_name, String &target)
	{
		if (table.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		if (old_name.empty())
		{
			m_sLastError = L"Key old name is required";
			return false;
		}
		if (new_name.empty())
		{
			m_sLastError = L"Key new name is required";
			return false;
		}
		target = L"ALTER TABLE " + PrepareColumnName(table) + L" RENAME KEY " + PrepareColumnName(old_name) + L" TO " + PrepareColumnName(new_name);
		return true;
	}

	bool CDbQueryBuilderMySql::DropKey(const String &table, const String &name, String &target)
	{
		if (table.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		if (name.empty())
		{
			m_sLastError = L"Key name is required";
			return false;
		}
		target = L"ALTER TABLE " + PrepareColumnName(table) + L" DROP KEY " + PrepareColumnName(name);
		return true;
	}

	bool CDbQueryBuilderMySql::DropPrimaryKey(const String &table, const String &name, String &target)
	{
		if (table.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		target = L"ALTER TABLE " + PrepareColumnName(table) + L" DROP PRIMARY KEY";
		if (!name.empty())
			target += L" " + PrepareColumnName(name);
		return true;
	}
#pragma endregion

#pragma region IDbQueryBuilder select queries
	bool CDbQueryBuilderMySql::Select(const IDbQuery *query, String &target)
	{
		if (!query)
		{
			m_sLastError = L"Query is required";
			return false;
		}

		String sql;
		if (!BuildSelect(query->aSelect, query->bDistinct, sql))
			return false;
		if (!BuildFrom(query->aFrom, sql))
			return false;
		if (!BuildJoin(L"INNER", query->aInnerJoin, sql))
			return false;
		if (!BuildJoin(L"LEFT", query->aLeftJoin, sql))
			return false;
		if (!BuildJoin(L"RIGHT", query->aRightJoin, sql))
			return false;
		if (!BuildWhere(query->pWhere, sql))
			return false;
		if (!BuildGroupBy(query->aGroupBy, sql))
			return false;
		if (!BuildHaving(query->pHaving, sql))
			return false;
		if (!BuildOrderBy(query->aOrderBy, sql))
			return false;
		if (!BuildLimit(query->iLimit, query->iOffset, sql))
			return false;
		if (!BuildUnion(query->aUnion, sql))
			return false;

		target = sql;
		return true;
	}

	bool CDbQueryBuilderMySql::Exists(const IDbQuery *query, String &target)
	{
		String sql;
		if (!Select(query, sql))
			return false;
		target = L"SELECT EXISTS(" + sql + L")";
		return true;
	}

	bool CDbQueryBuilderMySql::Scalar(const IDbQuery *query, const String &column, String &target)
	{
		if (!query)
		{
			m_sLastError = L"Query is required";
			return false;
		}

		String sql;
		if (!BuildSelect(StringKeyValueArray{ StringKeyValue { column, L"" } }, query->bDistinct, sql))
			return false;
		if (!BuildFrom(query->aFrom, sql))
			return false;
		if (!BuildJoin(L"INNER", query->aInnerJoin, sql))
			return false;
		if (!BuildJoin(L"LEFT", query->aLeftJoin, sql))
			return false;
		if (!BuildJoin(L"RIGHT", query->aRightJoin, sql))
			return false;
		if (!BuildWhere(query->pWhere, sql))
			return false;
		if (!BuildGroupBy(query->aGroupBy, sql))
			return false;
		if (!BuildHaving(query->pHaving, sql))
			return false;
		if (!BuildOrderBy(query->aOrderBy, sql))
			return false;
		if (!BuildLimit(query->iLimit, query->iOffset, sql))
			return false;

		target = sql;
		return true;
	}

	bool CDbQueryBuilderMySql::Count(const IDbQuery *query, const String &column, String &target)
	{
		return Scalar(query, L"COUNT(" + column + L")", target);
	}

	bool CDbQueryBuilderMySql::Sum(const IDbQuery *query, const String &column, String &target)
	{
		return Scalar(query, L"SUM(" + column + L")", target);
	}

	bool CDbQueryBuilderMySql::Average(const IDbQuery *query, const String &column, String &target)
	{
		return Scalar(query, L"AVG(" + column + L")", target);
	}

	bool CDbQueryBuilderMySql::Min(const IDbQuery *query, const String &column, String &target)
	{
		return Scalar(query, L"MIN(" + column + L")", target);
	}

	bool CDbQueryBuilderMySql::Max(const IDbQuery *query, const String &column, String &target)
	{
		return Scalar(query, L"MAX(" + column + L")", target);
	}
#pragma endregion

#pragma region IDbQueryBuilder delete queries
	bool CDbQueryBuilderMySql::Delete(const IDbQuery *query, String &target)
	{
		if (!query)
		{
			m_sLastError = L"Query is required";
			return false;
		}

		String sql{ L"DELETE" };
		if (!BuildFrom(query->aFrom, sql))
			return false;
		if (!BuildWhere(query->pWhere, sql))
			return false;
		if (!BuildOrderBy(query->aOrderBy, sql))
			return false;
		if (!BuildLimit(query->iLimit, -1, sql))
			return false;

		target = sql;
		return true;
	}
#pragma endregion

#pragma region IDbQueryBuilder insert queries
	bool CDbQueryBuilderMySql::Insert(const IDbQuery *query, const StringArray &columns, const DbRow &row, const String &on_duplicate_update, String &target)
	{
		if (!query)
		{
			m_sLastError = L"Query is required";
			return false;
		}
		if (query->sInto.empty())
		{
			m_sLastError = L"Target table name is required";
			return false;
		}
		if (columns.empty())
		{
			m_sLastError = L"Column names are required";
			return false;
		}
		if (row.size() != columns.size())
		{
			m_sLastError = L"Row element count should be equal to column count";
			return false;
		}
		String sql{ L"INSERT INTO " + PrepareColumnName(query->sInto) + L"(" };
		for (size_t i = 0; i < columns.size(); i++)
		{
			if (columns[i].empty())
			{
				m_sLastError = L"Column #" + ToString(int(i + 1)) + L" name is empty";
				return false;
			}
			if (i > 0)
				sql += L", ";
			sql += PrepareColumnName(columns[i]);
		}
		sql += L") VALUES (";
		for (size_t i = 0; i < row.size(); i++)
		{
			if (i > 0)
				sql += L", ";
			String s;
			if (!ValueToString(row[i], s))
				return false;
			sql += s;
		}
		sql += L")";
		if (!on_duplicate_update.empty())
			sql += L" ON DUPLICATE KEY UPDATE " + on_duplicate_update;
		target = sql;
		return true;
	}

	bool CDbQueryBuilderMySql::Insert(const IDbQuery *query, const StringArray &columns, const DbRows &rows, const String &on_duplicate_update, String &target)
	{
		if (!query)
		{
			m_sLastError = L"Query is required";
			return false;
		}
		if (query->sInto.empty())
		{
			m_sLastError = L"Target table name is required";
			return false;
		}
		if (columns.empty())
		{
			m_sLastError = L"Column names are required";
			return false;
		}
		if (rows.empty())
		{
			m_sLastError = L"Rows are required";
			return false;
		}
		for (size_t i = 0; i < rows.size(); i++)
			if (rows[i].size() != columns.size())
			{
				m_sLastError = L"Row #" + ToString(int(i + 1)) + L" element count should be equal to column count";
				return false;
			}
		String sql{ L"INSERT INTO " + PrepareColumnName(query->sInto) + L"(" };
		for (size_t i = 0; i < columns.size(); i++)
		{
			if (columns[i].empty())
			{
				m_sLastError = L"Column #" + ToString(int(i + 1)) + L" name is empty";
				return false;
			}
			if (i > 0)
				sql += L", ";
			sql += PrepareColumnName(columns[i]);
		}
		sql += L") VALUES ";
		for (size_t j = 0; j < rows.size(); j++)
		{
			if (j > 0)
				sql += L", ";
			sql += L"(";
			for (size_t i = 0; i < rows[j].size(); i++)
			{
				if (i > 0)
					sql += L", ";
				String s;
				if (!ValueToString(rows[j][i], s))
					return false;
				sql += s;
			}
			sql += L")";
		}
		if (!on_duplicate_update.empty())
			sql += L" ON DUPLICATE KEY UPDATE " + on_duplicate_update;
		target = sql;
		return true;
	}

	bool CDbQueryBuilderMySql::Insert(const IDbQuery *query, const DbSet &data, const String &on_duplicate_update, String &target)
	{
		if (!query)
		{
			m_sLastError = L"Query is required";
			return false;
		}
		if (query->sInto.empty())
		{
			m_sLastError = L"Target table name is required";
			return false;
		}
		if (data.empty())
		{
			m_sLastError = L"Data is required";
			return false;
		}
		String sql{ L"INSERT INTO " + PrepareColumnName(query->sInto) + L" SET " };
		bool first{ true };
		for (auto const &info : data)
		{
			if (info.first.empty())
			{
				m_sLastError = L"Column name cannot be empty";
				return false;
			}
			String s;
			if (!ValueToString(info.second, s))
				return false;
			if (first)
				first = false;
			else
				sql += L", ";
			sql += PrepareColumnName(info.first) + L" = " + s;
		}
		if (!on_duplicate_update.empty())
			sql += L" ON DUPLICATE KEY UPDATE " + on_duplicate_update;
		target = sql;
		return true;
	}
#pragma endregion

#pragma region IDbQueryBuilder update queries
	bool CDbQueryBuilderMySql::Update(const IDbQuery *query, const StringArray &columns, const DbRow &row, String &target)
	{
		if (!query)
		{
			m_sLastError = L"Query is required";
			return false;
		}
		if (query->sTable.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		if (columns.empty())
		{
			m_sLastError = L"Column names are required";
			return false;
		}
		if (row.size() != columns.size())
		{
			m_sLastError = L"Row element count should be equal to column count";
			return false;
		}
		String sql{ L"UPDATE " + PrepareColumnName(query->sTable) + L" SET " };
		for (size_t i = 0; i < columns.size(); i++)
		{
			if (columns[i].empty())
			{
				m_sLastError = L"Column #" + ToString(int(i + 1)) + L" name is empty";
				return false;
			}
			String s;
			if (!ValueToString(row[i], s))
				return false;
			if (i > 0)
				sql += L", ";
			sql += PrepareColumnName(columns[i]) + L" = " + s;
		}
		if (!BuildWhere(query->pWhere, sql))
			return false;
		if (!BuildOrderBy(query->aOrderBy, sql))
			return false;
		if (!BuildLimit(query->iLimit, -1, sql))
			return false;
		target = sql;
		return true;
	}

	bool CDbQueryBuilderMySql::Update(const IDbQuery *query, const DbSet &data, String &target)
	{
		if (!query)
		{
			m_sLastError = L"Query is required";
			return false;
		}
		if (query->sTable.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		if (data.empty())
		{
			m_sLastError = L"Data is required";
			return false;
		}
		String sql{ L"UPDATE " + PrepareColumnName(query->sTable) + L" SET " };
		bool first{ true };
		for (auto const &info : data)
		{
			if (info.first.empty())
			{
				m_sLastError = L"Column name cannot be empty";
				return false;
			}
			String s;
			if (!ValueToString(info.second, s))
				return false;
			if (first)
				first = false;
			else
				sql += L", ";
			sql += PrepareColumnName(info.first) + L" = " + s;
		}
		if (!BuildWhere(query->pWhere, sql))
			return false;
		if (!BuildOrderBy(query->aOrderBy, sql))
			return false;
		if (!BuildLimit(query->iLimit, -1, sql))
			return false;
		target = sql;
		return true;
	}
#pragma endregion

#pragma region IDbQueryBuilder transaction queries
	bool CDbQueryBuilderMySql::StartTransaction(const String &options, String &target)
	{
		target = L"START TRANSACTION";
		if (!options.empty())
			target += L" " + options;
		return true;
	}

	bool CDbQueryBuilderMySql::Commit(String &target)
	{
		target = L"COMMIT";
		return true;
	}

	bool CDbQueryBuilderMySql::RollBack(String &target)
	{
		target = L"ROLLBACK";
		return true;
	}
#pragma endregion

#pragma region IDbQueryBuilder informaition queries
	bool CDbQueryBuilderMySql::LastInsertId(String &target)
	{
		target = L"SELECT LAST_INSERT_ID()";
		return true;
	}

	bool CDbQueryBuilderMySql::AutoIncrementColumn(const String &table, String &target)
	{
		if (table.empty())
		{
			m_sLastError = L"Table name is required";
			return false;
		}
		target = L"SELECT COLUMN_NAME FROM information_schema.columns WHERE TABLE_SCHEMA = DATABASE() AND "
			L"TABLE_NAME = \"" + table + L"\" AND EXTRA LIKE '%auto_increment%'";
		return true;
	}
#pragma endregion

#pragma region Helpers
	String CDbQueryBuilderMySql::PrepareColumnName(const String &name) const
	{
		if (name.find_first_of(L" `'\"([{=><!&%*+-/:^|~", 0) != String::npos)
			return name;
		StringArray parts{ Explode(name, L".", false) };
		for (auto &part : parts)
		{
			if (part.empty())
				return name;
			part = L"`" + part + L"`";
		}
		return Implode(L".", parts);
	}

	bool CDbQueryBuilderMySql::ValueToString(const DbValue &value, String &target)
	{
		switch (value.Type)
		{
		case DbValueType::Null:
			target = L"NULL";
			break;
		case DbValueType::Bool:
			target = (bool)value ? L"TRUE" : L"FALSE";
			break;
		case DbValueType::String:
		case DbValueType::AnsiString:
			target = L"\"" + ReplaceAll((String)value, StringKeyValueArray{ StringKeyValue{ L"\\", L"\\\\" }, StringKeyValue{ L"\"", L"\\\"" } }) + L"\"";
			break;
		case DbValueType::Buffer:
			m_sLastError = L"BUFFER value is not supported";
			return false;
		case DbValueType::Date:
		case DbValueType::Time:
		case DbValueType::DateTime:
			target = L"\"" + (String)value + L"\"";
			break;
		default:
			target = (String)value;
		}
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionOperand1(const CDbCondition *condition, String &target)
	{
		switch (condition->Operand1Type)
		{
		case CDbCondition::OperandType::Column:
			if (condition->Column1.empty())
			{
				m_sLastError = L"Column1 cannot be empty";
				return false;
			}
			target = PrepareColumnName(condition->Column1);
			break;
		case CDbCondition::OperandType::Value:
			if (!ValueToString(condition->Value1, target))
				return false;
			break;
		case CDbCondition::OperandType::Expression:
			if (!condition->Operand1)
			{
				m_sLastError = L"Operand1 cannot be empty";
				return false;
			}
			if (!BuildCondition(condition->Operand1, target))
				return false;
			break;
		default:
			m_sLastError = L"Unknown operand1 type";
			return false;
		}
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionOperand2(const CDbCondition *condition, String &target)
	{
		switch (condition->Operand2Type)
		{
		case CDbCondition::OperandType::Column:
			if (condition->Column2.empty())
			{
				m_sLastError = L"Column2 cannot be empty";
				return false;
			}
			target = PrepareColumnName(condition->Column2);
			break;
		case CDbCondition::OperandType::Value:
			if (!ValueToString(condition->Value2, target))
				return false;
			break;
		case CDbCondition::OperandType::Expression:
			if (!condition->Operand2)
			{
				m_sLastError = L"Operand2 cannot be empty";
				return false;
			}
			if (!BuildCondition(condition->Operand2, target))
				return false;
			break;
		default:
			m_sLastError = L"Unknown operand2 type";
			return false;
		}
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionOperand3(const CDbCondition *condition, String &target)
	{
		switch (condition->Operand3Type)
		{
		case CDbCondition::OperandType::Column:
			if (condition->Column3.empty())
			{
				m_sLastError = L"Column3 cannot be empty";
				return false;
			}
			target = PrepareColumnName(condition->Column3);
			break;
		case CDbCondition::OperandType::Value:
			if (!ValueToString(condition->Value3, target))
				return false;
			break;
		case CDbCondition::OperandType::Expression:
			if (!condition->Operand3)
			{
				m_sLastError = L"Operand3 cannot be empty";
				return false;
			}
			if (!BuildCondition(condition->Operand3, target))
				return false;
			break;
		default:
			m_sLastError = L"Unknown operand3 type";
			return false;
		}
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionExpression(const CDbCondition *condition, String &target)
	{
		if (condition->Column1.empty())
		{
			m_sLastError = L"Expression cannot be empty";
			return false;
		}
		target = condition->Column1;
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionEquals(const CDbCondition *condition, String &target)
	{
		String v1;
		if (!BuildConditionOperand1(condition, v1))
			return false;
		if (condition->Operand2Type == CDbCondition::OperandType::Value && condition->Value2.Type == DbValueType::Null)
		{
			target = v1 + L" IS NULL";
			return true;
		}
		String v2;
		if (!BuildConditionOperand2(condition, v2))
			return false;
		target = v1 + L" = " + v2;
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionNotEquals(const CDbCondition *condition, String &target)
	{
		String v1;
		if (!BuildConditionOperand1(condition, v1))
			return false;
		if (condition->Operand2Type == CDbCondition::OperandType::Value && condition->Value2.Type == DbValueType::Null)
		{
			target = v1 + L" IS NOT NULL";
			return true;
		}
		String v2;
		if (!BuildConditionOperand2(condition, v2))
			return false;
		target = v1 + L" <> " + v2;
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionGreater(const CDbCondition *condition, String &target)
	{
		String v1;
		if (!BuildConditionOperand1(condition, v1))
			return false;
		String v2;
		if (!BuildConditionOperand2(condition, v2))
			return false;
		target = v1 + L" > " + v2;
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionGreaterEquals(const CDbCondition *condition, String &target)
	{
		String v1;
		if (!BuildConditionOperand1(condition, v1))
			return false;
		String v2;
		if (!BuildConditionOperand2(condition, v2))
			return false;
		target = v1 + L" >= " + v2;
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionLess(const CDbCondition *condition, String &target)
	{
		String v1;
		if (!BuildConditionOperand1(condition, v1))
			return false;
		String v2;
		if (!BuildConditionOperand2(condition, v2))
			return false;
		target = v1 + L" < " + v2;
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionLessEquals(const CDbCondition *condition, String &target)
	{
		String v1;
		if (!BuildConditionOperand1(condition, v1))
			return false;
		String v2;
		if (!BuildConditionOperand2(condition, v2))
			return false;
		target = v1 + L" <= " + v2;
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionAnd(const CDbCondition *condition, String &target)
	{
		if (!condition->Operand1)
		{
			m_sLastError = L"Operand1 cannot be empty";
			return false;
		}
		String v1;
		if (!BuildCondition(condition->Operand1, v1))
			return false;
		if (!condition->Operand2)
		{
			m_sLastError = L"Operand2 cannot be empty";
			return false;
		}
		String v2;
		if (!BuildCondition(condition->Operand2, v2))
			return false;
		target = L"(" + v1 + L") AND (" + v2 + L")";
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionOr(const CDbCondition *condition, String &target)
	{
		if (!condition->Operand1)
		{
			m_sLastError = L"Operand1 cannot be empty";
			return false;
		}
		String v1;
		if (!BuildCondition(condition->Operand1, v1))
			return false;
		if (!condition->Operand2)
		{
			m_sLastError = L"Operand2 cannot be empty";
			return false;
		}
		String v2;
		if (!BuildCondition(condition->Operand2, v2))
			return false;
		target = L"(" + v1 + L") OR (" + v2 + L")";
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionNot(const CDbCondition *condition, String &target)
	{
		if (!condition->Operand1)
		{
			m_sLastError = L"Operand1 cannot be empty";
			return false;
		}
		if (condition->Operand1->Type == CDbCondition::ConditionType::Equals &&
			condition->Operand1->Operand2Type == CDbCondition::OperandType::Value &&
			condition->Operand1->Value2.Type == DbValueType::Null)
		{
			String v;
			if (!BuildConditionOperand1(condition->Operand1, v))
				return false;
			target = v + L" IS NOT NULL";
			return true;
		}
		String v1;
		if (!BuildCondition(condition->Operand1, v1))
			return false;
		target = L"NOT (" + v1 + L")";
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionBetween(const CDbCondition *condition, String &target)
	{
		String v1;
		if (!BuildConditionOperand1(condition, v1))
			return false;
		String v2;
		if (!BuildConditionOperand2(condition, v2))
			return false;
		String v3;
		if (!BuildConditionOperand3(condition, v3))
			return false;
		target = v1 + L" BETWEEN " + v2 + L" AND " + v3;
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionNotBetween(const CDbCondition *condition, String &target)
	{
		String v1;
		if (!BuildConditionOperand1(condition, v1))
			return false;
		String v2;
		if (!BuildConditionOperand2(condition, v2))
			return false;
		String v3;
		if (!BuildConditionOperand3(condition, v3))
			return false;
		target = v1 + L" NOT BETWEEN " + v2 + L" AND " + v3;
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionIn(const CDbCondition *condition, String &target)
	{
		String v1;
		if (!BuildConditionOperand1(condition, v1))
			return false;
		if (condition->Values.empty())
		{
			m_sLastError = L"Values cannot be empty";
			return false;
		}
		String v2{ L"(" };
		for (size_t i = 0; i < condition->Values.size(); i++)
		{
			String v;
			if (!ValueToString(condition->Values[i], v))
				return false;
			if (i > 0)
				v2 += L", ";
			v2 += v;
		}
		v2 += L")";
		target = v1 + L" IN " + v2;
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionNotIn(const CDbCondition *condition, String &target)
	{
		String v1;
		if (!BuildConditionOperand1(condition, v1))
			return false;
		if (condition->Values.empty())
		{
			m_sLastError = L"Values cannot be empty";
			return false;
		}
		String v2{ L"(" };
		for (size_t i = 0; i < condition->Values.size(); i++)
		{
			String v;
			if (!ValueToString(condition->Values[i], v))
				return false;
			if (i > 0)
				v2 += L", ";
			v2 += v;
		}
		v2 += L")";
		target = v1 + L" NOT IN " + v2;
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionLike(const CDbCondition *condition, String &target)
	{
		String v1;
		if (!BuildConditionOperand1(condition, v1))
			return false;
		if (condition->Column2.empty())
		{
			m_sLastError = L"Pattern cannot be empty";
			return false;
		}
		target = v1 + L" LIKE '" + ReplaceAll(condition->Column2, L"'", L"\\'") + L"'";
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionNotLike(const CDbCondition *condition, String &target)
	{
		String v1;
		if (!BuildConditionOperand1(condition, v1))
			return false;
		if (condition->Column2.empty())
		{
			m_sLastError = L"Pattern cannot be empty";
			return false;
		}
		target = v1 + L" NOT LIKE '" + ReplaceAll(condition->Column2, L"'", L"\\'") + L"'";
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionExists(const CDbCondition *condition, String &target)
	{
		if (condition->Column1.empty())
		{
			m_sLastError = L"Query cannot be empty";
			return false;
		}
		target = L"EXISTS (" + condition->Column1 + L")";
		return true;
	}

	bool CDbQueryBuilderMySql::BuildConditionNotExists(const CDbCondition *condition, String &target)
	{
		if (condition->Column1.empty())
		{
			m_sLastError = L"Query cannot be empty";
			return false;
		}
		target = L"NOT EXISTS (" + condition->Column1 + L")";
		return true;
	}

	bool CDbQueryBuilderMySql::BuildCondition(const CDbCondition *condition, String &target)
	{
		switch (condition->Type)
		{
		case CDbCondition::ConditionType::Expression: return BuildConditionExpression(condition, target);
		case CDbCondition::ConditionType::Equals: return BuildConditionEquals(condition, target);
		case CDbCondition::ConditionType::NotEquals: return BuildConditionNotEquals(condition, target);
		case CDbCondition::ConditionType::Greater: return BuildConditionGreater(condition, target);
		case CDbCondition::ConditionType::GreaterEquals: return BuildConditionGreaterEquals(condition, target);
		case CDbCondition::ConditionType::Less: return BuildConditionLess(condition, target);
		case CDbCondition::ConditionType::LessEquals: return BuildConditionLessEquals(condition, target);
		case CDbCondition::ConditionType::And: return BuildConditionAnd(condition, target);
		case CDbCondition::ConditionType::Or: return BuildConditionOr(condition, target);
		case CDbCondition::ConditionType::Not: return BuildConditionNot(condition, target);
		case CDbCondition::ConditionType::Between: return BuildConditionBetween(condition, target);
		case CDbCondition::ConditionType::NotBetween: return BuildConditionNotBetween(condition, target);
		case CDbCondition::ConditionType::In: return BuildConditionIn(condition, target);
		case CDbCondition::ConditionType::NotIn: return BuildConditionNotIn(condition, target);
		case CDbCondition::ConditionType::Like: return BuildConditionLike(condition, target);
		case CDbCondition::ConditionType::NotLike: return BuildConditionNotLike(condition, target);
		case CDbCondition::ConditionType::Exists: return BuildConditionExists(condition, target);
		case CDbCondition::ConditionType::NotExists: return BuildConditionNotExists(condition, target);
		default:
			m_sLastError = L"Unsupported condition type";
			return false;
		}
	}

	bool CDbQueryBuilderMySql::BuildSelect(const StringKeyValueArray &selects, const bool distinct, String &sql)
	{
		sql = L"SELECT ";
		if (selects.empty())
		{
			if (distinct)
			{
				m_sLastError = L"DISTINCT is not allowed with selecting all columns";
				return false;
			}
			sql += L"*";
		}
		else
		{
			bool first{ true };
			for (auto const &column : selects)
			{
				if (first)
				{
					first = false;
					if (distinct)
						sql += L"DISTINCT ";
				}
				else
					sql += L", ";
				sql += PrepareColumnName(column.first);
				if (!column.second.empty())
					sql += L" AS " + PrepareColumnName(column.second);
			}
		}
		return true;
	}

	bool CDbQueryBuilderMySql::BuildFrom(const StringKeyValueArray &froms, String &sql)
	{
		sql += L" FROM ";
		bool first{ true };
		for (auto const &from : froms)
		{
			if (!first)
				sql += L", ";
			else
				first = false;
			sql += PrepareColumnName(from.first);
			if (!from.second.empty())
				sql += L" AS " + PrepareColumnName(from.second);
		}
		return true;
	}

	bool CDbQueryBuilderMySql::BuildJoin(const String &prefix, const IDbQuery::DbJoins &joins, String &sql)
	{
		for (auto const &join : joins)
		{
			sql += L" " + prefix + L" JOIN " + PrepareColumnName(join.Table);
			if (!join.Alias.empty())
				sql += L" AS " + PrepareColumnName(join.Alias);
			if (join.On)
			{
				String on;
				if (!BuildCondition(join.On, on))
					return false;
				sql += L" ON " + on;
			}
		}
		return true;
	}

	bool CDbQueryBuilderMySql::BuildWhere(const CDbCondition *condition, String &sql)
	{
		if (condition)
		{
			String cond;
			if (!BuildCondition(condition, cond))
				return false;
			sql += L" WHERE " + cond;
		}
		return true;
	}

	bool CDbQueryBuilderMySql::BuildGroupBy(const StringArray &group_by, String &sql)
	{
		if (!group_by.empty())
		{
			bool first{ true };
			for (auto const &groupBy : group_by)
			{
				if (first)
				{
					first = false;
					sql += L" GROUP BY ";
				}
				else
					sql += L", ";
				sql += PrepareColumnName(groupBy);
			}
		}
		return true;
	}

	bool CDbQueryBuilderMySql::BuildHaving(const CDbCondition *condition, String &sql)
	{
		if (condition)
		{
			String cond;
			if (!BuildCondition(condition, cond))
				return false;
			sql += L" HAVING " + cond;
		}
		return true;
	}

	bool CDbQueryBuilderMySql::BuildOrderBy(const DbOrderByArray &orders, String &sql)
	{
		if (!orders.empty())
		{
			bool first{ true };
			for (auto const &orderBy : orders)
			{
				if (first)
				{
					first = false;
					sql += L" ORDER BY ";
				}
				else
					sql += L", ";
				sql += PrepareColumnName(orderBy.first);
				switch (orderBy.second)
				{
				case DbOrder::Desc:
					sql += L" DESC";
					break;
				case DbOrder::Random:
					sql += L" RAND()";
					break;
				default:
					break;
				}
			}
		}
		return true;
	}

	bool CDbQueryBuilderMySql::BuildLimit(const int64 &limit, const int64 &offset, String &sql)
	{
		if (limit > 0 || offset >= 0)
		{
			sql += L" LIMIT ";
			if (offset >= 0)
			{
				if (limit <= 0)
				{
					m_sLastError = L"Limit value is required if offset value is specified";
					return false;
				}
				sql += ToString(offset) + L", " + ToString(limit);
			}
			else
				sql += ToString(limit);
		}
		return true;
	}

	bool CDbQueryBuilderMySql::BuildUnion(const IDbQuery::DbUnions &unions, String &sql)
	{
		for (auto const &u : unions)
		{
			String sql2;
			if (!Select(u.Query, sql2))
				return false;
			sql += L" UNION " + (u.All ? (String)L"ALL " : (String)L"") + sql2;
		}
		return true;
	}

	bool CDbQueryBuilderMySql::BuildColumnType(const IDbMigrationColumn *column, String &sql)
	{
		switch (column->eDataType)
		{
		case IDbMigrationColumn::DataType::Bool:
			sql += L"BOOL";
			break;
		case IDbMigrationColumn::DataType::Int:
			sql += L"INT";
			if (column->iWidth > 0)
				sql += L"(" + ToString(column->iWidth) + L")";
			if (column->bUnsigned)
				sql += L" UNSIGNED";
			break;
		case IDbMigrationColumn::DataType::TinyInt:
			sql += L"TINYINT";
			if (column->iWidth > 0)
				sql += L"(" + ToString(column->iWidth) + L")";
			if (column->bUnsigned)
				sql += L" UNSIGNED";
			break;
		case IDbMigrationColumn::DataType::SmallInt:
			sql += L"SMALLINT";
			if (column->iWidth > 0)
				sql += L"(" + ToString(column->iWidth) + L")";
			if (column->bUnsigned)
				sql += L" UNSIGNED";
			break;
		case IDbMigrationColumn::DataType::MediumInt:
			sql += L"MEDIUMINT";
			if (column->iWidth > 0)
				sql += L"(" + ToString(column->iWidth) + L")";
			if (column->bUnsigned)
				sql += L" UNSIGNED";
			break;
		case IDbMigrationColumn::DataType::BigInt:
			sql += L"BIGINT";
			if (column->iWidth > 0)
				sql += L"(" + ToString(column->iWidth) + L")";
			if (column->bUnsigned)
				sql += L" UNSIGNED";
			break;
		case IDbMigrationColumn::DataType::Decimal:
			sql += L"DECIMAL";
			if (column->iWidth > 0)
			{
				sql += L"(" + ToString(column->iWidth);
				if (column->iDigits >= 0)
					sql += L", " + ToString(column->iDigits);
				sql += L")";
			}
			if (column->bUnsigned)
				sql += L" UNSIGNED";
			break;
		case IDbMigrationColumn::DataType::Numeric:
			sql += L"NUMERIC";
			if (column->iWidth > 0)
			{
				sql += L"(" + ToString(column->iWidth);
				if (column->iDigits >= 0)
					sql += L", " + ToString(column->iDigits);
				sql += L")";
			}
			if (column->bUnsigned)
				sql += L" UNSIGNED";
			break;
		case IDbMigrationColumn::DataType::Float:
			sql += L"FLOAT";
			if (column->iWidth > 0)
			{
				sql += L"(" + ToString(column->iWidth);
				if (column->iDigits >= 0)
					sql += L", " + ToString(column->iDigits);
				sql += L")";
			}
			if (column->bUnsigned)
				sql += L" UNSIGNED";
			break;
		case IDbMigrationColumn::DataType::Double:
			sql += L"DOUBLE";
			if (column->iWidth > 0)
			{
				sql += L"(" + ToString(column->iWidth);
				if (column->iDigits >= 0)
					sql += L", " + ToString(column->iDigits);
				sql += L")";
			}
			if (column->bUnsigned)
				sql += L" UNSIGNED";
			break;
		case IDbMigrationColumn::DataType::Date:
			sql += L"DATE";
			break;
		case IDbMigrationColumn::DataType::Time:
			sql += L"TIME";
			if (column->iWidth > 0)
				sql += L"(" + ToString(column->iWidth) + L")";
			break;
		case IDbMigrationColumn::DataType::DateTime:
			sql += L"DATETIME";
			if (column->iWidth > 0)
				sql += L"(" + ToString(column->iWidth) + L")";
			break;
		case IDbMigrationColumn::DataType::TimeStamp:
			sql += L"TIMESTAMP";
			if (column->iWidth > 0)
				sql += L"(" + ToString(column->iWidth) + L")";
			break;
		case IDbMigrationColumn::DataType::Char:
			sql += L"CHAR";
			if (column->iWidth >= 0)
				sql += L"(" + ToString(column->iWidth) + L")";
			if (!column->sCharset.empty())
				sql += L" CHARACTER SET " + column->sCharset;
			if (!column->sCollation.empty())
				sql += L" COLLATE " + column->sCollation;
			break;
		case IDbMigrationColumn::DataType::VarChar:
			sql += L"VARCHAR";
			if (column->iWidth >= 0)
				sql += L"(" + ToString(column->iWidth) + L")";
			if (!column->sCharset.empty())
				sql += L" CHARACTER SET " + column->sCharset;
			if (!column->sCollation.empty())
				sql += L" COLLATE " + column->sCollation;
			break;
		case IDbMigrationColumn::DataType::Text:
			sql += L"TEXT";
			if (column->iWidth > 0)
				sql += L"(" + ToString(column->iWidth) + L")";
			if (!column->sCharset.empty())
				sql += L" CHARACTER SET " + column->sCharset;
			if (!column->sCollation.empty())
				sql += L" COLLATE " + column->sCollation;
			break;
		case IDbMigrationColumn::DataType::TinyText:
			sql += L"TINYTEXT";
			if (!column->sCharset.empty())
				sql += L" CHARACTER SET " + column->sCharset;
			if (!column->sCollation.empty())
				sql += L" COLLATE " + column->sCollation;
			break;
		case IDbMigrationColumn::DataType::MediumText:
			sql += L"MEDIUMTEXT";
			if (!column->sCharset.empty())
				sql += L" CHARACTER SET " + column->sCharset;
			if (!column->sCollation.empty())
				sql += L" COLLATE " + column->sCollation;
			break;
		case IDbMigrationColumn::DataType::LongText:
			sql += L"LONGTEXT";
			if (!column->sCharset.empty())
				sql += L" CHARACTER SET " + column->sCharset;
			if (!column->sCollation.empty())
				sql += L" COLLATE " + column->sCollation;
			break;
		case IDbMigrationColumn::DataType::Enum:
			if (column->aOptions.empty())
			{
				m_sLastError = L"Enumeration options are required";
				return false;
			}
			sql += L"ENUM(";
			for (size_t i = 0; i < column->aOptions.size(); i++)
			{
				if (i > 0)
					sql += L", ";
				sql += L"'" + ReplaceAll(column->aOptions[i], L"'", L"\\'") + L"'";
			}
			sql += L")";
			if (!column->sCharset.empty())
				sql += L" CHARACTER SET " + column->sCharset;
			if (!column->sCollation.empty())
				sql += L" COLLATE " + column->sCollation;
			break;
		case IDbMigrationColumn::DataType::Set:
			if (column->aOptions.empty())
			{
				m_sLastError = L"Set options are required";
				return false;
			}
			sql += L"SET(";
			for (size_t i = 0; i < column->aOptions.size(); i++)
			{
				if (i > 0)
					sql += L", ";
				sql += L"'" + ReplaceAll(column->aOptions[i], L"'", L"\\'") + L"'";
			}
			sql += L")";
			if (!column->sCharset.empty())
				sql += L" CHARACTER SET " + column->sCharset;
			if (!column->sCollation.empty())
				sql += L" COLLATE " + column->sCollation;
			break;
		case IDbMigrationColumn::DataType::Json:
			sql += L"JSON";
			break;
		default:
			m_sLastError = L"Column type is required";
			return false;
		}
		return true;
	}

	bool CDbQueryBuilderMySql::BuildColumnDefault(const IDbMigrationColumn *column, String &sql)
	{
		switch (column->eDataType)
		{
		case IDbMigrationColumn::DataType::Bool:
			if (column->bDefaultBoolSet)
				sql += L" DEFAULT " + (column->bDefaultBoolValue ? (String)L"TRUE" : (String)L"FALSE");
			break;
		case IDbMigrationColumn::DataType::Int:
		case IDbMigrationColumn::DataType::TinyInt:
		case IDbMigrationColumn::DataType::SmallInt:
		case IDbMigrationColumn::DataType::MediumInt:
		case IDbMigrationColumn::DataType::BigInt:
			if (column->bUnsigned)
			{
				if (column->bDefaultUIntSet)
					sql += L" DEFAULT " + ToString(column->iDefaultUIntValue);
				else if (column->bDefaultIntSet)
					sql += L" DEFAULT " + ToString(column->iDefaultIntValue);
			}
			else
			{
				if (column->bDefaultIntSet)
					sql += L" DEFAULT " + ToString(column->iDefaultIntValue);
				else if (column->bDefaultUIntSet)
					sql += L" DEFAULT " + ToString(column->iDefaultUIntValue);
			}
			break;
		case IDbMigrationColumn::DataType::Decimal:
		case IDbMigrationColumn::DataType::Numeric:
		case IDbMigrationColumn::DataType::Float:
		case IDbMigrationColumn::DataType::Double:
			if (column->bDefaultFloatSet)
				sql += L" DEFAULT " + ToStringCompact(column->fDefaultFloatValue);
			else if (column->bDefaultIntSet)
				sql += L" DEFAULT " + ToString(column->iDefaultIntValue);
			else if (column->bDefaultUIntSet)
				sql += L" DEFAULT " + ToString(column->iDefaultUIntValue);
			break;
		case IDbMigrationColumn::DataType::DateTime:
		case IDbMigrationColumn::DataType::TimeStamp:
			if (column->bDefaultStringSet)
			{
				if (column->sDefaultStringValue == L"CURRENT_TIMESTAMP")
					sql += L" DEFAULT CURRENT_TIMESTAMP";
				else
					sql += L" DEFAULT '" + ReplaceAll(column->sDefaultStringValue, L"'", L"\\'") + L"'";
			}
			break;
		case IDbMigrationColumn::DataType::Date:
		case IDbMigrationColumn::DataType::Time:
		case IDbMigrationColumn::DataType::Char:
		case IDbMigrationColumn::DataType::VarChar:
		case IDbMigrationColumn::DataType::Text:
		case IDbMigrationColumn::DataType::TinyText:
		case IDbMigrationColumn::DataType::MediumText:
		case IDbMigrationColumn::DataType::LongText:
		case IDbMigrationColumn::DataType::Enum:
		case IDbMigrationColumn::DataType::Set:
		case IDbMigrationColumn::DataType::Json:
			if (column->bDefaultStringSet)
				sql += L" DEFAULT '" + ReplaceAll(column->sDefaultStringValue, L"'", L"\\'") + L"'";
			break;
		default:
			m_sLastError = L"Column type is required";
			return false;
		}
		return true;
	}

	bool CDbQueryBuilderMySql::BuildColumn(const IDbMigrationColumn *column, String &sql)
	{
		if (column->sName.empty())
		{
			m_sLastError = L"Column name is required";
			return false;
		}
		sql = PrepareColumnName(column->sName) + L" ";
		if (!BuildColumnType(column, sql))
			return false;
		if (column->bNotNull)
			sql += L" NOT NULL";
		if (!BuildColumnDefault(column, sql))
			return false;
		if (column->bAutoIncrement)
			sql += L" AUTO_INCREMENT";
		if (column->bUnique)
			sql += L" UNIQUE";
		if (column->bPrimaryKey)
			sql += L" PRIMARY KEY";
		if (!column->sComment.empty())
			sql += L" COMMENT '" + ReplaceAll(column->sComment, L"'", L"\\'") + L"'";
		return true;
	}

	bool CDbQueryBuilderMySql::BuildKeyIndex(const IDbMigrationKey *key, String &sql)
	{
		if (key->aParts.empty())
		{
			m_sLastError = L"Key columns are required";
			return false;
		}
		sql = (key->bFullText ? L"FULLTEXT INDEX " : L"INDEX ");
		if (!key->sName.empty())
			sql += PrepareColumnName(key->sName) + L" ";
		sql += L"(";
		for (size_t i = 0; i < key->aParts.size(); i++)
		{
			if (key->aParts[i].empty())
			{
				m_sLastError = L"Column #" + ToString(int(i + 1)) + L" name is empty";
				return false;
			}
			if (i > 0)
				sql += L", ";
			sql += PrepareColumnName(key->aParts[i]);
		}
		sql += L")";
		return true;
	}

	bool CDbQueryBuilderMySql::BuildKeyPrimary(const IDbMigrationKey *key, String &sql)
	{
		if (key->aParts.empty())
		{
			m_sLastError = L"Key columns are required";
			return false;
		}
		sql = (key->sSymbol.empty() ? L"" : (L"CONSTRAINT " + PrepareColumnName(key->sSymbol) + L" ")) + L"PRIMARY KEY ";
		sql += L"(";
		for (size_t i = 0; i < key->aParts.size(); i++)
		{
			if (key->aParts[i].empty())
			{
				m_sLastError = L"Column #" + ToString(int(i + 1)) + L" name is empty";
				return false;
			}
			if (i > 0)
				sql += L", ";
			sql += PrepareColumnName(key->aParts[i]);
		}
		sql += L")";
		return true;
	}

	bool CDbQueryBuilderMySql::BuildKeyUnique(const IDbMigrationKey *key, String &sql)
	{
		if (key->aParts.empty())
		{
			m_sLastError = L"Key columns are required";
			return false;
		}
		sql = (key->sSymbol.empty() ? L"" : (L"CONSTRAINT " + PrepareColumnName(key->sSymbol) + L" ")) + L"UNIQUE ";
		if (!key->sName.empty())
			sql += PrepareColumnName(key->sName) + L" ";
		sql += L"(";
		for (size_t i = 0; i < key->aParts.size(); i++)
		{
			if (key->aParts[i].empty())
			{
				m_sLastError = L"Column #" + ToString(int(i + 1)) + L" name is empty";
				return false;
			}
			if (i > 0)
				sql += L", ";
			sql += PrepareColumnName(key->aParts[i]);
		}
		sql += L")";
		return true;
	}

	bool CDbQueryBuilderMySql::BuildKeyForeign(const IDbMigrationKey *key, String &sql)
	{
		if (key->aParts.empty())
		{
			m_sLastError = L"Key columns are required";
			return false;
		}
		if (key->sRefTable.empty())
		{
			m_sLastError = L"Key reference table is required";
			return false;
		}
		if (key->aRefParts.empty())
		{
			m_sLastError = L"Key reference columns are required";
			return false;
		}
		sql = (key->sSymbol.empty() ? L"" : (L"CONSTRAINT " + PrepareColumnName(key->sSymbol) + L" ")) + L"FOREIGN KEY ";
		if (!key->sName.empty())
			sql += PrepareColumnName(key->sName) + L" ";
		sql += L"(";
		for (size_t i = 0; i < key->aParts.size(); i++)
		{
			if (key->aParts[i].empty())
			{
				m_sLastError = L"Column #" + ToString(int(i + 1)) + L" name is empty";
				return false;
			}
			if (i > 0)
				sql += L", ";
			sql += PrepareColumnName(key->aParts[i]);
		}
		sql += L") REFERENCES " + PrepareColumnName(key->sRefTable) + L"(";
		for (size_t i = 0; i < key->aRefParts.size(); i++)
		{
			if (key->aRefParts[i].empty())
			{
				m_sLastError = L"Reference column #" + ToString(int(i + 1)) + L" name is empty";
				return false;
			}
			if (i > 0)
				sql += L", ";
			sql += PrepareColumnName(key->aRefParts[i]);
		}
		sql += L")";
		switch (key->eOnDelete)
		{
		case IDbMigrationKey::RefOption::NoAction:
			sql += L" ON DELETE NO ACTION";
			break;
		case IDbMigrationKey::RefOption::Restrict:
			sql += L" ON DELETE RESTRICT";
			break;
		case IDbMigrationKey::RefOption::Cascade:
			sql += L" ON DELETE CASCADE";
			break;
		case IDbMigrationKey::RefOption::SetNull:
			sql += L" ON DELETE SET NULL";
			break;
		case IDbMigrationKey::RefOption::SetDefault:
			sql += L" ON DELETE SET DEFAULT";
			break;
		default:
			break;
		}
		switch (key->eOnUpdate)
		{
		case IDbMigrationKey::RefOption::NoAction:
			sql += L" ON UPDATE NO ACTION";
			break;
		case IDbMigrationKey::RefOption::Restrict:
			sql += L" ON UPDATE RESTRICT";
			break;
		case IDbMigrationKey::RefOption::Cascade:
			sql += L" ON UPDATE CASCADE";
			break;
		case IDbMigrationKey::RefOption::SetNull:
			sql += L" ON UPDATE SET NULL";
			break;
		case IDbMigrationKey::RefOption::SetDefault:
			sql += L" ON UPDATE SET DEFAULT";
			break;
		default:
			break;
		}
		return true;
	}

	bool CDbQueryBuilderMySql::BuildKey(const IDbMigrationKey *key, String &sql)
	{
		switch (key->eType)
		{
		case IDbMigrationKey::Type::Index:
			return BuildKeyIndex(key, sql);
		case IDbMigrationKey::Type::Primary:
			return BuildKeyPrimary(key, sql);
		case IDbMigrationKey::Type::Unique:
			return BuildKeyUnique(key, sql);
		case IDbMigrationKey::Type::Foreign:
			return BuildKeyForeign(key, sql);
		default:
			m_sLastError = L"Unsupported key type";
			return false;
		}
	}
#pragma endregion
}