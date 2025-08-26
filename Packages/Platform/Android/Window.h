// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "Nitisa/Core/CreateParams.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Core/ModalResult.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/WindowPosition.h"
#include "Nitisa/Core/WindowState.h"
#include "Nitisa/Interfaces/IWindow.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/Rect.h"

namespace nitisa
{
	class ITimerListener;
	class IWindowListener;
	class IWindowService;

	namespace platform
	{
		namespace android
		{
			class CApplication;
			class CWindowService;

			// All windows are actually work with one native activity. Only main form or first window in list(if main form isn't assigned) will receive notifications(except for OnCreate and OnDestroy)
			class CWindow :public virtual IWindow
			{
				friend CWindowService;
			private:
				IWindowListener * m_pListener;
				IWindowService *m_pService;
				CApplication *m_pApplication;
				CreateParams m_sCreateParams;
				bool m_bCreated;
				int m_iID;
			public:
				bool isCreated() override; // Always true
				bool isVisible() override; // Return true if app is in resumed state, otherwise return false
				bool isEnabled() override; // Return true if app is in resumed state, otherwise return false
				bool isAcceptDragAndDrop() override; // Not supported. Always false
				bool isAcceptDropFiles() override; // Not supported. Always false
				String getCaption() override; // Not supported. Always L""
				Rect getRect() override;
				Point getSize() override;
				Point getPosition() override; // Always {0, 0}
				int getLeft() override; // Always 0
				int getTop() override; // Always 0
				int getWidth() override;
				int getHeight() override;
				Rect getClientRect() override;
				Point getClientSize() override;
				int getClientWidth() override;
				int getClientHeight() override;
				WindowState getState() override; // Return wsNormal if app is in resumed state, otherwise return wsHidden
				CreateParams getCreateParams() override;
				IWindow *getParent() override; // Not supported. Always nullptr
				bool hasProgressBar() override; // Not supported. Always false

				bool setVisible(const bool value) override; // Not supported. Return false
				bool setEnabled(const bool value) override; // Not supported. Return false
				bool setAcceptDrawAndDrop(const bool value) override; // Not supported. Return false
				bool setAcceptDropFiles(const bool value) override; // Not supported. Return false
				bool setCaption(const String &value) override; // Not supported. Return false
				bool setRect(const Rect &value) override; // Not supported. Return false
				bool setSize(const Point &value) override; // Not supported. Return false
				bool setPosition(const Point &value) override; // Not supported. Return false
				bool setLeft(const int value) override; // Not supported. Return false
				bool setTop(const int value) override; // Not supported. Return false
				bool setWidth(const int value) override; // Not supported. Return false
				bool setHeight(const int value) override; // Not supported. Return false
				bool setClientSize(const Point &value) override; // Not supported. Return false
				bool setCursor(const CursorType value) override; // Not supported. Return false
				bool setState(const WindowState value) override; // Not supported. Return false
				bool setCreateParams(const CreateParams &value) override;
				bool setParent(IWindow *value) override; // Not supported. Return false
				bool setModalResult(const ModalResult value) override; // Not supported. Return false
				bool setWindowPosition(const WindowPosition value) override; // Not supported. Return false
				bool setProgressType(const ProgressType value) override; // Not supported. Return false
				bool setProgressValue(const float value) override; // Not supported. Return false

				bool Show() override; // Not supported. Return false
				ModalResult ShowModal() override; // Not supported. Return mrCancel
				bool Hide() override; // Not supported. Return false
				bool Create() override;
				bool Create(IWindow *parent) override; // Parameters are not supported. Do the same as Create() without arguments
				bool Create(const CreateParams &params) override; // Parameters are not supported. Do the same as Create() without arguments
				bool Create(const CreateParams &params, IWindow *parent) override; // Parameters are not supported. Do the same as Create() without arguments
				PlatformHandle CreateTimer(ITimerListener *listener, const float interval) override;
				bool DeleteTimer(const PlatformHandle id) override;
				void DeleteTimers() override;
				bool ResetTimer(const PlatformHandle id, const float interval) override;
				bool CaptureMouse() override; // Not supported. Always true
				void ReleaseMouseCapture() override; // Not supported. Do nothing
				bool Maximize() override; // Not supported. Return false
				bool Minimize() override; // Not supported. Return false
				bool Restore() override; // Not supported. Return false
				bool CopyStringToClipboard(const String &str) override; // Not supported. Return false
				bool CopyStringFromClipboard() override; // Not supported. Return false
				Rect ScreenToClient(const Rect &rect) override;
				Point ScreenToClient(const Point &pos) override;
				Rect ClientToScreen(const Rect &rect) override;
				Point ClientToScreen(const Point &pos) override;
				void Release() override;
				IWindow *CreateInstance() override;
				IWindowService *QueryService() override;
				bool Close() override; // Finish application. Always return true
				int GenerateID() override;

				CWindow();
				virtual ~CWindow();
			};
		}
	}
}
#endif