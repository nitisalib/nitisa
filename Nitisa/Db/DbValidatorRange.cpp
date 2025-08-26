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
	CDbValidatorRange::CDbValidatorRange() :
		CDbValidator(),
		m_bStrict{ false },
		m_bNot{ false }
	{
		m_sMessage = L"{attribute} is invalid";
	}

	ReleasablePtr<CDbValidatorRange> CDbValidatorRange::Create()
	{
		return new CDbValidatorRange();
	}
#pragma endregion

#pragma region Validation
	bool CDbValidatorRange::Validate(CDbModel *model, IDbAttribute *attribute, String &error)
	{
		if (ShouldSkip(model, attribute))
			return true;
		DbValue value{ attribute->Get() };
		bool valid{ false };
		if (m_bNot)
		{
			bool found{ false };
			for (auto const &item : m_aRange)
			{
				if (m_bStrict && item.Type != value.Type)
					continue;
				if (item == value.Convert(item.Type))
				{
					found = true;
					break;
				}
			}
			if (!found)
				valid = true;
		}
		else
		{
			for (auto const &item : m_aRange)
			{
				if (m_bStrict && item.Type != value.Type)
					continue;
				if (item == value.Convert(item.Type))
				{
					valid = true;
					break;
				}
			}
		}
		if (!valid)
			error = ReplaceAll(m_sMessage, L"{attribute}", attribute->sName);
		return valid;
	}
#pragma endregion

#pragma region Setters
	CDbValidatorRange *CDbValidatorRange::setStrict(const bool &value)
	{
		m_bStrict = value;
		return this;
	}

	CDbValidatorRange *CDbValidatorRange::setNot(const bool &value)
	{
		m_bNot = value;
		return this;
	}

	CDbValidatorRange *CDbValidatorRange::setRange(const std::vector<DbValue> &value)
	{
		m_aRange = value;
		return this;
	}
#pragma endregion
}