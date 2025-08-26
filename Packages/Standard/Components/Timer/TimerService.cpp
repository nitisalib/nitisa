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
	namespace standard
	{
	#pragma region Constructor & destructor
		CTimerService::CTimerService(CTimer *timer) :
			CComponentService{ timer },
			m_pTimer{ timer }
		{

		}
	#pragma endregion

	#pragma region Notifications
		void CTimerService::NotifyOnAttach()
		{
			if (m_pTimer->m_bEnabled && !m_pTimer->m_iTimer && m_pTimer->getForm())
				m_pTimer->m_iTimer = m_pTimer->getForm()->CreateTimer(&m_pTimer->m_cTimerListener, m_pTimer->m_fInterval);
		}

		void CTimerService::NotifyOnFreeResources()
		{
			m_pTimer->FreeTimer();
		}
	#pragma endregion
	}
}