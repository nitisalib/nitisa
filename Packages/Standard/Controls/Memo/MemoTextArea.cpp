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
	#pragma region Constructor & destructor
		CMemo::CTextArea::CTextArea(CMemo *memo) :
			CBuiltInTextArea(),
			m_pMemo{ memo }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CMemo::CTextArea::getControl()
		{
			return m_pMemo;
		}

		CBuiltInTextArea::State CMemo::CTextArea::getState()
		{
			return m_pMemo->getState();
		}
	#pragma endregion
	}
}