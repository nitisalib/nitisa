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
		CDriveDropDown::CDropDown::CDropDown(CDriveDropDown *dropdown) :
			CBuiltInDropDown(true, nullptr, nullptr, nullptr),
			m_pDropDown{ dropdown },
			m_cOwner{ this, dropdown }
		{

		}

		IControl *CDriveDropDown::CDropDown::getControl()
		{
			return m_pDropDown;
		}

		CBuiltInDropDown::State CDriveDropDown::CDropDown::getState()
		{
			return m_pDropDown->getState();
		}

		IListItemOwner *CDriveDropDown::CDropDown::QueryListItemOwner()
		{
			return &m_cOwner;
		}
	}
}