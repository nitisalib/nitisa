// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IComponent.h"

namespace nitisa
{
	class Image;

	namespace standard
	{
		class ITrayIconService :public virtual IComponentService
		{
		protected:
			ITrayIconService() = default;
			~ITrayIconService() = default;
			ITrayIconService(const ITrayIconService &other) = delete;
			ITrayIconService(ITrayIconService &&other) = delete;
			ITrayIconService &operator=(const ITrayIconService &other) = delete;
			ITrayIconService &operator=(ITrayIconService &&other) = delete;
		public:
			// Keyboard input notifications
			virtual void NotifyOnKeyDown(const MessageKey &m) = 0; // Called when tray icon is focused and key is down
			virtual void NotifyOnKeyUp(const MessageKey &m) = 0; // Called when tray icon is focused and key is up
			virtual void NotifyOnChar(const MessageChar &m) = 0; // Called when tray icon is focused and char translated
			virtual void NotifyOnDeadChar(const MessageChar &m) = 0; // Called when tray icon is focused and dead char translated

			// Mouse input notifications
			virtual void NotifyOnMouseMove(const MessagePosition &m) = 0; // Called when tray icon is under mouse pointer and mouse moves
			virtual void NotifyOnLeftMouseButtonDown(const MessagePosition &m) = 0; // Called when tray icon is under mouse pointer and left mouse button down
			virtual void NotifyOnLeftMouseButtonUp(const MessagePosition &m) = 0; // Called when tray icon is under mouse pointer and left mouse button up
			virtual void NotifyOnLeftMouseButtonDoubleClick(const MessagePosition &m) = 0; // Called when tray icon is under mouse pointer and left mouse button double clicked
			virtual void NotifyOnRightMouseButtonDown(const MessagePosition &m) = 0; // Called when tray icon is under mouse pointer and right mouse button down
			virtual void NotifyOnRightMouseButtonUp(const MessagePosition &m) = 0; // Called when tray icon is under mouse pointer and right mouse button up
			virtual void NotifyOnRightMouseButtonDoubleClick(const MessagePosition &m) = 0; // Called when tray icon is under mouse pointer and right mouse mutton double clicked
			virtual void NotifyOnMiddleMouseButtonDown(const MessagePosition &m) = 0; // Called when tray icon is under mouse pointer and middle mouse button down
			virtual void NotifyOnMiddleMouseButtonUp(const MessagePosition &m) = 0; // Called when tray icon is under mouse pointer and middle mouse button up
			virtual void NotifyOnMiddleMouseButtonDoubleClick(const MessagePosition &m) = 0; // Called when tray icon is under mouse pointer and middle mouse button double clicked

			// Notification notifications
			virtual void NotifyOnNotificationShow() = 0; // Called when notification is shown
			virtual void NotifyOnNotificationHide() = 0; // Called when notification is hidden(programmatically)
			virtual void NotifyOnNotificationTimeout() = 0; // Called when notification is hidden due to timeout
			virtual void NotifyOnNotificationClick() = 0; // Called when user clicks on notification

			// Popup notifications
			virtual void NotifyOnPopupOpen() = 0; // Called when popup opens
			virtual void NotifyOnPopupClose() = 0; // Called when popup closes
		};

		class ITrayIcon :public virtual IComponent
		{
		protected:
			ITrayIcon() = default;
			~ITrayIcon() = default;
			ITrayIcon(const ITrayIcon &other) = delete;
			ITrayIcon(ITrayIcon &&other) = delete;
			ITrayIcon &operator=(const ITrayIcon &other) = delete;
			ITrayIcon &operator=(ITrayIcon &&other) = delete;
		public:
			// Keyboard input events
			void(*OnKeyDown)(ITrayIcon *sender, const MessageKey &m); // Event called when tray icon is focused and key is down
			void(*OnKeyUp)(ITrayIcon *sender, const MessageKey &m); // Event called when tray icon is focused and key is up
			void(*OnChar)(ITrayIcon *sender, const MessageChar &m); // Event called when tray icon is focused and char translated
			void(*OnDeadChar)(ITrayIcon *sender, const MessageChar &m); // Event called when tray icon is focused and dead char translated

			// Mouse input events
			void(*OnMouseMove)(ITrayIcon *sender, const MessagePosition &m); // Event called when tray icon is under mouse pointer and mouse moves
			void(*OnLeftMouseButtonDown)(ITrayIcon *sender, const MessagePosition &m); // Event called when tray icon is under mouse pointer and left mouse button down
			void(*OnLeftMouseButtonUp)(ITrayIcon *sender, const MessagePosition &m); // Event called when tray icon is under mouse pointer and left mouse button up
			void(*OnLeftMouseButtonDoubleClick)(ITrayIcon *sender, const MessagePosition &m); // Event called when tray icon is under mouse pointer and left mouse button double clicked
			void(*OnRightMouseButtonDown)(ITrayIcon *sender, const MessagePosition &m); // Event called when tray icon is under mouse pointer and right mouse button down
			void(*OnRightMouseButtonUp)(ITrayIcon *sender, const MessagePosition &m); // Event called when tray icon is under mouse pointer and right mouse button up
			void(*OnRightMouseButtonDoubleClick)(ITrayIcon *sender, const MessagePosition &m); // Event called when tray icon is under mouse pointer and right mouse mutton double clicked
			void(*OnMiddleMouseButtonDown)(ITrayIcon *sender, const MessagePosition &m); // Event called when tray icon is under mouse pointer and middle mouse button down
			void(*OnMiddleMouseButtonUp)(ITrayIcon *sender, const MessagePosition &m); // Event called when tray icon is under mouse pointer and middle mouse button up
			void(*OnMiddleMouseButtonDoubleClick)(ITrayIcon *sender, const MessagePosition &m); // Event called when tray icon is under mouse pointer and middle mouse button double clicked

			// Notification events
			void(*OnNotificationShow)(ITrayIcon *sender); // Event called when notification is shown
			void(*OnNotificationHide)(ITrayIcon *sender); // Event called when notification is hidden(programmatically)
			void(*OnNotificationTimeout)(ITrayIcon *sender); // Event called when notification is hidden due to timeout
			void(*OnNotificationClick)(ITrayIcon *sender); // Event called when user clicks on notification

			// Popup events
			void(*OnPopupOpen)(ITrayIcon *sender); // Event called when popup opens
			void(*OnPopupClose)(ITrayIcon *sender); // Event called when popup closes

			virtual String getTip() = 0; // Return tip
			virtual Image *getIcon() = 0; // Return icon
			virtual String getTitle() = 0; // Return notification title
			virtual String getMessage() = 0; // Return notification message

			virtual bool setTip(const String &value) = 0; // Set tip
			virtual bool setTitle(const String &value) = 0; // Set notification title
			virtual bool setMessage(const String &value) = 0; // Set notification message

			virtual bool ShowNotification() = 0; // Show notification. Allowed only when icon is added into tray
			virtual bool HideNotification() = 0; // Hide shown notification
			virtual void Update() = 0; // Should be called after updating icon
		};
	}
}