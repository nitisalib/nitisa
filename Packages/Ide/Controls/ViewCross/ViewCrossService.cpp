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
		CViewCrossService::CViewCrossService(CViewCross *control) :
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CViewCrossService::AlignControls()
		{
			m_pControl->AlignControls();
		}

		void CViewCrossService::CancelDown(const bool check_capture_mouse, const bool check_capture_keyboard)
		{
			if (m_pControl->m_eDownElement != CViewCross::Element::None)
			{
				m_pControl->m_eDownElement = CViewCross::Element::None;
				if (check_capture_mouse && m_pControl->isCaptureMouse())
					m_pControl->getForm()->ReleaseCaptureMouse();
				if (check_capture_keyboard && m_pControl->isCaptureKeyboard())
					m_pControl->getForm()->ReleaseCaptureKeyboard();
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CViewCrossService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
		}
	#pragma endregion

	#pragma region Notifications from child controls
		void CViewCrossService::NotifyOnChildTransform(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewCrossService::NotifyOnChildResize(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewCrossService::NotifyOnChildShow(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewCrossService::NotifyOnChildHide(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewCrossService::NotifyOnChildAttach(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewCrossService::NotifyOnChildDetach(IControl *control)
		{
			m_pControl->AlignControls();
		}

		void CViewCrossService::NotifyOnChildBeforeTransform(IControl *control, bool &allowed)
		{
			if (!m_pControl->m_bAligningControls)
				allowed = false;
		}

		void CViewCrossService::NotifyOnChildBeforeResize(IControl *control, bool &allowed)
		{
			if (!m_pControl->m_bAligningControls)
				allowed = false;
		}

		void CViewCrossService::NotifyOnChildBeforeHide(IControl *control, bool &allowed)
		{
			if (!m_pControl->m_bAligningControls)
				allowed = false;
		}
	#pragma endregion

	#pragma region State change notifications
		void CViewCrossService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
		}

		void CViewCrossService::NotifyOnKillCaptureKeyboard()
		{
			CancelDown(true, false);
		}

		void CViewCrossService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false, true);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CViewCrossService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
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
		void CViewCrossService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Escape)
			{
				if (m_pControl->m_eDownElement == CViewCross::Element::SeparatorCross)
				{
					CancelDown(true, true);
					m_pControl->setSeparatorH(m_sOldSeparator.X);
					m_pControl->setSeparatorV(m_sOldSeparator.Y);
					processed = true;
				}
				else if (m_pControl->m_eDownElement == CViewCross::Element::SeparatorH)
				{
					CancelDown(true, true);
					m_pControl->setSeparatorH(m_sOldSeparator.X);
					processed = true;
				}
				else if (m_pControl->m_eDownElement == CViewCross::Element::SeparatorV)
				{
					CancelDown(true, true);
					m_pControl->setSeparatorV(m_sOldSeparator.Y);
					processed = true;
				}
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CViewCrossService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_eDownElement == CViewCross::Element::SeparatorCross)
			{
				PointF p{ m_pControl->FormToLocal(m.Position) + m_sDistance };
				m_pControl->setSeparatorH(p.X / m_pControl->getWidth());
				m_pControl->setSeparatorV(p.Y / m_pControl->getHeight());
				processed = true;
			}
			else if (m_pControl->m_eDownElement == CViewCross::Element::SeparatorH)
			{
				float p{ m_pControl->FormToLocal(m.Position).X + m_sDistance.X };
				m_pControl->setSeparatorH(p / m_pControl->getWidth());
				processed = true;
			}
			else if (m_pControl->m_eDownElement == CViewCross::Element::SeparatorV)
			{
				float p{ m_pControl->FormToLocal(m.Position).Y + m_sDistance.Y };
				m_pControl->setSeparatorV(p / m_pControl->getHeight());
				processed = true;
			}
		}

		void CViewCrossService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_eDownElement == CViewCross::Element::None)
			{
				if (m_pControl->m_bResizable && !m.Alt && !m.Ctrl && !m.Shift && !m.Middle && !m.Right && m_pControl->isEnabled(true))
				{
					RectF r{ m_pControl->CalculateSeparatorCrossRect() };
					PointF p{ m_pControl->FormToLocal(m.Position) };
					if (r.is_inside(p) && m_pControl->getForm()->CaptureMouse(m_pControl, true))
					{
						if (m_pControl->getForm()->CaptureKeyboard(m_pControl))
						{
							m_sOldSeparator.X = m_pControl->m_fSeparatorH;
							m_sOldSeparator.Y = m_pControl->m_fSeparatorV;
							m_sDistance.X = p.X - (r.Left + r.Right) * 0.5f;
							m_sDistance.Y = p.Y - (r.Top + r.Bottom) * 0.5f;
							m_pControl->m_eDownElement = CViewCross::Element::SeparatorCross;
							m_pControl->Repaint(false);
							processed = true;
						}
						else
							m_pControl->getForm()->ReleaseCaptureMouse();
					}
					else
					{
						r = m_pControl->CalculateSeparatorHRect();
						if (r.is_inside(p) && m_pControl->getForm()->CaptureMouse(m_pControl, true))
						{
							if (m_pControl->getForm()->CaptureKeyboard(m_pControl))
							{
								m_sOldSeparator.X = m_pControl->m_fSeparatorH;
								m_sDistance.X = p.X - (r.Left + r.Right) * 0.5f;
								m_pControl->m_eDownElement = CViewCross::Element::SeparatorH;
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
									m_sOldSeparator.Y = m_pControl->m_fSeparatorV;
									m_sDistance.Y = p.Y - (r.Top + r.Bottom) * 0.5f;
									m_pControl->m_eDownElement = CViewCross::Element::SeparatorV;
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

		void CViewCrossService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_eDownElement != CViewCross::Element::None)
			{
				CancelDown(true, true);
				processed = true;
			}
		}

		void CViewCrossService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_bResizable && m_pControl->m_eDownElement == CViewCross::Element::None && !m.Alt && !m.Ctrl && !m.Shift && !m.Middle && !m.Right && m_pControl->isEnabled(true))
			{
				PointF p{ m_pControl->FormToLocal(m.Position) };
				if (m_pControl->CalculateSeparatorCrossRect().is_inside(p))
				{
					m_pControl->setSeparatorH(0.5f);
					m_pControl->setSeparatorV(0.5f);
					processed = true;
				}
				else if (m_pControl->CalculateSeparatorHRect().is_inside(p))
				{
					m_pControl->setSeparatorH(0.5f);
					processed = true;
				}
				else if (m_pControl->CalculateSeparatorVRect().is_inside(p))
				{
					m_pControl->setSeparatorV(0.5f);
					processed = true;
				}
			}
		}

		void CViewCrossService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewCrossService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewCrossService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewCrossService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewCrossService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CViewCrossService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}
	#pragma endregion
	}
}