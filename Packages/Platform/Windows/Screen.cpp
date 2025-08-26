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
			int CScreen::getWidth()
			{
				return (int)GetSystemMetrics(SM_CXSCREEN);
			}

			int CScreen::getHeight()
			{
				return (int)GetSystemMetrics(SM_CYSCREEN);
			}

			Point CScreen::getDPI()
			{
				return DesignDPI;
			}
		}
	}
}
#endif