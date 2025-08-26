// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace ide
	{
	#pragma region Constructor & destructor
		CViewH2Service::CViewH2Service(CViewH2 *control):
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CViewH2Service::AlignControls()
		{
			m_pControl->AlignControls();
		}

		void CViewH2Service::CancelDown(const bool check_capture_mouse, const bool check_capture_keyboard)
		{
			if (m_pControl->m_bSeparatorDown)
			{
				m_pControl->m_bSeparatorDown = false;
				if (check_capture_mouse && m_pControl->isCaptureMouse())
					m_pControl->getForm()->ReleaseCaptureMouse();
				if (check_capture_keyboard && m_pControl->isCaptureKeyboard())
					m_pControl->getForm()->ReleaseCaptureKeyboard();
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CViewH2Service::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
		}
	#pragma endregion

	#pragma region Notifications from child controls
		void CViewH2Service::NotifyOnChildTransform(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewH2Service::NotifyOnChildResize(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewH2Service::NotifyOnChildShow(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewH2Service::NotifyOnChildHide(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewH2Service::NotifyOnChildAttach(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewH2Service::NotifyOnChildDetach(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewH2Service::NotifyOnChildBeforeTransform(IControl *control, bool &allowed)
		{
			if (!m_pControl->m_bAligningControls)
				allowed = false;
		}

		void CViewH2Service::NotifyOnChildBeforeResize(IControl *control, bool &allowed)
		{
			if (!m_pControl->m_bAligningControls)
				allowed = false;
		}

		void CViewH2Service::NotifyOnChildBeforeHide(IControl *control, bool &allowed)
		{
			if (!m_pControl->m_bAligningControls)
				allowed = false;
		}
	#pragma endregion

	#pragma region State change notifications
		void CViewH2Service::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
		}

		void CViewH2Service::NotifyOnKillCaptureKeyboard()
		{
			CancelDown(true, false);
		}

		void CViewH2Service::NotifyOnKillCaptureMouse()
		{
			CancelDown(false, true);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CViewH2Service::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			draw_children = false;
			if (ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
			{
				if (m_pControl->getControl(0))
					CNotifier::Render(m_pControl->getControl(0), m, nullptr);
				if (m_pControl->getControl(1))
					CNotifier::Render(m_pControl->getControl(1), m, nullptr);
				if (!m.LastPass)
					m_pControl->Render();
			}
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CViewH2Service::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			if (m_pControl->m_bSeparatorDown && m.Key == Key::Escape)
			{
				CancelDown(true, true);
				m_pControl->setSeparator(m_fOldSeparator);
				processed = true;
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CViewH2Service::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_bSeparatorDown)
			{
				float p{ m_pControl->FormToLocal(m.Position).X + m_fDistance };
				m_pControl->setSeparator(p / m_pControl->getWidth());
				processed = true;
			}
		}

		void CViewH2Service::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (!m_pControl->m_bSeparatorDown)
			{
				if (m_pControl->m_bResizable && !m.Alt && !m.Ctrl && !m.Shift && !m.Middle && !m.Right && m_pControl->isEnabled(true))
				{
					RectF r{ m_pControl->CalculateSeparatorRect() };
					PointF p{ m_pControl->FormToLocal(m.Position) };
					if (r.is_inside(p) && m_pControl->getForm()->CaptureMouse(m_pControl, true))
					{
						if (m_pControl->getForm()->CaptureKeyboard(m_pControl))
						{
							m_fOldSeparator = m_pControl->m_fSeparator;
							m_fDistance = p.X - (r.Left + r.Right) * 0.5f;
							m_pControl->m_bSeparatorDown = true;
							m_pControl->Repaint(false);
							processed = true;
						}
						else
							m_pControl->getForm()->ReleaseCaptureMouse();
					}
				}
			}
			else
			{
				CancelDown(true, true);
				processed = true;
			}
		}

		void CViewH2Service::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_bSeparatorDown)
			{
				CancelDown(true, true);
				processed = true;
			}
		}

		void CViewH2Service::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_bResizable && !m_pControl->m_bSeparatorDown && !m.Alt && !m.Ctrl && !m.Shift && !m.Middle && !m.Right && m_pControl->isEnabled(true))
			{
				RectF r{ m_pControl->CalculateSeparatorRect() };
				PointF p{ m_pControl->FormToLocal(m.Position) };
				if (r.is_inside(p))
				{
					m_pControl->setSeparator(0.5f);
					processed = true;
				}
			}
		}

		void CViewH2Service::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewH2Service::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewH2Service::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewH2Service::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewH2Service::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewH2Service::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}
	#pragma endregion
	}
}