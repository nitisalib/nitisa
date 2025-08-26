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
		CTimePickerService::CTimePickerService(CTimePicker *control) :
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CTimePickerService::CancelDown(const bool check_capture)
		{
			if (m_pControl->m_eDownElement != CTimePicker::Element::None)
			{
				m_pControl->m_bFirstDigit = true;
				m_pControl->m_eDownElement = CTimePicker::Element::None;
				if (m_pControl->m_hTimer)
				{
					m_pControl->getForm()->DeleteTimer(m_pControl->m_hTimer);
					m_pControl->m_hTimer = nullptr;
				}
				if (check_capture && m_pControl->isCaptureMouse())
					m_pControl->getForm()->ReleaseCaptureMouse();
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CTimePickerService::NotifyOnAttach()
		{
			if (m_pControl->getForm())
			{
				m_pControl->m_bFirstDigit = true;
				m_pControl->UpdateMetrics();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CTimePickerService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
			if (m_pControl->m_hTimer)
			{
				m_pControl->getForm()->DeleteTimer(m_pControl->m_hTimer);
				m_pControl->m_hTimer = nullptr;
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CTimePickerService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CTimePickerService::NotifyOnParentFontChange()
		{
			if (m_pControl->getForm())
			{
				m_pControl->m_bFirstDigit = true;
				m_pControl->UpdateMetrics();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CTimePickerService::NotifyOnEnable()
		{
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_bFirstDigit = true;
				m_pControl->m_pCanvas->setValid(false);
			}
			m_pControl->Repaint(false);
		}

		void CTimePickerService::NotifyOnDisable()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CTimePickerService::NotifyOnResize()
		{
			m_pControl->m_bFirstDigit = true;
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CTimePickerService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CTimePickerService::NotifyOnFontChange()
		{
			if (m_pControl->getForm())
			{
				m_pControl->m_bFirstDigit = true;
				m_pControl->UpdateMetrics();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CTimePickerService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_bFirstDigit = true;
				m_pControl->m_pCanvas->setValid(false);
			}
			m_pControl->Repaint(false);
		}

		void CTimePickerService::NotifyOnKillFocus()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CTimePickerService::NotifyOnSetCaptureMouse()
		{
			m_pControl->m_bFirstDigit = true;
			m_pControl->m_hTimer = m_pControl->getForm()->CreateTimer(&m_pControl->m_cTimerListener, m_pControl->m_fTimerInterval);
		}

		void CTimePickerService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CTimePickerService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
				m_pControl->Render();
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CTimePickerService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			switch (m.Key)
			{
			case Key::Left:
			case Key::Numpad4:
				if (m.Key == Key::Left || (m.Key == Key::Numpad4 && !Application->Keyboard->isToggled(Key::NumLock)))
				{
					m_pControl->m_bFirstDigit = true;
					ProcessKeyLeft();
				}
				break;
			case Key::Right:
			case Key::Numpad6:
				if (m.Key == Key::Right || (m.Key == Key::Numpad6 && !Application->Keyboard->isToggled(Key::NumLock)))
				{
					m_pControl->m_bFirstDigit = true;
					ProcessKeyRight();
				}
				break;
			case Key::Up:
			case Key::Numpad8:
				if (m.Key == Key::Up || (m.Key == Key::Numpad8 && !Application->Keyboard->isToggled(Key::NumLock)))
				{
					m_pControl->m_bFirstDigit = true;
					ProcessKeyUp();
				}
				break;
			case Key::Down:
			case Key::Numpad2:
				if (m.Key == Key::Down || (m.Key == Key::Numpad2 && !Application->Keyboard->isToggled(Key::NumLock)))
				{
					m_pControl->m_bFirstDigit = true;
					ProcessKeyDown();
				}
				break;
			default:
				break;
			}
		}

		void CTimePickerService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			if (in(m.Char, { L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9' }))
			{
				String s{ m.Char };
				int d{ StringToInt(s) };
				switch (m_pControl->m_eActiveElement)
				{
				case CTimePicker::Element::Hours:
					ProcessHoursDigit(d);
					break;
				case CTimePicker::Element::Minutes:
					ProcessMinutesDigit(d);
					break;
				case CTimePicker::Element::Seconds:
					ProcessSecondsDigit(d);
					break;
				default:
					break;
				}
			}
			else
				m_pControl->m_bFirstDigit = true;
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CTimePickerService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pControl->isEnabled(true))
			{
				m_pControl->UpdateHoveredElement(m_pControl->FormToLocal(m.Position));
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CTimePickerService::NotifyOnMouseLeave()
		{
			if (m_pControl->isEnabled(true))
			{
				m_pControl->UpdateHoveredElement();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CTimePickerService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true) && m_pControl->UpdateHoveredElement(m_pControl->FormToLocal(m.Position)))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CTimePickerService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m_pControl->isCaptureMouse() && !m.Middle && !m.Right)
			{
				m_pControl->m_bFirstDigit = true;
				bool changed{ false };
				switch (m_pControl->m_eHoveredElement)
				{
				case CTimePicker::Element::UpArrow:
					switch (m_pControl->m_eActiveElement)
					{
					case CTimePicker::Element::Hours:
						m_pControl->setTime(m_pControl->m_iHour + 1, m_pControl->m_iMinute, m_pControl->m_iSecond);
						break;
					case CTimePicker::Element::Minutes:
						m_pControl->setTime(m_pControl->m_iHour, m_pControl->m_iMinute + 1, m_pControl->m_iSecond);
						break;
					case CTimePicker::Element::Seconds:
						m_pControl->setTime(m_pControl->m_iHour, m_pControl->m_iMinute, m_pControl->m_iSecond + 1);
						break;
					default:
						break;
					}
					changed = true;
					break;
				case CTimePicker::Element::DownArrow:
					switch (m_pControl->m_eActiveElement)
					{
					case CTimePicker::Element::Hours:
						m_pControl->setTime(m_pControl->m_iHour - 1, m_pControl->m_iMinute, m_pControl->m_iSecond);
						break;
					case CTimePicker::Element::Minutes:
						m_pControl->setTime(m_pControl->m_iHour, m_pControl->m_iMinute - 1, m_pControl->m_iSecond);
						break;
					case CTimePicker::Element::Seconds:
						m_pControl->setTime(m_pControl->m_iHour, m_pControl->m_iMinute, m_pControl->m_iSecond - 1);
						break;
					default:
						break;
					}
					changed = true;
					break;
				case CTimePicker::Element::Hours:
				case CTimePicker::Element::Minutes:
				case CTimePicker::Element::Seconds:
					if (m_pControl->m_eActiveElement != m_pControl->m_eHoveredElement)
					{
						m_pControl->m_eActiveElement = m_pControl->m_eHoveredElement;
						if (m_pControl->m_pCanvas)
							m_pControl->m_pCanvas->setValid(false);
						m_pControl->Repaint(false);
					}
					break;
				default:
					break;
				}
				if (changed)
				{
					m_pControl->m_eDownElement = m_pControl->m_eHoveredElement;
					m_pControl->getForm()->CaptureMouse(m_pControl, true);
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
			else
				CancelDown(true);
		}

		void CTimePickerService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			CancelDown(true);
		}

		void CTimePickerService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CTimePickerService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CTimePickerService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CTimePickerService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CTimePickerService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CTimePickerService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CTimePickerService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CTimePickerService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				m_pControl->m_bFirstDigit = true;
				bool changed{ false };
				switch (m_pControl->m_eActiveElement)
				{
				case CTimePicker::Element::Hours:
					changed = m_pControl->setTime(m_pControl->m_iHour + (m.Delta < 0 ? 1 : -1), m_pControl->m_iMinute, m_pControl->m_iSecond);
					break;
				case CTimePicker::Element::Minutes:
					changed = m_pControl->setTime(m_pControl->m_iHour, m_pControl->m_iMinute + (m.Delta < 0 ? 1 : -1), m_pControl->m_iSecond);
					break;
				case CTimePicker::Element::Seconds:
					changed = m_pControl->setTime(m_pControl->m_iHour, m_pControl->m_iMinute, m_pControl->m_iSecond + (m.Delta < 0 ? 1 : -1));
					break;
				default:
					break;
				}
				if (changed)
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
		}
	#pragma endregion

	#pragma region Keys
		void CTimePickerService::ProcessKeyLeft()
		{
			bool changed{ false };
			switch (m_pControl->m_eActiveElement)
			{
			case CTimePicker::Element::Seconds:
				m_pControl->m_eActiveElement = CTimePicker::Element::Minutes;
				changed = true;
				break;
			case CTimePicker::Element::Minutes:
				if (m_pControl->m_bShowSeconds)
				{
					m_pControl->m_eActiveElement = CTimePicker::Element::Hours;
					changed = true;
				}
				break;
			default:
				break;
			}
			if (changed)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CTimePickerService::ProcessKeyRight()
		{
			bool changed{ false };
			switch (m_pControl->m_eActiveElement)
			{
			case CTimePicker::Element::Hours:
				m_pControl->m_eActiveElement = CTimePicker::Element::Minutes;
				changed = true;
				break;
			case CTimePicker::Element::Minutes:
				if (m_pControl->m_bShowSeconds)
				{
					m_pControl->m_eActiveElement = CTimePicker::Element::Seconds;
					changed = true;
				}
				break;
			default:
				break;
			}
			if (changed)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CTimePickerService::ProcessKeyUp()
		{
			bool changed{ false };
			switch (m_pControl->m_eActiveElement)
			{
			case CTimePicker::Element::Hours:
				changed = m_pControl->setTime(m_pControl->m_iHour + 1, m_pControl->m_iMinute, m_pControl->m_iSecond);
				break;
			case CTimePicker::Element::Minutes:
				changed = m_pControl->setTime(m_pControl->m_iHour, m_pControl->m_iMinute + 1, m_pControl->m_iSecond);
				break;
			case CTimePicker::Element::Seconds:
				changed = m_pControl->setTime(m_pControl->m_iHour, m_pControl->m_iMinute, m_pControl->m_iSecond + 1);
				break;
			default:
				break;
			}
			if (changed)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CTimePickerService::ProcessKeyDown()
		{
			bool changed{ false };
			switch (m_pControl->m_eActiveElement)
			{
			case CTimePicker::Element::Hours:
				changed = m_pControl->setTime(m_pControl->m_iHour - 1, m_pControl->m_iMinute, m_pControl->m_iSecond);
				break;
			case CTimePicker::Element::Minutes:
				changed = m_pControl->setTime(m_pControl->m_iHour, m_pControl->m_iMinute - 1, m_pControl->m_iSecond);
				break;
			case CTimePicker::Element::Seconds:
				changed = m_pControl->setTime(m_pControl->m_iHour, m_pControl->m_iMinute, m_pControl->m_iSecond - 1);
				break;
			default:
				break;
			}
			if (changed)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Digits
		void CTimePickerService::ProcessHoursDigit(const int digit)
		{
			int new_value;
			if (m_pControl->m_bFirstDigit && digit <= 2)
			{
				new_value = digit;
				m_pControl->m_bFirstDigit = false;
			}
			else
			{
				new_value = m_pControl->m_bFirstDigit ? digit : (m_pControl->m_iHour * 10 + digit);
				m_pControl->m_bFirstDigit = true;
			}
			new_value = ntl::Clamp<int>(new_value, 0, 23);
			m_pControl->setTime(new_value, m_pControl->m_iMinute, m_pControl->m_iSecond);
			if (m_pControl->m_bFirstDigit)
				m_pControl->m_eActiveElement = CTimePicker::Element::Minutes;
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CTimePickerService::ProcessMinutesDigit(const int digit)
		{
			int new_value;
			if (m_pControl->m_bFirstDigit && digit <= 5)
			{
				new_value = digit;
				m_pControl->m_bFirstDigit = false;
			}
			else
			{
				new_value = m_pControl->m_bFirstDigit ? digit : (m_pControl->m_iMinute * 10 + digit);
				m_pControl->m_bFirstDigit = true;
			}
			new_value = ntl::Clamp<int>(new_value, 0, 59);
			m_pControl->setTime(m_pControl->m_iHour, new_value, m_pControl->m_iSecond);
			if (m_pControl->m_bFirstDigit && m_pControl->m_bShowSeconds)
				m_pControl->m_eActiveElement = CTimePicker::Element::Seconds;
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CTimePickerService::ProcessSecondsDigit(const int digit)
		{
			int new_value;
			if (m_pControl->m_bFirstDigit && digit <= 5)
			{
				new_value = digit;
				m_pControl->m_bFirstDigit = false;
			}
			else
			{
				new_value = m_pControl->m_bFirstDigit ? digit : (m_pControl->m_iSecond * 10 + digit);
				m_pControl->m_bFirstDigit = true;
			}
			new_value = ntl::Clamp<int>(new_value, 0, 59);
			if (m_pControl->setTime(m_pControl->m_iHour, m_pControl->m_iMinute, new_value))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion
	}
}