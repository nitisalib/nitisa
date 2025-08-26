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
		CCustomRadialChartService::CCustomRadialChartService(CCustomRadialChart *control) :
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CCustomRadialChartService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				m_pControl->UpdateHoveredPoint();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CCustomRadialChartService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
		}

		void CCustomRadialChartService::NotifyOnResize()
		{
			m_pControl->UpdateHoveredPoint();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CCustomRadialChartService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				m_pControl->UpdateHoveredPoint();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region Paint notifications
		void CCustomRadialChartService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
				m_pControl->Render();
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CCustomRadialChartService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pControl->isEnabled(true) && m_pControl->UpdateHoveredPoint(m.Position))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CCustomRadialChartService::NotifyOnMouseLeave()
		{
			if (m_pControl->isEnabled(true) && m_pControl->UpdateHoveredPoint())
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CCustomRadialChartService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true) && m_pControl->UpdateHoveredPoint(m.Position))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion
	}
}