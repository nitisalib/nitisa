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

	class CDbValidatorTrim :public CDbValidator
	{
	public:
		// IDbValidator methods
		bool Validate(CDbModel *model, IDbAttribute *attribute, String &error) override;

		CDbValidatorTrim();

		static ReleasablePtr<CDbValidatorTrim> Create(); // Helper static method to create validator in form used in model rule adding methods
	};
}