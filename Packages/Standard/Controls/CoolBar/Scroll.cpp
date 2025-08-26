// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
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
		CCoolBar::CScroll::CScroll(CCoolBar *control) :
			CBuiltInScroll(),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CCoolBar::CScroll::getControl()
		{
			return m_pControl;
		}
	#pragma endregion
	}
}