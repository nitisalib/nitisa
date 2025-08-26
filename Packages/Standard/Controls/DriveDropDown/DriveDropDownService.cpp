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
		CDriveDropDownService::CDriveDropDownService(CDriveDropDown *dropdown) :
			CControlService{ dropdown },
			m_pDropDown{ dropdown }
		{

		}
	#pragma endregion

	#pragma region State change notifications
		void CDriveDropDownService::NotifyOnAttach()
		{
			if (m_pDropDown->getForm())
				m_pDropDown->getDropDown()->NotifyOnAttach();
		}

		void CDriveDropDownService::NotifyOnDetaching()
		{
			m_pDropDown->Close();
		}

		void CDriveDropDownService::NotifyOnDetach()
		{
			m_pDropDown->m_pDirectoryTree = nullptr;
		}

		void CDriveDropDownService::NotifyOnFreeResources()
		{
			m_pDropDown->getDropDown()->NotifyOnFreeResources();
		}
	#pragma endregion

	#pragma region Component notifications
		void CDriveDropDownService::NotifyOnComponentDetach(IComponent *component)
		{
			if (m_pDropDown->m_pDirectoryTree && cast<IDirectoryTree*>(component) == m_pDropDown->m_pDirectoryTree)
				m_pDropDown->m_pDirectoryTree = nullptr;
		}
	#pragma endregion

	#pragma region Control notifications
		void CDriveDropDownService::NotifyOnControlDetach(IControl *control)
		{
			if (m_pDropDown->m_pDirectoryTree && cast<IDirectoryTree*>(control) == m_pDropDown->m_pDirectoryTree)
				m_pDropDown->m_pDirectoryTree = nullptr;
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CDriveDropDownService::NotifyOnParentStyleChange()
		{
			if (m_pDropDown->getStyle())
				m_pDropDown->UpdateFromStyle(m_pDropDown->getStyle());
		}

		void CDriveDropDownService::NotifyOnParentFontChange()
		{
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			m_pDropDown->getDropDown()->Update();
			m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}
	#pragma endregion

	#pragma region State change notifications
		void CDriveDropDownService::NotifyOnEnable()
		{
			m_pDropDown->getDropDown()->setEnabled(true);
		}

		void CDriveDropDownService::NotifyOnDisable()
		{
			m_pDropDown->Close();
			m_pDropDown->getDropDown()->setEnabled(false);
		}

		void CDriveDropDownService::NotifyOnResize()
		{
			m_pDropDown->UpdateDropDown();
		}

		void CDriveDropDownService::NotifyOnStyleChange()
		{
			if (m_pDropDown->getStyle())
				m_pDropDown->UpdateFromStyle(m_pDropDown->getStyle());
		}

		void CDriveDropDownService::NotifyOnFontChange()
		{
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			m_pDropDown->getDropDown()->Update();
			m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnSetFocus(const MessageFocus &m)
		{
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->setFocused(true))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnKillFocus()
		{
			m_pDropDown->Close();
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->setFocused(false))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnKillCaptureMouse()
		{
			if (m_pDropDown->getDropDown()->isOpened() && !m_pDropDown->m_bIgnoreKillCaptureMouse)
			{
				RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
				if (m_pDropDown->getDropDown()->Close())
					m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
			}
		}

		void CDriveDropDownService::NotifyOnDeactivate()
		{
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->Close())
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CDriveDropDownService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
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
		void CDriveDropDownService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnKeyDown(m.Key, ctrl, alt, shift, numlock))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnKeyUp(m.Key, ctrl, alt, shift, numlock))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnChar(m.Char, ctrl, alt, shift, numlock))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnDeadChar(const MessageChar &m, bool &processed)
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
		void CDriveDropDownService::NotifyOnMouseHover(const MessagePosition &m)
		{
			PointF position{ m_pDropDown->FormToLocal(m.Position) };
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseHover(position))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnMouseLeave()
		{
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseLeave())
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseMove(m_pDropDown->FormToLocal(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseLeftDown(m_pDropDown->FormToLocal(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseLeftUp(m_pDropDown->FormToLocal(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseLeftDoubleClick(m_pDropDown->FormToLocal(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseRightDown(m_pDropDown->FormToLocal(m.Position), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseRightUp(m_pDropDown->FormToLocal(m.Position), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseRightDoubleClick(m_pDropDown->FormToLocal(m.Position), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseMiddleDown(m_pDropDown->FormToLocal(m.Position), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseMiddleUp(m_pDropDown->FormToLocal(m.Position), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseMiddleDoubleClick(m_pDropDown->FormToLocal(m.Position), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}

		void CDriveDropDownService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			RectF r{ m_pDropDown->getDropDown()->getRenderRect() };
			if (m_pDropDown->getDropDown()->NotifyOnMouseVerticalWheel(m_pDropDown->FormToLocal(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
				m_pDropDown->Repaint(r + m_pDropDown->getDropDown()->getRenderRect(), true);
		}
	#pragma endregion
	}
}