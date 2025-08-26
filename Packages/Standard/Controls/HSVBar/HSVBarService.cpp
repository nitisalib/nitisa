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
		CHSVBarService::CHSVBarService(CHSVBar *bar) :
			CControlService(bar),
			m_pBar{ bar }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CHSVBarService::UpdateHue(const PointF &pos)
		{
			if (m_pBar->getHeight() > m_pBar->m_fPickerSize)
			{
				float y{ m_pBar->FormToLocal(pos).Y };
				int hue{ ntl::Clamp<int>(ntl::Round<int>(360 * (1 - (y - m_pBar->m_fPickerSize / 2) / (m_pBar->getHeight() - m_pBar->m_fPickerSize))), 0, 360) };
				if (hue != m_pBar->m_iHue)
				{
					m_pBar->m_iHue = hue;
					if (m_pBar->m_pCanvas)
						m_pBar->m_pCanvas->setValid(false);
					if (m_pBar->OnChange)
						m_pBar->OnChange(m_pBar);
					if (m_pBar->m_pHSVPlane)
						m_pBar->m_pHSVPlane->setHue(m_pBar->m_iHue);
					m_pBar->Repaint(false);
				}
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CHSVBarService::NotifyOnDetach()
		{
			m_pBar->m_pHSVPlane = nullptr;
		}
	#pragma endregion

	#pragma region Component notifications
		void CHSVBarService::NotifyOnComponentDetach(IComponent *component)
		{
			if (m_pBar->m_pHSVPlane && cast<IHSVPlane*>(component) == m_pBar->m_pHSVPlane)
				m_pBar->m_pHSVPlane = nullptr;
		}
	#pragma endregion

	#pragma region Control notifications
		void CHSVBarService::NotifyOnControlDetach(IControl *control)
		{
			if (m_pBar->m_pHSVPlane && cast<IHSVPlane*>(control) == m_pBar->m_pHSVPlane)
				m_pBar->m_pHSVPlane = nullptr;
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CHSVBarService::NotifyOnParentStyleChange()
		{
			if (m_pBar->getStyle())
			{
				m_pBar->UpdateFromStyle(m_pBar->getStyle());
				if (m_pBar->m_pCanvas)
					m_pBar->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CHSVBarService::NotifyOnFreeResources()
		{
			if (m_pBar->m_pCanvas)
			{
				m_pBar->m_pCanvas->Release();
				m_pBar->m_pCanvas = nullptr;
			}
		}

		void CHSVBarService::NotifyOnResize()
		{
			if (m_pBar->m_pCanvas)
				m_pBar->m_pCanvas->setValid(false);
		}

		void CHSVBarService::NotifyOnStyleChange()
		{
			if (m_pBar->getStyle())
			{
				m_pBar->UpdateFromStyle(m_pBar->getStyle());
				if (m_pBar->m_pCanvas)
					m_pBar->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region Paint notifications
		void CHSVBarService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pBar->getWidth(), 0) && ntl::IsGreater<float>(m_pBar->getHeight(), 0))
				m_pBar->Render();
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CHSVBarService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pBar->isCaptureMouse())
				UpdateHue(m.Position);
		}

		void CHSVBarService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m_pBar->isCaptureMouse() && !m.Middle && !m.Right)
			{
				m_pBar->getForm()->CaptureMouse(m_pBar, true);
				UpdateHue(m.Position);
			}
		}

		void CHSVBarService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pBar->isCaptureMouse())
				m_pBar->getForm()->ReleaseCaptureMouse();
		}

		void CHSVBarService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pBar->isCaptureMouse())
				m_pBar->getForm()->ReleaseCaptureMouse();
		}

		void CHSVBarService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m_pBar->isCaptureMouse())
				m_pBar->getForm()->ReleaseCaptureMouse();
		}

		void CHSVBarService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (m_pBar->isCaptureMouse())
				m_pBar->getForm()->ReleaseCaptureMouse();
		}

		void CHSVBarService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pBar->isCaptureMouse())
				m_pBar->getForm()->ReleaseCaptureMouse();
		}

		void CHSVBarService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m_pBar->isCaptureMouse())
				m_pBar->getForm()->ReleaseCaptureMouse();
		}

		void CHSVBarService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (m_pBar->isCaptureMouse())
				m_pBar->getForm()->ReleaseCaptureMouse();
		}

		void CHSVBarService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pBar->isCaptureMouse())
				m_pBar->getForm()->ReleaseCaptureMouse();
		}
	#pragma endregion
	}
}