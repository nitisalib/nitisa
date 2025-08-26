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
		CMemo::CScroll::CScroll(CMemo *memo) :
			CBuiltInScroll(),
			m_pMemo{ memo }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CMemo::CScroll::getControl()
		{
			return m_pMemo;
		}
	#pragma endregion
	}
}