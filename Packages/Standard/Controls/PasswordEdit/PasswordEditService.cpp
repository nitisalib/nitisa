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
		CPasswordEditService::CPasswordEditService(CPasswordEdit *edit) :
			CControlService(edit),
			m_pEdit{ edit }
		{

		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CPasswordEditService::NotifyOnParentStyleChange()
		{
			if (m_pEdit->getStyle())
			{
				m_pEdit->UpdateFromStyle();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
			}
		}

		void CPasswordEditService::NotifyOnParentFontChange()
		{
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CPasswordEditService::NotifyOnFreeResources()
		{
			if (m_pEdit->m_pTextInput)
				m_pEdit->m_pTextInput->NotifyOnFreeResources();
			if (m_pEdit->m_pCanvas)
			{
				m_pEdit->m_pCanvas->Release();
				m_pEdit->m_pCanvas = nullptr;
			}
		}

		void CPasswordEditService::NotifyOnEnable()
		{
			m_pEdit->getTextInput()->setEnabled(true);
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
		}

		void CPasswordEditService::NotifyOnDisable()
		{
			m_pEdit->getTextInput()->setEnabled(false);
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
		}

		void CPasswordEditService::NotifyOnResize()
		{
			m_pEdit->AdjustTextInputSize();
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
		}

		void CPasswordEditService::NotifyOnStyleChange()
		{
			if (m_pEdit->getStyle())
			{
				m_pEdit->UpdateFromStyle();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
			}
		}

		void CPasswordEditService::NotifyOnFontChange()
		{
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
		}

		void CPasswordEditService::NotifyOnSetFocus(const MessageFocus &m)
		{
			m_pEdit->getTextInput()->setFocused(true);
			if ((m.FocusedBy == FocusedBy::Tab || m.FocusedBy == FocusedBy::ShiftTab) && !m_pEdit->getTextInput()->hasSelection())
				m_pEdit->getTextInput()->SelectAll();
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
			m_pEdit->Repaint(false);
		}

		void CPasswordEditService::NotifyOnKillFocus()
		{
			m_pEdit->getTextInput()->setFocused(false);
			m_pEdit->getTextInput()->DeselectAll();
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
			m_pEdit->Repaint(false);
		}

		void CPasswordEditService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pEdit->getTextInput()->NotifyOnMouseHover(LocalToTextInput(m_pEdit->FormToLocal(m.Position))))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CPasswordEditService::NotifyOnMouseLeave()
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
		void CPasswordEditService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pEdit->getWidth(), 0) && ntl::IsGreater<float>(m_pEdit->getHeight(), 0))
				m_pEdit->Render();
		}
	#pragma endregion

	#pragma region Input notifications
		void CPasswordEditService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pEdit->getTextInput()->NotifyOnKeyDown(m.Key, ctrl, alt, shift, Application->Keyboard->isToggled(Key::NumLock)))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CPasswordEditService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pEdit->getTextInput()->NotifyOnKeyUp(m.Key, ctrl, alt, shift, Application->Keyboard->isToggled(Key::NumLock)))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CPasswordEditService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pEdit->getTextInput()->NotifyOnChar(m.Char, ctrl, alt, shift, Application->Keyboard->isToggled(Key::NumLock)))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CPasswordEditService::NotifyOnDeadChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pEdit->getTextInput()->NotifyOnDeadChar(m.Char, ctrl, alt, shift, Application->Keyboard->isToggled(Key::NumLock)))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CPasswordEditService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pEdit->getTextInput()->NotifyOnMouseMove(LocalToTextInput(m_pEdit->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CPasswordEditService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			m_pEdit->getForm()->CaptureMouse(m_pEdit, true);
			if (!m.Middle && !m.Right && m_pEdit->getTextInput()->NotifyOnMouseLeftDown(LocalToTextInput(m_pEdit->FormToLocal(m.Position)), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CPasswordEditService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			MouseUp(m.Position);
		}

		void CPasswordEditService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m.Middle && !m.Right && m_pEdit->getTextInput()->NotifyOnMouseLeftDoubleClick(LocalToTextInput(m_pEdit->FormToLocal(m.Position)), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CPasswordEditService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CPasswordEditService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CPasswordEditService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CPasswordEditService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CPasswordEditService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CPasswordEditService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CPasswordEditService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pEdit->getTextInput()->NotifyOnMouseVerticalWheel(LocalToTextInput(m_pEdit->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CPasswordEditService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pEdit->getTextInput()->NotifyOnMouseHorizontalWheel(LocalToTextInput(m_pEdit->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CPasswordEditService::NotifyOnDropFiles(const MessageDropFiles &m, bool &processed, bool &accepted)
		{
			processed = true;
			if (m_pEdit->getTextInput()->NotifyOnDropFiles(LocalToTextInput(m_pEdit->FormToLocal(m.Position)), m.FileNames))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Clipboard notifications
		void CPasswordEditService::NotifyOnPasteString(const MessagePasteString &m)
		{
			if (m_pEdit->getTextInput()->NotifyOnPasteString(m.Text))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Helpers
		void CPasswordEditService::MouseUp(const PointF &pos)
		{
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pEdit->getTextInput()->NotifyOnMouseLeftUp(LocalToTextInput(m_pEdit->FormToLocal(pos)), false, false, ctrl, alt, shift))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
			if (m_pEdit->isCaptureMouse())
				m_pEdit->getForm()->ReleaseCaptureMouse();
		}

		PointF CPasswordEditService::LocalToTextInput(const PointF &pos)
		{
			return PointF{ pos.X - m_pEdit->m_sBorderWidth.Left - m_pEdit->m_sPadding.Left, pos.Y - m_pEdit->m_sBorderWidth.Top - m_pEdit->m_sPadding.Top };
		}
	#pragma endregion
	}
}