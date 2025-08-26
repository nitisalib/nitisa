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
	CDbValidatorTrim::CDbValidatorTrim() :
		CDbValidator()
	{
		setSkipOnEmpty(false);
	}

	ReleasablePtr<CDbValidatorTrim> CDbValidatorTrim::Create()
	{
		return new CDbValidatorTrim();
	}
#pragma endregion

#pragma region Validation
	bool CDbValidatorTrim::Validate(CDbModel *model, IDbAttribute *attribute, String &error)
	{
		if (ShouldSkip(model, attribute))
			return true;
		attribute->Set(Trim((String)attribute->Get()));
		return true;
	}
#pragma endregion
}