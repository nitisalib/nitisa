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
	CDbValidatorDateTime::CDbValidatorDateTime() :
		CDbValidator(),
		m_bStrict{ false },
		m_eType{ Type::Date },
		m_sFormat{ L"%Y-%m-%d %H:%M:%S" },
		m_sMin{ DbDate{ std::numeric_limits<short>::min(), 1, 1 }, DbTime{ 0, 0, 0 }, 0 },
		m_sMax{ DbDate{ std::numeric_limits<short>::max(), 12, 31 }, DbTime{ 23, 59, 59 }, std::numeric_limits<unsigned int>::max() },
		m_sTooBig{ L"{attribute} must be no greater than {max}" },
		m_sTooSmall{ L"{attribute} must be no less than {min}" }
	{
		m_sMessage = L"The format of {attribute} is invalid";
	}

	ReleasablePtr<CDbValidatorDateTime> CDbValidatorDateTime::Create()
	{
		return new CDbValidatorDateTime();
	}
#pragma endregion

#pragma region Validation
	bool CDbValidatorDateTime::Validate(CDbModel *model, IDbAttribute *attribute, String &error)
	{
		if (ShouldSkip(model, attribute))
			return true;
		DbValue value{ attribute->Get() };
		if (m_bStrict)
		{
			DbValueType allowed;
			switch (m_eType)
			{
			case Type::Date:
				allowed = DbValueType::Date;
				break;
			case Type::Time:
				allowed = DbValueType::Time;
				break;
			default:
				allowed = DbValueType::DateTime;
				break;
			}
			if (value.Type != allowed)
			{
				error = ReplaceAll(m_sMessage, L"{attribute}", attribute->sName);
				return false;
			}
		}
		if (in(value.Type, { DbValueType::String, DbValueType::AnsiString }))
		{
		#ifndef __GNUC__
			tm dt;
			if (!ParseDateTime((String)value, dt, m_sFormat))
			{
				error = ReplaceAll(m_sMessage, L"{attribute}", attribute->sName);
				return false;
			}
			value = DbDateTime{
				DbDate{ short(dt.tm_year + 1900), (unsigned short)(dt.tm_mon + 1), (unsigned short)dt.tm_mday },
				DbTime{ (unsigned short)dt.tm_hour, (unsigned short)dt.tm_min, (unsigned short)dt.tm_sec },
				0 };
		#else
			error = L"Parsing date and time is not supported on GNUC systems";
			return false;
		#endif
		}
		bool valid{ true };
		switch (value.Type)
		{
		case DbValueType::Date:
		case DbValueType::Time:
		case DbValueType::DateTime:
			switch (m_eType)
			{
			case Type::Date:
				if ((DbDate)value > m_sMax.Date)
				{
					error = ReplaceAll(m_sTooBig, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{max}", (String)m_sMax.Date } });
					return false;
				}
				if ((DbDate)value < m_sMin.Date)
				{
					error = ReplaceAll(m_sTooSmall, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{min}", (String)m_sMin.Date } });
					return false;
				}
				break;
			case Type::Time:
				if ((DbTime)value > m_sMax.Time)
				{
					error = ReplaceAll(m_sTooBig, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{max}", (String)m_sMax.Time } });
					return false;
				}
				if ((DbTime)value < m_sMin.Time)
				{
					error = ReplaceAll(m_sTooSmall, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{min}", (String)m_sMin.Time } });
					return false;
				}
				break;
			default:
				if ((DbDateTime)value > m_sMax)
				{
					error = ReplaceAll(m_sTooBig, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{max}", (String)m_sMax } });
					return false;
				}
				if ((DbDateTime)value < m_sMin)
				{
					error = ReplaceAll(m_sTooSmall, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{min}", (String)m_sMin } });
					return false;
				}
				break;
			}
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
	CDbValidatorDateTime *CDbValidatorDateTime::setStrict(const bool &value)
	{
		m_bStrict = value;
		return this;
	}

	CDbValidatorDateTime *CDbValidatorDateTime::setType(const Type &value)
	{
		m_eType = value;
		return this;
	}

	CDbValidatorDateTime *CDbValidatorDateTime::setFormat(const String &value)
	{
		m_sFormat = value;
		return this;
	}

	CDbValidatorDateTime *CDbValidatorDateTime::setMin(const DbDateTime &value)
	{
		m_sMin = value;
		return this;
	}

	CDbValidatorDateTime *CDbValidatorDateTime::setMax(const DbDateTime &value)
	{
		m_sMax = value;
		return this;
	}

	CDbValidatorDateTime *CDbValidatorDateTime::setTooBig(const String &value)
	{
		m_sTooBig = value;
		return this;
	}

	CDbValidatorDateTime *CDbValidatorDateTime::setTooSmall(const String &value)
	{
		m_sTooSmall = value;
		return this;
	}
#pragma endregion
}