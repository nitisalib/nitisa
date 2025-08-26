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
		CMaskEditService::CMaskEditService(CMaskEdit *edit) :
			CControlService(edit),
			m_pEdit{ edit }
		{

		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CMaskEditService::NotifyOnParentStyleChange()
		{
			if (m_pEdit->getStyle())
			{
				m_pEdit->UpdateFromStyle();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
			}
		}

		void CMaskEditService::NotifyOnParentFontChange()
		{
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CMaskEditService::NotifyOnFreeResources()
		{
			if (m_pEdit->m_pTextInput)
				m_pEdit->m_pTextInput->NotifyOnFreeResources();
			if (m_pEdit->m_pCanvas)
			{
				m_pEdit->m_pCanvas->Release();
				m_pEdit->m_pCanvas = nullptr;
			}
		}

		void CMaskEditService::NotifyOnEnable()
		{
			m_pEdit->getTextInput()->setEnabled(true);
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
		}

		void CMaskEditService::NotifyOnDisable()
		{
			m_pEdit->getTextInput()->setEnabled(false);
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
		}

		void CMaskEditService::NotifyOnAttach()
		{
			if (m_pEdit->getForm())
				m_pEdit->getTextInput()->NotifyOnAttach();
		}

		void CMaskEditService::NotifyOnResize()
		{
			m_pEdit->AdjustTextInputSize();
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
		}

		void CMaskEditService::NotifyOnStyleChange()
		{
			if (m_pEdit->getStyle())
			{
				m_pEdit->UpdateFromStyle();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
			}
		}

		void CMaskEditService::NotifyOnFontChange()
		{
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
		}

		void CMaskEditService::NotifyOnSetFocus(const MessageFocus &m)
		{
			m_pEdit->getTextInput()->setFocused(true);
			if ((m.FocusedBy == FocusedBy::Tab || m.FocusedBy == FocusedBy::ShiftTab) && !m_pEdit->getTextInput()->hasSelection())
				m_pEdit->getTextInput()->SelectAll();
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
			m_pEdit->Repaint(false);
		}

		void CMaskEditService::NotifyOnKillFocus()
		{
			m_pEdit->getTextInput()->setFocused(false);
			m_pEdit->getTextInput()->DeselectAll();
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
			m_pEdit->Repaint(false);
		}

		void CMaskEditService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pEdit->getTextInput()->NotifyOnMouseHover(LocalToTextInput(m_pEdit->FormToLocal(m.Position))))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CMaskEditService::NotifyOnMouseLeave()
		{
			if (m_pEdit->getTextInput()->NotifyOnMouseLeave())
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Paint notifications
		void CMaskEditService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pEdit->getWidth(), 0) && ntl::IsGreater<float>(m_pEdit->getHeight(), 0))
				m_pEdit->Render();
		}
	#pragma endregion

	#pragma region Input notifications
		void CMaskEditService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			CMaskEdit::CAttempt attempt{ m_pEdit };
			if (m_pEdit->getTextInput()->NotifyOnKeyDown(m.Key, ctrl, alt, shift, Application->Keyboard->isToggled(Key::NumLock)) &&
				m_pEdit->ValidateAndSet(attempt.Text(), m_pEdit->getTextInput()->getText()))
			{
				attempt.Success();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CMaskEditService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			CMaskEdit::CAttempt attempt{ m_pEdit };
			if (m_pEdit->getTextInput()->NotifyOnKeyUp(m.Key, ctrl, alt, shift, Application->Keyboard->isToggled(Key::NumLock)) &&
				m_pEdit->ValidateAndSet(attempt.Text(), m_pEdit->getTextInput()->getText()))
			{
				attempt.Success();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CMaskEditService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			CMaskEdit::CAttempt attempt{ m_pEdit };
			if (m_pEdit->getTextInput()->NotifyOnChar(m.Char, ctrl, alt, shift, Application->Keyboard->isToggled(Key::NumLock)) &&
				m_pEdit->ValidateAndSet(attempt.Text(), m_pEdit->getTextInput()->getText()))
			{
				attempt.Success();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CMaskEditService::NotifyOnDeadChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			CMaskEdit::CAttempt attempt{ m_pEdit };
			if (m_pEdit->getTextInput()->NotifyOnDeadChar(m.Char, ctrl, alt, shift, Application->Keyboard->isToggled(Key::NumLock)) &&
				m_pEdit->ValidateAndSet(attempt.Text(), m_pEdit->getTextInput()->getText()))
			{
				attempt.Success();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CMaskEditService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			CMaskEdit::CAttempt attempt{ m_pEdit };
			if (m_pEdit->getTextInput()->NotifyOnMouseMove(LocalToTextInput(m_pEdit->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift) &&
				m_pEdit->ValidateAndSet(attempt.Text(), m_pEdit->getTextInput()->getText()))
			{
				attempt.Success();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CMaskEditService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			m_pEdit->getForm()->CaptureMouse(m_pEdit, true);
			CMaskEdit::CAttempt attempt{ m_pEdit };
			if (!m.Middle && !m.Right && m_pEdit->getTextInput()->NotifyOnMouseLeftDown(LocalToTextInput(m_pEdit->FormToLocal(m.Position)), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift) &&
				m_pEdit->ValidateAndSet(attempt.Text(), m_pEdit->getTextInput()->getText()))
			{
				attempt.Success();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CMaskEditService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			MouseUp(m.Position);
		}

		void CMaskEditService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			CMaskEdit::CAttempt attempt{ m_pEdit };
			if (!m.Middle && !m.Right && m_pEdit->getTextInput()->NotifyOnMouseLeftDoubleClick(LocalToTextInput(m_pEdit->FormToLocal(m.Position)), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift) &&
				m_pEdit->ValidateAndSet(attempt.Text(), m_pEdit->getTextInput()->getText()))
			{
				attempt.Success();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CMaskEditService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CMaskEditService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CMaskEditService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CMaskEditService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CMaskEditService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CMaskEditService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CMaskEditService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			CMaskEdit::CAttempt attempt{ m_pEdit };
			if (m_pEdit->getTextInput()->NotifyOnMouseVerticalWheel(LocalToTextInput(m_pEdit->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta) &&
				m_pEdit->ValidateAndSet(attempt.Text(), m_pEdit->getTextInput()->getText()))
			{
				attempt.Success();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CMaskEditService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			CMaskEdit::CAttempt attempt{ m_pEdit };
			if (m_pEdit->getTextInput()->NotifyOnMouseHorizontalWheel(LocalToTextInput(m_pEdit->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta) &&
				m_pEdit->ValidateAndSet(attempt.Text(), m_pEdit->getTextInput()->getText()))
			{
				attempt.Success();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CMaskEditService::NotifyOnDropFiles(const MessageDropFiles &m, bool &processed, bool &accepted)
		{
			processed = true;
			CMaskEdit::CAttempt attempt{ m_pEdit };
			if (m_pEdit->getTextInput()->NotifyOnDropFiles(LocalToTextInput(m_pEdit->FormToLocal(m.Position)), m.FileNames) &&
				m_pEdit->ValidateAndSet(attempt.Text(), m_pEdit->getTextInput()->getText()))
			{
				attempt.Success();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Clipboard notifications
		void CMaskEditService::NotifyOnPasteString(const MessagePasteString &m)
		{
			CMaskEdit::CAttempt attempt{ m_pEdit };
			if (m_pEdit->getTextInput()->NotifyOnPasteString(m.Text) && m_pEdit->ValidateAndSet(attempt.Text(), m_pEdit->getTextInput()->getText()))
			{
				attempt.Success();
				m_pEdit->getTextInput()->ScrollToCaret();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Helpers
		void CMaskEditService::MouseUp(const PointF &pos)
		{
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			CMaskEdit::CAttempt attempt{ m_pEdit };
			if (m_pEdit->getTextInput()->NotifyOnMouseLeftUp(LocalToTextInput(m_pEdit->FormToLocal(pos)), false, false, ctrl, alt, shift) &&
				m_pEdit->ValidateAndSet(attempt.Text(), m_pEdit->getTextInput()->getText()))
			{
				attempt.Success();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
			if (m_pEdit->isCaptureMouse())
				m_pEdit->getForm()->ReleaseCaptureMouse();
		}

		PointF CMaskEditService::LocalToTextInput(const PointF &pos)
		{
			return PointF{ pos.X - m_pEdit->m_sBorderWidth.Left - m_pEdit->m_sPadding.Left, pos.Y - m_pEdit->m_sBorderWidth.Top - m_pEdit->m_sPadding.Top };
		}
	#pragma endregion
	}
}