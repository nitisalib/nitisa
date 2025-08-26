// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#include "Platform/Windows/Window.h"
#include <Windows.h>
#include <windowsx.h>
#include <shellapi.h>
#endif

namespace nitisa
{
	namespace standard
	{
		CTrayIcon::CListener::CListener(CTrayIcon *component)
		#ifdef _WIN32
			: m_pComponent{ component }
		#endif
		{

		}

		bool CTrayIcon::CListener::OnMessage(const unsigned int uMsg, const unsigned long long wParam, const long long lParam, long long &result)
		{
		#ifdef _WIN32
			result = 0;
			if (uMsg == m_pComponent->m_pData->uCallbackMessage)
			{
				switch (LOWORD((LPARAM)lParam))
				{
				case NIN_BALLOONSHOW:
					m_pComponent->m_pService->NotifyOnNotificationShow();
					return true;
				case NIN_BALLOONHIDE:
					m_pComponent->m_pService->NotifyOnNotificationHide();
					return true;
				case NIN_BALLOONTIMEOUT:
					m_pComponent->m_pService->NotifyOnNotificationTimeout();
					return true;
				case NIN_BALLOONUSERCLICK:
					m_pComponent->m_pService->NotifyOnNotificationClick();
					return true;
				case NIN_POPUPOPEN:
					m_pComponent->m_pService->NotifyOnPopupOpen();
					return true;
				case NIN_POPUPCLOSE:
					m_pComponent->m_pService->NotifyOnPopupClose();
					return true;

				case WM_KEYDOWN:
					m_pComponent->m_pService->NotifyOnKeyDown(MessageKey{ platform::windows::CWindow::VirtualToKey((int)wParam) });
					return true;
				case WM_KEYUP:
					m_pComponent->m_pService->NotifyOnKeyUp(MessageKey{ platform::windows::CWindow::VirtualToKey((int)wParam) });
					return true;
				case WM_CHAR:
					m_pComponent->m_pService->NotifyOnChar(MessageChar{ (wchar_t)wParam });
					return true;
				case WM_DEADCHAR:
					m_pComponent->m_pService->NotifyOnDeadChar(MessageChar{ (wchar_t)wParam });
					return true;
				case WM_SYSKEYDOWN:
					m_pComponent->m_pService->NotifyOnKeyDown(MessageKey{ platform::windows::CWindow::VirtualToKey((int)wParam) });
					return true;
				case WM_SYSKEYUP:
					m_pComponent->m_pService->NotifyOnKeyUp(MessageKey{ platform::windows::CWindow::VirtualToKey((int)wParam) });
					return true;
				case WM_SYSCHAR:
					m_pComponent->m_pService->NotifyOnChar(MessageChar{ (wchar_t)wParam });
					return true;
				case WM_SYSDEADCHAR:
					m_pComponent->m_pService->NotifyOnDeadChar(MessageChar{ (wchar_t)wParam });
					return true;
				case WM_MOUSEMOVE:
					m_pComponent->m_pService->NotifyOnMouseMove(MessagePosition{ PointF{ (float)GET_X_LPARAM(wParam), (float)GET_Y_LPARAM(wParam) } });
					return true;
				case WM_LBUTTONDOWN:
					m_pComponent->m_pService->NotifyOnLeftMouseButtonDown(MessagePosition{ PointF{ (float)GET_X_LPARAM(wParam), (float)GET_Y_LPARAM(wParam) } });
					return true;
				case WM_LBUTTONUP:
					m_pComponent->m_pService->NotifyOnLeftMouseButtonUp(MessagePosition{ PointF{ (float)GET_X_LPARAM(wParam), (float)GET_Y_LPARAM(wParam) } });
					return true;
				case WM_LBUTTONDBLCLK:
					m_pComponent->m_pService->NotifyOnLeftMouseButtonDoubleClick(MessagePosition{ PointF{ (float)GET_X_LPARAM(wParam), (float)GET_Y_LPARAM(wParam) } });
					return true;

				case WM_MBUTTONDOWN:
					m_pComponent->m_pService->NotifyOnMiddleMouseButtonDown(MessagePosition{ PointF{ (float)GET_X_LPARAM(wParam), (float)GET_Y_LPARAM(wParam) } });
					return true;
				case WM_MBUTTONUP:
					m_pComponent->m_pService->NotifyOnMiddleMouseButtonUp(MessagePosition{ PointF{ (float)GET_X_LPARAM(wParam), (float)GET_Y_LPARAM(wParam) } });
					return true;
				case WM_MBUTTONDBLCLK:
					m_pComponent->m_pService->NotifyOnMiddleMouseButtonDoubleClick(MessagePosition{ PointF{ (float)GET_X_LPARAM(wParam), (float)GET_Y_LPARAM(wParam) } });
					return true;

				case WM_RBUTTONDOWN:
					m_pComponent->m_pService->NotifyOnRightMouseButtonDown(MessagePosition{ PointF{ (float)GET_X_LPARAM(wParam), (float)GET_Y_LPARAM(wParam) } });
					return true;
				case WM_RBUTTONUP:
					m_pComponent->m_pService->NotifyOnRightMouseButtonUp(MessagePosition{ PointF{ (float)GET_X_LPARAM(wParam), (float)GET_Y_LPARAM(wParam) } });
					return true;
				case WM_RBUTTONDBLCLK:
					m_pComponent->m_pService->NotifyOnRightMouseButtonDoubleClick(MessagePosition{ PointF{ (float)GET_X_LPARAM(wParam), (float)GET_Y_LPARAM(wParam) } });
					return true;
				}
			}
		#endif
			return false;
		}
	}
}