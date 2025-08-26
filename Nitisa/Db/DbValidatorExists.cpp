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
	CDbValidatorExists::CDbValidatorExists() :
		CDbValidator()
	{
		m_sMessage = L"{attribute} is invalid";
	}

	ReleasablePtr<CDbValidatorExists> CDbValidatorExists::Create()
	{
		return new CDbValidatorExists();
	}
#pragma endregion

#pragma region Validation
	bool CDbValidatorExists::Validate(CDbModel *model, IDbAttribute *attribute, String &error)
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
		for (auto const &attr_name : attrs)
		{
			if (attr_name.empty())
			{
				error = L"One of the target attribute names is empty";
				return false;
			}
			conditions.push_back(db::eqcv(attr_name, attribute->Get()));
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
		if (!query.Exists())
		{
			error = ReplaceAll(m_sMessage, L"{attribute}", attribute->sName);
			return false;
		}
		return true;
	}
#pragma endregion

#pragma region Setters
	CDbValidatorExists *CDbValidatorExists::setTarget(const String &table, const String &attribute)
	{
		m_sTargetTable = table;
		m_aTargetAttributes.clear();
		m_aTargetAttributes.push_back(attribute);
		return this;
	}

	CDbValidatorExists *CDbValidatorExists::setTarget(const String &table, const StringArray &attributes)
	{
		m_sTargetTable = table;
		m_aTargetAttributes = attributes;
		return this;
	}

	CDbValidatorExists *CDbValidatorExists::setTargetTable(const String &value)
	{
		m_sTargetTable = value;
		return this;
	}

	CDbValidatorExists *CDbValidatorExists::setTargetAttribute(const String &value)
	{
		m_aTargetAttributes.clear();
		m_aTargetAttributes.push_back(value);
		return this;
	}

	CDbValidatorExists *CDbValidatorExists::setTargetAttribute(const StringArray &value)
	{
		m_aTargetAttributes = value;
		return this;
	}
#pragma endregion
}