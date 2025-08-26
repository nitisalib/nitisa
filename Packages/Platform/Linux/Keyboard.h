// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "Nitisa/Core/Key.h"
#include "Nitisa/Interfaces/IKeyboard.h"

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
			class CApplication;

			class CKeyboard :public virtual IKeyboard
			{
			private:
				CApplication *m_pApplication;
			public:
				bool isDown(const Key key) override;
				bool isToggled(const Key key) override; // For the keys with are not CapsLock and NumsLock return the same as isDown()
				void getControlKeys(bool &ctrl, bool &alt, bool &shift) override;

				CKeyboard(CApplication *application);
			};
		}
	}
}
#endif