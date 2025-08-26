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
		CEditService::CEditService(CEdit *edit) :
			CControlService(edit),
			m_pEdit{ edit }
		{

		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CEditService::NotifyOnParentStyleChange()
		{
			if (m_pEdit->getStyle())
			{
				m_pEdit->UpdateFromStyle();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
			}
		}

		void CEditService::NotifyOnParentFontChange()
		{
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CEditService::NotifyOnFreeResources()
		{
			if (m_pEdit->m_pTextInput)
				m_pEdit->m_pTextInput->NotifyOnFreeResources();
			if (m_pEdit->m_pCanvas)
			{
				m_pEdit->m_pCanvas->Release();
				m_pEdit->m_pCanvas = nullptr;
			}
		}

		void CEditService::NotifyOnEnable()
		{
			m_pEdit->getTextInput()->setEnabled(true);
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
		}

		void CEditService::NotifyOnDisable()
		{
			m_pEdit->getTextInput()->setEnabled(false);
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
		}

		void CEditService::NotifyOnAttach()
		{
			if (m_pEdit->getForm())
			{
				if (!m_pEdit->m_bTextChanged)
					m_pEdit->setText(m_pEdit->m_sName);
				m_pEdit->getTextInput()->NotifyOnAttach();
			}
		}

		void CEditService::NotifyOnResize()
		{
			m_pEdit->AdjustTextInputSize();
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
		}

		void CEditService::NotifyOnStyleChange()
		{
			if (m_pEdit->getStyle())
			{
				m_pEdit->UpdateFromStyle();
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
			}
		}

		void CEditService::NotifyOnFontChange()
		{
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
		}

		void CEditService::NotifyOnSetFocus(const MessageFocus &m)
		{
			m_pEdit->getTextInput()->setFocused(true);
			if ((m.FocusedBy == FocusedBy::Tab || m.FocusedBy == FocusedBy::ShiftTab) && !m_pEdit->getTextInput()->hasSelection())
				m_pEdit->getTextInput()->SelectAll();
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
			m_pEdit->Repaint(false);
		}

		void CEditService::NotifyOnKillFocus()
		{
			m_pEdit->getTextInput()->setFocused(false);
			m_pEdit->getTextInput()->DeselectAll();
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
			m_pEdit->Repaint(false);
		}

		void CEditService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pEdit->getTextInput()->NotifyOnMouseHover(LocalToTextInput(m_pEdit->FormToLocal(m.Position))))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CEditService::NotifyOnMouseLeave()
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
		void CEditService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pEdit->getWidth(), 0) && ntl::IsGreater<float>(m_pEdit->getHeight(), 0))
				m_pEdit->Render();
		}
	#pragma endregion

	#pragma region Input notifications
		void CEditService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
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

		void CEditService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
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

		void CEditService::NotifyOnChar(const MessageChar &m, bool &processed)
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

		void CEditService::NotifyOnDeadChar(const MessageChar &m, bool &processed)
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

		void CEditService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pEdit->getTextInput()->NotifyOnMouseMove(LocalToTextInput(m_pEdit->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CEditService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
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

		void CEditService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			MouseUp(m.Position);
		}

		void CEditService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m.Middle && !m.Right && m_pEdit->getTextInput()->NotifyOnMouseLeftDoubleClick(LocalToTextInput(m_pEdit->FormToLocal(m.Position)), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CEditService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CEditService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CEditService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CEditService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CEditService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CEditService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CEditService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pEdit->getTextInput()->NotifyOnMouseVerticalWheel(LocalToTextInput(m_pEdit->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CEditService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pEdit->getTextInput()->NotifyOnMouseHorizontalWheel(LocalToTextInput(m_pEdit->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(false);
			}
		}

		void CEditService::NotifyOnDropFiles(const MessageDropFiles &m, bool &processed, bool &accepted)
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
		void CEditService::NotifyOnPasteString(const MessagePasteString &m)
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
		void CEditService::MouseUp(const PointF &pos)
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

		PointF CEditService::LocalToTextInput(const PointF &pos)
		{
			return{ pos.X - m_pEdit->m_sBorderWidth.Left - m_pEdit->m_sPadding.Left, pos.Y - m_pEdit->m_sBorderWidth.Top - m_pEdit->m_sPadding.Top };
		}
	#pragma endregion
	}
}