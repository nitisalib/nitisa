// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/CreateParams.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Core/Key.h"
#include "Nitisa/Core/ModalResult.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/WindowPosition.h"
#include "Nitisa/Core/WindowState.h"
#include "Nitisa/Interfaces/IWindow.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/Rect.h"

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	class ITimerListener;
	class IWindowListener;
	class IWindowService;

	namespace platform
	{
		namespace linux
		{
			class CApplication;
			class CWindowService;

			namespace opengl
			{
				class CBaseRenderer;
			}

			// In case of using with form the destruction should be done by form only!
			class CWindow :public virtual IWindow
			{
				friend CApplication;
				friend CWindowService;
				friend opengl::CBaseRenderer;
			private:
				CApplication *m_pApplication;
				IWindow *m_pParent;
				IWindow *m_pModalFor;
				IWindowService *m_pService;
				CreateParams m_sCreateParams;
				CursorType m_eCurrentCursor;
				ModalResult m_eModalResult;
				int m_iID;
				Rect m_sOldRect;
				bool m_bCursorSet;
				bool m_bModal;
				bool m_bEnabled;
				bool m_bVisible;
				PlatformHandle m_hParent;
				PlatformHandle m_hVisualInfo;
				PlatformHandle m_hColormap;

				Point CalculateCreatePosition(const Point &size);
				bool Create(const PlatformHandle parent);

				void ProcessKeyPress(const void *ev);
				void ProcessKeyRelease(const void *ev);
				void ProcessButtonPress(const void *ev);
				void ProcessButtonRelease(const void *ev);
				void ProcessMotion(const void *ev);
				void ProcessEnter(const void *ev);
				void ProcessLeave();
				void ProcessFocusIn();
				void ProcessFocusOut();
				void ProcessExpose(const void *ev);
				void ProcessConfigure(const void *ev);
				void ProcessDestroy();
				void ProcessMap();
				void ProcessUnmap();
				bool ProcessClientMessage(const void *ev);
				void ProcessPropertyNotify(const void *ev);
				void Constraints(const Rect &constraints);
				bool hasAtom(PlatformHandle name, PlatformHandle needed, bool &succeeded);
				bool isMaximized();
				bool isMinimized();
				bool ActivateWindow();
				bool Modal(IWindow *modal_for);
				bool Normal(IWindow *modal_for);
				bool DoClose();
				Key KeyCodeToKey(const PlatformHandle keycode);
			public:
				bool isCreated() override;
				bool isVisible() override;
				bool isEnabled() override;
				bool isAcceptDragAndDrop() override; // Return false. Not supported yet
				bool isAcceptDropFiles() override; // Return false. Not supported yet
				String getCaption() override;
				Rect getRect() override;
				Point getSize() override;
				Point getPosition() override;
				int getLeft() override;
				int getTop() override;
				int getWidth() override;
				int getHeight() override;
				Rect getClientRect() override;
				Point getClientSize() override;
				int getClientWidth() override;
				int getClientHeight() override;
				WindowState getState() override;
				CreateParams getCreateParams() override;
				IWindow *getParent() override;
				bool hasProgressBar() override; // Return false. Not supported yet

				bool setVisible(const bool value) override;
				bool setEnabled(const bool value) override;
				bool setAcceptDrawAndDrop(const bool value) override; // Return false. Not supported yet
				bool setAcceptDropFiles(const bool value) override; // Return false. Not supported yet
				bool setCaption(const String &value) override;
				bool setRect(const Rect &value) override;
				bool setSize(const Point &value) override;
				bool setPosition(const Point &value) override;
				bool setLeft(const int value) override;
				bool setTop(const int value) override;
				bool setWidth(const int value) override;
				bool setHeight(const int value) override;
				bool setClientSize(const Point &value) override;
				bool setCursor(const CursorType value) override;
				bool setState(const WindowState value) override;
				bool setCreateParams(const CreateParams &value) override;
				bool setParent(IWindow *value) override;
				bool setModalResult(const ModalResult value) override;
				bool setWindowPosition(const WindowPosition value) override;
				bool setProgressType(const ProgressType value) override; // Return false. Not supported yet
				bool setProgressValue(const float value) override; // Return false. Not supported yet

				bool Show() override;
				ModalResult ShowModal() override;
				bool Hide() override;
				bool Close() override;
				bool Create() override;
				bool Create(IWindow *parent) override;
				bool Create(const CreateParams &params) override;
				bool Create(const CreateParams &params, IWindow *parent) override;
				PlatformHandle CreateTimer(ITimerListener *listener, const float interval) override;
				bool DeleteTimer(const PlatformHandle id) override;
				void DeleteTimers() override;
				bool ResetTimer(const PlatformHandle id, const float interval) override;
				bool CaptureMouse() override;
				void ReleaseMouseCapture() override;
				bool Maximize() override;
				bool Minimize() override;
				bool Restore() override;
				bool CopyStringToClipboard(const String &str) override;
				bool CopyStringFromClipboard() override;
				Rect ScreenToClient(const Rect &rect) override;
				Point ScreenToClient(const Point &pos) override;
				Rect ClientToScreen(const Rect &rect) override;
				Point ClientToScreen(const Point &pos) override;
				void Release() override;
				IWindow *CreateInstance() override;
				IWindowService *QueryService() override;
				int GenerateID() override;

				CWindow();
				CWindow(void *parent);
				virtual ~CWindow();

				void WindowProc(void *ev); // Message processing method
				static Key VirtualToKey(const int value); // Convert from virtual key code to Key enumeration
				static int KeyToVirtual(const Key value); // Convert from Key enumeration to virtual key code
			};
		}
	}
}
#endif