// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#include <Windows.h>

namespace nitisa
{
	namespace platform
	{
		namespace windows
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
				TRACKMOUSEEVENT e;
				e.cbSize = sizeof(TRACKMOUSEEVENT);
				e.dwFlags = TME_LEAVE;
				e.hwndTrack = *reinterpret_cast<HWND*>(&m_pWindow->m_hHandle);
				e.dwHoverTime = HOVER_DEFAULT;
				TrackMouseEvent(&e);
			}
		}
	}
}
#endif