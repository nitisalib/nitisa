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
		CCustomDropDownService::CCustomDropDownService(CCustomDropDown *dropdown) :
			CControlService{ dropdown },
			m_pDropDown{ dropdown }
		{

		}
	#pragma endregion

	#pragma region Helpers
		bool CCustomDropDownService::MoveItem(IListItem *item, const int before)
		{
			if (m_pDropDown->getDropDown()->MoveItem(item, before))
			{
				m_pDropDown->Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region State change notifications
		void CCustomDropDownService::NotifyOnAttach()
		{
			if (m_pDropDown->getForm())
				m_pDropDown->getDropDown()->NotifyOnAttach();
		}

		void CCustomDropDownService::NotifyOnDetaching()
		{
			m_pDropDown->Close();
		}

		void CCustomDropDownService::NotifyOnFreeResources()
		{
			m_pDropDown->getDropDown()->NotifyOnFreeResources();
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CCustomDropDownService::NotifyOnParentStyleChange()
		{
			if (m_pDropDown->getStyle())
				m_pDropDown->UpdateFromStyle(m_pDropDown->getStyle());
		}

		void CCustomDropDownService::NotifyOnParentFontChange()
		{
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			m_pDropDown->getDropDown()->Update();
			m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}
	#pragma endregion

	#pragma region State change notifications
		void CCustomDropDownService::NotifyOnEnable()
		{
			m_pDropDown->getDropDown()->setEnabled(true);
		}

		void CCustomDropDownService::NotifyOnDisable()
		{
			m_pDropDown->Close();
			m_pDropDown->getDropDown()->setEnabled(false);
		}

		void CCustomDropDownService::NotifyOnResize()
		{
			m_pDropDown->UpdateDropDown();
		}

		void CCustomDropDownService::NotifyOnStyleChange()
		{
			if (m_pDropDown->getStyle())
				m_pDropDown->UpdateFromStyle(m_pDropDown->getStyle());
		}

		void CCustomDropDownService::NotifyOnFontChange()
		{
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			m_pDropDown->getDropDown()->Update();
			m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CCustomDropDownService::NotifyOnSetFocus(const MessageFocus &m)
		{
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			bool changed{ (m.FocusedBy == FocusedBy::Tab || m.FocusedBy == FocusedBy::ShiftTab) && m_pDropDown->getDropDown()->isEditable() && !m_pDropDown->getDropDown()->getTextInput()->hasSelection() && m_pDropDown->getDropDown()->getTextInput()->SelectAll() };
			if (m_pDropDown->getDropDown()->setFocused(true) || changed)
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CCustomDropDownService::NotifyOnKillFocus()
		{
			m_pDropDown->Close();
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->setFocused(false))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CCustomDropDownService::NotifyOnKillCaptureMouse()
		{
			if (m_pDropDown->getDropDown()->isOpened() && !m_pDropDown->m_bIgnoreKillCaptureMouse)
			{
				RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
				if (m_pDropDown->getDropDown()->Close())
					m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
			}
		}

		void CCustomDropDownService::NotifyOnDeactivate()
		{
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->Close())
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CCustomDropDownService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (ntl::IsGreater<float>(m_pDropDown->getWidth(), 0) && ntl::IsGreater<float>(m_pDropDown->getHeight(), 0))
			{
				if (m.LastPass)
					m_pDropDown->RenderList();
				else
					m_pDropDown->Render();
			}
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CCustomDropDownService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnKeyDown(m.Key, ctrl, alt, shift, numlock))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CCustomDropDownService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnKeyUp(m.Key, ctrl, alt, shift, numlock))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CCustomDropDownService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnChar(m.Char, ctrl, alt, shift, numlock))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CCustomDropDownService::NotifyOnDeadChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnDeadChar(m.Char, ctrl, alt, shift, numlock))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CCustomDropDownService::NotifyOnMouseHover(const MessagePosition &m)
		{
			PointF position{ m_pDropDown->FormToLocal(m.Position) };
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseHover(position))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CCustomDropDownService::NotifyOnMouseLeave()
		{
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseLeave())
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CCustomDropDownService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseMove(m_pDropDown->FormToLocal(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CCustomDropDownService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseLeftDown(m_pDropDown->FormToLocal(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
			if (m_pDropDown->isOpened())
				m_pDropDown->getForm()->CaptureMouse(m_pDropDown, true);
		}

		void CCustomDropDownService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseLeftUp(m_pDropDown->FormToLocal(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
			if (!m_pDropDown->isOpened() && m_pDropDown->isCaptureMouse())
				m_pDropDown->getForm()->ReleaseCaptureMouse();
		}

		void CCustomDropDownService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseLeftDoubleClick(m_pDropDown->FormToLocal(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
			if (!m_pDropDown->isOpened() && m_pDropDown->isCaptureMouse())
				m_pDropDown->getForm()->ReleaseCaptureMouse();
		}

		void CCustomDropDownService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseRightDown(m_pDropDown->FormToLocal(m.Position), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
			if (!m_pDropDown->isOpened() && m_pDropDown->isCaptureMouse())
				m_pDropDown->getForm()->ReleaseCaptureMouse();
		}

		void CCustomDropDownService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseRightUp(m_pDropDown->FormToLocal(m.Position), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
			if (!m_pDropDown->isOpened() && m_pDropDown->isCaptureMouse())
				m_pDropDown->getForm()->ReleaseCaptureMouse();
		}

		void CCustomDropDownService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseRightDoubleClick(m_pDropDown->FormToLocal(m.Position), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
			if (!m_pDropDown->isOpened() && m_pDropDown->isCaptureMouse())
				m_pDropDown->getForm()->ReleaseCaptureMouse();
		}

		void CCustomDropDownService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseMiddleDown(m_pDropDown->FormToLocal(m.Position), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
			if (!m_pDropDown->isOpened() && m_pDropDown->isCaptureMouse())
				m_pDropDown->getForm()->ReleaseCaptureMouse();
		}

		void CCustomDropDownService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseMiddleUp(m_pDropDown->FormToLocal(m.Position), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
			if (!m_pDropDown->isOpened() && m_pDropDown->isCaptureMouse())
				m_pDropDown->getForm()->ReleaseCaptureMouse();
		}

		void CCustomDropDownService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseMiddleDoubleClick(m_pDropDown->FormToLocal(m.Position), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
			if (!m_pDropDown->isOpened() && m_pDropDown->isCaptureMouse())
				m_pDropDown->getForm()->ReleaseCaptureMouse();
		}

		void CCustomDropDownService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseVerticalWheel(m_pDropDown->FormToLocal(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}
	#pragma endregion

	#pragma region Clipboard notifications
		void CCustomDropDownService::NotifyOnPasteString(const MessagePasteString &m)
		{
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnPasteString(m.Text))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}
	#pragma endregion
	}
}