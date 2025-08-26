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
	CStyleSkin::CStyleSkin(const String &name, IStyleImage *image, const RectF &rect) :
		m_pImage{ image }
	{
		m_sName = name;
		m_sRect = rect;
	}

	IStyleImage *CStyleSkin::getImage()
	{
		return m_pImage;
	}
}