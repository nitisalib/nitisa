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
		CMonthCalendarService::CMonthCalendarService(CMonthCalendar *control) :
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region State change notifications
		void CMonthCalendarService::NotifyOnAttach()
		{
			if (m_pControl->getForm())
			{
				m_pControl->getMonthCalendar()->NotifyOnAttach();
				m_pControl->UpdateSize();
			}
		}

		void CMonthCalendarService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pMonthCalendar)
				m_pControl->m_pMonthCalendar->NotifyOnFreeResources();
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
		}
	#pragma endregion

	#pragma region Application notifications
		void CMonthCalendarService::NotifyOnTranslateChange()
		{
			m_pControl->UpdateSize();
			m_pControl->Repaint(false);
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CMonthCalendarService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
		}

		void CMonthCalendarService::NotifyOnParentFontChange()
		{
			m_pControl->UpdateSize();
			m_pControl->Repaint(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CMonthCalendarService::NotifyOnEnable()
		{
			m_pControl->getMonthCalendar()->setEnabled(true);
			m_pControl->UpdateSize();
		}

		void CMonthCalendarService::NotifyOnDisable()
		{
			m_pControl->getMonthCalendar()->setEnabled(false);
			m_pControl->UpdateSize();
		}

		void CMonthCalendarService::NotifyOnResize()
		{
			m_pControl->UpdateSize();
		}

		void CMonthCalendarService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
		}

		void CMonthCalendarService::NotifyOnFontChange()
		{
			m_pControl->UpdateSize();
			m_pControl->Repaint(false);
		}

		void CMonthCalendarService::NotifyOnKillCaptureMouse()
		{
			m_pControl->getMonthCalendar()->NotifyOnMouseDownCancel();
		}

		void CMonthCalendarService::NotifyOnDeactivate()
		{
			m_pControl->getMonthCalendar()->NotifyOnDeactivate();
		}
	#pragma endregion

	#pragma region Paint notifications
		void CMonthCalendarService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
				m_pControl->Render();
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CMonthCalendarService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pControl->getMonthCalendar()->NotifyOnKeyDown(m.Key, ctrl, alt, shift, numlock))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CMonthCalendarService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pControl->getMonthCalendar()->NotifyOnKeyUp(m.Key, ctrl, alt, shift, numlock))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CMonthCalendarService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pControl->getMonthCalendar()->NotifyOnChar(m.Char, ctrl, alt, shift, numlock))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CMonthCalendarService::NotifyOnDeadChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pControl->getMonthCalendar()->NotifyOnDeadChar(m.Char, ctrl, alt, shift, numlock))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CMonthCalendarService::NotifyOnMouseHover(const MessagePosition &m)
		{
			m_pControl->getMonthCalendar()->NotifyOnMouseHover(m_pControl->FormToLocal(m.Position) - m_pControl->getMonthCalendar()->getPosition());
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CMonthCalendarService::NotifyOnMouseLeave()
		{
			m_pControl->getMonthCalendar()->NotifyOnMouseLeave();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CMonthCalendarService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->getMonthCalendar()->NotifyOnMouseMove(m_pControl->FormToLocal(m.Position) - m_pControl->getMonthCalendar()->getPosition(), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CMonthCalendarService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				if (m_pControl->getMonthCalendar()->NotifyOnMouseLeftDown(m_pControl->FormToLocal(m.Position) - m_pControl->getMonthCalendar()->getPosition(), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
				if (!m_pControl->isCaptureMouse() && m_pControl->getMonthCalendar()->isDown())
					m_pControl->getForm()->CaptureMouse(m_pControl, true);
				if (!m_pControl->getMonthCalendar()->isDown() && m_pControl->isCaptureMouse())
					m_pControl->getForm()->ReleaseCaptureMouse();
			}
		}

		void CMonthCalendarService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				if (m_pControl->getMonthCalendar()->NotifyOnMouseLeftUp(m_pControl->FormToLocal(m.Position) - m_pControl->getMonthCalendar()->getPosition(), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
				if (m_pControl->isCaptureMouse())
					m_pControl->getForm()->ReleaseCaptureMouse();
			}
		}

		void CMonthCalendarService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				if (m_pControl->getMonthCalendar()->NotifyOnMouseLeftDoubleClick(m_pControl->FormToLocal(m.Position) - m_pControl->getMonthCalendar()->getPosition(), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
				if (m_pControl->isCaptureMouse())
					m_pControl->getForm()->ReleaseCaptureMouse();
			}
		}

		void CMonthCalendarService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				if (m_pControl->getMonthCalendar()->NotifyOnMouseRightDown(m_pControl->FormToLocal(m.Position) - m_pControl->getMonthCalendar()->getPosition(), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
				if (m_pControl->isCaptureMouse())
					m_pControl->getForm()->ReleaseCaptureMouse();
			}
		}

		void CMonthCalendarService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				if (m_pControl->getMonthCalendar()->NotifyOnMouseRightUp(m_pControl->FormToLocal(m.Position) - m_pControl->getMonthCalendar()->getPosition(), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
				if (m_pControl->isCaptureMouse())
					m_pControl->getForm()->ReleaseCaptureMouse();
			}
		}

		void CMonthCalendarService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				if (m_pControl->getMonthCalendar()->NotifyOnMouseRightDoubleClick(m_pControl->FormToLocal(m.Position) - m_pControl->getMonthCalendar()->getPosition(), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
				if (m_pControl->isCaptureMouse())
					m_pControl->getForm()->ReleaseCaptureMouse();
			}
		}

		void CMonthCalendarService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				if (m_pControl->getMonthCalendar()->NotifyOnMouseMiddleDown(m_pControl->FormToLocal(m.Position) - m_pControl->getMonthCalendar()->getPosition(), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
				if (m_pControl->isCaptureMouse())
					m_pControl->getForm()->ReleaseCaptureMouse();
			}
		}

		void CMonthCalendarService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				if (m_pControl->getMonthCalendar()->NotifyOnMouseMiddleUp(m_pControl->FormToLocal(m.Position) - m_pControl->getMonthCalendar()->getPosition(), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
				if (m_pControl->isCaptureMouse())
					m_pControl->getForm()->ReleaseCaptureMouse();
			}
		}

		void CMonthCalendarService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				if (m_pControl->getMonthCalendar()->NotifyOnMouseMiddleDoubleClick(m_pControl->FormToLocal(m.Position) - m_pControl->getMonthCalendar()->getPosition(), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
				if (m_pControl->isCaptureMouse())
					m_pControl->getForm()->ReleaseCaptureMouse();
			}
		}

		void CMonthCalendarService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true) && m_pControl->getMonthCalendar()->NotifyOnMouseVerticalWheel(m_pControl->FormToLocal(m.Position) - m_pControl->getMonthCalendar()->getPosition(), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CMonthCalendarService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true) && m_pControl->getMonthCalendar()->NotifyOnMouseHorizontalWheel(m_pControl->FormToLocal(m.Position) - m_pControl->getMonthCalendar()->getPosition(), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion
	}
}