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
			bool CKeyboard::isDown(const Key key)
			{
				return (GetKeyState(CWindow::KeyToVirtual(key)) & 0x8000) > 0;
			}

			bool CKeyboard::isToggled(const Key key)
			{
				return (GetKeyState(CWindow::KeyToVirtual(key)) & 0x0001) > 0;
			}

			void CKeyboard::getControlKeys(bool &ctrl, bool &alt, bool &shift)
			{
				ctrl = (GetKeyState(VK_CONTROL) & 0x8000) > 0;
				alt = (GetKeyState(VK_MENU) & 0x8000) > 0;
				shift = (GetKeyState(VK_SHIFT) & 0x8000) > 0;
			}
		}
	}
}
#endif