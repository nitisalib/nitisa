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
		CHSVPlaneService::CHSVPlaneService(CHSVPlane *plane) :
			CControlService(plane),
			m_pPlane{ plane }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CHSVPlaneService::UpdateSV(const PointF &pos)
		{
			PointF local{ m_pPlane->FormToLocal(pos) };
			float s{ ntl::Clamp<float>(local.X / m_pPlane->getWidth(), 0.0f, 1.0f) };
			float v{ ntl::Clamp<float>(1 - local.Y / m_pPlane->getHeight(), 0.0f, 1.0f) };
			if (ntl::IsNotEqual<float>(s, m_pPlane->m_fSaturation) || ntl::IsNotEqual<float>(v, m_pPlane->m_fValue))
			{
				m_pPlane->m_fSaturation = s;
				m_pPlane->m_fValue = v;
				if (m_pPlane->m_pCanvas)
					m_pPlane->m_pCanvas->setValid(false);
				if (m_pPlane->OnChange)
					m_pPlane->OnChange(m_pPlane);
				m_pPlane->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CHSVPlaneService::NotifyOnParentStyleChange()
		{
			if (m_pPlane->getStyle())
			{
				m_pPlane->UpdateFromStyle(m_pPlane->getStyle());
				if (m_pPlane->m_pCanvas)
					m_pPlane->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CHSVPlaneService::NotifyOnFreeResources()
		{
			if (m_pPlane->m_pCanvas)
			{
				m_pPlane->m_pCanvas->Release();
				m_pPlane->m_pCanvas = nullptr;
			}
		}

		void CHSVPlaneService::NotifyOnResize()
		{
			if (m_pPlane->m_pCanvas)
				m_pPlane->m_pCanvas->setValid(false);
		}

		void CHSVPlaneService::NotifyOnStyleChange()
		{
			if (m_pPlane->getStyle())
			{
				m_pPlane->UpdateFromStyle(m_pPlane->getStyle());
				if (m_pPlane->m_pCanvas)
					m_pPlane->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region Paint notifications
		void CHSVPlaneService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pPlane->getWidth(), 0) && ntl::IsGreater<float>(m_pPlane->getHeight(), 0))
				m_pPlane->Render();
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CHSVPlaneService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pPlane->isCaptureMouse())
				UpdateSV(m.Position);
		}

		void CHSVPlaneService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m_pPlane->isCaptureMouse() && !m.Middle && !m.Right)
			{
				m_pPlane->getForm()->CaptureMouse(m_pPlane, true);
				UpdateSV(m.Position);
			}
		}

		void CHSVPlaneService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pPlane->isCaptureMouse())
				m_pPlane->getForm()->ReleaseCaptureMouse();
		}

		void CHSVPlaneService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pPlane->isCaptureMouse())
				m_pPlane->getForm()->ReleaseCaptureMouse();
		}

		void CHSVPlaneService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m_pPlane->isCaptureMouse())
				m_pPlane->getForm()->ReleaseCaptureMouse();
		}

		void CHSVPlaneService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (m_pPlane->isCaptureMouse())
				m_pPlane->getForm()->ReleaseCaptureMouse();
		}

		void CHSVPlaneService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pPlane->isCaptureMouse())
				m_pPlane->getForm()->ReleaseCaptureMouse();
		}

		void CHSVPlaneService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m_pPlane->isCaptureMouse())
				m_pPlane->getForm()->ReleaseCaptureMouse();
		}

		void CHSVPlaneService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (m_pPlane->isCaptureMouse())
				m_pPlane->getForm()->ReleaseCaptureMouse();
		}

		void CHSVPlaneService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pPlane->isCaptureMouse())
				m_pPlane->getForm()->ReleaseCaptureMouse();
		}
	#pragma endregion
	}
}