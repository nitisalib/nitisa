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
#include <vector>

namespace nitisa
{
	class IDbAttribute;

	class CDbModel;

	class CDbValidatorRange :public CDbValidator
	{
	private:
		bool m_bStrict;
		bool m_bNot;
		std::vector<DbValue> m_aRange;
	public:
		// IDbValidator methods
		bool Validate(CDbModel *model, IDbAttribute *attribute, String &error) override;

		CDbValidatorRange();

		CDbValidatorRange *setStrict(const bool &value); // Set whether strict comparison (check type) is required
		CDbValidatorRange *setNot(const bool &value); // Set whether to inverse comparison (NOT in range)
		CDbValidatorRange *setRange(const std::vector<DbValue> &value); // Set list of allowed values

		static ReleasablePtr<CDbValidatorRange> Create(); // Helper static method to create validator in form used in model rule adding methods
	};
}