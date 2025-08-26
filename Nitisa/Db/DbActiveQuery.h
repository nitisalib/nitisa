// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "../Core/ErrorInfo.h"
#include "../Core/Releasable.h"
#include "../Core/ReleasablePtr.h"
#include "../Core/Strings.h"
#include "../Interfaces/IDbConnection.h"
#include "../Interfaces/IDbQuery.h"
#include "../Interfaces/IDbQueryBuilder.h"
#include "../Interfaces/IDbRelation.h"
#include "../Interfaces/IDbStatement.h"
#include "../Interfaces/IErrorListener.h"
#include "DbCondition.h"
#include "DbExceptionBuildQuery.h"
#include "DbExceptionCreateStatement.h"
#include "DbExceptionExecuteStatement.h"
#include "DbExceptionNoConnection.h"
#include "DbExceptionNoQueryBuilder.h"
#include "DbExceptionNoResult.h"
#include "DbExceptionQueryPrimaryKeys.h"
#include "DbExceptionRelationNotFound.h"
#include "DbOrder.h"
#include "DbOrderByArray.h"
#include "DbResult.h"
#include "DbRow.h"
#include "DbRows.h"
#include "DbSchema.h"
#include "DbValue.h"
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace nitisa
{
	template<class Type>
	class TDbActiveQuery :public virtual IDbQuery, public CReleasable
	{
	private:
		using Model = ReleasablePtr<Type>;
		using Models = std::vector<Model>;

		class CErrorListener :public virtual IErrorListener
		{
		public:
			String Error;

			void NotifyOnError(const AnsiString &function, const int line, const ErrorInfo &info, const StringKeyValueArray &args = EmptyStringKeyValueArray) override
			{
				Error = L"ERROR " + ToString(info.Code) + L" in " + AnsiToString(function) + L":" + ToString(line) + L": " + ReplaceAll(info.Message, args);
			}
		};

		class CConnectionErrorListenerLock
		{
		private:
			IDbConnection *m_pConnection;
			IErrorListener *m_pOld;
		public:
			CConnectionErrorListenerLock(IDbConnection *connection, IErrorListener *listener) :
				m_pConnection{ connection },
				m_pOld{ connection->ErrorListener }
			{
				m_pConnection->setErrorListener(listener);
			}

			~CConnectionErrorListenerLock()
			{
				m_pConnection->setErrorListener(m_pOld);
			}
		};

		class CStatementErrorListenerLock
		{
		private:
			IDbStatement *m_pStatement;
			IErrorListener *m_pOld;
		public:
			CStatementErrorListenerLock(IDbStatement *statement, IErrorListener *listener) :
				m_pStatement{ statement },
				m_pOld{ statement->ErrorListener }
			{
				m_pStatement->setErrorListener(listener);
			}

			~CStatementErrorListenerLock()
			{
				m_pStatement->setErrorListener(m_pOld);
			}
		};
	private:
		CErrorListener m_cErrorListener;

		void LoadRelations(std::vector<CDbBaseActiveRecord *> &models, const StringArray &with)
		{
			std::unordered_set<String> names;
			std::unordered_map<String, StringArray> new_with;
			for (auto w : with)
			{
				StringArray parts{ Explode(w, L".") };
				if (parts.size() > 0)
				{
					String part{ Trim(parts[0]) };
					if (!part.empty())
						names.insert(part);
					if (parts.size() > 1)
					{
						parts.erase(parts.begin());
						new_with[part].push_back(Implode(L".", parts));
					}
				}
			}
			if (names.empty())
				return;
			IDbRelation *relation;
			for (auto name : names)
			{
				if (!(relation = models[0]->getRelation(name)))
					throw DbExceptionRelationNotFound(models[0]->getTable(), name);
				std::vector<CDbBaseActiveRecord *> out_models;
				Relation_LoadRelations(relation, models, out_models);
				if (!out_models.empty() && !new_with[name].empty())
					LoadRelations(out_models, new_with[name]);
			}
		}
	public:
	#pragma region Constructor & destructor
		TDbActiveQuery() :
			CReleasable()
		{
			m_bDistinct = false;
			m_iLimit = -1;
			m_iOffset = -1;
		}
	#pragma endregion

	#pragma region Query building
		TDbActiveQuery *Select(const String &column) // Add column to be selected from DB
		{
			if (!column.empty())
				m_aSelect.push_back(StringKeyValue{ column, L"" });
			return this;
		}

		TDbActiveQuery *Select(const String &column, const String &alias) // Add column with alias to be selected from DB
		{
			if (!column.empty())
				m_aSelect.push_back(StringKeyValue{ column, alias });
			return this;
		}

		TDbActiveQuery *Select(const StringKeyValue &column) // Add column with alias to be selected from DB
		{
			if (!column.first.empty())
				m_aSelect.push_back(column);
			return this;
		}

		TDbActiveQuery *Select(const StringArray &columns) // Add columns to be selected from DB
		{
			for (auto const &column : columns)
				if (!column.empty())
					m_aSelect.push_back(StringKeyValue{ column, L"" });
			return this;
		}

		TDbActiveQuery *Select(const StringKeyValueArray &columns) // Add columns with alias to be selected from DB
		{
			for (auto const &column : columns)
				if (!column.first.empty())
					m_aSelect.push_back(column);
			return this;
		}

		TDbActiveQuery *Distinct(const bool &value) // Sets whether only unique values should be selected
		{
			m_bDistinct = value;
			return this;
		}

		TDbActiveQuery *From(const String &table) // Add table from which data is to be selected
		{
			if (!table.empty())
				m_aFrom.push_back(StringKeyValue{ table, L"" });
			return this;
		}

		TDbActiveQuery *From(const String &table, const String &alias) // Add table with alias from which data is to be selected
		{
			if (!table.empty())
				m_aFrom.push_back(StringKeyValue{ table, alias });
			return this;
		}

		TDbActiveQuery *From(const StringArray &tables) // Add tables from which data is to be selected
		{
			for (auto const &table : tables)
				if (!table.empty())
					m_aFrom.push_back(StringKeyValue{ table, L"" });
			return this;
		}

		TDbActiveQuery *From(const StringKeyValueArray &tables) // Add tables with aliases from which data is to be selected
		{
			for (auto const &table : tables)
				if (!table.first.empty())
					m_aFrom.push_back(table);
			return this;
		}

		TDbActiveQuery *InnerJoin(const String &table, DbCondition on) // Add inner join table condition
		{
			if (!table.empty())
				m_aInnerJoins.push_back(DbJoin{ table, L"", on });
			return this;
		}

		TDbActiveQuery *InnerJoin(const String &table, const String &alias, DbCondition on) // Add inner join table with alias condition
		{
			if (!table.empty())
				m_aInnerJoins.push_back(DbJoin{ table, alias, on });
			return this;
		}

		TDbActiveQuery *InnerJoin(const DbJoin &table) // Add inner join table
		{
			m_aInnerJoins.push_back(table);
			return this;
		}

		TDbActiveQuery *LeftJoin(const String &table, DbCondition on) // Add left join table condition
		{
			if (!table.empty())
				m_aLeftJoins.push_back(DbJoin{ table, L"", on });
			return this;
		}

		TDbActiveQuery *LeftJoin(const String &table, const String &alias, DbCondition on) // Add left join table with alias condition
		{
			if (!table.empty())
				m_aLeftJoins.push_back(DbJoin{ table, alias, on });
			return this;
		}

		TDbActiveQuery *LeftJoin(const DbJoin &table) // Add left join table
		{
			m_aLeftJoins.push_back(table);
			return this;
		}

		TDbActiveQuery *RightJoin(const String &table, DbCondition on) // Add right join table condition
		{
			if (!table.empty())
				m_aRightJoins.push_back(DbJoin{ table, L"", on });
			return this;
		}

		TDbActiveQuery *RightJoin(const String &table, const String &alias, DbCondition on) // Add right join table with alias condition
		{
			if (!table.empty())
				m_aRightJoins.push_back(DbJoin{ table, alias, on });
			return this;
		}

		TDbActiveQuery *RightJoin(const DbJoin &table) // Add right join table
		{
			m_aRightJoins.push_back(table);
			return this;
		}

		TDbActiveQuery *Where(DbCondition condition) // Set query condition
		{
			m_pWhere = condition;
			return this;
		}

		TDbActiveQuery *Where(const DbConditions &conditions) // Set query conditions joined by AND operator
		{
			m_pWhere = nullptr;
			for (auto condition : conditions)
				AndWhere(condition);
			return this;
		}

		TDbActiveQuery *AndWhere(DbCondition condition) // Add query condition joining by AND operator
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

		TDbActiveQuery *OrWhere(DbCondition condition) // Add query condition joining by OR operator
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

		TDbActiveQuery *GroupBy(const String &column) // Add grouping by column
		{
			if (!column.empty())
				m_aGroupBy.push_back(column);
			return this;
		}

		TDbActiveQuery *GroupBy(const StringArray &columns) // Add grouping by columns
		{
			for (auto const &column : columns)
				if (!column.empty())
					m_aGroupBy.push_back(column);
			return this;
		}

		TDbActiveQuery *Having(DbCondition condition) // Set filter condition
		{
			m_pHaving = condition;
			return this;
		}

		TDbActiveQuery *Having(const DbConditions &conditions) // Set filter conditions joining by AND operator
		{
			m_pHaving = nullptr;
			for (auto condition : conditions)
				AndHaving(condition);
			return this;
		}

		TDbActiveQuery *AndHaving(DbCondition condition) // Add filter condition joining by AND operator
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

		TDbActiveQuery *OrHaving(DbCondition condition) // Add filter condition joining by OR operator
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

		TDbActiveQuery *OrderBy(const String &column, const DbOrder &order) // Add ordering by column
		{
			if (!column.empty())
				m_aOrderBy.push_back(DbOrderBy{ column, order });
			return this;
		}

		TDbActiveQuery *OrderBy(const DbOrderByArray &columns) // Add ordering by columns
		{
			for (auto const &column : columns)
				if (!column.first.empty())
					m_aOrderBy.push_back(column);
			return this;
		}

		TDbActiveQuery *Limit(const int64 &limit = -1) // Set result maximum allowed record count. -1 means no limit or all records will be returned
		{
			m_iLimit = limit;
			return this;
		}

		TDbActiveQuery *Offset(const int64 &offset = -1) // Set result offset or at which record start to get records. -1 means no offset or from the beginning
		{
			m_iOffset = offset;
			return this;
		}

		TDbActiveQuery *Union(ReleasablePtr<IDbQuery> query, const bool all = false) // Set union query
		{
			if (query)
				m_aUnions.push_back(DbUnion{ query, all });
			return this;
		}

		TDbActiveQuery *With(const String &relation) // Add relation(s) to load
		{
			m_aWith.push_back(relation);
			return this;
		}

		TDbActiveQuery *With(const StringArray &relations) // Set relation(s) to load
		{
			m_aWith = relations;
			return this;
		}
	#pragma endregion

	#pragma region Query result
		DbValue Column() // Executes the query and returns the first column of the result. Throw exceptions in case of error
		{
			Type ar_model;

			// Check connection
			if (!ar_model.getStatement() && !ar_model.getConnection())
				throw DbExceptionNoConnection();

			// Check query builder
			IDbQueryBuilder *query_builder{ ar_model.getQueryBuilder() };
			if (!query_builder)
				throw DbExceptionNoQueryBuilder();

			// Prepare raw query
			if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
				From(ar_model.getTable());
			String query;
			int64 old_limit{ m_iLimit };
			m_iLimit = 1;
			if (!query_builder->Select(this, query))
			{
				m_iLimit = old_limit;
				throw DbExceptionBuildQuery(query_builder->LastError);
			}
			m_iLimit = old_limit;

			// Prepare statement
			ReleasablePtr<IDbStatement> statement;
			if (!ar_model.getStatement())
			{
				CConnectionErrorListenerLock e_lock{ ar_model.getConnection(), &m_cErrorListener };
				statement = ar_model.getConnection()->CreateStatement();
				if (!statement)
					throw DbExceptionCreateStatement(m_cErrorListener.Error);
			}
			else
			{
				statement = ar_model.getStatement();
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

		int64 Count(const String &column = L"*") // Returns the number of records. Throw exceptions in case of error
		{
			Type ar_model;

			// Check connection
			if (!ar_model.getStatement() && !ar_model.getConnection())
				throw DbExceptionNoConnection();

			// Check query builder
			IDbQueryBuilder *query_builder{ ar_model.getQueryBuilder() };
			if (!query_builder)
				throw DbExceptionNoQueryBuilder();

			// Prepare raw query
			if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
				From(ar_model.getTable());
			String query;
			if (!query_builder->Count(this, column, query))
				throw DbExceptionBuildQuery(query_builder->LastError);

			// Prepare statement
			ReleasablePtr<IDbStatement> statement;
			if (!ar_model.getStatement())
			{
				CConnectionErrorListenerLock e_lock{ ar_model.getConnection(), &m_cErrorListener };
				statement = ar_model.getConnection()->CreateStatement();
				if (!statement)
					throw DbExceptionCreateStatement(m_cErrorListener.Error);
			}
			else
			{
				statement = ar_model.getStatement();
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

		bool Exists() // Return whether there is any records in query stored in this object or not. Throw exceptions in case of error
		{
			Type ar_model;

			// Check connection
			if (!ar_model.getStatement() && !ar_model.getConnection())
				throw DbExceptionNoConnection();

			// Check query builder
			IDbQueryBuilder *query_builder{ ar_model.getQueryBuilder() };
			if (!query_builder)
				throw DbExceptionNoQueryBuilder();

			// Prepare raw query
			if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
				From(ar_model.getTable());
			String query;
			if (!query_builder->Exists(this, query))
				throw DbExceptionBuildQuery(query_builder->LastError);

			// Prepare statement
			ReleasablePtr<IDbStatement> statement;
			if (!ar_model.getStatement())
			{
				CConnectionErrorListenerLock e_lock{ ar_model.getConnection(), &m_cErrorListener };
				statement = ar_model.getConnection()->CreateStatement();
				if (!statement)
					throw DbExceptionCreateStatement(m_cErrorListener.Error);
			}
			else
			{
				statement = ar_model.getStatement();
				statement->AddRef();
			}
			CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };

			// Execute statement
			DbResult result{ statement->Execute(query) };
			if (!result.Successful)
				throw DbExceptionExecuteStatement(m_cErrorListener.Error);
			if (result.Rows.empty() || result.Rows[0].empty())
				throw DbExceptionNoResult();

			return (bool)result.Rows[0][0];
		}

		template<class ScalarType>
		ScalarType Scalar(const String &column) // Returns the query result as a scalar value. Throw exceptions in case of error
		{
			Type ar_model;

			// Check connection
			if (!ar_model.getStatement() && !ar_model.getConnection())
				throw DbExceptionNoConnection();

			// Check query builder
			IDbQueryBuilder *query_builder{ ar_model.getQueryBuilder() };
			if (!query_builder)
				throw DbExceptionNoQueryBuilder();

			// Prepare raw query
			if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
				From(ar_model.getTable());
			String query;
			int64 old_limit{ m_iLimit };
			m_iLimit = 1;
			if (!query_builder->Scalar(this, column, query))
			{
				m_iLimit = old_limit;
				throw DbExceptionBuildQuery(query_builder->LastError);
			}
			m_iLimit = old_limit;

			// Prepare statement
			ReleasablePtr<IDbStatement> statement;
			if (!ar_model.getStatement())
			{
				CConnectionErrorListenerLock e_lock{ ar_model.getConnection(), &m_cErrorListener };
				statement = ar_model.getConnection()->CreateStatement();
				if (!statement)
					throw DbExceptionCreateStatement(m_cErrorListener.Error);
			}
			else
			{
				statement = ar_model.getStatement();
				statement->AddRef();
			}
			CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };

			// Execute statement
			DbResult result{ statement->Execute(query) };
			if (!result.Successful)
				throw DbExceptionExecuteStatement(m_cErrorListener.Error);
			if (result.Rows.empty() || result.Rows[0].empty())
				throw DbExceptionNoResult();

			return (ScalarType)result.Rows[0][0];
		}

		template<class ResultType>
		ResultType Sum(const String &column) // Returns the sum of the specified column values. Throw exceptions in case of error
		{
			Type ar_model;

			// Check connection
			if (!ar_model.getStatement() && !ar_model.getConnection())
				throw DbExceptionNoConnection();

			// Check query builder
			IDbQueryBuilder *query_builder{ ar_model.getQueryBuilder() };
			if (!query_builder)
				throw DbExceptionNoQueryBuilder();

			// Prepare raw query
			if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
				From(ar_model.getTable());
			String query;
			if (!query_builder->Sum(this, column, query))
				throw DbExceptionBuildQuery(query_builder->LastError);

			// Prepare statement
			ReleasablePtr<IDbStatement> statement;
			if (!ar_model.getStatement())
			{
				CConnectionErrorListenerLock e_lock{ ar_model.getConnection(), &m_cErrorListener };
				statement = ar_model.getConnection()->CreateStatement();
				if (!statement)
					throw DbExceptionCreateStatement(m_cErrorListener.Error);
			}
			else
			{
				statement = ar_model.getStatement();
				statement->AddRef();
			}
			CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };

			// Execute statement
			DbResult result{ statement->Execute(query) };
			if (!result.Successful)
				throw DbExceptionExecuteStatement(m_cErrorListener.Error);
			if (result.Rows.empty() || result.Rows[0].empty())
				throw DbExceptionNoResult();

			return (ResultType)result.Rows[0][0];
		}

		template<class ResultType>
		ResultType Average(const String &column) // Returns the average of the specified column values. Throw exceptions in case of error
		{
			Type ar_model;

			// Check connection
			if (!ar_model.getStatement() && !ar_model.getConnection())
				throw DbExceptionNoConnection();

			// Check query builder
			IDbQueryBuilder *query_builder{ ar_model.getQueryBuilder() };
			if (!query_builder)
				throw DbExceptionNoQueryBuilder();

			// Prepare raw query
			if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
				From(ar_model.getTable());
			String query;
			if (!query_builder->Average(this, column, query))
				throw DbExceptionBuildQuery(query_builder->LastError);

			// Prepare statement
			ReleasablePtr<IDbStatement> statement;
			if (!ar_model.getStatement())
			{
				CConnectionErrorListenerLock e_lock{ ar_model.getConnection(), &m_cErrorListener };
				statement = ar_model.getConnection()->CreateStatement();
				if (!statement)
					throw DbExceptionCreateStatement(m_cErrorListener.Error);
			}
			else
			{
				statement = ar_model.getStatement();
				statement->AddRef();
			}
			CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };

			// Execute statement
			DbResult result{ statement->Execute(query) };
			if (!result.Successful)
				throw DbExceptionExecuteStatement(m_cErrorListener.Error);
			if (result.Rows.empty() || result.Rows[0].empty())
				throw DbExceptionNoResult();

			return (ResultType)result.Rows[0][0];
		}

		template<class ResultType>
		ResultType Min(const String &column) // Returns the minimum of the specified column values. Throw exceptions in case of error
		{
			Type ar_model;

			// Check connection
			if (!ar_model.getStatement() && !ar_model.getConnection())
				throw DbExceptionNoConnection();

			// Check query builder
			IDbQueryBuilder *query_builder{ ar_model.getQueryBuilder() };
			if (!query_builder)
				throw DbExceptionNoQueryBuilder();

			// Prepare raw query
			if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
				From(ar_model.getTable());
			String query;
			if (!query_builder->Min(this, column, query))
				throw DbExceptionBuildQuery(query_builder->LastError);

			// Prepare statement
			ReleasablePtr<IDbStatement> statement;
			if (!ar_model.getStatement())
			{
				CConnectionErrorListenerLock e_lock{ ar_model.getConnection(), &m_cErrorListener };
				statement = ar_model.getConnection()->CreateStatement();
				if (!statement)
					throw DbExceptionCreateStatement(m_cErrorListener.Error);
			}
			else
			{
				statement = ar_model.getStatement();
				statement->AddRef();
			}
			CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };

			// Execute statement
			DbResult result{ statement->Execute(query) };
			if (!result.Successful)
				throw DbExceptionExecuteStatement(m_cErrorListener.Error);
			if (result.Rows.empty() || result.Rows[0].empty())
				throw DbExceptionNoResult();

			return (ResultType)result.Rows[0][0];
		}

		template<class ResultType>
		ResultType Max(const String &column) // Returns the maximum of the specified column values. Throw exceptions in case of error
		{
			Type ar_model;

			// Check connection
			if (!ar_model.getStatement() && !ar_model.getConnection())
				throw DbExceptionNoConnection();

			// Check query builder
			IDbQueryBuilder *query_builder{ ar_model.getQueryBuilder() };
			if (!query_builder)
				throw DbExceptionNoQueryBuilder();

			// Prepare raw query
			if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
				From(ar_model.getTable());
			String query;
			if (!query_builder->Max(this, column, query))
				throw DbExceptionBuildQuery(query_builder->LastError);

			// Prepare statement
			ReleasablePtr<IDbStatement> statement;
			if (!ar_model.getStatement())
			{
				CConnectionErrorListenerLock e_lock{ ar_model.getConnection(), &m_cErrorListener };
				statement = ar_model.getConnection()->CreateStatement();
				if (!statement)
					throw DbExceptionCreateStatement(m_cErrorListener.Error);
			}
			else
			{
				statement = ar_model.getStatement();
				statement->AddRef();
			}
			CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };

			// Execute statement
			DbResult result{ statement->Execute(query) };
			if (!result.Successful)
				throw DbExceptionExecuteStatement(m_cErrorListener.Error);
			if (result.Rows.empty() || result.Rows[0].empty())
				throw DbExceptionNoResult();

			return (ResultType)result.Rows[0][0];
		}

		Models All() // Executes the query and returns all unique (by primary key) results as model array. Throw exceptions in case of error
		{
			Type ar_model;

			// Check connection
			if (!ar_model.getStatement() && !ar_model.getConnection())
				throw DbExceptionNoConnection();

			// Check query builder
			IDbQueryBuilder *query_builder{ ar_model.getQueryBuilder() };
			if (!query_builder)
				throw DbExceptionNoQueryBuilder();

			// Prepare raw query
			if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
				From(ar_model.getTable());
			String query;
			if (!query_builder->Select(this, query))
				throw DbExceptionBuildQuery(query_builder->LastError);

			// Prepare statement
			ReleasablePtr<IDbStatement> statement;
			if (!ar_model.getStatement())
			{
				CConnectionErrorListenerLock e_lock{ ar_model.getConnection(), &m_cErrorListener };
				statement = ar_model.getConnection()->CreateStatement();
				if (!statement)
					throw DbExceptionCreateStatement(m_cErrorListener.Error);
			}
			else
			{
				statement = ar_model.getStatement();
				statement->AddRef();
			}
			CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };

			// Get primary key columns
			DbSchema::PrimaryKey pk_columns;
			if (!DbSchema::getPrimaryKey(ar_model.getTable(), statement, ar_model.getQueryBuilder(), pk_columns, false))
				throw DbExceptionQueryPrimaryKeys(m_cErrorListener.Error);

			// Prepare and execute statement
			statement->setRetrieveColumnName(true);
			statement->setRetrieveColumnAlias(true);
			DbResult result{ statement->Execute(query) };
			if (!result.Successful)
				throw DbExceptionExecuteStatement(m_cErrorListener.Error);
			if (result.Rows.empty())
				return Models{ };

			// Prepare column->attribute mapping
			std::vector<std::pair<size_t, size_t>> mapping;
			size_t attribute_index{ 0 };
			for (auto attribute : ar_model.Attributes)
			{
				size_t column_index{ 0 };
				for (auto const &column : result.Columns)
				{
					if (column.Name == attribute->sName || column.Alias == attribute->sName)
					{
						mapping.push_back(std::pair<size_t, size_t>{ attribute_index, column_index });
						break;
					}
					column_index++;
				}
				attribute_index++;
			}

			// Prepare column->pk mapping
			std::vector<size_t> pk_mapping;
			for (auto const &pk_column : pk_columns.Columns)
			{
				size_t column_index{ 0 }, index{ (size_t)-1 };
				for (auto const &column : result.Columns)
				{
					if (column.Name == pk_column || column.Alias == pk_column)
					{
						index = column_index;
						break;
					}
					column_index++;
				}
				pk_mapping.push_back(index);
			}

			bool duplicates_possible{ !m_aInnerJoins.empty() || !m_aLeftJoins.empty() || !m_aRightJoins.empty() || !m_aUnions.empty() };

			// Create result array
			Models models;
			for (size_t row_index = 0; row_index < result.Rows.size(); row_index++)
			{
				// Populate primary key
				DbActiveRecordPrimaryKey pk;
				for (size_t index = 0; index < pk_mapping.size(); index++)
					if (pk_mapping[index] == (size_t)-1)
						pk.push_back(std::pair<String, DbValue>{ pk_columns.Columns[index], DbValue{ } });
					else
						pk.push_back(std::pair<String, DbValue>{ pk_columns.Columns[index], result.Rows[row_index][pk_mapping[index]] });
				// Check whether a model with the same primary key already exists
				if (duplicates_possible)
				{
					bool found{ false };
					for (auto model : models)
						if (model->getPrimaryKey() == pk)
						{
							found = true;
							break;
						}
					if (found)
						continue;
				}
				// Add model in list and set its attributes
				Type *model{ new Type() };
				models.push_back(model);
				for (auto const &map : mapping)
					setAttributeValue(model->Attributes[map.first], result.Rows[row_index][map.second]);
				setActiveRecordNew(model, false);
				setActiveRecordPrimaryKey(model, pk);
				model->AfterLoad();
			}

			// Load relations
			if (!models.empty() && !m_aWith.empty())
			{
				std::vector<CDbBaseActiveRecord *> list;
				for (auto model : models)
					list.push_back(model);
				LoadRelations(list, m_aWith);
			}

			return models;
		}

		Model One() // Executes the query and returns a single row of result as a model. Throw exceptions in case of error
		{
			Model ar_model{ new Type() };

			// Check connection
			if (!ar_model->getStatement() && !ar_model->getConnection())
				throw DbExceptionNoConnection();

			// Check query builder
			IDbQueryBuilder *query_builder{ ar_model->getQueryBuilder() };
			if (!query_builder)
				throw DbExceptionNoQueryBuilder();

			// Prepare raw query
			if (m_aFrom.empty()) // If no custom "from" part of the query is specified, add ActiveRecord model table to it
				From(ar_model->getTable());
			int64 old_limit{ m_iLimit };
			m_iLimit = 1;
			String query;
			if (!query_builder->Select(this, query))
			{
				m_iLimit = old_limit;
				throw DbExceptionBuildQuery(query_builder->LastError);
			}
			m_iLimit = old_limit;

			// Prepare statement
			ReleasablePtr<IDbStatement> statement;
			if (!ar_model->getStatement())
			{
				CConnectionErrorListenerLock e_lock{ ar_model->getConnection(), &m_cErrorListener };
				statement = ar_model->getConnection()->CreateStatement();
				if (!statement)
					throw DbExceptionCreateStatement(m_cErrorListener.Error);
			}
			else
			{
				statement = ar_model->getStatement();
				statement->AddRef();
			}
			CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };

			// Get primary key columns
			DbSchema::PrimaryKey pk_columns;
			if (!DbSchema::getPrimaryKey(ar_model->getTable(), statement, ar_model->getQueryBuilder(), pk_columns, false))
				throw DbExceptionQueryPrimaryKeys(m_cErrorListener.Error);

			// Prepare and execute statement
			statement->setRetrieveColumnName(true);
			statement->setRetrieveColumnAlias(true);
			DbResult result{ statement->Execute(query) };
			if (!result.Successful)
				throw DbExceptionExecuteStatement(m_cErrorListener.Error);
			if (result.Rows.empty())
				return nullptr;

			// Prepare column->attribute mapping
			std::vector<std::pair<size_t, size_t>> mapping;
			size_t attribute_index{ 0 };
			for (auto attribute : ar_model->Attributes)
			{
				size_t column_index{ 0 };
				for (auto const &column : result.Columns)
				{
					if (column.Name == attribute->sName || column.Alias == attribute->sName)
					{
						mapping.push_back(std::pair<size_t, size_t>{ attribute_index, column_index });
						break;
					}
					column_index++;
				}
				attribute_index++;
			}

			// Prepare column->pk mapping
			std::vector<size_t> pk_mapping;
			for (auto const &pk_column : pk_columns.Columns)
			{
				size_t column_index{ 0 }, index{ (size_t)-1 };
				for (auto const &column : result.Columns)
				{
					if (column.Name == pk_column || column.Alias == pk_column)
					{
						index = column_index;
						break;
					}
					column_index++;
				}
				pk_mapping.push_back(index);
			}

			// Populate primary key
			DbActiveRecordPrimaryKey pk;
			for (size_t index = 0; index < pk_mapping.size(); index++)
				if (pk_mapping[index] == (size_t)-1)
					pk.push_back(std::pair<String, DbValue>{ pk_columns.Columns[index], DbValue{ } });
				else
					pk.push_back(std::pair<String, DbValue>{ pk_columns.Columns[index], result.Rows[0][pk_mapping[index]] });
			// Add model in list and set its attributes
			for (auto const &map : mapping)
				setAttributeValue(ar_model->Attributes[map.first], result.Rows[0][map.second]);
			setActiveRecordNew(ar_model, false);
			setActiveRecordPrimaryKey(ar_model, pk);
			ar_model->AfterLoad();

			// Load relations
			if (!m_aWith.empty())
			{
				std::vector<CDbBaseActiveRecord *> models{ ar_model };
				LoadRelations(models, m_aWith);
			}

			return ar_model;
		}
	#pragma endregion
	};
}