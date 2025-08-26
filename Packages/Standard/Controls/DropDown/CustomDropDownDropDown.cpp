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
	namespace standard
	{
		CCustomDropDown::CDropDown::CDropDown(CCustomDropDown *dropdown) :
			CBuiltInDropDown(true, nullptr, nullptr, nullptr),
			m_pDropDown{ dropdown }
		{

		}

		IControl *CCustomDropDown::CDropDown::getControl()
		{
			return m_pDropDown;
		}

		CBuiltInDropDown::State CCustomDropDown::CDropDown::getState()
		{
			return m_pDropDown->getState();
		}
	}
}