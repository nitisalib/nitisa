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
	CStyleImage::CStyleImage(const String &name, const nitisa::Image &data)
	{
		m_sName = name;
		m_sImage = data;
	}

	CStyleImage::CStyleImage(const String &name, const int width, const int height, const Color *data)
	{
		m_sName = name;
		m_sImage.setData(width, height, data);
	}
}