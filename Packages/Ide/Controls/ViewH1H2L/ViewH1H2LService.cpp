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
		CViewH1H2LService::CViewH1H2LService(CViewH1H2L *control) :
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CViewH1H2LService::AlignControls()
		{
			m_pControl->AlignControls();
		}

		void CViewH1H2LService::CancelDown(const bool check_capture_mouse, const bool check_capture_keyboard)
		{
			if (m_pControl->m_eDownElement != CViewH1H2L::Element::None)
			{
				m_pControl->m_eDownElement = CViewH1H2L::Element::None;
				if (check_capture_mouse && m_pControl->isCaptureMouse())
					m_pControl->getForm()->ReleaseCaptureMouse();
				if (check_capture_keyboard && m_pControl->isCaptureKeyboard())
					m_pControl->getForm()->ReleaseCaptureKeyboard();
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CViewH1H2LService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
		}
	#pragma endregion

	#pragma region Notifications from child controls
		void CViewH1H2LService::NotifyOnChildTransform(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewH1H2LService::NotifyOnChildResize(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewH1H2LService::NotifyOnChildShow(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewH1H2LService::NotifyOnChildHide(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewH1H2LService::NotifyOnChildAttach(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewH1H2LService::NotifyOnChildDetach(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewH1H2LService::NotifyOnChildBeforeTransform(IControl *control, bool &allowed)
		{
			if (!m_pControl->m_bAligningControls)
				allowed = false;
		}

		void CViewH1H2LService::NotifyOnChildBeforeResize(IControl *control, bool &allowed)
		{
			if (!m_pControl->m_bAligningControls)
				allowed = false;
		}

		void CViewH1H2LService::NotifyOnChildBeforeHide(IControl *control, bool &allowed)
		{
			if (!m_pControl->m_bAligningControls)
				allowed = false;
		}
	#pragma endregion

	#pragma region State change notifications
		void CViewH1H2LService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
		}

		void CViewH1H2LService::NotifyOnKillCaptureKeyboard()
		{
			CancelDown(true, false);
		}

		void CViewH1H2LService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false, true);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CViewH1H2LService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
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
		void CViewH1H2LService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Escape)
			{
				if (m_pControl->m_eDownElement == CViewH1H2L::Element::SeparatorH)
				{
					CancelDown(true, true);
					m_pControl->setSeparatorH(m_fOldSeparator);
					processed = true;
				}
				else if (m_pControl->m_eDownElement == CViewH1H2L::Element::SeparatorV)
				{
					CancelDown(true, true);
					m_pControl->setSeparatorV(m_fOldSeparator);
					processed = true;
				}
				else if (m_pControl->m_eDownElement == CViewH1H2L::Element::SeparatorX)
				{
					CancelDown(true, true);
					m_pControl->setSeparatorX(m_fOldSeparator);
					processed = true;
				}
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CViewH1H2LService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_eDownElement == CViewH1H2L::Element::SeparatorH)
			{
				float p{ m_pControl->FormToLocal(m.Position).X + m_fDistance };
				m_pControl->setSeparatorH(p / m_pControl->getWidth());
				processed = true;
			}
			else if (m_pControl->m_eDownElement == CViewH1H2L::Element::SeparatorV)
			{
				float p{ m_pControl->FormToLocal(m.Position).Y + m_fDistance };
				m_pControl->setSeparatorV(p / m_pControl->getHeight());
				processed = true;
			}
			else if (m_pControl->m_eDownElement == CViewH1H2L::Element::SeparatorX)
			{
				float p{ m_pControl->FormToLocal(m.Position).Y + m_fDistance };
				m_pControl->setSeparatorX(p / m_pControl->getHeight());
				processed = true;
			}
		}

		void CViewH1H2LService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_eDownElement == CViewH1H2L::Element::None)
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
							m_pControl->m_eDownElement = CViewH1H2L::Element::SeparatorH;
							m_pControl->Repaint(false);
							processed = true;
						}
						else
							m_pControl->getForm()->ReleaseCaptureMouse();
					}
					else
					{
						r = m_pControl->CalculateSeparatorVRect();
						if (r.is_inside(p) && m_pControl->getForm()->CaptureMouse(m_pControl, true))
						{
							if (m_pControl->getForm()->CaptureKeyboard(m_pControl))
							{
								m_fOldSeparator = m_pControl->m_fSeparatorV;
								m_fDistance = p.Y - (r.Top + r.Bottom) * 0.5f;
								m_pControl->m_eDownElement = CViewH1H2L::Element::SeparatorV;
								m_pControl->Repaint(false);
								processed = true;
							}
							else
								m_pControl->getForm()->ReleaseCaptureMouse();
						}
						else
						{
							r = m_pControl->CalculateSeparatorXRect();
							if (r.is_inside(p) && m_pControl->getForm()->CaptureMouse(m_pControl, true))
							{
								if (m_pControl->getForm()->CaptureKeyboard(m_pControl))
								{
									m_fOldSeparator = m_pControl->m_fSeparatorX;
									m_fDistance = p.Y - (r.Top + r.Bottom) * 0.5f;
									m_pControl->m_eDownElement = CViewH1H2L::Element::SeparatorX;
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

		void CViewH1H2LService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_eDownElement != CViewH1H2L::Element::None)
			{
				CancelDown(true, true);
				processed = true;
			}
		}

		void CViewH1H2LService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_bResizable && m_pControl->m_eDownElement == CViewH1H2L::Element::None && !m.Alt && !m.Ctrl && !m.Shift && !m.Middle && !m.Right && m_pControl->isEnabled(true))
			{
				PointF p{ m_pControl->FormToLocal(m.Position) };
				if (m_pControl->CalculateSeparatorHRect().is_inside(p))
				{
					m_pControl->setSeparatorH(0.5f);
					processed = true;
				}
				else if (m_pControl->CalculateSeparatorVRect().is_inside(p))
				{
					m_pControl->setSeparatorV(0.5f);
					processed = true;
				}
				else if (m_pControl->CalculateSeparatorXRect().is_inside(p))
				{
					m_pControl->setSeparatorX(0.75f);
					processed = true;
				}
			}
		}

		void CViewH1H2LService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewH1H2LService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewH1H2LService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewH1H2LService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewH1H2LService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewH1H2LService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}
	#pragma endregion
	}
}