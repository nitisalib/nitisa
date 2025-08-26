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
		CViewV3V1Service::CViewV3V1Service(CViewV3V1 *control) :
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CViewV3V1Service::AlignControls()
		{
			m_pControl->AlignControls();
		}

		void CViewV3V1Service::CancelDown(const bool check_capture_mouse, const bool check_capture_keyboard)
		{
			if (m_pControl->m_eDownElement != CViewV3V1::Element::None)
			{
				m_pControl->m_eDownElement = CViewV3V1::Element::None;
				if (check_capture_mouse && m_pControl->isCaptureMouse())
					m_pControl->getForm()->ReleaseCaptureMouse();
				if (check_capture_keyboard && m_pControl->isCaptureKeyboard())
					m_pControl->getForm()->ReleaseCaptureKeyboard();
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CViewV3V1Service::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
		}
	#pragma endregion

	#pragma region Notifications from child controls
		void CViewV3V1Service::NotifyOnChildTransform(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewV3V1Service::NotifyOnChildResize(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewV3V1Service::NotifyOnChildShow(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewV3V1Service::NotifyOnChildHide(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewV3V1Service::NotifyOnChildAttach(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewV3V1Service::NotifyOnChildDetach(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewV3V1Service::NotifyOnChildBeforeTransform(IControl *control, bool &allowed)
		{
			if (!m_pControl->m_bAligningControls)
				allowed = false;
		}

		void CViewV3V1Service::NotifyOnChildBeforeResize(IControl *control, bool &allowed)
		{
			if (!m_pControl->m_bAligningControls)
				allowed = false;
		}

		void CViewV3V1Service::NotifyOnChildBeforeHide(IControl *control, bool &allowed)
		{
			if (!m_pControl->m_bAligningControls)
				allowed = false;
		}
	#pragma endregion

	#pragma region State change notifications
		void CViewV3V1Service::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
		}

		void CViewV3V1Service::NotifyOnKillCaptureKeyboard()
		{
			CancelDown(true, false);
		}

		void CViewV3V1Service::NotifyOnKillCaptureMouse()
		{
			CancelDown(false, true);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CViewV3V1Service::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			draw_children = false;
			if (ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
			{
				if (m_pControl->getControl(0))
					CNotifier::Render(m_pControl->getControl(0), m, nullptr);
				if (m_pControl->getControl(1))
					CNotifier::Render(m_pControl->getControl(1), m, nullptr);
				if (m_pControl->getControl(2))
					CNotifier::Render(m_pControl->getControl(2), m, nullptr);
				if (m_pControl->getControl(3))
					CNotifier::Render(m_pControl->getControl(3), m, nullptr);
				if (!m.LastPass)
					m_pControl->Render();
			}
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CViewV3V1Service::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Escape)
			{
				if (m_pControl->m_eDownElement == CViewV3V1::Element::SeparatorH)
				{
					CancelDown(true, true);
					m_pControl->setSeparatorH(m_fOldSeparator);
					processed = true;
				}
				else if (m_pControl->m_eDownElement == CViewV3V1::Element::SeparatorV1)
				{
					CancelDown(true, true);
					m_pControl->setSeparatorV1(m_fOldSeparator);
					processed = true;
				}
				else if (m_pControl->m_eDownElement == CViewV3V1::Element::SeparatorV2)
				{
					CancelDown(true, true);
					m_pControl->setSeparatorV2(m_fOldSeparator);
					processed = true;
				}
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CViewV3V1Service::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_eDownElement == CViewV3V1::Element::SeparatorH)
			{
				float p{ m_pControl->FormToLocal(m.Position).X + m_fDistance };
				m_pControl->setSeparatorH(p / m_pControl->getWidth());
				processed = true;
			}
			else if (m_pControl->m_eDownElement == CViewV3V1::Element::SeparatorV1)
			{
				float p{ m_pControl->FormToLocal(m.Position).Y + m_fDistance };
				m_pControl->setSeparatorV1(p / m_pControl->getHeight());
				processed = true;
			}
			else if (m_pControl->m_eDownElement == CViewV3V1::Element::SeparatorV2)
			{
				float p{ m_pControl->FormToLocal(m.Position).Y + m_fDistance };
				m_pControl->setSeparatorV2(p / m_pControl->getHeight());
				processed = true;
			}
		}

		void CViewV3V1Service::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_eDownElement == CViewV3V1::Element::None)
			{
				if (m_pControl->m_bResizable && !m.Alt && !m.Ctrl && !m.Shift && !m.Middle && !m.Right && m_pControl->isEnabled(true))
				{
					RectF r{ m_pControl->CalculateSeparatorHRect() };
					PointF p{ m_pControl->FormToLocal(m.Position) };
					if (r.is_inside(p) && m_pControl->getForm()->CaptureMouse(m_pControl, true))
					{
						if (m_pControl->getForm()->CaptureKeyboard(m_pControl))
						{
							m_fOldSeparator = m_pControl->m_fSeparatorH;
							m_fDistance = p.X - (r.Left + r.Right) * 0.5f;
							m_pControl->m_eDownElement = CViewV3V1::Element::SeparatorH;
							m_pControl->Repaint(false);
							processed = true;
						}
						else
							m_pControl->getForm()->ReleaseCaptureMouse();
					}
					else
					{
						r = m_pControl->CalculateSeparatorV1Rect();
						if (r.is_inside(p) && m_pControl->getForm()->CaptureMouse(m_pControl, true))
						{
							if (m_pControl->getForm()->CaptureKeyboard(m_pControl))
							{
								m_fOldSeparator = m_pControl->m_fSeparatorV1;
								m_fDistance = p.Y - (r.Top + r.Bottom) * 0.5f;
								m_pControl->m_eDownElement = CViewV3V1::Element::SeparatorV1;
								m_pControl->Repaint(false);
								processed = true;
							}
							else
								m_pControl->getForm()->ReleaseCaptureMouse();
						}
						else
						{
							r = m_pControl->CalculateSeparatorV2Rect();
							if (r.is_inside(p) && m_pControl->getForm()->CaptureMouse(m_pControl, true))
							{
								if (m_pControl->getForm()->CaptureKeyboard(m_pControl))
								{
									m_fOldSeparator = m_pControl->m_fSeparatorV2;
									m_fDistance = p.Y - (r.Top + r.Bottom) * 0.5f;
									m_pControl->m_eDownElement = CViewV3V1::Element::SeparatorV2;
									m_pControl->Repaint(false);
									processed = true;
								}
								else
									m_pControl->getForm()->ReleaseCaptureMouse();
							}
						}
					}
				}
			}
			else
			{
				CancelDown(true, true);
				processed = true;
			}
		}

		void CViewV3V1Service::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_eDownElement != CViewV3V1::Element::None)
			{
				CancelDown(true, true);
				processed = true;
			}
		}

		void CViewV3V1Service::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_bResizable && m_pControl->m_eDownElement == CViewV3V1::Element::None && !m.Alt && !m.Ctrl && !m.Shift && !m.Middle && !m.Right && m_pControl->isEnabled(true))
			{
				PointF p{ m_pControl->FormToLocal(m.Position) };
				if (m_pControl->CalculateSeparatorHRect().is_inside(p))
				{
					m_pControl->setSeparatorH(0.5f);
					processed = true;
				}
				else if (m_pControl->CalculateSeparatorV1Rect().is_inside(p))
				{
					m_pControl->setSeparatorV1(0.3333f);
					processed = true;
				}
				else if (m_pControl->CalculateSeparatorV2Rect().is_inside(p))
				{
					m_pControl->setSeparatorV2(0.6667f);
					processed = true;
				}
			}
		}

		void CViewV3V1Service::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewV3V1Service::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewV3V1Service::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewV3V1Service::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewV3V1Service::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewV3V1Service::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}
	#pragma endregion
	}
}