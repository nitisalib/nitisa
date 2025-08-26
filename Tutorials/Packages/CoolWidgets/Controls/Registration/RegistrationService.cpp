#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
	#pragma region Constructor & destructor
		CRegistrationService::CRegistrationService(CRegistration *control):
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CRegistrationService::CancelDown(const bool release_capture)
		{
			if (m_pControl->m_eDownElement != CRegistration::Element::None)
			{
				// Send cancel down notification to the input on which down was done
				switch (m_pControl->m_eDownElement)
				{
				case CRegistration::Element::InputFirstName:
					m_pControl->getInputFirstName()->NotifyOnMouseDownCancel();
					break;
				case CRegistration::Element::InputLastName:
					m_pControl->getInputLastName()->NotifyOnMouseDownCancel();
					break;
				}
				m_pControl->m_eDownElement = CRegistration::Element::None;
			}
			if (release_capture && m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}
	#pragma endregion

	#pragma region State change notifications
		void CRegistrationService::NotifyOnAttach()
		{
			if (m_pControl->getForm())
			{
				m_pControl->getInputFirstName()->NotifyOnAttach();
				m_pControl->getInputLastName()->NotifyOnAttach();
				m_pControl->getCalendar()->NotifyOnAttach();
			}
		}

		void CRegistrationService::NotifyOnFreeResources()
		{
			// Close calendar if it's opened
			m_pControl->CloseCalendar();
			// Delete both canvas if they are created
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
			if (m_pControl->m_pCanvasCalendar)
			{
				m_pControl->m_pCanvasCalendar->Release();
				m_pControl->m_pCanvasCalendar = nullptr;
			}
			// Notify built-in controls
			if (m_pControl->m_pInputFirstName)
				m_pControl->m_pInputFirstName->NotifyOnFreeResources();
			if (m_pControl->m_pInputLastName)
				m_pControl->m_pInputLastName->NotifyOnFreeResources();
			if (m_pControl->m_pCalendar)
				m_pControl->m_pCalendar->NotifyOnFreeResources();
		}
	#pragma endregion

	#pragma region Application notifications
		void CRegistrationService::NotifyOnTranslateChange()
		{
			m_pControl->CloseCalendar();
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CRegistrationService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->CloseCalendar();
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CRegistrationService::NotifyOnParentFontChange()
		{
			m_pControl->CloseCalendar();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CRegistrationService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->CloseCalendar();
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CRegistrationService::NotifyOnFontChange()
		{
			m_pControl->CloseCalendar();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CRegistrationService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m.FocusedBy != FocusedBy::LeftMouse)
			{
				m_pControl->m_eFocusedElement = CRegistration::Element::InputFirstName;
				m_pControl->getInputFirstName()->setFocused(true);
				m_pControl->getInputLastName()->setFocused(false);
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CRegistrationService::NotifyOnKillFocus()
		{
			m_pControl->CloseCalendar();
			m_pControl->m_eFocusedElement = CRegistration::Element::None;
			m_pControl->getInputFirstName()->setFocused(false);
			m_pControl->getInputLastName()->setFocused(false);
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CRegistrationService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CRegistrationService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass)
				m_pControl->RenderControl(m_pControl->getForm()->getRenderer());
			else if (m_pControl->m_bCalendarOpened)
				m_pControl->RenderCalendar(m_pControl->getForm()->getRenderer());
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CRegistrationService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			bool changed{ false }, numlock{ Application->Keyboard->isToggled(Key::NumLock) }, ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			switch (m_pControl->m_eFocusedElement)
			{
			case CRegistration::Element::InputFirstName:
				if (m_pControl->getInputFirstName()->NotifyOnKeyDown(m.Key, ctrl, alt, shift, numlock))
					changed = true;
				break;
			case CRegistration::Element::InputLastName:
				if (m_pControl->getInputLastName()->NotifyOnKeyDown(m.Key, ctrl, alt, shift, numlock))
					changed = true;
				break;
			case CRegistration::Element::Date:
				if (m_pControl->m_bCalendarOpened && m_pControl->getCalendar()->NotifyOnKeyDown(m.Key, ctrl, alt, shift, numlock))
					changed = true;
				break;
			}
			if (changed)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_pCanvasCalendar)
					m_pControl->m_pCanvasCalendar->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CRegistrationService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			bool changed{ false }, numlock{ Application->Keyboard->isToggled(Key::NumLock) }, ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (!ctrl && !alt && !shift)
			{
				switch (m.Key)
				{
				case Key::Up:
					switch (m_pControl->m_eFocusedElement)
					{
					case CRegistration::Element::InputLastName:
						m_pControl->m_eFocusedElement = CRegistration::Element::InputFirstName;
						m_pControl->getInputLastName()->setFocused(false);
						m_pControl->getInputFirstName()->setFocused(true);
						break;
					case CRegistration::Element::Date:
						m_pControl->m_eFocusedElement = CRegistration::Element::InputLastName;
						m_pControl->getInputLastName()->setFocused(true);
						break;
					default:
						m_pControl->m_eFocusedElement = CRegistration::Element::Date;
						m_pControl->getInputFirstName()->setFocused(false);
						break;
					}
					if (m_pControl->m_bCalendarOpened)
						m_pControl->CloseCalendar();
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					if (m_pControl->m_pCanvasCalendar)
						m_pControl->m_pCanvasCalendar->setValid(false);
					m_pControl->Repaint(false);
					return;
				case Key::Down:
					switch (m_pControl->m_eFocusedElement)
					{
					case CRegistration::Element::InputFirstName:
						m_pControl->m_eFocusedElement = CRegistration::Element::InputLastName;
						m_pControl->getInputFirstName()->setFocused(false);
						m_pControl->getInputLastName()->setFocused(false);
						break;
					case CRegistration::Element::InputLastName:
						m_pControl->m_eFocusedElement = CRegistration::Element::Date;
						m_pControl->getInputLastName()->setFocused(false);
						break;
					default:
						m_pControl->m_eFocusedElement = CRegistration::Element::InputFirstName;
						m_pControl->getInputFirstName()->setFocused(true);
						break;
					}
					if (m_pControl->m_bCalendarOpened)
						m_pControl->CloseCalendar();
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					if (m_pControl->m_pCanvasCalendar)
						m_pControl->m_pCanvasCalendar->setValid(false);
					m_pControl->Repaint(false);
					return;
				case Key::F4:
					if (m_pControl->m_eFocusedElement == CRegistration::Element::Date)
					{
						m_pControl->m_bCalendarOpened ? m_pControl->CloseCalendar() : m_pControl->OpenCalendar();
						if (m_pControl->m_pCanvas)
							m_pControl->m_pCanvas->setValid(false);
						if (m_pControl->m_pCanvasCalendar)
							m_pControl->m_pCanvasCalendar->setValid(false);
						m_pControl->Repaint(false);
						return;
					}
					break;
				}
			}
			switch (m_pControl->m_eFocusedElement)
			{
			case CRegistration::Element::InputFirstName:
				if (m_pControl->getInputFirstName()->NotifyOnKeyUp(m.Key, ctrl, alt, shift, numlock))
					changed = true;
				break;
			case CRegistration::Element::InputLastName:
				if (m_pControl->getInputLastName()->NotifyOnKeyUp(m.Key, ctrl, alt, shift, numlock))
					changed = true;
				break;
			case CRegistration::Element::Date:
				if (m_pControl->m_bCalendarOpened && m_pControl->getCalendar()->NotifyOnKeyUp(m.Key, ctrl, alt, shift, numlock))
					changed = true;
				break;
			}
			if (changed)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_pCanvasCalendar)
					m_pControl->m_pCanvasCalendar->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CRegistrationService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			bool changed{ false }, numlock{ Application->Keyboard->isToggled(Key::NumLock) }, ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			switch (m_pControl->m_eFocusedElement)
			{
			case CRegistration::Element::InputFirstName:
				if (m_pControl->getInputFirstName()->NotifyOnChar(m.Char, ctrl, alt, shift, numlock))
					changed = true;
				break;
			case CRegistration::Element::InputLastName:
				if (m_pControl->getInputLastName()->NotifyOnChar(m.Char, ctrl, alt, shift, numlock))
					changed = true;
				break;
			case CRegistration::Element::Date:
				if (m_pControl->m_bCalendarOpened && m_pControl->getCalendar()->NotifyOnChar(m.Char, ctrl, alt, shift, numlock))
					changed = true;
				break;
			}
			if (changed)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_pCanvasCalendar)
					m_pControl->m_pCanvasCalendar->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CRegistrationService::NotifyOnDeadChar(const MessageChar &m, bool &processed)
		{
			bool changed{ false }, numlock{ Application->Keyboard->isToggled(Key::NumLock) }, ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			switch (m_pControl->m_eFocusedElement)
			{
			case CRegistration::Element::InputFirstName:
				if (m_pControl->getInputFirstName()->NotifyOnDeadChar(m.Char, ctrl, alt, shift, numlock))
					changed = true;
				break;
			case CRegistration::Element::InputLastName:
				if (m_pControl->getInputLastName()->NotifyOnDeadChar(m.Char, ctrl, alt, shift, numlock))
					changed = true;
				break;
			case CRegistration::Element::Date:
				if (m_pControl->m_bCalendarOpened && m_pControl->getCalendar()->NotifyOnDeadChar(m.Char, ctrl, alt, shift, numlock))
					changed = true;
				break;
			}
			if (changed)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_pCanvasCalendar)
					m_pControl->m_pCanvasCalendar->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CRegistrationService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pControl->UpdateHoveredElement(m_pControl->FormToLocal(m.Position)))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_pCanvasCalendar)
					m_pControl->m_pCanvasCalendar->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CRegistrationService::NotifyOnMouseLeave()
		{
			if (m_pControl->UpdateHoveredElement(m_pControl->FormToLocal((PointF)m_pControl->getForm()->ScreenToClient(Application->Mouse->getPosition()))))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_pCanvasCalendar)
					m_pControl->m_pCanvasCalendar->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CRegistrationService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			bool changed{ m_pControl->UpdateHoveredElement(m_pControl->FormToLocal(m.Position)) };
			if (m_pControl->m_eDownElement != CRegistration::Element::None)
			{
				switch (m_pControl->m_eDownElement)
				{
				case CRegistration::Element::InputFirstName:
					if (m_pControl->getInputFirstName()->NotifyOnMouseMove(m_pControl->FormToLocal(m.Position) - m_pControl->getInputFirstName()->getPosition(), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						changed = true;
						processed = true;
					}
					break;
				case CRegistration::Element::InputLastName:
					if (m_pControl->getInputLastName()->NotifyOnMouseMove(m_pControl->FormToLocal(m.Position) - m_pControl->getInputLastName()->getPosition(), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						changed = true;
						processed = true;
					}
					break;
				}
				if (changed)
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					if (m_pControl->m_pCanvasCalendar)
						m_pControl->m_pCanvasCalendar->setValid(false);
					m_pControl->Repaint(false);
				}
				return;
			}
			switch (m_pControl->m_eHoveredElement)
			{
			case CRegistration::Element::InputFirstName:
				if (m_pControl->getInputFirstName()->NotifyOnMouseMove(m_pControl->FormToLocal(m.Position) - m_pControl->getInputFirstName()->getPosition(), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					changed = true;
				break;
			case CRegistration::Element::InputLastName:
				if (m_pControl->getInputLastName()->NotifyOnMouseMove(m_pControl->FormToLocal(m.Position) - m_pControl->getInputLastName()->getPosition(), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					changed = true;
				break;
			case CRegistration::Element::Calendar:
				if (m_pControl->getCalendar()->NotifyOnMouseMove(m_pControl->FormToLocal(m.Position) - m_pControl->m_sCalendarRect.LeftTop, m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					changed = true;
				break;
			}
			if (changed)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_pCanvasCalendar)
					m_pControl->m_pCanvasCalendar->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CRegistrationService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_eDownElement == CRegistration::Element::None && !m.Middle && !m.Right && !m.Ctrl && !m.Alt && !m.Shift)
			{
				bool changed{ false };
				switch (m_pControl->m_eHoveredElement)
				{
				case CRegistration::Element::InputFirstName:
					if (m_pControl->getInputFirstName()->NotifyOnMouseLeftDown(m_pControl->FormToLocal(m.Position) - m_pControl->getInputFirstName()->getPosition(), false, false, false, false, false))
						changed = true;
					m_pControl->m_eDownElement = CRegistration::Element::InputFirstName;
					m_pControl->m_eFocusedElement = CRegistration::Element::InputFirstName;
					m_pControl->getInputLastName()->setFocused(false);
					m_pControl->getInputFirstName()->setFocused(true);
					if (m_pControl->m_bCalendarOpened)
						m_pControl->CloseCalendar();
					break;
				case CRegistration::Element::InputLastName:
					if (m_pControl->getInputLastName()->NotifyOnMouseLeftDown(m_pControl->FormToLocal(m.Position) - m_pControl->getInputLastName()->getPosition(), false, false, false, false, false))
						changed = true;
					m_pControl->m_eDownElement = CRegistration::Element::InputLastName;
					m_pControl->m_eFocusedElement = CRegistration::Element::InputLastName;
					m_pControl->getInputFirstName()->setFocused(false);
					m_pControl->getInputLastName()->setFocused(true);
					if (m_pControl->m_bCalendarOpened)
						m_pControl->CloseCalendar();
					break;
				case CRegistration::Element::Calendar:
					m_pControl->getInputLastName()->setFocused(false);
					m_pControl->getInputFirstName()->setFocused(false);
					m_pControl->m_eFocusedElement = CRegistration::Element::Date;
					if (m_pControl->getCalendar()->NotifyOnMouseLeftDown(m_pControl->FormToLocal(m.Position) - m_pControl->m_sCalendarRect.LeftTop, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
						changed = true;
					break;
				case CRegistration::Element::Date:
					m_pControl->getInputLastName()->setFocused(false);
					m_pControl->getInputFirstName()->setFocused(false);
					m_pControl->m_eFocusedElement = CRegistration::Element::Date;
					if (m_pControl->m_bCalendarOpened)
						m_pControl->CloseCalendar();
					break;
				case CRegistration::Element::DateArrow:
					m_pControl->getInputLastName()->setFocused(false);
					m_pControl->getInputFirstName()->setFocused(false);
					m_pControl->m_eFocusedElement = CRegistration::Element::Date;
					m_pControl->m_bCalendarOpened ? m_pControl->CloseCalendar() : m_pControl->OpenCalendar();
					changed = true;
					break;
				default:
					if (m_pControl->m_bCalendarOpened)
					{
						changed = true;
						m_pControl->CloseCalendar();
					}
				}
				if (changed)
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					if (m_pControl->m_pCanvasCalendar)
						m_pControl->m_pCanvasCalendar->setValid(false);
					m_pControl->Repaint(false);
					if (m_pControl->m_eDownElement != CRegistration::Element::None)
						m_pControl->getForm()->CaptureMouse(m_pControl, true);
				}
			}
			else
				CancelDown(true);
		}

		void CRegistrationService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			bool changed{ false };
			if (m_pControl->m_eDownElement != CRegistration::Element::None)
			{
				switch (m_pControl->m_eDownElement)
				{
				case CRegistration::Element::InputFirstName:
					if (m_pControl->getInputFirstName()->NotifyOnMouseLeftUp(m_pControl->FormToLocal(m.Position) - m_pControl->getInputFirstName()->getPosition(), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
						changed = true;
					break;
				case CRegistration::Element::InputLastName:
					if (m_pControl->getInputLastName()->NotifyOnMouseLeftUp(m_pControl->FormToLocal(m.Position) - m_pControl->getInputLastName()->getPosition(), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
						changed = true;
					break;
				}
				CancelDown(true);
				if (changed)
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
				processed = true;
				return;
			}
			switch (m_pControl->m_eHoveredElement)
			{
			case CRegistration::Element::InputFirstName:
				if (m_pControl->getInputFirstName()->NotifyOnMouseLeftUp(m_pControl->FormToLocal(m.Position) - m_pControl->getInputFirstName()->getPosition(), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					changed = true;
				break;
			case CRegistration::Element::InputLastName:
				if (m_pControl->getInputLastName()->NotifyOnMouseLeftUp(m_pControl->FormToLocal(m.Position) - m_pControl->getInputLastName()->getPosition(), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					changed = true;
				break;
			case CRegistration::Element::Calendar:
				if (m_pControl->getCalendar()->NotifyOnMouseLeftUp(m_pControl->FormToLocal(m.Position) - m_pControl->m_sCalendarRect.LeftTop, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					changed = true;
				break;
			}
			if (changed)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_pCanvasCalendar)
					m_pControl->m_pCanvasCalendar->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CRegistrationService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
			bool changed{ false };
			switch (m_pControl->m_eHoveredElement)
			{
			case CRegistration::Element::InputFirstName:
				if (m_pControl->getInputFirstName()->NotifyOnMouseLeftUp(m_pControl->FormToLocal(m.Position) - m_pControl->getInputFirstName()->getPosition(), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					changed = true;
				break;
			case CRegistration::Element::InputLastName:
				if (m_pControl->getInputLastName()->NotifyOnMouseLeftUp(m_pControl->FormToLocal(m.Position) - m_pControl->getInputLastName()->getPosition(), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					changed = true;
				break;
			case CRegistration::Element::Calendar:
				if (m_pControl->getCalendar()->NotifyOnMouseLeftUp(m_pControl->FormToLocal(m.Position) - m_pControl->m_sCalendarRect.LeftTop, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					changed = true;
				break;
			}
			if (changed)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_pCanvasCalendar)
					m_pControl->m_pCanvasCalendar->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CRegistrationService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CRegistrationService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CRegistrationService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CRegistrationService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CRegistrationService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CRegistrationService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}
	#pragma endregion

	#pragma region Clipboard notifications
		void CRegistrationService::NotifyOnPasteString(const MessagePasteString &m)
		{
			bool changed{ false };
			switch (m_pControl->m_eFocusedElement)
			{
			case CRegistration::Element::InputFirstName:
				if (m_pControl->getInputFirstName()->NotifyOnPasteString(m.Text))
					changed = true;
				break;
			case CRegistration::Element::InputLastName:
				if (m_pControl->getInputLastName()->NotifyOnPasteString(m.Text))
					changed = true;
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
	}
}