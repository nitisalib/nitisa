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
		CTrackRangeService::CTrackRangeService(CTrackRange *control) :
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CTrackRangeService::MouseUp(const bool check_capture)
		{
			if (m_pControl->m_eDownElement != CTrackRange::Element::None)
			{
				m_pControl->m_eDownElement = CTrackRange::Element::None;
				if (check_capture)
					m_pControl->getForm()->ReleaseCaptureMouse();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CTrackRangeService::NotifyOnParentStyleChange()
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
		void CTrackRangeService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
		}

		void CTrackRangeService::NotifyOnEnable()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CTrackRangeService::NotifyOnDisable()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CTrackRangeService::NotifyOnResize()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CTrackRangeService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CTrackRangeService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CTrackRangeService::NotifyOnKillFocus()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CTrackRangeService::NotifyOnKillCaptureMouse()
		{
			MouseUp(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CTrackRangeService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
				m_pControl->Render();
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CTrackRangeService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			switch (m.Key)
			{
			case Key::Left:
			case Key::Numpad4:
				if (m.Key == Key::Left || (m.Key == Key::Numpad4 && !Application->Keyboard->isToggled(Key::NumLock)))
				{
					if (shift && m_pControl->m_sTrackerEnabled.Y)
					{
						if (m_pControl->setValue2(m_pControl->getValue().Y - 1) && m_pControl->OnChange)
							m_pControl->OnChange(m_pControl);
					}
					else if (!shift && m_pControl->m_sTrackerEnabled.X)
					{
						if (m_pControl->setValue1(m_pControl->getValue().X - 1) && m_pControl->OnChange)
							m_pControl->OnChange(m_pControl);
					}
				}
				break;
			case Key::Right:
			case Key::Numpad6:
				if (m.Key == Key::Right || (m.Key == Key::Numpad6 && !Application->Keyboard->isToggled(Key::NumLock)))
				{
					if (shift && m_pControl->m_sTrackerEnabled.Y)
					{
						if (m_pControl->setValue2(m_pControl->getValue().Y + 1) && m_pControl->OnChange)
							m_pControl->OnChange(m_pControl);
					}
					else if (!shift && m_pControl->m_sTrackerEnabled.X)
					{
						if (m_pControl->setValue1(m_pControl->getValue().X + 1) && m_pControl->OnChange)
							m_pControl->OnChange(m_pControl);
					}
				}
				break;
			case Key::Prior:
			case Key::Numpad9:
				if (m.Key == Key::Prior || (m.Key == Key::Numpad9 && !Application->Keyboard->isToggled(Key::NumLock)))
				{
					if (shift && m_pControl->m_sTrackerEnabled.Y)
					{
						if (m_pControl->setValue2(m_pControl->getValue().Y - ntl::Max<int>(1, m_pControl->m_iTickInterval)) && m_pControl->OnChange)
							m_pControl->OnChange(m_pControl);
					}
					else if (!shift && m_pControl->m_sTrackerEnabled.X)
					{
						if (m_pControl->setValue1(m_pControl->getValue().X - ntl::Max<int>(1, m_pControl->m_iTickInterval)) && m_pControl->OnChange)
							m_pControl->OnChange(m_pControl);
					}
				}
				break;
			case Key::Next:
			case Key::Numpad3:
				if (m.Key == Key::Next || (m.Key == Key::Numpad4 && !Application->Keyboard->isToggled(Key::NumLock)))
				{
					if (shift && m_pControl->m_sTrackerEnabled.Y)
					{
						if (m_pControl->setValue2(m_pControl->getValue().Y + ntl::Max<int>(1, m_pControl->m_iTickInterval)) && m_pControl->OnChange)
							m_pControl->OnChange(m_pControl);
					}
					else if (!shift && m_pControl->m_sTrackerEnabled.X)
					{
						if (m_pControl->setValue1(m_pControl->getValue().X + ntl::Max<int>(1, m_pControl->m_iTickInterval)) && m_pControl->OnChange)
							m_pControl->OnChange(m_pControl);
					}
				}
				break;
			case Key::Home:
			case Key::Numpad7:
				if (m.Key == Key::Home || (m.Key == Key::Numpad7 && !Application->Keyboard->isToggled(Key::NumLock)))
				{
					if (shift && m_pControl->m_sTrackerEnabled.Y)
					{
						if (m_pControl->setValue2(m_pControl->getMin()) && m_pControl->OnChange)
							m_pControl->OnChange(m_pControl);
					}
					else if (!shift && m_pControl->m_sTrackerEnabled.X)
					{
						if (m_pControl->setValue1(m_pControl->getMin()) && m_pControl->OnChange)
							m_pControl->OnChange(m_pControl);
					}
				}
				break;
			case Key::End:
			case Key::Numpad1:
				if (m.Key == Key::End || (m.Key == Key::Numpad1 && !Application->Keyboard->isToggled(Key::NumLock)))
				{
					if (shift && m_pControl->m_sTrackerEnabled.Y)
					{
						if (m_pControl->setValue2(m_pControl->getMax()) && m_pControl->OnChange)
							m_pControl->OnChange(m_pControl);
					}
					else if (!shift && m_pControl->m_sTrackerEnabled.X)
					{
						if (m_pControl->setValue1(m_pControl->getMax()) && m_pControl->OnChange)
							m_pControl->OnChange(m_pControl);
					}
				}
				break;
			default:
				break;
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CTrackRangeService::NotifyOnMouseHover(const MessagePosition &m)
		{
			m_pControl->UpdateHoveredElement(m_pControl->FormToLocal(m.Position));
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CTrackRangeService::NotifyOnMouseLeave()
		{
			m_pControl->UpdateHoveredElement(m_pControl->FormToLocal((PointF)m_pControl->getForm()->ScreenToClient(Application->Mouse->getPosition())));
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CTrackRangeService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			switch (m_pControl->m_eDownElement)
			{
			case CTrackRange::Element::Tracker1:
				if (m_pControl->setValue1(m_pControl->ClientToValue(m_pControl->FormToLocal(m.Position))) && m_pControl->OnChange)
					m_pControl->OnChange(m_pControl);
				break;
			case CTrackRange::Element::Tracker2:
				if (m_pControl->setValue2(m_pControl->ClientToValue(m_pControl->FormToLocal(m.Position))) && m_pControl->OnChange)
					m_pControl->OnChange(m_pControl);
				break;
			default:
				if (m_pControl->UpdateHoveredElement(m_pControl->FormToLocal(m.Position)))
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
		}

		void CTrackRangeService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m.Middle && !m.Right && !m_pControl->isCaptureMouse() && m_pControl->isEnabled(true))
			{
				int v{ m_pControl->ClientToValue(m_pControl->FormToLocal(m.Position)) };
				switch (m_pControl->m_eHoveredElement)
				{
				case CTrackRange::Element::Tracker1:
					if (m_pControl->m_sTrackerEnabled.X)
					{
						m_pControl->m_eDownElement = CTrackRange::Element::Tracker1;
						if (m_pControl->setValue1(v) && m_pControl->OnChange)
							m_pControl->OnChange(m_pControl);
					}
					break;
				case CTrackRange::Element::Tracker2:
					if (m_pControl->m_sTrackerEnabled.Y)
					{
						m_pControl->m_eDownElement = CTrackRange::Element::Tracker2;
						if (m_pControl->setValue2(v) && m_pControl->OnChange)
							m_pControl->OnChange(m_pControl);
					}
					break;
				default:
					if (m.Shift && m_pControl->m_sTrackerEnabled.Y)
					{
						m_pControl->m_eDownElement = CTrackRange::Element::Tracker2;
						if (m_pControl->setValue2(v) && m_pControl->OnChange)
							m_pControl->OnChange(m_pControl);
					}
					else if (!m.Shift && m_pControl->m_sTrackerEnabled.X)
					{
						m_pControl->m_eDownElement = CTrackRange::Element::Tracker1;
						if (m_pControl->setValue1(v) && m_pControl->OnChange)
							m_pControl->OnChange(m_pControl);
					}
				}
				if (m_pControl->m_eDownElement != CTrackRange::Element::None)
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
					m_pControl->getForm()->CaptureMouse(m_pControl, true);
				}
			}
			else
				MouseUp(true);
		}

		void CTrackRangeService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			MouseUp(true);
		}

		void CTrackRangeService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CTrackRangeService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CTrackRangeService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CTrackRangeService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CTrackRangeService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CTrackRangeService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CTrackRangeService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CTrackRangeService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				if (m.Shift && m_pControl->m_sTrackerEnabled.Y)
				{
					if (m_pControl->setValue2(m_pControl->getValue().Y + (m.Delta < 0 ? 1 : -1)) && m_pControl->OnChange)
						m_pControl->OnChange(m_pControl);
				}
				else if (!m.Shift && m_pControl->m_sTrackerEnabled.X)
				{
					if (m_pControl->setValue1(m_pControl->getValue().X + (m.Delta < 0 ? 1 : -1)) && m_pControl->OnChange)
						m_pControl->OnChange(m_pControl);
				}
			}
		}

		void CTrackRangeService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				if (m.Shift && m_pControl->m_sTrackerEnabled.Y)
				{
					if (m_pControl->setValue2(m_pControl->getValue().Y + (m.Delta < 0 ? 1 : -1)) && m_pControl->OnChange)
						m_pControl->OnChange(m_pControl);
				}
				else if (!m.Shift && m_pControl->m_sTrackerEnabled.X)
				{
					if (m_pControl->setValue1(m_pControl->getValue().X + (m.Delta < 0 ? 1 : -1)) && m_pControl->OnChange)
						m_pControl->OnChange(m_pControl);
				}
			}
		}
	#pragma endregion
	}
}