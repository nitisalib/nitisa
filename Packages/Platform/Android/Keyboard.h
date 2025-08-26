// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "Nitisa/Core/Key.h"
#include "Nitisa/Interfaces/IKeyboard.h"

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
			class CApplication;

			class CKeyboard :public virtual IKeyboard
			{
				friend CApplication;
			private:
				bool m_bCtrl;
				bool m_bAlt;
				bool m_bShift;
				bool m_bCapsLock;
				bool m_bScrollLock;
				bool m_bNumLock;
			public:
				bool isDown(const Key key) override; // Always return false
				bool isToggled(const Key key) override; // Works only for CAPS LOCK, SCROLL LOCK, NUM LOCK. Return last known state
				void getControlKeys(bool &ctrl, bool &alt, bool &shift) override; // Return last know state(if used outside key events/notifications, the result may be wrong)

				CKeyboard();
			};
		}
	}
}
#endif