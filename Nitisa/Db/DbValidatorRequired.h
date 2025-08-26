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

	class CDbValidatorRequired :public CDbValidator
	{
	private:
		bool m_bStrict;
		DbValue m_sRequiredValue;
		String m_sMessageValue;
	public:
		// IDbValidator methods
		bool Validate(CDbModel *model, IDbAttribute *attribute, String &error) override;

		CDbValidatorRequired();

		CDbValidatorRequired *setStrict(const bool &value); // Set whether strict comparison (check type) is required. Used when RequiredValue is not Null
		CDbValidatorRequired *setRequiredValue(const DbValue &value); // Set which value is expected to be in attribute. By default any not null value is Ok
		CDbValidatorRequired *setMessageValue(const String &value); // Set error message indication validation failed

		static ReleasablePtr<CDbValidatorRequired> Create(); // Helper static method to create validator in form used in model rule adding methods
	};
}