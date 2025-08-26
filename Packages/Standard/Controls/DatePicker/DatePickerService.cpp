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
		CDatePickerService::CDatePickerService(CDatePicker *control):
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CDatePickerService::CancelDown(const bool check_capture)
		{
			m_pControl->m_bFirstDigit = true;
			m_pControl->m_eDownElement = CDatePicker::Element::None;
			if (m_pControl->m_hTimer)
			{
				m_pControl->getForm()->DeleteTimer(m_pControl->m_hTimer);
				m_pControl->m_hTimer = nullptr;
			}
			m_pControl->getMonthCalendar()->NotifyOnMouseDownCancel();
			if (check_capture && m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		PointF CDatePickerService::FormToCalendar(const PointF &pos)
		{
			return m_pControl->FormToLocal(pos) - m_pControl->m_sCalendarRect.LeftTop - m_pControl->getMonthCalendar()->getPosition();
		}

		bool CDatePickerService::InCalendar(const PointF &pos)
		{
			PointF p{ m_pControl->FormToLocal(pos) };
			return p.X >= m_pControl->m_sCalendarRect.Left && p.X < m_pControl->m_sCalendarRect.Right && p.Y >= m_pControl->m_sCalendarRect.Top && p.Y < m_pControl->m_sCalendarRect.Bottom;
		}
	#pragma endregion

	#pragma region State change notifications
		void CDatePickerService::NotifyOnAttach()
		{
			if (m_pControl->getForm())
				m_pControl->getMonthCalendar()->NotifyOnAttach();
		}

		void CDatePickerService::NotifyOnFreeResources()
		{
			m_pControl->Close();
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
			if (m_pControl->m_pMonthCalendar)
				m_pControl->m_pMonthCalendar->NotifyOnFreeResources();
		}
	#pragma endregion

	#pragma region Component notifications
		void CDatePickerService::NotifyOnComponentDetach(IComponent *component)
		{
			if (m_pControl->m_pImageList && cast<IImageList*>(component) == m_pControl->m_pImageList)
			{
				m_pControl->m_pImageList = nullptr;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CDatePickerService::NotifyOnComponentChange(IComponent *component)
		{
			if (m_pControl->m_pImageList && cast<IImageList*>(component) == m_pControl->m_pImageList)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Control notifications
		void CDatePickerService::NotifyOnControlDetach(IControl *control)
		{
			if (m_pControl->m_pImageList && cast<IImageList*>(control) == m_pControl->m_pImageList)
			{
				m_pControl->m_pImageList = nullptr;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CDatePickerService::NotifyOnControlChange(IControl *control)
		{
			if (m_pControl->m_pImageList && cast<IImageList*>(control) == m_pControl->m_pImageList)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Application notifications
		void CDatePickerService::NotifyOnTranslateChange()
		{
			m_pControl->Close();
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CDatePickerService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CDatePickerService::NotifyOnParentFontChange()
		{
			m_pControl->m_bFirstDigit = true;
			m_pControl->Close();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CDatePickerService::NotifyOnEnable()
		{
			m_pControl->m_bFirstDigit = true;
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CDatePickerService::NotifyOnDisable()
		{
			m_pControl->m_bFirstDigit = true;
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CDatePickerService::NotifyOnResize()
		{
			m_pControl->m_bFirstDigit = true;
			m_pControl->Close();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CDatePickerService::NotifyOnStyleChange()
		{
			m_pControl->m_bFirstDigit = true;
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CDatePickerService::NotifyOnFontChange()
		{
			m_pControl->m_bFirstDigit = true;
			m_pControl->Close();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CDatePickerService::NotifyOnSetFocus(const MessageFocus &m)
		{
			m_pControl->m_bFirstDigit = true;
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CDatePickerService::NotifyOnKillFocus()
		{
			m_pControl->Close();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CDatePickerService::NotifyOnSetCaptureMouse()
		{
			m_pControl->m_bFirstDigit = true;
			if (m_pControl->m_eDownElement == CDatePicker::Element::DownArrow || m_pControl->m_eDownElement == CDatePicker::Element::UpArrow)
				m_pControl->m_hTimer = m_pControl->getForm()->CreateTimer(&m_pControl->m_cTimerListener, m_pControl->m_fTimerInterval);
		}

		void CDatePickerService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CDatePickerService::NotifyOnDeactivate()
		{
			m_pControl->m_bFirstDigit = true;
			m_pControl->Close();
			m_pControl->getMonthCalendar()->NotifyOnDeactivate();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CDatePickerService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
			{
				if (!m.LastPass)
					m_pControl->RenderControl();
				else if (m.LastPass && m_pControl->m_bOpened)
					m_pControl->RenderCalendar();
			}
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CDatePickerService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_bOpened)
			{
				bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (m_pControl->getMonthCalendar()->NotifyOnKeyDown(m.Key, ctrl, alt, shift, numlock))
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
					return;
				}
			}
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
			case Key::F4:
				if (m_pControl->m_eDisplayMode == CDatePicker::DisplayMode::DropDown)
					m_pControl->m_bOpened ? m_pControl->Close() : m_pControl->Open();
				break;
			default:
				break;
			}
		}

		void CDatePickerService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_bOpened)
			{
				bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (m_pControl->getMonthCalendar()->NotifyOnKeyUp(m.Key, ctrl, alt, shift, numlock))
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
		}

		void CDatePickerService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_bOpened)
			{
				bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (m_pControl->getMonthCalendar()->NotifyOnChar(m.Char, ctrl, alt, shift, numlock))
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
					return;
				}
			}
			if (in(m.Char, { L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9' }))
			{
				String s{ m.Char };
				int d{ StringToInt(s) };
				switch (m_pControl->m_eActiveElement)
				{
				case CDatePicker::Element::Years:
					ProcessYearsDigit(d);
					break;
				case CDatePicker::Element::Months:
					ProcessMonthsDigit(d);
					break;
				case CDatePicker::Element::Days:
					ProcessDaysDigit(d);
					break;
				default:
					break;
				}
			}
			else
				m_pControl->m_bFirstDigit = true;
		}

		void CDatePickerService::NotifyOnDeadChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_bOpened)
			{
				bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (m_pControl->getMonthCalendar()->NotifyOnDeadChar(m.Char, ctrl, alt, shift, numlock))
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CDatePickerService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pControl->isEnabled(true))
			{
				m_pControl->UpdateHoveredElement(m_pControl->FormToLocal(m.Position));
				if (m_pControl->m_bOpened && m_pControl->getMonthCalendar()->NotifyOnMouseHover(FormToCalendar(m.Position)))
				{
					if (m_pControl->m_pCanvasCalendar)
						m_pControl->m_pCanvasCalendar->setValid(false);
				}
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CDatePickerService::NotifyOnMouseLeave()
		{
			if (m_pControl->isEnabled(true))
			{
				if (m_pControl->m_bOpened)
				{
					m_pControl->getMonthCalendar()->NotifyOnMouseLeave();
					if (m_pControl->m_pCanvasCalendar)
						m_pControl->m_pCanvasCalendar->setValid(false);
				}
				m_pControl->UpdateHoveredElement();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CDatePickerService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				bool changed{ false };
				if (m_pControl->m_bOpened && m_pControl->getMonthCalendar()->NotifyOnMouseMove(FormToCalendar(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pControl->m_pCanvasCalendar)
						m_pControl->m_pCanvasCalendar->setValid(false);
					changed = true;
				}
				if (m_pControl->UpdateHoveredElement(m_pControl->FormToLocal(m.Position)))
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					changed = true;
				}
				if (changed)
					m_pControl->Repaint(false);
			}
		}

		void CDatePickerService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				bool in_calendar{ false };
				m_pControl->m_bFirstDigit = true;
				if (m_pControl->m_bOpened)
				{
					if (m_pControl->getMonthCalendar()->NotifyOnMouseLeftDown(FormToCalendar(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						if (m_pControl->m_pCanvasCalendar)
							m_pControl->m_pCanvasCalendar->setValid(false);
						m_pControl->Repaint(false);
					}
					in_calendar = InCalendar(m.Position);
				}
				if (!in_calendar)
				{
					if (m_pControl->m_eHoveredElement != CDatePicker::Element::Arrow)
						m_pControl->Close();
					switch (m_pControl->m_eHoveredElement)
					{
					case CDatePicker::Element::UpArrow:
						switch (m_pControl->m_eActiveElement)
						{
						case CDatePicker::Element::Years:
							m_pControl->setYear(m_pControl->getYear() + 1);
							break;
						case CDatePicker::Element::Months:
							m_pControl->setMonth(m_pControl->getMonth() + 1);
							break;
						case CDatePicker::Element::Days:
							m_pControl->setDay(m_pControl->getDay() + 1);
							break;
						default:
							break;
						}
						m_pControl->m_eDownElement = CDatePicker::Element::UpArrow;
						m_pControl->getForm()->CaptureMouse(m_pControl, true);
						break;
					case CDatePicker::Element::DownArrow:
						switch (m_pControl->m_eActiveElement)
						{
						case CDatePicker::Element::Years:
							m_pControl->setYear(m_pControl->getYear() - 1);
							break;
						case CDatePicker::Element::Months:
							m_pControl->setMonth(m_pControl->getMonth() - 1);
							break;
						case CDatePicker::Element::Days:
							m_pControl->setDay(m_pControl->getDay() - 1);
							break;
						default:
							break;
						}
						m_pControl->m_eDownElement = CDatePicker::Element::DownArrow;
						m_pControl->getForm()->CaptureMouse(m_pControl, true);
						break;
					case CDatePicker::Element::Arrow:
						m_pControl->m_bOpened ? m_pControl->Close() : m_pControl->Open();
						break;
					case CDatePicker::Element::Years:
					case CDatePicker::Element::Months:
					case CDatePicker::Element::Days:
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
				}
			}
			else
				CancelDown(true);
		}

		void CDatePickerService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				m_pControl->m_bFirstDigit = true;
				if (m_pControl->m_bOpened && m_pControl->getMonthCalendar()->NotifyOnMouseLeftUp(FormToCalendar(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pControl->m_pCanvasCalendar)
						m_pControl->m_pCanvasCalendar->setValid(false);
					m_pControl->Repaint(false);
				}
				if ((!m_pControl->m_bOpened || !InCalendar(m.Position)) && m_pControl->m_eHoveredElement != CDatePicker::Element::Arrow)
					CancelDown(true);
			}
		}

		void CDatePickerService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				m_pControl->m_bFirstDigit = true;
				if (m_pControl->m_bOpened)
				{
					if (m_pControl->getMonthCalendar()->NotifyOnMouseLeftDoubleClick(FormToCalendar(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift) && m_pControl->m_pCanvasCalendar)
						m_pControl->m_pCanvasCalendar->setValid(false);
					if (!InCalendar(m.Position))
						m_pControl->Close();
					m_pControl->Repaint(false);
				}
				else
					CancelDown(true);
			}
		}

		void CDatePickerService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				m_pControl->m_bFirstDigit = true;
				if (m_pControl->m_bOpened)
				{
					if (m_pControl->getMonthCalendar()->NotifyOnMouseRightDown(FormToCalendar(m.Position), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift) && m_pControl->m_pCanvasCalendar)
						m_pControl->m_pCanvasCalendar->setValid(false);
					if (!InCalendar(m.Position))
						m_pControl->Close();
				}
				else
					CancelDown(true);
			}
		}

		void CDatePickerService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				m_pControl->m_bFirstDigit = true;
				if (m_pControl->m_bOpened && m_pControl->getMonthCalendar()->NotifyOnMouseRightUp(FormToCalendar(m.Position), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pControl->m_pCanvasCalendar)
						m_pControl->m_pCanvasCalendar->setValid(false);
					m_pControl->Repaint(false);
				}
				if (!m_pControl->m_bOpened || !InCalendar(m.Position))
					CancelDown(true);
			}
		}

		void CDatePickerService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				m_pControl->m_bFirstDigit = true;
				if (m_pControl->m_bOpened)
				{
					if (m_pControl->getMonthCalendar()->NotifyOnMouseRightDoubleClick(FormToCalendar(m.Position), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift) && m_pControl->m_pCanvasCalendar)
						m_pControl->m_pCanvasCalendar->setValid(false);
					if (InCalendar(m.Position))
						m_pControl->Close();
					m_pControl->Repaint(false);
				}
				else
					CancelDown(true);
			}
		}

		void CDatePickerService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				m_pControl->m_bFirstDigit = true;
				if (m_pControl->m_bOpened)
				{
					if (m_pControl->getMonthCalendar()->NotifyOnMouseMiddleDown(FormToCalendar(m.Position), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift) && m_pControl->m_pCanvasCalendar)
						m_pControl->m_pCanvasCalendar->setValid(false);
					if (InCalendar(m.Position))
						m_pControl->Close();
					m_pControl->Repaint(false);
				}
				else
					CancelDown(true);
			}
		}

		void CDatePickerService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				m_pControl->m_bFirstDigit = true;
				if (m_pControl->m_bOpened && m_pControl->getMonthCalendar()->NotifyOnMouseMiddleUp(FormToCalendar(m.Position), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pControl->m_pCanvasCalendar)
						m_pControl->m_pCanvasCalendar->setValid(false);
					m_pControl->Repaint(false);
				}
				if (!m_pControl->m_bOpened || !InCalendar(m.Position))
					CancelDown(true);
			}
		}

		void CDatePickerService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				m_pControl->m_bFirstDigit = true;
				if (m_pControl->m_bOpened)
				{
					if (m_pControl->getMonthCalendar()->NotifyOnMouseMiddleDoubleClick(FormToCalendar(m.Position), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift) && m_pControl->m_pCanvasCalendar)
						m_pControl->m_pCanvasCalendar->setValid(false);
					if (InCalendar(m.Position))
						m_pControl->Close();
					m_pControl->Repaint(false);
				}
				else
					CancelDown(true);
			}
		}

		void CDatePickerService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				m_pControl->m_bFirstDigit = true;
				if (m_pControl->m_bOpened && m_pControl->getMonthCalendar()->NotifyOnMouseVerticalWheel(FormToCalendar(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
				{
					if (m_pControl->m_pCanvasCalendar)
						m_pControl->m_pCanvasCalendar->setValid(false);
					m_pControl->Repaint(false);
				}
				if (!m_pControl->m_bOpened || !InCalendar(m.Position))
				{
					switch (m_pControl->m_eActiveElement)
					{
					case CDatePicker::Element::Years:
						m_pControl->setYear(m_pControl->getYear() + (m.Delta < 0 ? 1 : -1));
						break;
					case CDatePicker::Element::Months:
						m_pControl->setMonth(m_pControl->getMonth() + (m.Delta < 0 ? 1 : -1));
						break;
					case CDatePicker::Element::Days:
						m_pControl->setDay(m_pControl->getDay() + (m.Delta < 0 ? 1 : -1));
						break;
					default:
						break;
					}
				}
			}
		}

		void CDatePickerService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true) && m_pControl->m_bOpened && m_pControl->getMonthCalendar()->NotifyOnMouseHorizontalWheel(FormToCalendar(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
			{
				if (m_pControl->m_pCanvasCalendar)
					m_pControl->m_pCanvasCalendar->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Keys
		void CDatePickerService::ProcessKeyLeft()
		{
			CDatePicker::Element prev{ m_pControl->getPrevElement() };
			if (prev != m_pControl->m_eActiveElement)
			{
				m_pControl->m_eActiveElement = prev;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CDatePickerService::ProcessKeyRight()
		{
			CDatePicker::Element next{ m_pControl->getNextElement() };
			if (next != m_pControl->m_eActiveElement)
			{
				m_pControl->m_eActiveElement = next;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CDatePickerService::ProcessKeyUp()
		{
			switch (m_pControl->m_eActiveElement)
			{
			case CDatePicker::Element::Years:
				m_pControl->setYear(m_pControl->getYear() + 1);
				break;
			case CDatePicker::Element::Months:
				m_pControl->setMonth(m_pControl->getMonth() + 1);
				break;
			case CDatePicker::Element::Days:
				m_pControl->setDay(m_pControl->getDay() + 1);
				break;
			default:
				break;
			}
		}

		void CDatePickerService::ProcessKeyDown()
		{
			switch (m_pControl->m_eActiveElement)
			{
			case CDatePicker::Element::Years:
				m_pControl->setYear(m_pControl->getYear() - 1);
				break;
			case CDatePicker::Element::Months:
				m_pControl->setMonth(m_pControl->getMonth() - 1);
				break;
			case CDatePicker::Element::Days:
				m_pControl->setDay(m_pControl->getDay() - 1);
				break;
			default:
				break;
			}
		}
	#pragma endregion

	#pragma region Digits
		void CDatePickerService::ProcessYearsDigit(const int digit)
		{
			int new_value;
			if (m_pControl->m_bFirstDigit)
			{
				new_value = digit;
				m_pControl->m_bFirstDigit = false;
			}
			else
				new_value = m_pControl->getYear() * 10 + digit;
			m_pControl->setYear(new_value);
		}

		void CDatePickerService::ProcessMonthsDigit(const int digit)
		{
			int new_value;
			if (m_pControl->m_bFirstDigit && digit <= 1)
			{
				new_value = digit;
				m_pControl->m_bFirstDigit = false;
			}
			else
			{
				new_value = m_pControl->m_bFirstDigit ? digit : (m_pControl->getMonth() * 10 + digit);
				m_pControl->m_bFirstDigit = true;
			}
			new_value = ntl::Clamp<int>(new_value, 1, 12);
			bool f{ m_pControl->m_bFirstDigit };
			m_pControl->setMonth(new_value);
			m_pControl->m_bFirstDigit = f;
			if (m_pControl->m_bFirstDigit)
				m_pControl->m_eActiveElement = m_pControl->getNextElement();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CDatePickerService::ProcessDaysDigit(const int digit)
		{
			int new_value;
			if (m_pControl->m_bFirstDigit && digit <= 3)
			{
				new_value = digit;
				m_pControl->m_bFirstDigit = false;
			}
			else
			{
				new_value = m_pControl->m_bFirstDigit ? digit : (m_pControl->getDay() * 10 + digit);
				m_pControl->m_bFirstDigit = true;
			}
			new_value = ntl::Clamp<int>(new_value, 1, 31);
			bool f{ m_pControl->m_bFirstDigit };
			m_pControl->setDay(new_value);
			m_pControl->m_bFirstDigit = f;
			if (m_pControl->m_bFirstDigit)
				m_pControl->m_eActiveElement = m_pControl->getNextElement();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}
	#pragma endregion
	}
}