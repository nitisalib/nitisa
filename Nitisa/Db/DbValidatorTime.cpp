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
	CDbValidatorTime::CDbValidatorTime() :
		CDbValidatorDateTime()
	{
		setType(Type::Time);
		setFormat(L"%H:%M:%S");
	}

	ReleasablePtr<CDbValidatorTime> CDbValidatorTime::Create()
	{
		return new CDbValidatorTime();
	}
#pragma endregion
}