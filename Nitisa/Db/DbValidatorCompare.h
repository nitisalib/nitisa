// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/ReleasablePtr.h"
#include "../Core/Strings.h"
#include "DbValidator.h"
#include "DbValue.h"

namespace nitisa
{
	class IDbAttribute;

	class CDbModel;

	class CDbValidatorCompare :public CDbValidator
	{
	public:
		enum class Operator // Comparison operator type
		{
			StrictEquals, // = with type check
			Equals, // =
			StrictNotEquals, // != with type check
			NotEquals, // !=
			Greater, // >
			GreaterEquals, // >=
			Less, // <
			LessEquals // <=
		};

		enum class Operands // Operand type
		{
			Strings,
			Integers,
			Floats
		};
	private:
		Operator m_eOperator;
		Operands m_eOperands;
		String m_sAttribute;
		DbValue m_sValue;
		double m_fTolerance;
		bool m_bRelativeTolerance;
		String m_sMessageNoAttribute;

		bool CheckEquals(const DbValue &value, const DbValue &compare);
		bool CheckNotEquals(const DbValue &value, const DbValue &compare);
		bool CheckGreater(const DbValue &value, const DbValue &compare);
		bool CheckGreaterEquals(const DbValue &value, const DbValue &compare);
		bool CheckLess(const DbValue &value, const DbValue &compare);
		bool CheckLessEquals(const DbValue &value, const DbValue &compare);
	public:
		// IDbValidator methods
		bool Validate(CDbModel *model, IDbAttribute *attribute, String &error) override;

		CDbValidatorCompare();

		CDbValidatorCompare *setOperator(const Operator &value); // Set comparison operator type
		CDbValidatorCompare *setOperands(const Operands &value); // Set operands type
		CDbValidatorCompare *setAttribute(const String &value); // Set attribute name to be compared with
		CDbValidatorCompare *setValue(const DbValue &value); // Set value to be compared with
		CDbValidatorCompare *setTolerance(const double &value); // Set absolute comparison tolerance when comparing float values
		CDbValidatorCompare *setRelativeTolerance(const bool &value); // Set relative comparison tolerance when comparing float values
		CDbValidatorCompare *setMessageNoAttribute(const String &value); // Set error message indicating specified attribute is not found in model

		static ReleasablePtr<CDbValidatorCompare> Create(); // Helper static method to create validator in form used in model rule adding methods
	};
}