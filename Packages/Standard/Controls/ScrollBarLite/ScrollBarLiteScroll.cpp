// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		CScrollBarLite::CScroll::CScroll(CScrollBarLite *control) :
			CBuiltInScrollLite(),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CScrollBarLite::CScroll::getControl()
		{
			return m_pControl;
		}
	#pragma endregion
	}
}