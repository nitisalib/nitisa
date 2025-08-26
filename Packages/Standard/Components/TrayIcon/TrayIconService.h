// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ComponentService.h"
#include "Nitisa/Core/Messages.h"
#include "../ITrayIcon.h"

namespace nitisa
{
	namespace standard
	{
		class CTrayIcon;

		class CTrayIconService :public virtual ITrayIconService, public CComponentService
		{
		private:
			CTrayIcon *m_pComponent;
		public:
			CTrayIconService(CTrayIcon *component);

			// State change notifications
			void NotifyOnAttach() override;
			void NotifyOnDetaching() override;
			void NotifyOnFreeResources() override;

			// Keyboard input notifications
			void NotifyOnKeyDown(const MessageKey &m) override;
			void NotifyOnKeyUp(const MessageKey &m) override;
			void NotifyOnChar(const MessageChar &m) override;
			void NotifyOnDeadChar(const MessageChar &m) override;

			// Mouse input notifications
			void NotifyOnMouseMove(const MessagePosition &m) override;
			void NotifyOnLeftMouseButtonDown(const MessagePosition &m) override;
			void NotifyOnLeftMouseButtonUp(const MessagePosition &m) override;
			void NotifyOnLeftMouseButtonDoubleClick(const MessagePosition &m) override;
			void NotifyOnRightMouseButtonDown(const MessagePosition &m) override;
			void NotifyOnRightMouseButtonUp(const MessagePosition &m) override;
			void NotifyOnRightMouseButtonDoubleClick(const MessagePosition &m) override;
			void NotifyOnMiddleMouseButtonDown(const MessagePosition &m) override;
			void NotifyOnMiddleMouseButtonUp(const MessagePosition &m) override;
			void NotifyOnMiddleMouseButtonDoubleClick(const MessagePosition &m) override;

			// Notification notifications
			void NotifyOnNotificationShow() override;
			void NotifyOnNotificationHide() override;
			void NotifyOnNotificationTimeout() override;
			void NotifyOnNotificationClick() override;

			// Popup notifications
			void NotifyOnPopupOpen() override;
			void NotifyOnPopupClose() override;
		};
	}
}