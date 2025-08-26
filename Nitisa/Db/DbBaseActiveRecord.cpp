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
#pragma region Constructor & destructor
	CDbBaseActiveRecord::CDbBaseActiveRecord(const String& table) :
		CDbModel(),
		m_bNewRecord{ true },
		m_sTable{ table }
	{

	}
#pragma endregion

#pragma region Virtual getters
	const String& CDbBaseActiveRecord::getTable() const
	{
		return m_sTable;
	}
#pragma endregion

#pragma region Getters
	bool CDbBaseActiveRecord::isNewRecord() const
	{
		return m_bNewRecord;
	}

	bool CDbBaseActiveRecord::hasRelation(const String &name) const
	{
		for (auto relation : m_aRelations)
			if (relation->sName == name)
				return true;
		return false;
	}

	IDbRelation* CDbBaseActiveRecord::getRelation(const String &name) const
	{
		for (auto relation : m_aRelations)
			if (relation->sName == name)
				return relation;
		return nullptr;
	}

	const DbActiveRecordPrimaryKey& CDbBaseActiveRecord::getPrimaryKey() const
	{
		return m_sPrimaryKey;
	}
#pragma endregion

#pragma region Setters
	bool CDbBaseActiveRecord::setNewRecord(const bool value)
	{
		if (value && value != m_bNewRecord)
		{
			m_bNewRecord = true;
			m_sPrimaryKey.clear();
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Event methods
	bool CDbBaseActiveRecord::BeforeSave()
	{
		return true;
	}

	bool CDbBaseActiveRecord::BeforeUpdate()
	{
		return true;
	}

	bool CDbBaseActiveRecord::BeforeInsert()
	{
		return true;
	}

	bool CDbBaseActiveRecord::BeforeDelete()
	{
		return true;
	}

	void CDbBaseActiveRecord::AfterSave()
	{
		// Nothing
	}

	void CDbBaseActiveRecord::AfterUpdate()
	{
		// Nothing
	}

	void CDbBaseActiveRecord::AfterInsert()
	{
		// Nothing
	}

	void CDbBaseActiveRecord::AfterDelete()
	{
		// Nothing
	}
#pragma endregion

#pragma region Methods
	bool CDbBaseActiveRecord::LoadDefaultValues(const bool skip_if_set)
	{
		bool changed{ false };
		for (auto attr : Attributes)
		{
			if (skip_if_set && !attr->bNull)
				continue;
			DbSchema::Column column;
			bool column_get{ getStatement() ?
				DbSchema::getColumn(getTable(), attr->sName, getStatement(), column, false) :
				DbSchema::getColumn(getTable(), attr->sName, getConnection(), column, false)
			};
			if (column_get)
			{
				attr->Set(column.DefaultValue);
				changed = true;
			}
		}
		return changed;
	}

	bool CDbBaseActiveRecord::Refresh()
	{
		if (m_bNewRecord)
			return false;
		
		// Build condition to search by primary key
		DbSchema::PrimaryKey pk;
		DbConditions conditions;
		bool pk_get{ getStatement() ?
			DbSchema::getPrimaryKey(getTable(), getStatement(), getQueryBuilder(), pk) :
			DbSchema::getPrimaryKey(getTable(), getConnection(), getQueryBuilder(), pk)
		};
		if (pk_get && !pk.Columns.empty())
		{
			for (auto const& pk_column : pk.Columns)
			{
				for (auto attr : Attributes)
					if (attr->sName == pk_column)
					{
						conditions.push_back(db::Equals(pk_column, attr->Old()));
						break;
					}
			}
		}
		if (conditions.empty())
			return false;

		// Build column list to load
		StringArray columns;
		std::vector<IDbAttribute*> attributes;
		for (auto attr : Attributes)
		{
			bool is_pk{ false };
			for (auto const& pk_column : pk.Columns)
				if (attr->sName == pk_column)
				{
					is_pk = true;
					break;
				}
			if (!is_pk)
			{
				columns.push_back(attr->sName);
				attributes.push_back(attr);
			}
		}
		if (columns.empty())
			return false;

		// Execute load
		CDbQuery query{ getTable(), getConnection(), getStatement(), getQueryBuilder() };
		DbRow row = query.Select(columns)->Where(conditions)->Row();
		if (row.size() != columns.size())
			return false;

		// Update attributes
		for (size_t i = 0; i < row.size(); i++)
			attributes[i]->SetInternal(row[i], false);

		AfterLoad();
		return true;
	}

	bool CDbBaseActiveRecord::Delete()
	{
		if (m_bNewRecord)
			return false;
		// Build condition to delete by primary key
		DbSchema::PrimaryKey pk;
		DbConditions conditions;
		bool pk_get{ getStatement() ?
			DbSchema::getPrimaryKey(getTable(), getStatement(), getQueryBuilder(), pk) :
			DbSchema::getPrimaryKey(getTable(), getConnection(), getQueryBuilder(), pk)
		};
		if (pk_get && !pk.Columns.empty())
		{
			for (auto const &pk_column : pk.Columns)
			{
				for (auto attr : Attributes)
					if (attr->sName == pk_column)
					{
						conditions.push_back(db::Equals(pk_column, attr->Old()));
						break;
					}
			}
		}
		if (conditions.empty())
			return false;

		// Execute deletion and update model
		if (!BeforeDelete())
			return false;
		CDbDelete query{ getConnection(), getStatement(), getQueryBuilder() };
		query.From(getTable())->Where(conditions)->Execute();
		for (auto attr : Attributes)
			attr->SetInternal(DbValue{ }, false);
		m_bNewRecord = true;
		m_sPrimaryKey.clear();
		AfterDelete();
		return true;
	}
#pragma endregion

#pragma region Save methods
	bool CDbBaseActiveRecord::Save(const bool validate, const StringArray& attributes)
	{
		if (Attributes.empty())
			throw DbExceptionNoAttributes();
		if (!BeforeSave())
			return false;
		if (validate && !Validate(attributes))
			return false;
		if (m_bNewRecord)
		{
			if (!BeforeInsert())
				return false;
			Insert();
			AfterInsert();
		}
		else
		{
			if (!BeforeUpdate())
				return false;
			Update();
			AfterUpdate();
		}
		AfterSave();
		return true;
	}

	void CDbBaseActiveRecord::Insert()
	{
		// Collect changed attributes
		std::map<String, DbValue> data;
		for (auto attr : Attributes)
			if (attr->bChanged)
				data[attr->sName] = attr->Get();

		// Perform insert
		CDbInsert insert{ getConnection(), getStatement(), getQueryBuilder() };
		uint64 id{ insert.Into(getTable())->Execute(data)->Id() };

		// It's not a new record anymore
		m_bNewRecord = false;

		// Update auto incrementing field if there is one
		String column;
		bool column_get{ getStatement() ?
			DbSchema::getAutoIncrementColumn(getTable(), getStatement(), getQueryBuilder(), column) :
			DbSchema::getAutoIncrementColumn(getTable(), getConnection(), getQueryBuilder(), column)
		};
		if (column_get && !column.empty())
		{
			for (auto attr : Attributes)
				if (attr->sName == column)
				{
					attr->SetInternal(DbValue{ id }, false);
					break;
				}
		}

		// Mark all attributes as unchanged
		for (auto attr : Attributes)
			attr->m_bChanged = false;

		// Update primary key if there is one
		DbSchema::PrimaryKey pk;
		bool pk_get{ getStatement() ?
			DbSchema::getPrimaryKey(getTable(), getStatement(), getQueryBuilder(), pk) :
			DbSchema::getPrimaryKey(getTable(), getConnection(), getQueryBuilder(), pk)
		};
		if (pk_get && !pk.Columns.empty())
		{
			DbActiveRecordPrimaryKey ar_pk;
			for (auto const& column : pk.Columns)
				if (hasAttribute(column))
					ar_pk.push_back(std::pair<String, DbValue>{ column, getAttribute(column) });
			m_sPrimaryKey = ar_pk;
		}
	}

	void CDbBaseActiveRecord::Update()
	{
		// Collect changed attributes
		std::map<String, DbValue> data;
		for (auto attr : Attributes)
			if (attr->bChanged)
				data[attr->sName] = attr->Get();

		// If nothing is changed, do nothing
		if (data.empty())
			return;

		// Get old primary key if there is one, build update condition, and find out whether primary key was changed
		bool pk_changed{ false };
		DbConditions conditions;
		DbSchema::PrimaryKey pk;
		bool pk_get{ getStatement() ?
			DbSchema::getPrimaryKey(getTable(), getStatement(), getQueryBuilder(), pk) :
			DbSchema::getPrimaryKey(getTable(), getConnection(), getQueryBuilder(), pk)
		};
		if (pk_get && !pk.Columns.empty())
		{
			for (auto const& pk_column : pk.Columns)
			{
				for (auto attr : Attributes)
					if (attr->sName == pk_column)
					{
						conditions.push_back(db::Equals(pk_column, attr->Old()));
						if (attr->bChanged)
							pk_changed = true;
						break;
					}
			}
		}

		// Execute update
		CDbUpdate update{ getConnection(), getStatement(), getQueryBuilder() };
		update.Table(getTable());
		if (!conditions.empty())
			update.Where(conditions);
		update.Execute(data);

		// Mark all attributes as unchanged
		for (auto attr : Attributes)
			attr->m_bChanged = false;

		// Update primary key if there is one
		if (pk_changed)
		{
			DbActiveRecordPrimaryKey ar_pk;
			for (auto const& column : pk.Columns)
				if (hasAttribute(column))
					ar_pk.push_back(std::pair<String, DbValue>{ column, getAttribute(column) });
			m_sPrimaryKey = ar_pk;
		}
	}

	void CDbBaseActiveRecord::AfterLoad()
	{

	}
#pragma endregion
}