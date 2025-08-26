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
	CDbValidatorRequired::CDbValidatorRequired() :
		CDbValidator(),
		m_bStrict{ false },
		m_sMessageValue{ L"{attribute} must be '{value}'" }
	{
		setSkipOnEmpty(false);
		m_sMessage = L"{attribute} cannot be blank";
	}

	ReleasablePtr<CDbValidatorRequired> CDbValidatorRequired::Create()
	{
		return new CDbValidatorRequired();
	}
#pragma endregion

#pragma region Validation
	bool CDbValidatorRequired::Validate(CDbModel *model, IDbAttribute *attribute, String &error)
	{
		if (ShouldSkip(model, attribute))
			return true;
		DbValue value{ attribute->Get() };
		if (m_sRequiredValue.Type != DbValueType::Null && value.Type != DbValueType::Null)
		{
			if (m_bStrict && value.Type != m_sRequiredValue.Type)
			{
				error = ReplaceAll(m_sMessageValue, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{value}", (String)m_sRequiredValue } });
				return false;
			}
			if (value != m_sRequiredValue.Convert(value.Type))
			{
				error = ReplaceAll(m_sMessageValue, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{value}", (String)m_sRequiredValue } });
				return false;
			}
			return true;
		}
		bool valid{ true };
		switch (value.Type)
		{
		case DbValueType::Bool:
			break;
		case DbValueType::Char:
			if ((char)value == 0)
				valid = false;
			break;
		case DbValueType::Byte:
			if ((byte)value == 0)
				valid = false;
			break;
		case DbValueType::Short:
			if ((short)value == 0)
				valid = false;
			break;
		case DbValueType::UShort:
			if ((word)value == 0)
				valid = false;
			break;
		case DbValueType::Int:
			if ((int)value == 0)
				valid = false;
			break;
		case DbValueType::UInt:
			if ((uint)value == 0)
				valid = false;
			break;
		case DbValueType::Int64:
			if ((int64)value == 0)
				valid = false;
			break;
		case DbValueType::UInt64:
			if ((uint64)value == 0)
				valid = false;
			break;
		case DbValueType::Float:
			if ((float)value == 0)
				valid = false;
			break;
		case DbValueType::Double:
			if ((double)value == 0)
				valid = false;
			break;
		case DbValueType::String:
		case DbValueType::AnsiString:
		case DbValueType::Buffer:
			if (value.Length() == 0)
				valid = false;
			break;
		case DbValueType::Date:
		case DbValueType::Time:
		case DbValueType::DateTime:
			break;
		default:
			valid = false;
			break;
		}
		if (!valid)
			error = ReplaceAll(m_sMessage, L"{attribute}", attribute->sName);
		return valid;
	}
#pragma endregion

#pragma region Setters
	CDbValidatorRequired *CDbValidatorRequired::setStrict(const bool &value)
	{
		m_bStrict = value;
		return this;
	}

	CDbValidatorRequired *CDbValidatorRequired::setRequiredValue(const DbValue &value)
	{
		m_sRequiredValue = value;
		return this;
	}

	CDbValidatorRequired *CDbValidatorRequired::setMessageValue(const String &value)
	{
		m_sMessageValue = value;
		return this;
	}
#pragma endregion
}