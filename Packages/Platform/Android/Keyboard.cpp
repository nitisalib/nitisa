// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

#ifdef __ANDROID__
namespace nitisa
{
	namespace platform
	{
		namespace android
		{
			CKeyboard::CKeyboard() :
				m_bCtrl{ false },
				m_bAlt{ false },
				m_bShift{ false },
				m_bCapsLock{ false },
				m_bScrollLock{ false },
				m_bNumLock{ false }
			{

			}

			bool CKeyboard::isDown(const Key key)
			{
				return false;
			}

			bool CKeyboard::isToggled(const Key key)
			{
				switch (key)
				{
				case Key::CapsLock:
					return m_bCapsLock;
				case Key::NumLock:
					return m_bNumLock;
				case Key::ScrollLock:
					return m_bScrollLock;
				default:
					return false;
				}
			}

			void CKeyboard::getControlKeys(bool &ctrl, bool &alt, bool &shift)
			{
				ctrl = m_bCtrl;
				alt = m_bAlt;
				shift = m_bShift;
			}
		}
	}
}
#endif