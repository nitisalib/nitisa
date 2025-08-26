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
	#pragma region CTimerListener
		CTimer::CTimerListener::CTimerListener(CTimer *control) :
			m_pControl{ control }
		{

		}

		void CTimer::CTimerListener::NotifyOnTimer(const PlatformHandle id)
		{
			if (m_pControl->OnTimer)
				m_pControl->OnTimer(m_pControl);
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CTimer::CTimer() :
			CComponent(L"Timer"),
			m_iTimer{ 0 },
			m_fInterval{ 1 },
			m_bEnabled{ false },
			m_cTimerListener{ this }
		{
			setService(new CTimerService(this), true);
			OnTimer = nullptr;
		}

		CTimer::CTimer(IForm *parent) :CTimer()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Getters
		float CTimer::getInterval()
		{
			return m_fInterval;
		}

		bool CTimer::isEnabled()
		{
			return m_bEnabled;
		}
	#pragma endregion

	#pragma region Setters
		bool CTimer::setInterval(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fInterval))
			{
				m_fInterval = value;
				if (m_bEnabled && m_iTimer && getForm())
					getForm()->ResetTimer(m_iTimer, m_fInterval);
				return true;
			}
			return false;
		}

		bool CTimer::setEnabled(const bool value)
		{
			if (value != m_bEnabled)
			{
				m_bEnabled = value;
				if (m_bEnabled && !m_iTimer && getForm())
					m_iTimer = getForm()->CreateTimer(&m_cTimerListener, m_fInterval);
				if (!m_bEnabled)
					FreeTimer();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CTimer::FreeTimer()
		{
			if (getForm())
			{
				getForm()->DeleteTimer(m_iTimer);
				m_iTimer = 0;
			}
		}
	#pragma endregion
	}
}