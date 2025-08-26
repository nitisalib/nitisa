// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	CPropertyHandler::CPropertyHandler(IPackage *package, const String &name) :
		CBuiltInControl(L"PropertyHandler"),
		m_pControl{ nullptr },
		m_pPackage{ package }
	{
		m_sName = name;
	}
#pragma endregion

#pragma region Getters
	IControl *CPropertyHandler::getControl()
	{
		return m_pControl;
	}

	IPackage *CPropertyHandler::getPackage()
	{
		return m_pPackage;
	}
#pragma endregion

#pragma region Setters
	bool CPropertyHandler::setControl(IControl *value)
	{
		if (value != m_pControl)
		{
			m_pControl = value;
			return true;
		}
		return false;
	}
#pragma endregion
}