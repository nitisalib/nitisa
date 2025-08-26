// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	CBuiltInDropDown::CScroll::CScroll(CBuiltInDropDown *dropdown) :
		CBuiltInScroll(),
		m_pDropDown{ dropdown }
	{

	}
#pragma endregion

#pragma region Getters
	IControl *CBuiltInDropDown::CScroll::getControl()
	{
		return m_pDropDown->getControl();
	}
#pragma endregion
}