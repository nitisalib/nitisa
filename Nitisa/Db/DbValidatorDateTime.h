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
#include "DbDateTime.h"
#include "DbValidator.h"

namespace nitisa
{
	class IDbAttribute;

	class CDbModel;

	class CDbValidatorDateTime :public CDbValidator
	{
	public:
		enum class Type // Comparison type
		{
			Date, // As date only
			Time, // As time only
			DateTime // Both date and time
		};
	private:
		bool m_bStrict;
		Type m_eType;
		String m_sFormat;
		DbDateTime m_sMin;
		DbDateTime m_sMax;
		String m_sTooBig;
		String m_sTooSmall;
	public:
		// IDbValidator methods
		bool Validate(CDbModel *model, IDbAttribute *attribute, String &error) override;

		CDbValidatorDateTime();

		CDbValidatorDateTime *setStrict(const bool &value); // Set whether strict comparison (type check) is required
		CDbValidatorDateTime *setType(const Type &value); // Set comparison type
		CDbValidatorDateTime *setFormat(const String &value); // Set format to convert from string to datetime
		CDbValidatorDateTime *setMin(const DbDateTime &value); // Set minimum value
		CDbValidatorDateTime *setMax(const DbDateTime &value); // Set maximum value
		CDbValidatorDateTime *setTooBig(const String &value); // Set error message indicating a value is too big (greater than maximum value)
		CDbValidatorDateTime *setTooSmall(const String &value); // Set error message indicating a value is too small (less than minimum value)

		static ReleasablePtr<CDbValidatorDateTime> Create(); // Helper static method to create validator in form used in model rule adding methods
	};
}