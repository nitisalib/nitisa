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
	CDbValidator::CDbValidator() :
		CReleasable(),
		m_bSkipOnError{ true },
		m_bSkipOnEmpty{ true },
		m_fWhen{ nullptr }
	{
		m_iCode = 0;
	}
#pragma endregion

#pragma region IDbValidator setters
	IDbValidator *CDbValidator::setCode(const int value)
	{
		m_iCode = value;
		return this;
	}

	IDbValidator *CDbValidator::setMessage(const String &value)
	{
		m_sMessage = value;
		return this;
	}

	IDbValidator *CDbValidator::setOn(const StringArray &value)
	{
		m_aOn = value;
		return this;
	}

	IDbValidator *CDbValidator::setExcept(const StringArray &value)
	{
		m_aExcept = value;
		return this;
	}

	IDbValidator *CDbValidator::setSkipOnError(const bool &value)
	{
		m_bSkipOnError = value;
		return this;
	}

	IDbValidator *CDbValidator::setSkipOnEmpty(const bool &value)
	{
		m_bSkipOnEmpty = value;
		return this;
	}

	IDbValidator *CDbValidator::setWhen(FWhen value)
	{
		m_fWhen = value;
		return this;
	}
#pragma endregion

#pragma region Helpers
	bool CDbValidator::ShouldSkip(CDbModel *model, IDbAttribute *attribute)
	{
		if (!m_aOn.empty() && !in(model->Scenario, m_aOn))
			return true;
		if (!m_aExcept.empty() && in(model->Scenario, m_aExcept))
			return true;
		if (m_bSkipOnEmpty && attribute->bNull)
			return true;
		if (m_bSkipOnError && model->hasErrors(attribute->sName))
			return true;
		if (m_fWhen && !m_fWhen(model, attribute))
			return true;
		return false;
	}
#pragma endregion
}