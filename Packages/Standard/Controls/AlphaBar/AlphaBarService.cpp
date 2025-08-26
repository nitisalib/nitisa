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
		CAlphaBarService::CAlphaBarService(CAlphaBar *control) :
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CAlphaBarService::UpdateAlpha(const PointF &pos)
		{
			if (m_pControl->getHeight() > m_pControl->m_fPickerSize)
			{
				float y{ m_pControl->FormToLocal(pos).Y };
				int alpha{ ntl::Clamp<int>(ntl::Round<int>(255 * (1 - (y - m_pControl->m_fPickerSize / 2) / (m_pControl->getHeight() - m_pControl->m_fPickerSize))), 0, 255) };
				if (alpha != m_pControl->m_iAlpha)
				{
					m_pControl->m_iAlpha = alpha;
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					if (m_pControl->OnChange)
						m_pControl->OnChange(m_pControl);
					m_pControl->Repaint(false);
				}
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CAlphaBarService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CAlphaBarService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
		}

		void CAlphaBarService::NotifyOnResize()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CAlphaBarService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region Paint notifications
		void CAlphaBarService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
				m_pControl->Render();
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CAlphaBarService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isCaptureMouse())
				UpdateAlpha(m.Position);
		}

		void CAlphaBarService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m_pControl->isCaptureMouse() && !m.Middle && !m.Right)
			{
				m_pControl->getForm()->CaptureMouse(m_pControl, true);
				UpdateAlpha(m.Position);
			}
		}

		void CAlphaBarService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CAlphaBarService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CAlphaBarService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CAlphaBarService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CAlphaBarService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CAlphaBarService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CAlphaBarService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CAlphaBarService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}
	#pragma endregion
	}
}