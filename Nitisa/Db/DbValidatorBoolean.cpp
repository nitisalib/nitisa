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
	CDbValidatorBoolean::CDbValidatorBoolean() :
		CDbValidator(),
		m_bStrict{ false }
	{
		m_sMessage = L"{attribute} must be either 'true' or 'false'";
	}

	ReleasablePtr<CDbValidatorBoolean> CDbValidatorBoolean::Create()
	{
		return new CDbValidatorBoolean();
	}
#pragma endregion

#pragma region Validation
	bool CDbValidatorBoolean::Validate(CDbModel *model, IDbAttribute *attribute, String &error)
	{
		if (ShouldSkip(model, attribute))
			return true;
		DbValue value{ attribute->Get() };
		if (m_bStrict)
		{
			if (value.Type != DbValueType::Bool)
			{
				error = ReplaceAll(m_sMessage, L"{attribute}", attribute->sName);
				return false;
			}
			return true;
		}
		bool valid{ true };
		switch (value.Type)
		{
		case DbValueType::Null:
		case DbValueType::Bool :
			break;
		case DbValueType::Char:
		case DbValueType::Byte:
		case DbValueType::Short:
		case DbValueType::UShort:
		case DbValueType::Int:
		case DbValueType::UInt:
		case DbValueType::Int64:
		case DbValueType::UInt64:
			if (!in((int)value, { 0, 1 }))
				valid = false;
			break;
		case DbValueType::String:
			if (!in((String)value, { L"true", L"false", L"1", L"0" }))
				valid = false;
			break;
		case DbValueType::AnsiString:
			if (!in((AnsiString)value, { "true", "false", "1", "0" }))
				valid = false;
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
	CDbValidatorBoolean *CDbValidatorBoolean::setStrict(const bool &value)
	{
		m_bStrict = value;
		return this;
	}
#pragma endregion
}