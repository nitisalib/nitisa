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

	class CDbValidatorNumber :public CDbValidator
	{
	private:
		bool m_bIntegerOnly;
		bool m_bStrict;
		DbValue m_sMin;
		DbValue m_sMax;
		String m_sTooBig;
		String m_sTooSmall;
	public:
		// IDbValidator methods
		bool Validate(CDbModel *model, IDbAttribute *attribute, String &error) override;

		CDbValidatorNumber();

		CDbValidatorNumber *setIntegerOnly(const bool &value); // Set whether value should be integer
		CDbValidatorNumber *setStrict(const bool &value); // Set whether strict comparison (check type) is required
		CDbValidatorNumber *setMin(const DbValue &value); // Set minimum allowed value
		CDbValidatorNumber *setMax(const DbValue &value); // Set maximum allowed value
		CDbValidatorNumber *setTooBig(const String &value); // Set error message indicating a value is too big (greater than maximum value)
		CDbValidatorNumber *setTooSmall(const String &value); // Set error message indicating a value is too small (less than minimum value)

		static ReleasablePtr<CDbValidatorNumber> Create(); // Helper static method to create validator in form used in model rule adding methods
	};
}