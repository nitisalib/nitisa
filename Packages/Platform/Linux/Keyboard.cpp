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
			CKeyboard::CKeyboard(CApplication *application) :
				m_pApplication{ application }
			{

			}

			bool CKeyboard::isDown(const Key key)
			{
				if (*reinterpret_cast<Display**>(&m_pApplication->m_hHandle))
				{
					char keys_return[32];
					XQueryKeymap(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), keys_return);
					KeyCode kc2{ XKeysymToKeycode(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), (KeySym)CWindow::KeyToVirtual(key)) };
					bool pressed = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
					return pressed;
				}
				return false;
			}

			bool CKeyboard::isToggled(const Key key)
			{
				if (key == Key::CapsLock || key == Key::NumLock)
				{
					if (*reinterpret_cast<Display**>(&m_pApplication->m_hHandle))
					{
						XKeyboardState x;
						XGetKeyboardControl(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), &x);
						if (key == Key::CapsLock)
							return (x.led_mask & 1) ? true : false;
						if (key == Key::NumLock)
							return (x.led_mask & 2) ? true : false;
					}
				}
				return isDown(key);
			}

			void CKeyboard::getControlKeys(bool &ctrl, bool &alt, bool &shift)
			{
				ctrl = alt = shift = false;
				if (*reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow))
				{
					Window root, child;
					int x_root, y_root, x_child, y_child;
					unsigned int mask;
					if (XQueryPointer(*reinterpret_cast<Display**>(&m_pApplication->m_hHandle), *reinterpret_cast<Window*>(&m_pApplication->m_hRootWindow), &root, &child, &x_root, &y_root, &x_child, &y_child, &mask))
					{
						ctrl = (mask & ControlMask) > 0;
						alt = (mask & Mod1Mask) > 0;
						shift = (mask & ShiftMask) > 0;
					}
				}
			}
		}
	}
}
#endif