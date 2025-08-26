// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#include <Windows.h>
#include <shellapi.h>
#endif

namespace nitisa
{
	namespace standard
	{
	#pragma region Constructor & destructor
		CTrayIconService::CTrayIconService(CTrayIcon *component):
			CComponentService(component),
			m_pComponent{ component }
		{

		}
	#pragma endregion

	#pragma region State change notifications
		void CTrayIconService::NotifyOnAttach()
		{
			m_pComponent->AddIcon();
			m_pComponent->getForm()->QueryService()->RegisterMessageListener(m_pComponent, &m_pComponent->m_cListener);
		}

		void CTrayIconService::NotifyOnDetaching()
		{
			m_pComponent->getForm()->QueryService()->UnregisterMessageListeners(m_pComponent);
			NotifyOnFreeResources();
		}

		void CTrayIconService::NotifyOnFreeResources()
		{
		#ifdef _WIN32
			m_pComponent->RemoveIcon();
			if (m_pComponent->m_pData->hIcon)
			{
				DestroyIcon(m_pComponent->m_pData->hIcon);
				m_pComponent->m_pData->hIcon = 0;
			}
			if (m_pComponent->m_pData->hBalloonIcon)
			{
				DestroyIcon(m_pComponent->m_pData->hBalloonIcon);
				m_pComponent->m_pData->hBalloonIcon = 0;
			}
		#endif
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CTrayIconService::NotifyOnKeyDown(const MessageKey &m)
		{
			if (m_pComponent->OnKeyDown)
				m_pComponent->OnKeyDown(m_pComponent, m);
		}

		void CTrayIconService::NotifyOnKeyUp(const MessageKey &m)
		{
			if (m_pComponent->OnKeyUp)
				m_pComponent->OnKeyUp(m_pComponent, m);
		}

		void CTrayIconService::NotifyOnChar(const MessageChar &m)
		{
			if (m_pComponent->OnChar)
				m_pComponent->OnChar(m_pComponent, m);
		}

		void CTrayIconService::NotifyOnDeadChar(const MessageChar &m)
		{
			if (m_pComponent->OnDeadChar)
				m_pComponent->OnDeadChar(m_pComponent, m);
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CTrayIconService::NotifyOnMouseMove(const MessagePosition &m)
		{
			if (m_pComponent->OnMouseMove)
				m_pComponent->OnMouseMove(m_pComponent, m);
		}

		void CTrayIconService::NotifyOnLeftMouseButtonDown(const MessagePosition &m)
		{
			if (m_pComponent->OnLeftMouseButtonDown)
				m_pComponent->OnLeftMouseButtonDown(m_pComponent, m);
		}

		void CTrayIconService::NotifyOnLeftMouseButtonUp(const MessagePosition &m)
		{
			if (m_pComponent->OnLeftMouseButtonUp)
				m_pComponent->OnLeftMouseButtonUp(m_pComponent, m);
		}

		void CTrayIconService::NotifyOnLeftMouseButtonDoubleClick(const MessagePosition &m)
		{
			if (m_pComponent->OnLeftMouseButtonDoubleClick)
				m_pComponent->OnLeftMouseButtonDoubleClick(m_pComponent, m);
		}

		void CTrayIconService::NotifyOnRightMouseButtonDown(const MessagePosition &m)
		{
			if (m_pComponent->OnRightMouseButtonDown)
				m_pComponent->OnRightMouseButtonDown(m_pComponent, m);
		}

		void CTrayIconService::NotifyOnRightMouseButtonUp(const MessagePosition &m)
		{
			if (m_pComponent->OnRightMouseButtonUp)
				m_pComponent->OnRightMouseButtonUp(m_pComponent, m);
		}

		void CTrayIconService::NotifyOnRightMouseButtonDoubleClick(const MessagePosition &m)
		{
			if (m_pComponent->OnRightMouseButtonDoubleClick)
				m_pComponent->OnRightMouseButtonDoubleClick(m_pComponent, m);
		}

		void CTrayIconService::NotifyOnMiddleMouseButtonDown(const MessagePosition &m)
		{
			if (m_pComponent->OnMiddleMouseButtonDown)
				m_pComponent->OnMiddleMouseButtonDown(m_pComponent, m);
		}

		void CTrayIconService::NotifyOnMiddleMouseButtonUp(const MessagePosition &m)
		{
			if (m_pComponent->OnMiddleMouseButtonUp)
				m_pComponent->OnMiddleMouseButtonUp(m_pComponent, m);
		}

		void CTrayIconService::NotifyOnMiddleMouseButtonDoubleClick(const MessagePosition &m)
		{
			if (m_pComponent->OnMiddleMouseButtonDoubleClick)
				m_pComponent->OnMiddleMouseButtonDoubleClick(m_pComponent, m);
		}
	#pragma endregion

	#pragma region Notification notifications
		void CTrayIconService::NotifyOnNotificationShow()
		{
			if (m_pComponent->OnNotificationShow)
				m_pComponent->OnNotificationShow(m_pComponent);
		}

		void CTrayIconService::NotifyOnNotificationHide()
		{
			if (m_pComponent->OnNotificationHide)
				m_pComponent->OnNotificationHide(m_pComponent);
		}

		void CTrayIconService::NotifyOnNotificationTimeout()
		{
			if (m_pComponent->OnNotificationTimeout)
				m_pComponent->OnNotificationTimeout(m_pComponent);
		}

		void CTrayIconService::NotifyOnNotificationClick()
		{
			if (m_pComponent->OnNotificationClick)
				m_pComponent->OnNotificationClick(m_pComponent);
		}
	#pragma endregion

	#pragma region Popup notifications
		void CTrayIconService::NotifyOnPopupOpen()
		{
			if (m_pComponent->OnPopupOpen)
				m_pComponent->OnPopupOpen(m_pComponent);
		}

		void CTrayIconService::NotifyOnPopupClose()
		{
			if (m_pComponent->OnPopupClose)
				m_pComponent->OnPopupClose(m_pComponent);
		}
	#pragma endregion
	}
}