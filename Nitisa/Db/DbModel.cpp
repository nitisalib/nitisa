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
#pragma region CAttributes
	void CDbModel::CAttributes::Add(IDbAttribute* item)
	{
		m_aItems.push_back(item);
	}

	IDbAttribute* CDbModel::CAttributes::operator[](const size_t index)
	{
		if (index < m_aItems.size())
			return m_aItems[index];
		return nullptr;
	}

	CDbModel::CAttributes &CDbModel::CAttributes::operator=(const DbSet &attributes)
	{
		for (auto value : attributes)
			for (auto attr : m_aItems)
				if (attr->sName == value.first)
				{
					if (value.second.Type == DbValueType::Null)
						attr->SetNull();
					else
						attr->Set(value.second);
				}
		return *this;
	}

	std::vector<IDbAttribute*>::iterator CDbModel::CAttributes::begin()
	{
		return m_aItems.begin();
	}

	std::vector<IDbAttribute*>::iterator CDbModel::CAttributes::end()
	{
		return m_aItems.end();
	}

	std::vector<IDbAttribute*>::const_iterator CDbModel::CAttributes::begin() const
	{
		return m_aItems.begin();
	}

	std::vector<IDbAttribute*>::const_iterator CDbModel::CAttributes::end() const
	{
		return m_aItems.end();
	}

	std::vector<IDbAttribute*>::const_iterator CDbModel::CAttributes::cbegin() const
	{
		return m_aItems.cbegin();
	}

	std::vector<IDbAttribute*>::const_iterator CDbModel::CAttributes::cend() const
	{
		return m_aItems.cend();
	}

	std::vector<IDbAttribute*>::reverse_iterator CDbModel::CAttributes::rbegin()
	{
		return m_aItems.rbegin();
	}

	std::vector<IDbAttribute*>::reverse_iterator CDbModel::CAttributes::rend()
	{
		return m_aItems.rend();
	}

	std::vector<IDbAttribute*>::const_reverse_iterator CDbModel::CAttributes::rbegin() const
	{
		return m_aItems.rbegin();
	}

	std::vector<IDbAttribute*>::const_reverse_iterator CDbModel::CAttributes::rend() const
	{
		return m_aItems.rend();
	}

	std::vector<IDbAttribute*>::const_reverse_iterator CDbModel::CAttributes::crbegin() const
	{
		return m_aItems.crbegin();
	}

	std::vector<IDbAttribute*>::const_reverse_iterator CDbModel::CAttributes::crend() const
	{
		return m_aItems.crend();
	}

	std::vector<IDbAttribute*>::size_type CDbModel::CAttributes::size() const
	{
		return m_aItems.size();
	}

	bool CDbModel::CAttributes::empty() const
	{
		return m_aItems.empty();
	}
#pragma endregion

#pragma region Constructor & destructor
	CDbModel::CDbModel() :
		CReleasable(),
		m_sScenario{ L"DEFAULT" }
	{

	}
#pragma endregion

#pragma region Getters
	bool CDbModel::hasAttribute(const String& name) const
	{
		for (auto const attr : Attributes)
			if (attr->sName == name)
				return true;
		return false;
	}

	DbValue CDbModel::getAttribute(const String& name) const
	{
		for (auto const attr : Attributes)
			if (attr->sName == name)
				return attr->Get();
		return DbValue{ };
	}

	DbValue CDbModel::getOldAttribute(const String& name) const
	{
		for (auto const attr : Attributes)
			if (attr->sName == name)
				return attr->Old();
		return DbValue{ };
	}

	bool CDbModel::hasErrors() const
	{
		return !m_aErrors.empty();
	}

	bool CDbModel::hasErrors(const String &attribute) const
	{
		auto pos{ m_aErrors.find(attribute) };
		return pos != m_aErrors.end();
	}

	const CDbModel::ErrorList& CDbModel::getErrors() const
	{
		return m_aErrors;
	}

	CDbModel::ErrorInfos CDbModel::getErrors(const String& attribute) const
	{
		for (auto const& errors : m_aErrors)
			if (errors.first == attribute)
				return errors.second;
		return { };
	}

	ErrorInfo CDbModel::getFirstError() const
	{
		for (auto const &errors : m_aErrors)
			if (!errors.second.empty())
				return errors.second[0];
		return ErrorInfo{ 0, L"" };
	}

	ErrorInfo CDbModel::getFirstError(const String &attribute) const
	{
		for (auto const &errors : m_aErrors)
			if (errors.first == attribute)
			{
				if (!errors.second.empty())
					return errors.second[0];
				break;
			}
		return ErrorInfo{ 0, L"" };
	}
#pragma endregion

#pragma region Setters
	bool CDbModel::setAttribute(const String& name, const DbValue& value)
	{
		for (auto attr : Attributes)
			if (attr->sName == name)
			{
				if (value.Type == DbValueType::Null)
					attr->SetNull();
				else
					attr->Set(value);
				return true;
			}
		return false;
	}

	bool CDbModel::setScenario(const String &value)
	{
		if (value != m_sScenario)
		{
			m_sScenario = value;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Validation
	bool CDbModel::AddError(const String& attribute, const String& error, const int code)
	{
		if (!attribute.empty() && !error.empty())
		{
			m_aErrors[attribute].push_back(ErrorInfo{ code, error });
			return true;
		}
		return false;
	}

	bool CDbModel::BeforeValidate()
	{
		return true;
	}

	void CDbModel::AfterValidate()
	{
		// Nothing
	}

	bool CDbModel::Validate(const StringArray& attributes)
	{
		if (!BeforeValidate())
			return false;
		m_aErrors.clear();
		bool valid{ true };
		for (auto rule : m_aRules)
		{
			String error;
			if ((attributes.empty() || in(rule.first->sName, attributes)) && !rule.second->Validate(this, rule.first, error))
			{
				m_aErrors[rule.first->sName].push_back(ErrorInfo{ rule.second->iCode, error });
				valid = false;
			}
		}
		AfterValidate();
		return valid;
	}
#pragma endregion
}