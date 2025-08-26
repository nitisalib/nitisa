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
		CBitBtnService::CBitBtnService(CBitBtn *bitbtn) :
			CControlService{ bitbtn },
			m_pBitBtn{ bitbtn }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CBitBtnService::CancelMouseDown()
		{
			if (m_pBitBtn->isCaptureMouse())
				m_pBitBtn->getForm()->ReleaseCaptureMouse();
			if (m_pBitBtn->m_bMouseDown)
			{
				m_pBitBtn->m_bMouseDown = false;
				if (m_pBitBtn->m_pCanvas)
					m_pBitBtn->m_pCanvas->setValid(false);
				m_pBitBtn->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CBitBtnService::NotifyOnAttach()
		{
			m_pBitBtn->UpdateHotkeys();
		}

		void CBitBtnService::NotifyOnFreeResources()
		{
			if (m_pBitBtn->m_pCanvas)
			{
				m_pBitBtn->m_pCanvas->Release();
				m_pBitBtn->m_pCanvas = nullptr;
			}
		}
	#pragma endregion

	#pragma region Other input notifications
		void CBitBtnService::NotifyOnHotkey(const MessageHotkey &m)
		{
			if (m_pBitBtn->isEnabled(true))
			{
				switch (m_pBitBtn->m_eKind)
				{
				case IBitBtn::Kind::Abord:
				case IBitBtn::Kind::Cancel:
				case IBitBtn::Kind::Close:
				case IBitBtn::Kind::Ignore:
				case IBitBtn::Kind::No:
					if (m.Key == Key::Escape)
						m_pBitBtn->Click();
					break;
				case IBitBtn::Kind::All:
				case IBitBtn::Kind::Ok:
				case IBitBtn::Kind::Retry:
				case IBitBtn::Kind::Yes:
					if ((m.Key == Key::Return || m.Key == Key::Separator) && !m_pBitBtn->isFocused())
						m_pBitBtn->Click();
					break;
				default:
					break;
				}
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CBitBtnService::NotifyOnParentStyleChange()
		{
			if (m_pBitBtn->getStyle())
			{
				m_pBitBtn->UpdateFromStyle(m_pBitBtn->getStyle());
				if (m_pBitBtn->m_pCanvas)
					m_pBitBtn->m_pCanvas->setValid(false);
			}
		}

		void CBitBtnService::NotifyOnParentFontChange()
		{
			if (m_pBitBtn->m_pCanvas)
				m_pBitBtn->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CBitBtnService::NotifyOnResize()
		{
			if (m_pBitBtn->m_pCanvas)
				m_pBitBtn->m_pCanvas->setValid(false);
		}

		void CBitBtnService::NotifyOnStyleChange()
		{
			if (m_pBitBtn->getStyle())
			{
				m_pBitBtn->UpdateFromStyle(m_pBitBtn->getStyle());
				if (m_pBitBtn->m_pCanvas)
					m_pBitBtn->m_pCanvas->setValid(false);
			}
		}

		void CBitBtnService::NotifyOnFontChange()
		{
			if (m_pBitBtn->m_pCanvas)
				m_pBitBtn->m_pCanvas->setValid(false);
		}

		void CBitBtnService::NotifyOnEnable()
		{
			m_pBitBtn->UpdateHotkeys();
			if (m_pBitBtn->m_pCanvas)
				m_pBitBtn->m_pCanvas->setValid(false);
		}

		void CBitBtnService::NotifyOnDisable()
		{
			m_pBitBtn->UpdateHotkeys();
			if (m_pBitBtn->m_pCanvas)
				m_pBitBtn->m_pCanvas->setValid(false);
		}

		void CBitBtnService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pBitBtn->m_pCanvas)
				m_pBitBtn->m_pCanvas->setValid(false);
			m_pBitBtn->Repaint(false);
		}

		void CBitBtnService::NotifyOnKillFocus()
		{
			if (m_pBitBtn->m_pCanvas)
				m_pBitBtn->m_pCanvas->setValid(false);
			m_pBitBtn->Repaint(false);
		}

		void CBitBtnService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pBitBtn->m_pCanvas)
				m_pBitBtn->m_pCanvas->setValid(false);
			m_pBitBtn->Repaint(false);
		}

		void CBitBtnService::NotifyOnMouseLeave()
		{
			if (m_pBitBtn->m_pCanvas)
				m_pBitBtn->m_pCanvas->setValid(false);
			m_pBitBtn->Repaint(false);
		}

		void CBitBtnService::NotifyOnKillCaptureMouse()
		{
			if (m_pBitBtn->m_bMouseDown)
			{
				m_pBitBtn->m_bMouseDown = false;
				if (m_pBitBtn->m_pCanvas)
					m_pBitBtn->m_pCanvas->setValid(false);
				m_pBitBtn->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Paint notifications
		void CBitBtnService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pBitBtn->getWidth(), 0) && ntl::IsGreater<float>(m_pBitBtn->getHeight(), 0))
				m_pBitBtn->Render();
		}
	#pragma endregion

	#pragma region Input notifications
		void CBitBtnService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m_pBitBtn->isEnabled(true) && !m_pBitBtn->m_bKeyDown && (m.Key == Key::Return || m.Key == Key::Separator))
			{
				bool ctrl, alt, shift;
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (!ctrl && !alt && !shift)
				{
					m_pBitBtn->m_bKeyDown = true;
					if (m_pBitBtn->m_pCanvas)
						m_pBitBtn->m_pCanvas->setValid(false);
					m_pBitBtn->Repaint(false);
				}
			}
		}

		void CBitBtnService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m_pBitBtn->m_bKeyDown)
			{
				if (m_pBitBtn->isEnabled(true) && (m.Key == Key::Return || m.Key == Key::Separator))
				{
					m_pBitBtn->m_bKeyDown = false;
					m_pBitBtn->Click();
					if (m_pBitBtn->m_pCanvas)
						m_pBitBtn->m_pCanvas->setValid(false);
					m_pBitBtn->Repaint(false);
				}
				else
				{
					m_pBitBtn->m_bKeyDown = false;
					if (m_pBitBtn->m_pCanvas)
						m_pBitBtn->m_pCanvas->setValid(false);
					m_pBitBtn->Repaint(false);
				}
			}
		}

		void CBitBtnService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pBitBtn->isEnabled(true) && !m_pBitBtn->m_bMouseDown && m.Left && !m.Middle && !m.Right)
			{
				m_pBitBtn->m_bMouseDown = true;
				m_pBitBtn->getForm()->CaptureMouse(m_pBitBtn, true);
				if (m_pBitBtn->m_pCanvas)
					m_pBitBtn->m_pCanvas->setValid(false);
				m_pBitBtn->Repaint(false);
			}
			else
				CancelMouseDown();
		}

		void CBitBtnService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pBitBtn->isEnabled(true) && m_pBitBtn->m_bMouseDown && m.Left && !m.Middle && !m.Right && m_pBitBtn->isHovered())
			{
				CancelMouseDown();
				m_pBitBtn->Click();
			}
			else
				CancelMouseDown();
		}

		void CBitBtnService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CBitBtnService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CBitBtnService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CBitBtnService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CBitBtnService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CBitBtnService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}

		void CBitBtnService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelMouseDown();
		}
	#pragma endregion
	}
}