// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef __ANDROID__
#include "NativeApplication.h"

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
		#pragma region Constructor & destructor
			CScreen::CScreen(CApplication *application) :
				m_pApplication{ application }
			{

			}
		#pragma endregion

		#pragma region Getters
			int CScreen::getWidth()
			{
				if (NativeApplication::getWindow())
					return ANativeWindow_getWidth(NativeApplication::getWindow());
				return 0;
			}

			int CScreen::getHeight()
			{
				if (NativeApplication::getWindow())
					return ANativeWindow_getHeight(NativeApplication::getWindow());
				return 0;
			}

			Point CScreen::getDPI()
			{
				if (m_pApplication->getConfiguration())
					return Point{ AConfiguration_getScreenWidthDp(m_pApplication->getConfiguration()), AConfiguration_getScreenHeightDp(m_pApplication->getConfiguration()) };
				return DesignDPI;
			}
		#pragma endregion
		}
	}
}
#endif