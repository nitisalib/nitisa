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
	CDbValidatorUnique::CDbValidatorUnique() :
		CDbValidator()
	{
		m_sMessage = L"{attribute} '{value}' has already been taken";
	}

	ReleasablePtr<CDbValidatorUnique> CDbValidatorUnique::Create()
	{
		return new CDbValidatorUnique();
	}
#pragma endregion

#pragma region Validation
	bool CDbValidatorUnique::Validate(CDbModel *model, IDbAttribute *attribute, String &error)
	{
		if (ShouldSkip(model, attribute))
			return true;
		CDbBaseActiveRecord *ar{ cast<CDbBaseActiveRecord *>(model) };
		if (!ar)
		{
			error = L"'Exists' validator can only be used on ActiveRecord instances";
			return false;
		}
		StringArray attrs{ m_aTargetAttributes };
		if (attrs.empty())
			attrs.push_back(attribute->sName);
		DbConditions conditions;
		for (auto const &name : attrs)
		{
			if (name.empty())
			{
				error = L"One of the target attribute names is empty";
				return false;
			}
			conditions.push_back(db::eqcv(name, attribute->Get()));
		}
		String table{ m_sTargetTable.empty() ? ar->getTable() : m_sTargetTable };
		CDbQuery query{ table, ar->getConnection(), ar->getStatement(), ar->getQueryBuilder() };
		query.Where(conditions);
		if (!ar->isNewRecord() && table == ar->getTable())
		{
			DbActiveRecordPrimaryKey pk{ ar->getPrimaryKey() };
			DbCondition condition;
			for (auto c : pk)
				if (condition)
					condition = db::o(condition, db::necv(c.first, c.second));
				else
					condition = db::necv(c.first, c.second);
			if (condition)
				query.AndWhere(condition);
		}
		bool valid{ !query.Exists() };
		if (!valid)
		{
			StringArray values;
			for (auto const &name : attrs)
				values.push_back((String)model->getAttribute(name));
			error = ReplaceAll(m_sMessage, StringKeyValueArray{
				StringKeyValue{ L"{attribute}", attribute->sName },
				StringKeyValue{ L"{value}", (String)attribute->Get() },
				StringKeyValue{ L"{values}", Implode(L", ", values) }
			});
		}
		return valid;
	}
#pragma endregion

#pragma region Setters
	CDbValidatorUnique *CDbValidatorUnique::setTarget(const String &table, const String &attribute)
	{
		m_sTargetTable = table;
		m_aTargetAttributes.clear();
		m_aTargetAttributes.push_back(attribute);
		return this;
	}

	CDbValidatorUnique *CDbValidatorUnique::setTarget(const String &table, const StringArray &attributes)
	{
		m_sTargetTable = table;
		m_aTargetAttributes = attributes;
		return this;
	}

	CDbValidatorUnique *CDbValidatorUnique::setTargetTable(const String &value)
	{
		m_sTargetTable = value;
		return this;
	}

	CDbValidatorUnique *CDbValidatorUnique::setTargetAttribute(const String &value)
	{
		m_aTargetAttributes.clear();
		m_aTargetAttributes.push_back(value);
		return this;
	}

	CDbValidatorUnique *CDbValidatorUnique::setTargetAttribute(const StringArray &value)
	{
		m_aTargetAttributes = value;
		return this;
	}
#pragma endregion
}