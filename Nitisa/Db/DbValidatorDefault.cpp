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
	CDbValidatorDefault::CDbValidatorDefault() :
		CDbValidator()
	{
		
	}

	ReleasablePtr<CDbValidatorDefault> CDbValidatorDefault::Create()
	{
		return new CDbValidatorDefault();
	}
#pragma endregion

#pragma region Validation
	bool CDbValidatorDefault::Validate(CDbModel *model, IDbAttribute *attribute, String &error)
	{
		attribute->Set(m_sValue);
		return true;
	}
#pragma endregion

#pragma region Setters
	CDbValidatorDefault *CDbValidatorDefault::setValue(const DbValue &value)
	{
		m_sValue = value;
		return this;
	}
#pragma endregion
}