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

namespace nitisa
{
	class IDbAttribute;

	class CDbModel;

	class CDbValidatorString :public CDbValidator
	{
	private:
		bool m_bStrict;
		size_t m_iMin;
		size_t m_iMax;
		String m_sTooShort;
		String m_sTooLong;
	public:
		// IDbValidator methods
		bool Validate(CDbModel *model, IDbAttribute *attribute, String &error) override;

		CDbValidatorString();

		CDbValidatorString *setStrict(const bool &value); // Set whether strict comparison (check type) is required
		CDbValidatorString *setMin(const size_t &value); // Set minimum required string length
		CDbValidatorString *setMax(const size_t &value); // Set maximum allowed string length
		CDbValidatorString *setLength(const size_t &value); // Set fixed string length is only allowed
		CDbValidatorString *setTooShort(const String &value); // Set error message indication string is too short
		CDbValidatorString *setTooLong(const String &value); // Set error message indication string is too long

		static ReleasablePtr<CDbValidatorString> Create(); // Helper static method to create validator in form used in model rule adding methods
	};
}