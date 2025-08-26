// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#if defined(__linux__) && !defined(__ANDROID__)

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
			CWindowService::CWindowService(CWindow *window) :
				m_pWindow{ window }
			{

			}

			void CWindowService::Release()
			{
				delete this;
			}

			IWindowListener *CWindowService::getListener()
			{
				return m_pWindow->m_pListener;
			}

			void CWindowService::setHandle(PlatformHandle value)
			{
				m_pWindow->m_hHandle = value;
			}

			void CWindowService::setListener(IWindowListener *value)
			{
				m_pWindow->m_pListener = value;
			}

			void CWindowService::StartTrackMouseLeave()
			{
				
			}
		}
	}
}
#endif