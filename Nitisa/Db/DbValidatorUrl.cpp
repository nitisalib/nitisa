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
	CDbValidatorUrl::CDbValidatorUrl() :
		CDbValidator(),
		m_sPattern{ L"{schemes}:\\/\\/(www\\.)?[a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=\\*]*)" },
		m_aValidSchemes{ L"http", L"https" }
	{
		m_sMessage = L"{attribute} is not a valid URL";
	}

	ReleasablePtr<CDbValidatorUrl> CDbValidatorUrl::Create()
	{
		return new CDbValidatorUrl();
	}
#pragma endregion

#pragma region Validation
	bool CDbValidatorUrl::Validate(CDbModel *model, IDbAttribute *attribute, String &error)
	{
		if (ShouldSkip(model, attribute))
			return true;
		DbValue value{ attribute->Get() };
		if (!in(value.Type, { DbValueType::String, DbValueType::AnsiString }) || value.Length() > 2000)
		{
			error = ReplaceAll(m_sMessage, L"{attribute}", attribute->sName);
			return false;
		}
		bool update{ false };
		String str{ (String)value };
		if (!m_sDefaultScheme.empty() && str.find(L"://") == String::npos)
		{
			str = m_sDefaultScheme + L"://" + str;
			update = true;
		}
		String pattern{ m_sPattern };
		if (pattern.find(L"{schemes}") != String::npos)
			ReplaceAllDirect(pattern, L"{schemes}", L"(" + Implode(L"|", m_aValidSchemes) + L")");
		if (!std::regex_match(str, std::wregex{ pattern, std::regex_constants::icase }))
		{
			error = ReplaceAll(m_sMessage, L"{attribute}", attribute->sName);
			return false;
		}
		if (update)
			attribute->Set(str);
		return true;
	}
#pragma endregion

#pragma region Setters
	CDbValidatorUrl *CDbValidatorUrl::setPattern(const String &value)
	{
		m_sPattern = value;
		return this;
	}

	CDbValidatorUrl *CDbValidatorUrl::setDefaultScheme(const String &value)
	{
		m_sDefaultScheme = value;
		return this;
	}

	CDbValidatorUrl *CDbValidatorUrl::setValidSchemes(const StringArray &value)
	{
		m_aValidSchemes = value;
		return this;
	}
#pragma endregion
}