// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
			Point CMouse::getPosition()
			{
				::POINT p;
				if (GetCursorPos(&p))
					return Point{ p.x, p.y };
				return Point{ -1, -1 };
			}

			bool CMouse::setPosition(const Point &value)
			{
				return SetCursorPos(value.X, value.Y) ? true : false;
			}
		}
	}
}
#endif