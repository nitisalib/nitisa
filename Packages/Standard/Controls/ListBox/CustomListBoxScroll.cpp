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
	namespace standard
	{
	#pragma region Constructor & destructor
		CCustomListBox::CScroll::CScroll(CCustomListBox *listbox) :
			CBuiltInScroll(),
			m_pListBox{ listbox }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CCustomListBox::CScroll::getControl()
		{
			return m_pListBox;
		}
	#pragma endregion
	}
}