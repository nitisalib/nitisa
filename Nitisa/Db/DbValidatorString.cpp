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
	CDbValidatorString::CDbValidatorString() :
		CDbValidator(),
		m_bStrict{ true },
		m_iMin{ 0 },
		m_iMax{std::numeric_limits<size_t>::max() },
		m_sTooShort{ L"{attribute} length should be at least {min}" },
		m_sTooLong{ L"{attribute} length should be no more than {max}" }
	{
		m_sMessage = L"{attribute} must be a string";
	}

	ReleasablePtr<CDbValidatorString> CDbValidatorString::Create()
	{
		return new CDbValidatorString();
	}
#pragma endregion

#pragma region Validation
	bool CDbValidatorString::Validate(CDbModel *model, IDbAttribute *attribute, String &error)
	{
		if (ShouldSkip(model, attribute))
			return true;
		DbValue value{ attribute->Get() };
		if (m_bStrict && !in(value.Type, { DbValueType::String, DbValueType::AnsiString }))
		{
			error = ReplaceAll(m_sMessage, L"{attribute}", attribute->sName);
			return false;
		}
		if (value.Length() > m_iMax)
		{
			error = ReplaceAll(m_sTooLong, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{max}", ToString((uint64)m_iMax) } });
			return false;
		}
		if (value.Length() < m_iMin)
		{
			error = ReplaceAll(m_sTooShort, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{min}", ToString((uint64)m_iMin) } });
			return false;
		}
		return true;
	}
#pragma endregion

#pragma region Setters
	CDbValidatorString *CDbValidatorString::setStrict(const bool &value)
	{
		m_bStrict = value;
		return this;
	}

	CDbValidatorString *CDbValidatorString::setMin(const size_t &value)
	{
		m_iMin = value;
		return this;
	}

	CDbValidatorString *CDbValidatorString::setMax(const size_t &value)
	{
		m_iMax = value;
		return this;
	}

	CDbValidatorString *CDbValidatorString::setLength(const size_t &value)
	{
		m_iMax = m_iMin = value;
		return this;
	}

	CDbValidatorString *CDbValidatorString::setTooShort(const String &value)
	{
		m_sTooShort = value;
		return this;
	}

	CDbValidatorString *CDbValidatorString::setTooLong(const String &value)
	{
		m_sTooLong = value;
		return this;
	}
#pragma endregion
}