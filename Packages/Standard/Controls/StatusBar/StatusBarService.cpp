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
		CStatusBarService::CStatusBarService(CStatusBar *statusbar) :
			CControlService{ statusbar },
			m_pStatusBar{ statusbar }
		{

		}
	#pragma endregion

	#pragma region Helpers
		bool CStatusBarService::MoveItem(IListItem *item, const int before)
		{
			return MoveListItem(m_pStatusBar->m_aItems, m_pStatusBar, item, before);
		}
	#pragma endregion

	#pragma region State change notifications
		void CStatusBarService::NotifyOnAttach()
		{
			if (m_pStatusBar->getForm())
				m_pStatusBar->Update();
		}
	
		void CStatusBarService::NotifyOnFreeResources()
		{
			for (auto pos = m_pStatusBar->m_aItems.begin(); pos != m_pStatusBar->m_aItems.end(); pos++)
				(*pos)->QueryService()->NotifyOnFreeResources();
			if (m_pStatusBar->m_pCanvas)
			{
				m_pStatusBar->m_pCanvas->Release();
				m_pStatusBar->m_pCanvas = nullptr;
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CStatusBarService::NotifyOnParentStyleChange()
		{
			if (m_pStatusBar->getStyle())
			{
				m_pStatusBar->UpdateFromStyle(m_pStatusBar->getStyle());
				m_pStatusBar->Update();
				if (m_pStatusBar->m_pCanvas)
					m_pStatusBar->m_pCanvas->setValid(false);
			}
		}

		void CStatusBarService::NotifyOnParentFontChange()
		{
			m_pStatusBar->Update();
			if (m_pStatusBar->m_pCanvas)
				m_pStatusBar->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CStatusBarService::NotifyOnResize()
		{
			if (m_pStatusBar->m_pCanvas)
				m_pStatusBar->m_pCanvas->setValid(false);
			m_pStatusBar->Update();
		}

		void CStatusBarService::NotifyOnEnable()
		{
			if (m_pStatusBar->m_pCanvas)
				m_pStatusBar->m_pCanvas->setValid(false);
		}

		void CStatusBarService::NotifyOnDisable()
		{
			if (m_pStatusBar->m_pCanvas)
				m_pStatusBar->m_pCanvas->setValid(false);
		}

		void CStatusBarService::NotifyOnStyleChange()
		{
			if (m_pStatusBar->getStyle())
			{
				m_pStatusBar->UpdateFromStyle(m_pStatusBar->getStyle());
				m_pStatusBar->Update();
				if (m_pStatusBar->m_pCanvas)
					m_pStatusBar->m_pCanvas->setValid(false);
			}
		}

		void CStatusBarService::NotifyOnFontChange()
		{
			m_pStatusBar->Update();
			if (m_pStatusBar->m_pCanvas)
				m_pStatusBar->m_pCanvas->setValid(false);
		}

		void CStatusBarService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pStatusBar->UpdateHoveredItem())
			{
				if (m_pStatusBar->m_pCanvas)
					m_pStatusBar->m_pCanvas->setValid(false);
				m_pStatusBar->Repaint(false);
			}
		}

		void CStatusBarService::NotifyOnMouseLeave()
		{
			if (m_pStatusBar->UpdateHoveredItem())
			{
				if (m_pStatusBar->m_pCanvas)
					m_pStatusBar->m_pCanvas->setValid(false);
				m_pStatusBar->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Paint notifications
		void CStatusBarService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pStatusBar->getWidth(), 0) && ntl::IsGreater<float>(m_pStatusBar->getHeight(), 0))
				m_pStatusBar->Render();
		}
	#pragma endregion

	#pragma region Input notifications
		void CStatusBarService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pStatusBar->isEnabled(false) && m_pStatusBar->UpdateHoveredItem(m_pStatusBar->FormToLocal(m.Position)))
			{
				if (m_pStatusBar->m_pCanvas)
					m_pStatusBar->m_pCanvas->setValid(false);
				m_pStatusBar->Repaint(false);
			}
		}
	#pragma endregion
	}
}