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
		CScrollBox::CScroll::CScroll(CScrollBox *scrollbox) :
			CBuiltInScroll(),
			m_pScrollBox{ scrollbox }
		{

		}

		IControl *CScrollBox::CScroll::getControl()
		{
			return m_pScrollBox;
		}
	}
}