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
	CDbValidatorEmail::CDbValidatorEmail() :
		CDbValidator(),
		m_sPattern{ L"^[a-zA-Z0-9!#$%&'*+\\/=?^_`{|}~-]+(?:\\.[a-zA-Z0-9!#$%&'*+\\/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$" },
		m_sFullPattern{ L"^[^@]*<[a-zA-Z0-9!#$%&'*+\\/=?^_`{|}~-]+(?:\\.[a-zA-Z0-9!#$%&'*+\\/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?>$" },
		m_bAllowName{ false }
	{
		m_sMessage = L"{attribute} is not a valid email address";
	}

	ReleasablePtr<CDbValidatorEmail> CDbValidatorEmail::Create()
	{
		return new CDbValidatorEmail();
	}
#pragma endregion

#pragma region Validation
	bool CDbValidatorEmail::Validate(CDbModel *model, IDbAttribute *attribute, String &error)
	{
		if (ShouldSkip(model, attribute))
			return true;
		DbValue value{ attribute->Get() };
		bool valid{ true };
		if (in(value.Type, { DbValueType::String, DbValueType::AnsiString }))
		{
			std::wregex re{ m_bAllowName ? m_sFullPattern : m_sPattern };
			if (!std::regex_match((String)value, re))
				valid = false;
		}
		else
			valid = false;
		if (!valid)
			error = ReplaceAll(m_sMessage, L"{attribute}", attribute->sName);
		return valid;
	}
#pragma endregion

#pragma region Setters
	CDbValidatorEmail *CDbValidatorEmail::setPattern(const String &value)
	{
		m_sPattern = value;
		return this;
	}

	CDbValidatorEmail *CDbValidatorEmail::setFullPattern(const String &value)
	{
		m_sFullPattern = value;
		return this;
	}

	CDbValidatorEmail *CDbValidatorEmail::setAllowName(const bool &value)
	{
		m_bAllowName = value;
		return this;
	}
#pragma endregion
}