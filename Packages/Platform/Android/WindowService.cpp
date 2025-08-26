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
			CWindowService::CWindowService(CWindow *window) :
				m_pWindow{ window }
			{

			}

			void CWindowService::Release()
			{
				delete this;
			}
		#pragma endregion

		#pragma region Getters
			IWindowListener *CWindowService::getListener()
			{
				return m_pWindow->m_pListener;
			}
		#pragma endregion

		#pragma region Setters
			void CWindowService::setHandle(PlatformHandle value)
			{
				// Unsupported
			}

			void CWindowService::setListener(IWindowListener *value)
			{
				m_pWindow->m_pListener = value;
			}
		#pragma endregion

		#pragma region Helpers
			void CWindowService::StartTrackMouseLeave()
			{
				// Do nothing
			}
		#pragma endregion
		}
	}
}
#endif