// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#if defined(__linux__) && !defined(__ANDROID__)
#include <X11/Xlib.h>

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
			CMouse::CMouse(CApplication *application) :
				m_pApplication{ application }
			{

			}

			Point CMouse::getPosition()
			{
				if (*reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow))
				{
					Window root, child;
					int x_root, y_root, x_child, y_child;
					unsigned int mask;
					if (XQueryPointer(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), &root, &child, &x_root, &y_root, &x_child, &y_child, &mask))
						return Point{ x_root, y_root };
				}
				return Point{ -1, -1 };
			}

			bool CMouse::setPosition(const Point &value)
			{
				if (*reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow))
				{
					XWarpPointer(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), None, *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), 0, 0, 0, 0, value.X, value.Y);
					return true;
				}
				return false;
			}
		}
	}
}
#endif