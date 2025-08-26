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
	namespace standard
	{
	#pragma region Constructor & destructor
		CEditCalcService::CEditCalcService(CEditCalc *control) :
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CEditCalcService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CEditCalcService::NotifyOnParentFontChange()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CEditCalcService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pTextInput)
				m_pControl->m_pTextInput->NotifyOnFreeResources();
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
		}

		void CEditCalcService::NotifyOnEnable()
		{
			m_pControl->getTextInput()->setEnabled(true);
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CEditCalcService::NotifyOnDisable()
		{
			m_pControl->getTextInput()->setEnabled(false);
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CEditCalcService::NotifyOnAttach()
		{
			if (m_pControl->getForm())
			{
				if (!m_pControl->m_bTextChanged)
					m_pControl->setText(m_pControl->m_sName);
				m_pControl->getTextInput()->NotifyOnAttach();
			}
		}

		void CEditCalcService::NotifyOnResize()
		{
			m_pControl->AdjustTextInputSize();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CEditCalcService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CEditCalcService::NotifyOnFontChange()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CEditCalcService::NotifyOnSetFocus(const MessageFocus &m)
		{
			m_pControl->getTextInput()->setFocused(true);
			if ((m.FocusedBy == FocusedBy::Tab || m.FocusedBy == FocusedBy::ShiftTab) && !m_pControl->getTextInput()->hasSelection())
				m_pControl->getTextInput()->SelectAll();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CEditCalcService::NotifyOnKillFocus()
		{
			m_pControl->getTextInput()->setFocused(false);
			m_pControl->getTextInput()->DeselectAll();
			if (m_pControl->m_bAutoCalculate)
				m_pControl->Calculate();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CEditCalcService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pControl->getTextInput()->NotifyOnMouseHover(LocalToTextInput(m_pControl->FormToLocal(m.Position))))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CEditCalcService::NotifyOnMouseLeave()
		{
			if (m_pControl->getTextInput()->NotifyOnMouseLeave())
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Paint notifications
		void CEditCalcService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
				m_pControl->Render();
		}
	#pragma endregion

	#pragma region Input notifications
		void CEditCalcService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pControl->getTextInput()->NotifyOnKeyDown(m.Key, ctrl, alt, shift, Application->Keyboard->isToggled(Key::NumLock)))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CEditCalcService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pControl->getTextInput()->NotifyOnKeyUp(m.Key, ctrl, alt, shift, Application->Keyboard->isToggled(Key::NumLock)))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
			else if (m_pControl->m_bCalculateOnReturn && (m.Key == Key::Return || m.Key == Key::Separator) && !ctrl && !alt && !shift)
				m_pControl->Calculate();
		}

		void CEditCalcService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pControl->getTextInput()->NotifyOnChar(m.Char, ctrl, alt, shift, Application->Keyboard->isToggled(Key::NumLock)))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CEditCalcService::NotifyOnDeadChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pControl->getTextInput()->NotifyOnDeadChar(m.Char, ctrl, alt, shift, Application->Keyboard->isToggled(Key::NumLock)))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CEditCalcService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->getTextInput()->NotifyOnMouseMove(LocalToTextInput(m_pControl->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CEditCalcService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			m_pControl->getForm()->CaptureMouse(m_pControl, true);
			if (!m.Middle && !m.Right && m_pControl->getTextInput()->NotifyOnMouseLeftDown(LocalToTextInput(m_pControl->FormToLocal(m.Position)), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CEditCalcService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			MouseUp(m.Position);
		}

		void CEditCalcService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m.Middle && !m.Right && m_pControl->getTextInput()->NotifyOnMouseLeftDoubleClick(LocalToTextInput(m_pControl->FormToLocal(m.Position)), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CEditCalcService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CEditCalcService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CEditCalcService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CEditCalcService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CEditCalcService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CEditCalcService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CEditCalcService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->getTextInput()->NotifyOnMouseVerticalWheel(LocalToTextInput(m_pControl->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CEditCalcService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->getTextInput()->NotifyOnMouseHorizontalWheel(LocalToTextInput(m_pControl->FormToLocal(m.Position)), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CEditCalcService::NotifyOnDropFiles(const MessageDropFiles &m, bool &processed, bool &accepted)
		{
			processed = true;
			if (m_pControl->getTextInput()->NotifyOnDropFiles(LocalToTextInput(m_pControl->FormToLocal(m.Position)), m.FileNames))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Clipboard notifications
		void CEditCalcService::NotifyOnPasteString(const MessagePasteString &m)
		{
			if (m_pControl->getTextInput()->NotifyOnPasteString(m.Text))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Helpers
		void CEditCalcService::MouseUp(const PointF &pos)
		{
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (m_pControl->getTextInput()->NotifyOnMouseLeftUp(LocalToTextInput(m_pControl->FormToLocal(pos)), false, false, ctrl, alt, shift))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		PointF CEditCalcService::LocalToTextInput(const PointF &pos)
		{
			return{ pos.X - m_pControl->m_sBorderWidth.Left - m_pControl->m_sPadding.Left, pos.Y - m_pControl->m_sBorderWidth.Top - m_pControl->m_sPadding.Top };
		}
	#pragma endregion
	}
}