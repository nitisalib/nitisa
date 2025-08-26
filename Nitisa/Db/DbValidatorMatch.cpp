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
	CDbValidatorMatch::CDbValidatorMatch() :
		CDbValidator(),
		m_bNot{ false }
	{
		m_sMessage = L"{attribute} is invalid";
	}

	ReleasablePtr<CDbValidatorMatch> CDbValidatorMatch::Create()
	{
		return new CDbValidatorMatch();
	}
#pragma endregion

#pragma region Validation
	bool CDbValidatorMatch::Validate(CDbModel *model, IDbAttribute *attribute, String &error)
	{
		if (ShouldSkip(model, attribute))
			return true;
		DbValue value{ attribute->Get() };
		bool match{ std::regex_match((String)value, std::wregex{ m_sPattern }) };
		bool valid{ m_bNot ? (!match) : match };
		if (!valid)
			error = ReplaceAll(m_sMessage, L"{attribute}", attribute->sName);
		return valid;
	}
#pragma endregion

#pragma region Setters
	CDbValidatorMatch *CDbValidatorMatch::setNot(const bool &value)
	{
		m_bNot = value;
		return this;
	}

	CDbValidatorMatch *CDbValidatorMatch::setPattern(const String &value)
	{
		m_sPattern = value;
		return this;
	}
#pragma endregion
}