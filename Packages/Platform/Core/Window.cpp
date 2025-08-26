// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	IWindow *CWindow::Create()
	{
	#ifdef _WIN32
		return new platform::windows::CWindow();
	#endif
	#if defined(__linux__) && !defined(__ANDROID__)
		return new platform::linux::CWindow();
	#endif
	#ifdef __ANDROID__
		return new platform::android::CWindow();
	#endif
	}
}