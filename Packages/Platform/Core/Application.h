// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef _WIN32
	#include "../Windows/Application.h"
#endif
#if defined(__linux__) && !defined(__ANDROID__)
	#include "../Linux/Application.h"
	#ifdef linux
		#undef linux
	#endif
#endif
#ifdef __ANDROID__
	#include "../Android/Application.h"
#endif

namespace nitisa
{
#ifdef _WIN32
	class CApplication :public platform::windows::CApplication
#endif
#if defined(__linux__) && !defined(__ANDROID__)
	class CApplication :public platform::linux::CApplication
#endif
#ifdef __ANDROID__
	class CApplication :public platform::android::CApplication
#endif
	{
	public:
		CApplication();
	};
}