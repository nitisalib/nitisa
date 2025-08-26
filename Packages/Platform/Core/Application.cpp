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
	CApplication::CApplication() :
	#ifdef _WIN32
		platform::windows::CApplication()
	#endif
	#if defined(__linux__) && !defined(__ANDROID__)
		platform::linux::CApplication()
	#endif
	#ifdef __ANDROID__
		platform::android::CApplication()
	#endif
	{

	}
}