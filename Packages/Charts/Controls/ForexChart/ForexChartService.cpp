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
	namespace charts
	{
	#pragma region Constructor & destructor
		CForexChartService::CForexChartService(CForexChart *control) :
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CForexChartService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				m_pControl->UpdateAutoRanges();
				m_pControl->UpdateHoveredPoint();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CForexChartService::NotifyOnParentFontChange()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CForexChartService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
		}

		void CForexChartService::NotifyOnEnable()
		{
			if (m_pControl->UpdateHoveredPoint() && m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CForexChartService::NotifyOnDisable()
		{
			if (m_pControl->UpdateHoveredPoint() && m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CForexChartService::NotifyOnResize()
		{
			m_pControl->UpdateAutoRanges();
			m_pControl->UpdateHoveredPoint();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CForexChartService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				m_pControl->UpdateAutoRanges();
				m_pControl->UpdateHoveredPoint();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CForexChartService::NotifyOnFontChange()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CForexChartService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
				m_pControl->Render();
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CForexChartService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pControl->UpdateHoveredPoint(m.Position))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CForexChartService::NotifyOnMouseLeave()
		{
			if (m_pControl->UpdateHoveredPoint())
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CForexChartService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->UpdateHoveredPoint(m.Position))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion
	}
}