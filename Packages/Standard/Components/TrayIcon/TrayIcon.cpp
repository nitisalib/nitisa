// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#include <Windows.h>
#include <shellapi.h>
#else
struct _NOTIFYICONDATAW
{

};
#endif

namespace nitisa
{
	namespace standard
	{
	#ifdef _WIN32
		DWORD NotificationIconTypeToDWORD(const CTrayIcon::NotificationIconType value)
		{
			switch (value)
			{
			case CTrayIcon::NotificationIconType::Info: return NIIF_INFO;
			case CTrayIcon::NotificationIconType::Warning: return NIIF_WARNING;
			case CTrayIcon::NotificationIconType::Error: return NIIF_ERROR;
			case CTrayIcon::NotificationIconType::Custom: return NIIF_USER;
			default: return NIIF_NONE;
			}
		}

		HICON BitmapToIcon(Image &bmp)
		{
			if (bmp.isEmpty())
				return 0;
			unsigned char *colorBits{ new unsigned char[bmp.Width * bmp.Height * 4] };
			unsigned char *maskBits{ new unsigned char[bmp.Width * bmp.Height * 4] };
			for (int y = 0; y < bmp.Height; y++)
				for (int x = 0; x < bmp.Width; x++)
				{
					if (bmp[x][y].A == 0)
					{
						colorBits[(y * bmp.Width + x) * 4 + 0] = 0;
						colorBits[(y * bmp.Width + x) * 4 + 1] = 0;
						colorBits[(y * bmp.Width + x) * 4 + 2] = 0;
						colorBits[(y * bmp.Width + x) * 4 + 3] = 0;
						maskBits[(y * bmp.Width + x) * 4 + 0] = 255;
						maskBits[(y * bmp.Width + x) * 4 + 1] = 255;
						maskBits[(y * bmp.Width + x) * 4 + 2] = 255;
						maskBits[(y * bmp.Width + x) * 4 + 3] = 255;
					}
					else
					{
						colorBits[(y * bmp.Width + x) * 4 + 0] = bmp[x][y].B;
						colorBits[(y * bmp.Width + x) * 4 + 1] = bmp[x][y].G;
						colorBits[(y * bmp.Width + x) * 4 + 2] = bmp[x][y].R;
						colorBits[(y * bmp.Width + x) * 4 + 3] = 255;
						maskBits[(y * bmp.Width + x) * 4 + 0] = 0;
						maskBits[(y * bmp.Width + x) * 4 + 1] = 0;
						maskBits[(y * bmp.Width + x) * 4 + 2] = 0;
						maskBits[(y * bmp.Width + x) * 4 + 3] = 0;
					}
				}
			HICON result{ 0 };
			HBITMAP hBitmapColor{ CreateBitmap(bmp.Width, bmp.Height, 1, 32, colorBits) };
			if (hBitmapColor)
			{
				HBITMAP hBitmapMask{ CreateBitmap(bmp.Width, bmp.Height, 1, 32, maskBits) };
				if (hBitmapMask)
				{
					ICONINFO i{ TRUE, 0, 0, hBitmapMask, hBitmapColor };
					result = CreateIconIndirect(&i);
					DeleteObject(hBitmapMask);
				}
				DeleteObject(hBitmapColor);
			}
			delete[] maskBits;
			delete[] colorBits;
			return result;
		}
	#endif

	#pragma region Constructor & destructor
		CTrayIcon::CTrayIcon():
			CComponent(L"TrayIcon"),
			m_eNotificationIconType{ NotificationIconType::None },
			m_bPlaySound{ true },
			m_bRespectQuietTime{ true },
			m_pService{ new CTrayIconService(this) },
			m_cListener{ this },
			m_bIsIconShown{ false },
			m_pData{ new _NOTIFYICONDATAW }
		{
			OnKeyDown = nullptr;
			OnKeyUp = nullptr;
			OnChar = nullptr;
			OnDeadChar = nullptr;
			OnMouseMove = nullptr;
			OnLeftMouseButtonDown = nullptr;
			OnLeftMouseButtonUp = nullptr;
			OnLeftMouseButtonDoubleClick = nullptr;
			OnRightMouseButtonDown = nullptr;
			OnRightMouseButtonUp = nullptr;
			OnRightMouseButtonDoubleClick = nullptr;
			OnMiddleMouseButtonDown = nullptr;
			OnMiddleMouseButtonUp = nullptr;
			OnMiddleMouseButtonDoubleClick = nullptr;
			OnNotificationShow = nullptr;
			OnNotificationHide = nullptr;
			OnNotificationTimeout = nullptr;
			OnNotificationClick = nullptr;
			OnPopupOpen = nullptr;
			OnPopupClose = nullptr;

			setService(m_pService, true);
		#ifdef _WIN32
			m_pData->cbSize = sizeof(NOTIFYICONDATA);
			m_pData->uTimeout = 5000;
			m_pData->uVersion = NOTIFYICON_VERSION_4;
			m_pData->hIcon = 0;
			m_pData->hBalloonIcon = 0;
		#endif
		}

		CTrayIcon::CTrayIcon(IForm *parent) :CTrayIcon()
		{
			setForm(parent);
		}

		CTrayIcon::~CTrayIcon()
		{
			delete m_pData;
		}
	#pragma endregion

	#pragma region Interface getters
		String CTrayIcon::getTip()
		{
			return m_sTip;
		}

		Image *CTrayIcon::getIcon()
		{
			return &m_cIcon;
		}

		String CTrayIcon::getTitle()
		{
			return m_sTitle;
		}

		String CTrayIcon::getMessage()
		{
			return m_sMessage;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CTrayIcon::setTip(const String &value)
		{
			if (value != m_sTip)
			{
				m_sTip = value;
				AddUpdateRemoveIcon();
				return true;
			}
			return false;
		}

		bool CTrayIcon::setTitle(const String &value)
		{
			if (value != m_sTitle)
			{
				m_sTitle = value;
				return true;
			}
			return false;
		}

		bool CTrayIcon::setMessage(const String &value)
		{
			if (value != m_sMessage)
			{
				m_sMessage = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface methods
		bool CTrayIcon::ShowNotification()
		{
		#ifdef _WIN32
			if (m_bIsIconShown)
			{
				m_pData->uFlags = NIF_INFO;
				memcpy(&m_pData->szInfo[0], m_sMessage.data(), sizeof(wchar_t) * ntl::Min<int>(200, (int)m_sMessage.length()));
				m_pData->szInfo[ntl::Min<int>(200, (int)m_sMessage.length())] = 0;
				memcpy(&m_pData->szInfoTitle[0], m_sTitle.data(), sizeof(wchar_t) * ntl::Min<int>(48, (int)m_sTitle.length()));
				m_pData->szInfoTitle[ntl::Min<int>(48, (int)m_sTitle.length())] = 0;
				m_pData->dwInfoFlags = NotificationIconTypeToDWORD(m_eNotificationIconType);
				if (!m_bPlaySound)
					m_pData->dwInfoFlags |= NIIF_NOSOUND;
				if (m_bRespectQuietTime)
					m_pData->dwInfoFlags |= NIIF_RESPECT_QUIET_TIME;
				if (m_eNotificationIconType == NotificationIconType::Custom)
				{
					m_pData->dwInfoFlags |= NIIF_LARGE_ICON;
					if (m_pData->hBalloonIcon)
						DestroyIcon(m_pData->hBalloonIcon);
					m_pData->hBalloonIcon = BitmapToIcon(m_cNotificationIcon);
					m_pData->uFlags |= NIF_ICON;
				}
				if (Shell_NotifyIcon(NIM_MODIFY, m_pData))
					return true;
			}
		#endif
			return false;
		}

		bool CTrayIcon::HideNotification()
		{
		#ifdef _WIN32
			if (m_bIsIconShown)
			{
				m_pData->uFlags = NIF_INFO;
				m_pData->szInfo[0] = 0;
				if (Shell_NotifyIcon(NIM_MODIFY, m_pData))
					return true;
			}
		#endif
			return false;
		}

		void CTrayIcon::Update()
		{
			AddUpdateRemoveIcon();
		}
	#pragma endregion

	#pragma region Getters
		CTrayIcon::NotificationIconType CTrayIcon::getNotificationIconType() const
		{
			return m_eNotificationIconType;
		}

		bool CTrayIcon::isPlaySound() const
		{
			return m_bPlaySound;
		}

		bool CTrayIcon::isRespectQuietTime() const
		{
			return m_bRespectQuietTime;
		}

		Image *CTrayIcon::getNotificationIcon()
		{
			return &m_cNotificationIcon;
		}
	#pragma endregion

	#pragma region Setters
		bool CTrayIcon::setNotificationIconType(const NotificationIconType value)
		{
			if (value != m_eNotificationIconType)
			{
				m_eNotificationIconType = value;
				return true;
			}
			return false;
		}

		bool CTrayIcon::setPlaySound(const bool value)
		{
			if (value != m_bPlaySound)
			{
				m_bPlaySound = value;
				return true;
			}
			return false;
		}

		bool CTrayIcon::setRespectQuietTime(const bool value)
		{
			if (value != m_bRespectQuietTime)
			{
				m_bRespectQuietTime = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CTrayIcon::AddUpdateRemoveIcon()
		{
			m_cIcon.isEmpty() ? RemoveIcon() : (m_bIsIconShown ? UpdateIcon() : AddIcon());
		}

		void CTrayIcon::AddIcon()
		{
		#ifdef _WIN32
			if (getForm() && !Application->Editor && getForm()->QueryService()->getWindow() && !m_cIcon.isEmpty())
			{
				HWND wnd{ *reinterpret_cast<const HWND*>(&getForm()->QueryService()->getWindow()->Handle) };
				if (wnd)
				{
					m_pData->hWnd = wnd;
					m_pData->uID = getForm()->QueryService()->getWindow()->GenerateID();
					m_pData->uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
					m_pData->uCallbackMessage = WM_USER + m_pData->uID;
					m_pData->hIcon = BitmapToIcon(m_cIcon);
					memcpy(&m_pData->szTip[0], m_sTip.data(), sizeof(wchar_t) * ntl::Min<int>(127, (int)m_sTip.length()));
					m_pData->szTip[ntl::Min<int>(127, (int)m_sTip.length())] = 0;
					if (Shell_NotifyIcon(NIM_ADD, m_pData))
						m_bIsIconShown = true;
				}
			}
		#endif
		}

		void CTrayIcon::UpdateIcon()
		{
		#ifdef _WIN32
			if (m_bIsIconShown)
			{
				m_pData->uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
				if (m_pData->hIcon)
					DestroyIcon(m_pData->hIcon);
				m_pData->hIcon = BitmapToIcon(m_cIcon);
				memcpy(&m_pData->szTip[0], m_sTip.data(), sizeof(wchar_t) * ntl::Min<int>(127, (int)m_sTip.length()));
				m_pData->szTip[ntl::Min<int>(127, (int)m_sTip.length())] = 0;
				Shell_NotifyIcon(NIM_MODIFY, m_pData);
			}
		#endif
		}

		void CTrayIcon::RemoveIcon()
		{
		#ifdef _WIN32
			if (m_bIsIconShown)
			{
				m_pData->uFlags = NIF_MESSAGE;
				Shell_NotifyIcon(NIM_DELETE, m_pData);
				m_bIsIconShown = false;
			}
		#endif
		}
	#pragma endregion
	}
}