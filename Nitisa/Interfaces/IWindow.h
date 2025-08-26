// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "../Core/CreateParams.h"
#include "../Core/CursorType.h"
#include "../Core/ModalResult.h"
#include "../Core/Strings.h"
#include "../Core/WindowPosition.h"
#include "../Core/WindowState.h"
#include "../Math/Point.h"
#include "../Math/Rect.h"

namespace nitisa
{
	class ITimerListener;
	class IWindowListener;
	class IWindowService;

	// In case of using window with a form, do not change events and try to avoid using any methods(they are for internal usage by form or if window is not associated with form) except probably
	// for getters(but use form's methods instead). Release() should not delete self, it should destroy system window if exists. Delete window class instance should be handled by application object.
	class IWindow
	{
	protected:
		IWindow() = default;
		~IWindow() = default;
		IWindow(const IWindow &other) = delete;
		IWindow(IWindow &&other) = delete;
		IWindow &operator=(const IWindow &other) = delete;
		IWindow &operator=(IWindow &&other) = delete;
	public:
		enum class ProgressType // Describe type of progress bar shown in task bar over the window
		{
			None, // The progress bar is not visible
			Indeterminate, // The progress bar shows indeterminate progress by running in marquee mode
			Normal, // The normal state (green in the default theme)
			Paused, // The paused state (yellow in the default theme)
			Error // The error state (red in the default theme)
		};
	protected:
		PlatformHandle m_hHandle;
		IWindowListener *m_pListener;
	public:
		PlatformHandle const &Handle{ m_hHandle };
		IWindowListener* const &Listener{ m_pListener };

		virtual bool isCreated() = 0; // Whether a real system window was created or not
		virtual bool isVisible() = 0; // Whether window is visible
		virtual bool isEnabled() = 0; // Whether window is enabled
		virtual bool isAcceptDragAndDrop() = 0; // Whether window accepts drag and drop
		virtual bool isAcceptDropFiles() = 0; // Whether window accepts files dropping
		virtual String getCaption() = 0; // Return caption
		virtual Rect getRect() = 0; // Return rectangle in screen coordinates
		virtual Point getSize() = 0; // Return size
		virtual Point getPosition() = 0; // Return position in screen coordinates
		virtual int getLeft() = 0; // Return left position on screen
		virtual int getTop() = 0; // Return top position on screen
		virtual int getWidth() = 0; // Return width
		virtual int getHeight() = 0; // Return height
		virtual Rect getClientRect() = 0; // Return client area rectangle
		virtual Point getClientSize() = 0; // Return client area size
		virtual int getClientWidth() = 0; // Return client area width
		virtual int getClientHeight() = 0; // Return client area height
		virtual WindowState getState() = 0; // Return state
		virtual CreateParams getCreateParams() = 0; // Return creation parameters
		virtual IWindow *getParent() = 0; // Return parent window
		virtual bool hasProgressBar() = 0; // Return whether task bar progress bar is available
		
		virtual bool setVisible(const bool value) = 0; // Show/hide
		virtual bool setEnabled(const bool value) = 0; // Enable/disable
		virtual bool setAcceptDrawAndDrop(const bool value) = 0; // Set whether accepts drag and drop
		virtual bool setAcceptDropFiles(const bool value) = 0; // Set whether accepts files dropping
		virtual bool setCaption(const String &value) = 0; // Set caption
		virtual bool setRect(const Rect &value) = 0; // Set rectangle in screen coordinates
		virtual bool setSize(const Point &value) = 0; // Set size
		virtual bool setPosition(const Point &value) = 0; // Set position on screen
		virtual bool setLeft(const int value) = 0; // Set left position on screen
		virtual bool setTop(const int value) = 0; // Set top position on screen
		virtual bool setWidth(const int value) = 0; // Set width
		virtual bool setHeight(const int value) = 0; // Set height
		virtual bool setClientSize(const Point &value) = 0; // Set client area size
		virtual bool setCursor(const CursorType value) = 0; // Set cursor
		virtual bool setState(const WindowState value) = 0; // Set state
		virtual bool setCreateParams(const CreateParams &value) = 0; // Set creation parameters. Has effect only before creation a real system window
		virtual bool setParent(IWindow *value) = 0; // Set parent window. Has effect only before creation a real system window
		virtual bool setModalResult(const ModalResult value) = 0; // Set modal result and close window. Only used when window was shown by ShowModal methods
		virtual bool setWindowPosition(const WindowPosition value) = 0; // Set window position relative to screen or main window
		virtual bool setProgressType(const ProgressType value) = 0; // Set task bar progress bar type if possible
		virtual bool setProgressValue(const float value) = 0; // Set task bar progress bar value if possible. Should be in range 0..1

		virtual bool Show() = 0; // Show
		virtual ModalResult ShowModal() = 0; // Show as modal
		virtual bool Hide() = 0; // Hide
		virtual bool Close() = 0; // Close window(send close message)
		virtual bool Create() = 0; // Create real window
		virtual bool Create(IWindow *parent) = 0; // Create real window as child of specified one
		virtual bool Create(const CreateParams &params) = 0; // Create real window with specified parameters
		virtual bool Create(const CreateParams &params, IWindow *parent) = 0; // Create real window with specified parameters and parent window
		virtual PlatformHandle CreateTimer(ITimerListener *listener, const float interval) = 0; // Create timer. Interval is in seconds. Return unique identifier
		virtual bool DeleteTimer(const PlatformHandle id) = 0; // Delete timer by identifier
		virtual void DeleteTimers() = 0; // Delete all timers
		virtual bool ResetTimer(const PlatformHandle id, const float interval) = 0; // Change timer interval and reset it
		virtual bool CaptureMouse() = 0; // Capture mouse input
		virtual void ReleaseMouseCapture() = 0; // Cancel capturing mouse input
		virtual bool Maximize() = 0; // Maximize
		virtual bool Minimize() = 0; // Minimize
		virtual bool Restore() = 0; // Restore
		virtual bool CopyStringToClipboard(const String &str) = 0; // Copy string to clipboard
		virtual bool CopyStringFromClipboard() = 0; // Copy string from clipboard. If successful IWindowListener::OnPasteString() will be called immediately or later with the string to be inserted
		virtual Rect ScreenToClient(const Rect &rect) = 0; // Convert from screen to client area coordinates
		virtual Point ScreenToClient(const Point &pos) = 0; // Convert from screen to client area coordinates
		virtual Rect ClientToScreen(const Rect &rect) = 0; // Convert from client area to screen coordinates
		virtual Point ClientToScreen(const Point &pos) = 0; // Convert from client area to screen coordinates
		virtual void Release() = 0; // Destroy instance. Usually you don't need to call this method
		virtual IWindow *CreateInstance() = 0; // Create same class instance(without creating real window)
		virtual IWindowService *QueryService() = 0; // Return service
		virtual int GenerateID() = 0; // Generate new unique ID. Generation starts from 1 and increase value each call of this method. This ID is unique for given window only
	};
}