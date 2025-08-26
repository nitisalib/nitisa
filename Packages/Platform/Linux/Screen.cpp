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
			CScreen::CScreen(CApplication *application) :
				m_pApplication{ application }
			{

			}

			int CScreen::getWidth()
			{
				if (*reinterpret_cast<Display**>(&m_pApplication->m_hHandle))
					return XDisplayWidth(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), DefaultScreen(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle)));
				return 0;
			}

			int CScreen::getHeight()
			{
				if (*reinterpret_cast<Display**>(&m_pApplication->m_hHandle))
					return XDisplayHeight(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), DefaultScreen(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle)));
				return 0;
			}

			Point CScreen::getDPI()
			{
				if (*reinterpret_cast<Display**>(&m_pApplication->m_hHandle))
				{
					return Point{
						ntl::Round<int>((float)XDisplayWidth(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), DefaultScreen(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle))) * 25.4f /
							(float)XDisplayWidthMM(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), DefaultScreen(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle)))),
						ntl::Round<int>((float)XDisplayHeight(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), DefaultScreen(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle))) * 25.4f /
							(float)XDisplayHeightMM(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), DefaultScreen(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle))))
					};
				}
				return Point{ 96, 96 };
			}
		}
	}
}
#endif