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

	class CDbValidatorBoolean :public CDbValidator
	{
	private:
		bool m_bStrict;
	public:
		// IDbValidator methods
		bool Validate(CDbModel *model, IDbAttribute *attribute, String &error) override;

		CDbValidatorBoolean();

		CDbValidatorBoolean *setStrict(const bool &value); // Set whether to check attribute data type as well (should be boolean if strict check is active)

		static ReleasablePtr<CDbValidatorBoolean> Create(); // Helper static method to create validator in form used in model rule adding methods
	};
}