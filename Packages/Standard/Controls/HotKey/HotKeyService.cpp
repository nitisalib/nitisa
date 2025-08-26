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
		CHotKeyService::CHotKeyService(CHotKey *hotkey) :
			CControlService(hotkey),
			m_pHotKey{ hotkey }
		{

		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CHotKeyService::NotifyOnParentStyleChange()
		{
			if (m_pHotKey->getStyle())
			{
				m_pHotKey->UpdateFromStyle(m_pHotKey->getStyle());
				if (m_pHotKey->m_pCanvas)
					m_pHotKey->m_pCanvas->setValid(false);
			}
		}

		void CHotKeyService::NotifyOnParentFontChange()
		{
			if (m_pHotKey->m_pCanvas)
				m_pHotKey->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CHotKeyService::NotifyOnFreeResources()
		{
			if (m_pHotKey->m_pCanvas)
			{
				m_pHotKey->m_pCanvas->Release();
				m_pHotKey->m_pCanvas = nullptr;
			}
		}

		void CHotKeyService::NotifyOnEnable()
		{
			if (m_pHotKey->m_pCanvas)
				m_pHotKey->m_pCanvas->setValid(false);
		}

		void CHotKeyService::NotifyOnDisable()
		{
			if (m_pHotKey->m_pCanvas)
				m_pHotKey->m_pCanvas->setValid(false);
		}

		void CHotKeyService::NotifyOnResize()
		{
			if (m_pHotKey->m_pCanvas)
				m_pHotKey->m_pCanvas->setValid(false);
		}

		void CHotKeyService::NotifyOnStyleChange()
		{
			if (m_pHotKey->getStyle())
			{
				m_pHotKey->UpdateFromStyle(m_pHotKey->getStyle());
				if (m_pHotKey->m_pCanvas)
					m_pHotKey->m_pCanvas->setValid(false);
			}
		}

		void CHotKeyService::NotifyOnFontChange()
		{
			if (m_pHotKey->m_pCanvas)
				m_pHotKey->m_pCanvas->setValid(false);
		}

		void CHotKeyService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pHotKey->m_pCanvas)
				m_pHotKey->m_pCanvas->setValid(false);
			m_pHotKey->Repaint(false);
		}

		void CHotKeyService::NotifyOnKillFocus()
		{
			if (m_pHotKey->m_pCanvas)
				m_pHotKey->m_pCanvas->setValid(false);
			m_pHotKey->Repaint(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CHotKeyService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pHotKey->getWidth(), 0) && ntl::IsGreater<float>(m_pHotKey->getHeight(), 0))
				m_pHotKey->Render();
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CHotKeyService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m.Key != Key::Control && m.Key != Key::Shift)
			{
				Hotkey h{ m.Key };
				Application->Keyboard->getControlKeys(h.Ctrl, h.Alt, h.Shift);
				m_pHotKey->setHotKey(h);
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CHotKeyService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pHotKey->m_pCanvas)
				m_pHotKey->m_pCanvas->setValid(false);
			m_pHotKey->Repaint(false);
		}

		void CHotKeyService::NotifyOnMouseLeave()
		{
			if (m_pHotKey->m_pCanvas)
				m_pHotKey->m_pCanvas->setValid(false);
			m_pHotKey->Repaint(false);
		}
	#pragma endregion
	}
}