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
	CDbValidatorNumber::CDbValidatorNumber() :
		CDbValidator(),
		m_bIntegerOnly{ false },
		m_bStrict{ false },
		m_sTooBig{ L"{attribute} must be no greater than {max}" },
		m_sTooSmall{ L"{attribute} must be no less than {min}" }
	{
		m_sMessage = L"{attribute} must be a number";
	}

	ReleasablePtr<CDbValidatorNumber> CDbValidatorNumber::Create()
	{
		return new CDbValidatorNumber();
	}
#pragma endregion

#pragma region Validation
	bool CDbValidatorNumber::Validate(CDbModel *model, IDbAttribute *attribute, String &error)
	{
		if (ShouldSkip(model, attribute))
			return true;
		DbValue value{ attribute->Get() };
		bool valid{ true };
		switch (value.Type)
		{
		case DbValueType::Null:
		case DbValueType::Bool:
			if (m_bStrict)
			{
				valid = false;
				break;
			}
			if (m_sMax.Type != DbValueType::Null && (int64)value > (int64)m_sMax)
			{
				error = ReplaceAll(m_sTooBig, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{max}", (String)m_sMax } });
				return false;
			}
			if (m_sMin.Type != DbValueType::Null && (int64)value < (int64)m_sMin)
			{
				error = ReplaceAll(m_sTooSmall, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{min}", (String)m_sMin } });
				return false;
			}
			break;
		case DbValueType::Char:
		case DbValueType::Byte:
		case DbValueType::Short:
		case DbValueType::UShort:
		case DbValueType::Int:
		case DbValueType::UInt:
		case DbValueType::Int64:
		case DbValueType::UInt64:
			if (m_sMax.Type != DbValueType::Null && (int64)value > (int64)m_sMax)
			{
				error = ReplaceAll(m_sTooBig, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{max}", (String)m_sMax } });
				return false;
			}
			if (m_sMin.Type != DbValueType::Null && (int64)value < (int64)m_sMin)
			{
				error = ReplaceAll(m_sTooSmall, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{min}", (String)m_sMin } });
				return false;
			}
			break;
		case DbValueType::Float:
		case DbValueType::Double:
			if (m_bIntegerOnly)
			{
				valid = false;
				break;
			}
			if (m_sMax.Type != DbValueType::Null && ntl::IsGreater<double>((double)value, (double)m_sMax))
			{
				error = ReplaceAll(m_sTooBig, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{max}", (String)m_sMax } });
				return false;
			}
			if (m_sMin.Type != DbValueType::Null && ntl::IsLess<double>((double)value, (double)m_sMin))
			{
				error = ReplaceAll(m_sTooSmall, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{min}", (String)m_sMin } });
				return false;
			}
			break;
		case DbValueType::String:
		case DbValueType::AnsiString:
			if (m_bStrict)
				valid = false;
			else
			{
				int64 i;
				if (TryStringToInt64((String)value, i))
				{
					if (m_sMax.Type != DbValueType::Null && i > (int64)m_sMax)
					{
						error = ReplaceAll(m_sTooBig, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{max}", (String)m_sMax } });
						return false;
					}
					if (m_sMin.Type != DbValueType::Null && i < (int64)m_sMin)
					{
						error = ReplaceAll(m_sTooSmall, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{min}", (String)m_sMin } });
						return false;
					}
				}
				else
				{
					if (m_bIntegerOnly)
					{
						valid = false;
						break;
					}
					double f;
					if (TryStringToDouble((String)value, f))
					{
						if (m_sMax.Type != DbValueType::Null && ntl::IsGreater<double>(f, (double)m_sMax))
						{
							error = ReplaceAll(m_sTooBig, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{max}", (String)m_sMax } });
							return false;
						}
						if (m_sMin.Type != DbValueType::Null && ntl::IsLess<double>(f, (double)m_sMin))
						{
							error = ReplaceAll(m_sTooSmall, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{min}", (String)m_sMin } });
							return false;
						}
					}
				}
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
	CDbValidatorNumber *CDbValidatorNumber::setIntegerOnly(const bool &value)
	{
		m_bIntegerOnly = value;
		return this;
	}

	CDbValidatorNumber *CDbValidatorNumber::setStrict(const bool &value)
	{
		m_bStrict = value;
		return this;
	}

	CDbValidatorNumber *CDbValidatorNumber::setMin(const DbValue &value)
	{
		m_sMin = value;
		return this;
	}

	CDbValidatorNumber *CDbValidatorNumber::setMax(const DbValue &value)
	{
		m_sMax = value;
		return this;
	}

	CDbValidatorNumber *CDbValidatorNumber::setTooBig(const String &value)
	{
		m_sTooBig = value;
		return this;
	}

	CDbValidatorNumber *CDbValidatorNumber::setTooSmall(const String &value)
	{
		m_sTooSmall = value;
		return this;
	}
#pragma endregion
}