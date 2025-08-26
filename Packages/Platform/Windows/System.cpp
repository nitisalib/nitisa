// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
			CSystem::CSystem()
			{
				m_ePlatform = PlatformType::Windows;
				m_sDirectorySeparator = L'\\';
			}
		}
	}
}
#endif