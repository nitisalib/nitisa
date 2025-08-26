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
		CSelectService::CSelectService(CSelect *control) :
			CControlService{ control },
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Helpers
		bool CSelectService::MoveItem(IListItem *item, const int before)
		{
			if (m_pControl->getSelect()->MoveItem(item, before))
			{
				m_pControl->Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region State change notifications
		void CSelectService::NotifyOnAttach()
		{
			if (m_pControl->getForm())
				m_pControl->getSelect()->NotifyOnAttach();
		}

		void CSelectService::NotifyOnDetaching()
		{
			m_pControl->Close();
		}

		void CSelectService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pSelect)
				m_pControl->m_pSelect->NotifyOnFreeResources();
			m_pControl->m_cCategoryFont.NotifyOnFreeResources();
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CSelectService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
		}

		void CSelectService::NotifyOnParentFontChange()
		{
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			m_pControl->m_pSelect->Update();
			m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
		}
	#pragma endregion

	#pragma region State change notifications
		void CSelectService::NotifyOnEnable()
		{
			m_pControl->getSelect()->setEnabled(true);
		}

		void CSelectService::NotifyOnDisable()
		{
			m_pControl->Close();
			m_pControl->getSelect()->setEnabled(false);
		}

		void CSelectService::NotifyOnResize()
		{
			m_pControl->UpdateSelect();
		}

		void CSelectService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
		}

		void CSelectService::NotifyOnFontChange()
		{
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			m_pControl->m_pSelect->Update();
			m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
		}

		void CSelectService::NotifyOnSetFocus(const MessageFocus &m)
		{
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			bool changed{ (m.FocusedBy == FocusedBy::Tab || m.FocusedBy == FocusedBy::ShiftTab) && m_pControl->m_pSelect->isOpened() && !m_pControl->m_pSelect->getTextInput()->hasSelection() &&
				m_pControl->m_pSelect->getTextInput()->SelectAll() };
			if (m_pControl->m_pSelect->setFocused(true) || changed)
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
		}

		void CSelectService::NotifyOnKillFocus()
		{
			m_pControl->Close();
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->setFocused(false))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
		}

		void CSelectService::NotifyOnKillCaptureMouse()
		{
			if (m_pControl->getSelect()->isOpened() && !m_pControl->m_bIgnoreKillCaptureMouse)
			{
				RectF r{ m_pControl->m_pSelect->getRenderRect() };
				if (m_pControl->m_pSelect->Close())
					m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
			}
		}

		void CSelectService::NotifyOnDeactivate()
		{
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->Close())
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CSelectService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
			{
				if (m.LastPass)
					m_pControl->RenderList();
				else
					m_pControl->Render();
			}
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CSelectService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnKeyDown(m.Key, ctrl, alt, shift, numlock))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
		}

		void CSelectService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnKeyUp(m.Key, ctrl, alt, shift, numlock))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
		}

		void CSelectService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnChar(m.Char, ctrl, alt, shift, numlock))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
		}

		void CSelectService::NotifyOnDeadChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnDeadChar(m.Char, ctrl, alt, shift, numlock))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CSelectService::NotifyOnMouseHover(const MessagePosition &m)
		{
			PointF position{ m_pControl->FormToLocal(m.Position) };
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnMouseHover(position))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
		}

		void CSelectService::NotifyOnMouseLeave()
		{
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnMouseLeave())
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
		}

		void CSelectService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnMouseMove(m_pControl->FormToLocal(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
		}

		void CSelectService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnMouseLeftDown(m_pControl->FormToLocal(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
			if (m_pControl->isOpened())
				m_pControl->getForm()->CaptureMouse(m_pControl, true);
		}

		void CSelectService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnMouseLeftUp(m_pControl->FormToLocal(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
			if (!m_pControl->isOpened() && m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CSelectService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnMouseLeftDoubleClick(m_pControl->FormToLocal(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
			if (!m_pControl->isOpened() && m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CSelectService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnMouseRightDown(m_pControl->FormToLocal(m.Position), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
			if (!m_pControl->isOpened() && m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CSelectService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnMouseRightUp(m_pControl->FormToLocal(m.Position), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
			if (!m_pControl->isOpened() && m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CSelectService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnMouseRightDoubleClick(m_pControl->FormToLocal(m.Position), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
			if (!m_pControl->isOpened() && m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CSelectService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnMouseMiddleDown(m_pControl->FormToLocal(m.Position), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
			if (!m_pControl->isOpened() && m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CSelectService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnMouseMiddleUp(m_pControl->FormToLocal(m.Position), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
			if (!m_pControl->isOpened() && m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CSelectService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnMouseMiddleDoubleClick(m_pControl->FormToLocal(m.Position), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
			if (!m_pControl->isOpened() && m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CSelectService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnMouseVerticalWheel(m_pControl->FormToLocal(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
		}
	#pragma endregion

	#pragma region Clipboard notifications
		void CSelectService::NotifyOnPasteString(const MessagePasteString &m)
		{
			RectF r{ m_pControl->getSelect()->getRenderRect() };
			if (m_pControl->m_pSelect->NotifyOnPasteString(m.Text))
				m_pControl->Repaint(r + m_pControl->m_pSelect->getRenderRect(), true);
		}
	#pragma endregion
	}
}