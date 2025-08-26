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
	CDbValidatorCompare::CDbValidatorCompare() :
		CDbValidator(),
		m_eOperator{ Operator::Equals },
		m_eOperands{ Operands::Strings },
		m_sAttribute{ L"" },
		m_fTolerance{ ntl::Tolerance<double> },
		m_bRelativeTolerance{ false },
		m_sMessageNoAttribute{ L"Model has no attribute called '{name}'" }
	{
		m_sMessage = L"{attribute} must be equal to '{compare}'";
	}

	ReleasablePtr<CDbValidatorCompare> CDbValidatorCompare::Create()
	{
		return new CDbValidatorCompare();
	}
#pragma endregion

#pragma region Validation
	bool CDbValidatorCompare::Validate(CDbModel *model, IDbAttribute *attribute, String &error)
	{
		if (ShouldSkip(model, attribute))
			return true;
		DbValue compare{ m_sValue };
		if (!m_sAttribute.empty())
		{
			if (!model->hasAttribute(m_sAttribute))
			{
				error = ReplaceAll(m_sMessageNoAttribute, L"{name}", m_sAttribute);
				return false;
			}
			compare = model->getAttribute(m_sAttribute);
		}
		DbValue value{ attribute->Get() };
		bool valid{ true };
		switch (m_eOperator)
		{
		case Operator::StrictEquals:
			if (value.Type != compare.Type)
			{
				valid = false;
				break;
			}
		case Operator::Equals:
			if (!CheckEquals(value, compare))
				valid = false;
			break;
		case Operator::StrictNotEquals:
			if (value.Type != compare.Type)
				break;
		case Operator::NotEquals:
			if (!CheckNotEquals(value, compare))
				valid = false;
			break;
		case Operator::Greater:
			if (!CheckGreater(value, compare))
				valid = false;
			break;
		case Operator::GreaterEquals:
			if (!CheckGreaterEquals(value, compare))
				valid = false;
			break;
		case Operator::Less:
			if (!CheckLess(value, compare))
				valid = false;
			break;
		case Operator::LessEquals:
			if (!CheckLessEquals(value, compare))
				valid = false;
			break;
		}
		if (!valid)
			error = ReplaceAll(m_sMessage, StringKeyValueArray{ StringKeyValue{ L"{attribute}", attribute->sName }, StringKeyValue{ L"{compare}", (String)compare } });
		return valid;
	}

	bool CDbValidatorCompare::CheckEquals(const DbValue &value, const DbValue &compare)
	{
		switch (m_eOperands)
		{
		case Operands::Integers:
			if ((int64)value != (int64)compare)
				return false;
			break;
		case Operands::Floats:
			if (m_bRelativeTolerance)
			{
				if (ntl::NotEquals<double>((double)value, (double)compare, m_fTolerance))
					return false;
			}
			else
			{
				if (ntl::IsNotEqual<double>((double)value, (double)compare, m_fTolerance))
					return false;
			}
			break;
		default:
			if ((String)value != (String)compare)
				return false;
			break;
		}
		return true;
	}

	bool CDbValidatorCompare::CheckNotEquals(const DbValue &value, const DbValue &compare)
	{
		switch (m_eOperands)
		{
		case Operands::Integers:
			if ((int64)value == (int64)compare)
				return false;
			break;
		case Operands::Floats:
			if (m_bRelativeTolerance)
			{
				if (ntl::Equals<double>((double)value, (double)compare, m_fTolerance))
					return false;
			}
			else
			{
				if (ntl::IsEqual<double>((double)value, (double)compare, m_fTolerance))
					return false;
			}
			break;
		default:
			if ((String)value == (String)compare)
				return false;
			break;
		}
		return true;
	}

	bool CDbValidatorCompare::CheckGreater(const DbValue &value, const DbValue &compare)
	{
		switch (m_eOperands)
		{
		case Operands::Integers:
			if ((int64)value <= (int64)compare)
				return false;
			break;
		case Operands::Floats:
			if (m_bRelativeTolerance)
			{
				if (!ntl::Greater<double>((double)value, (double)compare, m_fTolerance))
					return false;
			}
			else
			{
				if (!ntl::IsGreater<double>((double)value, (double)compare, m_fTolerance))
					return false;
			}
			break;
		default:
			if ((String)value <= (String)compare)
				return false;
			break;
		}
		return true;
	}

	bool CDbValidatorCompare::CheckGreaterEquals(const DbValue &value, const DbValue &compare)
	{
		switch (m_eOperands)
		{
		case Operands::Integers:
			if ((int64)value < (int64)compare)
				return false;
			break;
		case Operands::Floats:
			if (m_bRelativeTolerance)
			{
				if (!ntl::Greater<double>((double)value, (double)compare, m_fTolerance) && !ntl::Equals<double>((double)value, (double)compare, m_fTolerance))
					return false;
			}
			else
			{
				if (!ntl::IsGreaterOrEqual<double>((double)value, (double)compare, m_fTolerance))
					return false;
			}
			break;
		default:
			if ((String)value < (String)compare)
				return false;
			break;
		}
		return true;
	}

	bool CDbValidatorCompare::CheckLess(const DbValue &value, const DbValue &compare)
	{
		switch (m_eOperands)
		{
		case Operands::Integers:
			if ((int64)value >= (int64)compare)
				return false;
			break;
		case Operands::Floats:
			if (m_bRelativeTolerance)
			{
				if (!ntl::Less<double>((double)value, (double)compare, m_fTolerance))
					return false;
			}
			else
			{
				if (!ntl::IsLess<double>((double)value, (double)compare, m_fTolerance))
					return false;
			}
			break;
		default:
			if ((String)value >= (String)compare)
				return false;
			break;
		}
		return true;
	}

	bool CDbValidatorCompare::CheckLessEquals(const DbValue &value, const DbValue &compare)
	{
		switch (m_eOperands)
		{
		case Operands::Integers:
			if ((int64)value > (int64)compare)
				return false;
			break;
		case Operands::Floats:
			if (m_bRelativeTolerance)
			{
				if (!ntl::Less<double>((double)value, (double)compare, m_fTolerance) || !ntl::Equals<double>((double)value, (double)compare, m_fTolerance))
					return false;
			}
			else
			{
				if (!ntl::IsLessOrEqual<double>((double)value, (double)compare, m_fTolerance))
					return false;
			}
			break;
		default:
			if ((String)value > (String)compare)
				return false;
			break;
		}
		return true;
	}
#pragma endregion

#pragma region Setters
	CDbValidatorCompare *CDbValidatorCompare::setOperator(const Operator &value)
	{
		if (value != m_eOperator)
		{
			m_eOperator = value;
			switch (m_eOperator)
			{
			case Operator::StrictEquals:
			case Operator::Equals:
				m_sMessage = L"{attribute} must be equal to '{compare}'";
				break;
			case Operator::StrictNotEquals:
			case Operator::NotEquals:
				m_sMessage = L"{attribute} must not be equal to '{compare}'";
				break;
			case Operator::Greater:
				m_sMessage = L"{attribute} must be greater than '{compare}'";
				break;
			case Operator::GreaterEquals:
				m_sMessage = L"{attribute} must be greater than or equal to '{compare}'";
				break;
			case Operator::Less:
				m_sMessage = L"{attribute} must be less than '{compare}'";
				break;
			case Operator::LessEquals:
				m_sMessage = L"{attribute} must be less than or equal to '{compare}'";
				break;
			}
		}
		return this;
	}

	CDbValidatorCompare *CDbValidatorCompare::setOperands(const Operands &value)
	{
		m_eOperands = value;
		return this;
	}

	CDbValidatorCompare *CDbValidatorCompare::setAttribute(const String &value)
	{
		m_sAttribute = value;
		return this;
	}

	CDbValidatorCompare *CDbValidatorCompare::setValue(const DbValue &value)
	{
		m_sValue = value;
		m_sAttribute.clear();
		return this;
	}

	CDbValidatorCompare *CDbValidatorCompare::setTolerance(const double &value)
	{
		m_fTolerance = value;
		return this;
	}

	CDbValidatorCompare *CDbValidatorCompare::setRelativeTolerance(const bool &value)
	{
		m_bRelativeTolerance = value;
		return this;
	}

	CDbValidatorCompare *CDbValidatorCompare::setMessageNoAttribute(const String &value)
	{
		m_sMessageNoAttribute = value;
		return this;
	}
#pragma endregion
}