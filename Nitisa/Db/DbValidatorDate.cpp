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
	CDbValidatorDate::CDbValidatorDate() :
		CDbValidatorDateTime()
	{
		setType(Type::Date);
		setFormat(L"%Y-%m-%d");
	}

	ReleasablePtr<CDbValidatorDate> CDbValidatorDate::Create()
	{
		return new CDbValidatorDate();
	}
#pragma endregion
}