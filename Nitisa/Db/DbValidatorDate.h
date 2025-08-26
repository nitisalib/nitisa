// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/ReleasablePtr.h"
#include "DbValidatorDateTime.h"

namespace nitisa
{
	class CDbValidatorDate :public CDbValidatorDateTime
	{
	public:
		CDbValidatorDate();

		static ReleasablePtr<CDbValidatorDate> Create(); // Helper static method to create validator in form used in model rule adding methods
	};
}