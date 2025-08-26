// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Component.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/Image.h"
#include "Nitisa/Interfaces/IWindowListenerOnMessage.h"
#include "../ITrayIcon.h"

struct _NOTIFYICONDATAW;

namespace nitisa
{
	class IForm;

	namespace standard
	{
		class CTrayIconService;

		class CTrayIcon : public virtual ITrayIcon, public CComponent
		{
			friend CTrayIconService;
		public:
			enum class NotificationIconType // Notification icon types
			{
				None, // Use the same icon as is set as a tray icon
				Info, // Use system information icon
				Warning, // Use system warning icon
				Error, // Use system error icon
				Custom // Use icon set in NotificationIcon property
			};
		private:
			class CListener :public virtual IWindowListenerOnMessage
			{
			private:
			#ifdef _WIN32
				CTrayIcon *m_pComponent;
			#endif
			public:
				bool OnMessage(const unsigned int uMsg, const unsigned long long wParam, const long long lParam, long long &result) override;

				CListener(CTrayIcon *component);
			};
		private:
			String m_sTip;
			Image m_cIcon;
			String m_sTitle;
			String m_sMessage;
			NotificationIconType m_eNotificationIconType;
			bool m_bPlaySound;
			bool m_bRespectQuietTime;
			Image m_cNotificationIcon;
			
			CTrayIconService *m_pService;
			CListener m_cListener;
			bool m_bIsIconShown;
			_NOTIFYICONDATAW *m_pData;

			void AddUpdateRemoveIcon();
			void AddIcon();
			void UpdateIcon();
			void RemoveIcon();
		public:
			String getTip() override;
			Image *getIcon() override;
			String getTitle() override;
			String getMessage() override;

			bool setTip(const String &value) override;
			bool setTitle(const String &value) override;
			bool setMessage(const String &value) override;

			bool ShowNotification() override;
			bool HideNotification() override;
			void Update() override;

			CTrayIcon();
			CTrayIcon(IForm *parent);
			~CTrayIcon() override;

			NotificationIconType getNotificationIconType() const; // Return notification icon type
			bool isPlaySound() const; // Return whether standard sound should be played when showing notification
			bool isRespectQuietTime() const; // Return whether quiet time should be taken in consideration when showing notification
			Image *getNotificationIcon(); // Return notification custom icon

			bool setNotificationIconType(const NotificationIconType value); // Set notification icon type
			bool setPlaySound(const bool value); // Set whether standard sound should be played when showing notification
			bool setRespectQuietTime(const bool value); // Set whether quiet time should be taken in consideration when showing notification
		};
	}
}