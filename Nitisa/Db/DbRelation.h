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
#include "../Interfaces/IDbConnection.h"
#include "../Interfaces/IDbQuery.h"
#include "../Interfaces/IDbQueryBuilder.h"
#include "../Interfaces/IDbRelation.h"
#include "../Interfaces/IDbStatement.h"
#include "../Interfaces/IErrorListener.h"
#include "DbActiveQuery.h"
#include "DbBaseActiveRecord.h"
#include "DbCondition.h"
#include "DbExceptionBuildQuery.h"
#include "DbExceptionCreateStatement.h"
#include "DbExceptionExecuteStatement.h"
#include "DbExceptionNoConnection.h"
#include "DbExceptionNoQueryBuilder.h"
#include "DbExceptionQueryPrimaryKeys.h"
#include "DbExceptionRelationNotFound.h"
#include "DbOrder.h"
#include "DbOrderByArray.h"
#include "DbQuery.h"
#include "DbSchema.h"
#include "DbValue.h"
#include <vector>

namespace nitisa
{
	template<class Model>
	class TDbRelation :public virtual IDbRelation, public CReleasable
	{
	private:
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
		CDbBaseActiveRecord *m_pParent;
		String m_sParentAttribute;
		String m_sRelationAttribute;
		String m_sLinkTable;
		String m_sLinkParentAttribute;
		String m_sLinkRelationAttribute;
		bool m_bMany;
		bool m_bLoaded;
		std::vector<ReleasablePtr<Model>> m_aModels;
		// Query building
		StringKeyValueArray m_aSelect; // [{ column|expression, alias }, ...]
		bool m_bDistinct;
		StringKeyValueArray m_aFrom; // [{ table, alias }, ...]
		IDbQuery::DbJoins m_aInnerJoins; // [ { { table, alias }, on_condition }, ...]
		IDbQuery::DbJoins m_aLeftJoins; // [ { { table, alias }, on_condition }, ...]
		IDbQuery::DbJoins m_aRightJoins; // [ { { table, alias }, on_condition }, ...]
		DbCondition m_pWhere;
		StringArray m_aGroupBy;
		DbCondition m_pHaving;
		DbOrderByArray m_aOrderBy;
		int64 m_iLimit;
		int64 m_iOffset;

		bool isManyToMany() const
		{
			return !m_sLinkTable.empty() && !m_sLinkParentAttribute.empty() && !m_sLinkRelationAttribute.empty();
		}

		void MergeQuery(TDbActiveQuery<Model> &target)
		{
			target.Select(m_aSelect);
			target.Distinct(m_bDistinct);
			target.From(m_aFrom);
			for (auto join : m_aInnerJoins)
				target.InnerJoin(join);
			for (auto join : m_aLeftJoins)
				target.LeftJoin(join);
			for (auto join : m_aRightJoins)
				target.RightJoin(join);
			if (m_pWhere)
				target.AndWhere(m_pWhere);
			target.GroupBy(m_aGroupBy);
			if (m_pHaving)
				target.AndHaving(m_pHaving);
			target.OrderBy(m_aOrderBy);
			target.Limit(m_iLimit);
			target.Offset(m_iOffset);
		}

		void MergeQuery(CDbQuery &target)
		{
			target.Select(m_aSelect);
			target.Distinct(m_bDistinct);
			target.From(m_aFrom);
			for (auto join : m_aInnerJoins)
				target.InnerJoin(join);
			for (auto join : m_aLeftJoins)
				target.LeftJoin(join);
			for (auto join : m_aRightJoins)
				target.RightJoin(join);
			if (m_pWhere)
				target.AndWhere(m_pWhere);
			target.GroupBy(m_aGroupBy);
			if (m_pHaving)
				target.AndHaving(m_pHaving);
			target.OrderBy(m_aOrderBy);
			target.Limit(m_iLimit);
			target.Offset(m_iOffset);
		}

		void Load()
		{
			// Example 1: One-to-One
			// Parent model: Post (id, title, author_id)
			// Relation model: Author (id, name)
			// SELECT * FROM author WHERE id = {post.AuthorId} LIMIT 1
			// ParentAttribute = "author_id" - attribute where related model id value is stored
			// RelationAttribute = "id" - related model id to be searched by
			// SELECT * FROM {TRelation.Table} WHERE {RelationAttribute} = {Parent->AttributeValue(ParentAttribute)}
			// 
			// Example 2: One-to-Many
			// Parent model: Author (id, name)
			// Relation model: Post (id, title, author_id)
			// SELECT * FROM post WHERE author_id = {Id}
			// ParentAttribute = "id" - attribute where related model id value is stored
			// RelationAttribute = "author_id" - related model id to be searched by
			// SELECT * FROM {TRelation.Table} WHERE {RelationAttribute} = {Parent->AttributeValue(ParentAttribute)}
			// 
			// Example 3: Many-to-Many
			// Parent model: Category (id, name)
			// Relation model: Post (id, title)
			// Link table: PostCategory (id, post_id, category_id)
			// SELECT * FROM post INNER JOIN post_category ON post_category.post_id = post.id WHERE post_category.category_id = {id}
			// ParentAttribute: "id"
			// RelationAttribute: "id"
			// Link: { Table: "post_category", ParentAttribute: "category_id", RelationAttribute: "post_id" }
			// SELECT * FROM {TRelation.Table}
			//		INNER JOIN {LinkTable} ON {LinkTable}.{LinkRelationAttribute} = {TRelation.Table}.{RelationAttribute}
			//		WHERE {LinkTable}.{LinkParentAttribute} = {Parent->AttributeValue(ParentAttribute)}

			m_bLoaded = true;
			TDbActiveQuery<Model> query;
			if (isManyToMany())
			{
				Model m;
				query.InnerJoin(m_sLinkTable, db::eqcc(m_sLinkTable + L"." + m_sLinkRelationAttribute, m.getTable() + L"." + m_sRelationAttribute));
				query.Where(db::eqcv(m_sLinkTable + L"." + m_sLinkParentAttribute, m_pParent->getAttribute(m_sParentAttribute)));
			}
			else
				query.Where(db::eqcv(m_sRelationAttribute, m_pParent->getAttribute(m_sParentAttribute)));
			if (!m_aOrderBy.empty())
				query.OrderBy(m_aOrderBy);
			MergeQuery(query);
			if (!m_bMany)
			{
				m_aModels.clear();
				ReleasablePtr<Model> model{ query.One() };
				if (model)
					m_aModels.push_back(model);
			}
			else
				m_aModels = query.All();
		}

		static bool CompareAsInt64(const DbRow &a, const DbRow &b)
		{
			return (int64)a[0] < (int64)b[0];
		}

		static bool CompareAsUInt64(const DbRow &a, const DbRow &b)
		{
			return (uint64)a[0] < (uint64)b[0];
		}

		static bool CompareAsDouble(const DbRow &a, const DbRow &b)
		{
			return (double)a[0] < (double)b[0];
		}

		static bool CompareAsString(const DbRow &a, const DbRow &b)
		{
			return (String)a[0] < (String)b[0];
		}

		using FCompare = bool(*)(const DbRow &a, const DbRow &b);
	protected:
		void LoadRelations(std::vector<CDbBaseActiveRecord *> &parent_models, std::vector<CDbBaseActiveRecord *> &out_models) override
		{
			Model relation_model;

			// Check connection
			if (!relation_model.getStatement() && !relation_model.getConnection())
				throw DbExceptionNoConnection();

			// Check query builder
			IDbQueryBuilder *query_builder{ relation_model.getQueryBuilder() };
			if (!query_builder)
				throw DbExceptionNoQueryBuilder();

			// Prepare statement
			ReleasablePtr<IDbStatement> statement;
			if (!relation_model.getStatement())
			{
				CConnectionErrorListenerLock e_lock{ relation_model.getConnection(), &m_cErrorListener };
				statement = relation_model.getConnection()->CreateStatement();
				if (!statement)
					throw DbExceptionCreateStatement(m_cErrorListener.Error);
			}
			else
			{
				statement = relation_model.getStatement();
				statement->AddRef();
			}
			statement->setRetrieveColumnName(true);
			statement->setRetrieveColumnAlias(true);
			CStatementErrorListenerLock e_lock{ statement, &m_cErrorListener };

			// Get list of parent model ids
			DbRow parent_ids;
			for (auto parent_model : parent_models)
				parent_ids.push_back(parent_model->getAttribute(m_sParentAttribute));

			// Build query
			CDbQuery query{ L"", nullptr, nullptr, nullptr };
			query.From(relation_model.getTable());
			if (isManyToMany())
			{
				query.Select(m_sLinkTable + L"." + m_sLinkParentAttribute, L"_it_parent_id_");
				query.Select(relation_model.getTable() + L".*");
				query.InnerJoin(m_sLinkTable, db::eqcc(m_sLinkTable + L"." + m_sLinkRelationAttribute, relation_model.getTable() + L"." + m_sRelationAttribute));
				query.Where(db::inc(m_sLinkTable + L"." + m_sLinkParentAttribute, parent_ids));
			}
			else
			{
				query.Select(relation_model.getTable() + L"." + m_sRelationAttribute, L"_it_parent_id_");
				query.Select(relation_model.getTable() + L".*");
				query.Where(db::inc(m_sRelationAttribute, parent_ids));
			}
			query.OrderBy(L"_it_parent_id_", DbOrder::Asc);
			MergeQuery(query);

			// Get query as string
			String query_str;
			if (!query_builder->Select(&query, query_str))
				throw DbExceptionBuildQuery(query_builder->LastError);

			// Execute query
			DbResult result{ statement->Execute(query_str) };
			if (!result.Successful)
				throw DbExceptionExecuteStatement(m_cErrorListener.Error);
			if (result.Rows.empty())
				return;

			// Get primary key columns
			DbSchema::PrimaryKey pk_columns;
			if (!DbSchema::getPrimaryKey(relation_model.getTable(), statement, relation_model.getQueryBuilder(), pk_columns, false))
				throw DbExceptionQueryPrimaryKeys(m_cErrorListener.Error);

			// Prepare column->attribute mapping
			std::vector<std::pair<size_t, size_t>> mapping;
			size_t attribute_index{ 0 };
			for (auto attribute : relation_model.Attributes)
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

			// Prepare sorted array of parent models
			FCompare compareRows;
			std::vector<CDbBaseActiveRecord *> sorted_parents{ parent_models };
			if (in(sorted_parents[0]->getAttribute(m_sParentAttribute).Type, { DbValueType::Null, DbValueType::Bool, DbValueType::Char, DbValueType::Byte, DbValueType::Short,
				DbValueType::UShort, DbValueType::Int, DbValueType::UInt, DbValueType::Int64 }))
			{
				compareRows = &CompareAsInt64;
				std::sort(sorted_parents.begin(), sorted_parents.end(), [this](CDbBaseActiveRecord *a, CDbBaseActiveRecord *b) {
					return (int64)a->getAttribute(m_sParentAttribute) < (int64)b->getAttribute(m_sParentAttribute);
				});
			}
			else if (sorted_parents[0]->getAttribute(m_sParentAttribute).Type == DbValueType::UInt64)
			{
				compareRows = &CompareAsUInt64;
				std::sort(sorted_parents.begin(), sorted_parents.end(), [this](CDbBaseActiveRecord *a, CDbBaseActiveRecord *b) {
					return (uint64)a->getAttribute(m_sParentAttribute) < (uint64)b->getAttribute(m_sParentAttribute);
				});
			}
			else if (in(sorted_parents[0]->getAttribute(m_sParentAttribute).Type, { DbValueType::Float, DbValueType::Double }))
			{
				compareRows = &CompareAsDouble;
				std::sort(sorted_parents.begin(), sorted_parents.end(), [this](CDbBaseActiveRecord *a, CDbBaseActiveRecord *b) {
					return (double)a->getAttribute(m_sParentAttribute) < (double)b->getAttribute(m_sParentAttribute);
				});
			}
			else
			{
				compareRows = &CompareAsString;
				std::sort(sorted_parents.begin(), sorted_parents.end(), [this](CDbBaseActiveRecord *a, CDbBaseActiveRecord *b) {
					return (String)a->getAttribute(m_sParentAttribute) < (String)b->getAttribute(m_sParentAttribute);
				});
			}

			// Build models
			TDbRelation<Model> *relation;
			size_t parent_index{ 0 };
			String parent_id;
			while (parent_index < sorted_parents.size())
			{
				if (!(relation = cast<TDbRelation<Model>*>(sorted_parents[parent_index]->getRelation(m_sName))))
					throw DbExceptionRelationNotFound(sorted_parents[parent_index]->getTable(), m_sName);
				relation->clear(false);

				parent_id = (String)sorted_parents[parent_index]->getAttribute(m_sParentAttribute);

				auto pos{ std::lower_bound(result.Rows.begin(), result.Rows.end(), DbRow{ DbValue{ parent_id } }, compareRows) };

				// Process rows that belong to current parent
				while (pos != result.Rows.end() && (String)(*pos)[0] == parent_id)
				{
					// Populate primary key
					DbActiveRecordPrimaryKey pk;
					for (size_t index = 0; index < pk_mapping.size(); index++)
						if (pk_mapping[index] == (size_t)-1)
							pk.push_back(std::pair<String, DbValue>{ pk_columns.Columns[index], DbValue{ } });
						else
							pk.push_back(std::pair<String, DbValue>{ pk_columns.Columns[index], (*pos)[pk_mapping[index]] });

					// Add model to lists and set its attributes
					Model *model{ new Model() };
					relation->push_back(model);
					out_models.push_back(model);
					for (auto const &map : mapping)
						setAttributeValue(model->Attributes[map.first], (*pos)[map.second]);
					setActiveRecordNew(model, false);
					setActiveRecordPrimaryKey(model, pk);
					model->AfterLoad();

					pos++;
				}

				parent_index++;
			}
		}
	public:
	#pragma region Constructor & destructor
		TDbRelation( // Constructor representing One-to-One or One-to-Many relation
			CDbBaseActiveRecord *parent,
			const String &name,
			const String &parent_attribute,
			const String &relation_attribute,
			const bool many = false) :
			IDbRelation{ name, parent },
			CReleasable(),
			m_pParent{ parent },
			m_sParentAttribute{ parent_attribute },
			m_sRelationAttribute{ relation_attribute },
			m_bMany{ many },
			m_bLoaded{ false }
		{
			m_bDistinct = false;
			m_iLimit = -1;
			m_iOffset = -1;
		}

		TDbRelation( // Constructor representing Many-to-Many relation
			CDbBaseActiveRecord *parent,
			const String &name,
			const String &parent_attribute,
			const String &relation_attribute,
			const String &link_table,
			const String &link_parent_attribute,
			const String &link_relation_attribute) :
			IDbRelation{ name, parent },
			CReleasable(),
			m_pParent{ parent },
			m_sParentAttribute{ parent_attribute },
			m_sRelationAttribute{ relation_attribute },
			m_sLinkTable{ link_table },
			m_sLinkParentAttribute{ link_parent_attribute },
			m_sLinkRelationAttribute{ link_relation_attribute },
			m_bMany{ true },
			m_bLoaded{ false }
		{
			m_bDistinct = false;
			m_iLimit = -1;
			m_iOffset = -1;
		}
	#pragma endregion

	#pragma region Operators
		template<class T> ReleasablePtr<Model> &operator=(T) = delete;

		ReleasablePtr<Model> operator->() // Return first model or nullptr if no models in list. Load models first if they were not loaded yet (lazy loading)
		{
			if (!m_bLoaded)
				Load();
			if (m_aModels.empty())
				return nullptr;
			return m_aModels[0];
		}

		ReleasablePtr<Model> operator[](const size_t index) // Return model by index or nullptr if index out of bounds. Load models first if they were not loaded yet (lazy loading)
		{
			if (!m_bLoaded)
				Load();
			if (index < m_aModels.size())
				return  m_aModels[index];
			return nullptr;
		}

		const ReleasablePtr<Model> operator[](const size_t index) const // Return model by index or nullptr if index out of bounds. Load models first if they were not loaded yet (lazy loading)
		{
			if (!m_bLoaded)
				Load();
			if (index < m_aModels.size())
				return  m_aModels[index];
			return nullptr;
		}
	#pragma endregion

	#pragma region Iterators & container methods
		typename std::vector<ReleasablePtr<Model>>::iterator begin() // Return iterator pointing to the beginning. Load models first if they were not loaded yet (lazy loading)
		{
			if (!m_bLoaded)
				Load();
			return m_aModels.begin();
		}

		typename std::vector<ReleasablePtr<Model>>::iterator end() // Return iterator pointing to the end. Load models first if they were not loaded yet (lazy loading)
		{
			if (!m_bLoaded)
				Load();
			return m_aModels.end();
		}

		typename std::vector<ReleasablePtr<Model>>::reverse_iterator rbegin() // Return reverse iterator pointing to the beginning. Load models first if they were not loaded yet (lazy loading)
		{
			if (!m_bLoaded)
				Load();
			return m_aModels.rbegin();
		}

		typename std::vector<ReleasablePtr<Model>>::reverse_iterator rend() // Return reverse iterator pointing to the end. Load models first if they were not loaded yet (lazy loading)
		{
			if (!m_bLoaded)
				Load();
			return m_aModels.rend();
		}

		typename std::vector<ReleasablePtr<Model>>::size_type size(const bool load = true) // Return count of models. Load models first if they were not loaded yet (lazy loading)
		{
			if (!m_bLoaded)
			{
				if (load)
					Load();
				else
					m_bLoaded = true;
			}
			return m_aModels.size();
		}

		bool empty(const bool load = true) // Return whether there are any models in list. Load models first if they were not loaded yet (lazy loading)
		{
			if (!m_bLoaded)
			{
				if (load)
					Load();
				else
					m_bLoaded = true;
			}
			return m_aModels.empty();
		}

		void push_back(ReleasablePtr<Model> model, const bool load = true) // Add new model to the list. Load models first if they were not loaded yet (lazy loading)
		{
			if (!m_bLoaded)
			{
				if (load)
					Load();
				else
					m_bLoaded = true;
			}
			m_aModels.push_back(model);
		}

		typename std::vector<ReleasablePtr<Model>>::iterator erase(typename std::vector<ReleasablePtr<Model>>::iterator pos, const bool load = true) // Remove model at the specified position from the list and calls model's Delete() method. Load models first if they were not loaded yet (lazy loading)
		{
			if (!m_bLoaded)
			{
				if (load)
					Load();
				else
					m_bLoaded = true;
			}
			(*pos)->Delete();
			return m_aModels.erase(pos);
		}

		typename std::vector<ReleasablePtr<Model>>::iterator erase(typename std::vector<ReleasablePtr<Model>>::iterator start, typename std::vector<ReleasablePtr<Model>>::iterator end, const bool load = true) // Remove models range from the list and calls models' Delete() method. Load models first if they were not loaded yet (lazy loading)
		{
			if (!m_bLoaded)
			{
				if (load)
					Load();
				else
					m_bLoaded = true;
			}
			auto pos{ start };
			while (pos != end)
			{
				(*pos)->Delete();
				pos++;
			}
			return m_aModels.erase(start, end);
		}

		void clear(const bool load) // Clear models and call theirs Delete() method. If "load" is true, models first loaded (if they are not loaded yet). If "load" is false, models won't be loaded and relation will be marked as already loaded so other operations will not load models (unless clear(true) is called)
		{
			if (!m_bLoaded)
			{
				if (load)
					Load();
				else
					m_bLoaded = true;
			}
			for (auto model : m_aModels)
				model->Delete();
			m_aModels.clear();
			m_bLoaded = !load;
		}
	#pragma endregion

	#pragma region Query building
		// Relation controlling/customization methods
		TDbRelation<Model> *Select(const String &column)
		{
			if (!column.empty())
				m_aSelect.push_back(StringKeyValue{ column, L"" });
			return this;
		}

		TDbRelation<Model> *Select(const String &column, const String &alias)
		{
			if (!column.empty())
				m_aSelect.push_back(StringKeyValue{ column, alias });
			return this;
		}

		TDbRelation<Model> *Select(const StringKeyValue &column)
		{
			if (!column.first.empty())
				m_aSelect.push_back(column);
			return this;
		}

		TDbRelation<Model> *Select(const StringArray &columns)
		{
			for (auto const &column : columns)
				if (!column.empty())
					m_aSelect.push_back(StringKeyValue{ column, L"" });
			return this;
		}

		TDbRelation<Model> *Select(const StringKeyValueArray &columns)
		{
			for (auto const &column : columns)
				if (!column.first.empty())
					m_aSelect.push_back(column);
			return this;
		}

		TDbRelation<Model> *Distinct(const bool &value)
		{
			m_bDistinct = value;
			return this;
		}

		TDbRelation<Model> *From(const String &table)
		{
			if (!table.empty())
				m_aFrom.push_back(StringKeyValue{ table, L"" });
			return this;
		}

		TDbRelation<Model> *From(const String &table, const String &alias)
		{
			if (!table.empty())
				m_aFrom.push_back(StringKeyValue{ table, alias });
			return this;
		}

		TDbRelation<Model> *From(const StringArray &tables)
		{
			for (auto const &table : tables)
				if (!table.empty())
					m_aFrom.push_back(StringKeyValue{ table, L"" });
			return this;
		}

		TDbRelation<Model> *From(const StringKeyValueArray &tables)
		{
			for (auto const &table : tables)
				if (!table.first.empty())
					m_aFrom.push_back(table);
			return this;
		}

		TDbRelation<Model> *InnerJoin(const String &table, DbCondition on)
		{
			if (!table.empty())
				m_aInnerJoins.push_back(IDbQuery::DbJoin{ table, L"", on });
			return this;
		}

		TDbRelation<Model> *InnerJoin(const String &table, const String &alias, DbCondition on)
		{
			if (!table.empty())
				m_aInnerJoins.push_back(IDbQuery::DbJoin{ table, alias, on });
			return this;
		}

		TDbRelation<Model> *InnerJoin(const IDbQuery::DbJoin &table)
		{
			m_aInnerJoins.push_back(table);
			return this;
		}

		TDbRelation<Model> *LeftJoin(const String &table, DbCondition on)
		{
			if (!table.empty())
				m_aLeftJoins.push_back(IDbQuery::DbJoin{ table, L"", on });
			return this;
		}

		TDbRelation<Model> *LeftJoin(const String &table, const String &alias, DbCondition on)
		{
			if (!table.empty())
				m_aLeftJoins.push_back(IDbQuery::DbJoin{ table, alias, on });
			return this;
		}

		TDbRelation<Model> *LeftJoin(const IDbQuery::DbJoin &table)
		{
			m_aLeftJoins.push_back(table);
			return this;
		}

		TDbRelation<Model> *RightJoin(const String &table, DbCondition on)
		{
			if (!table.empty())
				m_aRightJoins.push_back(IDbQuery::DbJoin{ table, L"", on });
			return this;
		}

		TDbRelation<Model> *RightJoin(const String &table, const String &alias, DbCondition on)
		{
			if (!table.empty())
				m_aRightJoins.push_back(IDbQuery::DbJoin{ table, alias, on });
			return this;
		}

		TDbRelation<Model> *RightJoin(const IDbQuery::DbJoin &table)
		{
			m_aRightJoins.push_back(table);
			return this;
		}

		TDbRelation<Model> *Where(DbCondition condition)
		{
			m_pWhere = condition;
			return this;
		}

		TDbRelation<Model> *Where(const DbConditions &conditions)
		{
			m_pWhere = nullptr;
			for (auto condition : conditions)
				AndWhere(condition);
			return this;
		}

		TDbRelation<Model> *AndWhere(DbCondition condition)
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

		TDbRelation<Model> *OrWhere(DbCondition condition)
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

		TDbRelation<Model> *GroupBy(const String &column)
		{
			if (!column.empty())
				m_aGroupBy.push_back(column);
			return this;
		}

		TDbRelation<Model> *GroupBy(const StringArray &columns)
		{
			for (auto const &column : columns)
				if (!column.empty())
					m_aGroupBy.push_back(column);
			return this;
		}

		TDbRelation<Model> *Having(DbCondition condition)
		{
			m_pHaving = condition;
			return this;
		}

		TDbRelation<Model> *Having(const DbConditions &conditions)
		{
			m_pHaving = nullptr;
			for (auto condition : conditions)
				AndHaving(condition);
			return this;
		}

		TDbRelation<Model> *AndHaving(DbCondition condition)
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

		TDbRelation<Model> *OrHaving(DbCondition condition)
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

		TDbRelation<Model> *OrderBy(const String &column, const DbOrder &order)
		{
			if (!column.empty())
				m_aOrderBy.push_back(DbOrderBy{ column, order });
			return this;
		}

		TDbRelation<Model> *OrderBy(const DbOrderByArray &columns)
		{
			for (auto const &column : columns)
				if (!column.first.empty())
					m_aOrderBy.push_back(column);
			return this;
		}

		TDbRelation<Model> *Limit(const int64 &limit)
		{
			m_iLimit = limit;
			return this;
		}

		TDbRelation<Model> *Offset(const int64 &offset)
		{
			m_iOffset = offset;
			return this;
		}
	#pragma endregion

	#pragma region Query
		ReleasablePtr<TDbActiveQuery<Model>> Query() // Return Active Query prefilled with relation loading conditions
		{
			ReleasablePtr<TDbActiveQuery<Model>> query{ new TDbActiveQuery<Model>() };
			if (isManyToMany())
			{
				Model m;
				query.InnerJoin(m_sLinkTable, db::eqcc(m_sLinkTable + L"." + m_sLinkRelationAttribute, m.getTable() + L"." + m_sRelationAttribute));
				query.Where(db::eqcv(m_sLinkTable + L"." + m_sLinkParentAttribute, m_pParent->getAttribute(m_sParentAttribute)));
			}
			else
				query.Where(db::eqcv(m_sRelationAttribute, m_pParent->getAttribute(m_sParentAttribute)));
			if (!m_aOrderBy.empty())
				query.OrderBy(m_aOrderBy);
			MergeQuery(query);
			return query;
		}
	#pragma endregion
	};
}