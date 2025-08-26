// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef _WIN32
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
#include <vector>

#pragma warning(disable: 4250)

namespace nitisa
{
	class ITimerListener;
	class IWindowListener;
	class IWindowService;

	namespace platform
	{
		namespace windows
		{
			namespace opengl31d
			{
				class CRenderer;
			}

			namespace opengl31r
			{
				class CRenderer;
			}

			namespace opengl45d
			{
				class CRenderer;
			}

			namespace opengl45r
			{
				class CRenderer;
			}

			class CApplication;
			class CWindowService;

			struct PD_APPLICATION;

			// In case of using with form the destruction should be done by form only!
			// To change default state, just create new class derived from it and set required default properties in constructor
			class CWindow :public virtual IWindow
			{
				friend CApplication;
				friend CWindowService;
				friend PD_APPLICATION;
				friend opengl31d::CRenderer;
				friend opengl31r::CRenderer;
				friend opengl45d::CRenderer;
				friend opengl45r::CRenderer;
			private:
				struct TIMER
				{
					ITimerListener *Listener;
					PlatformHandle Id;
				};

				struct WINDOW_ENABLE
				{
					PlatformHandle Handle;
					bool Enabled;
				};
			private:
				CApplication *m_pApplication;
				std::vector<TIMER> m_aTimers;
				CursorType m_eCurrentCursor;
				bool m_bCursorSet;
				IWindowService *m_pService;
				bool m_bAcceptDragAndDrop;
				bool m_bAcceptDropFiles;
				CreateParams m_sCreateParams;
				IWindow *m_pParent;
				bool m_bModal;
				ModalResult m_eModalResult;
				int m_iID;
				PlatformHandle m_hParent;
				std::vector<WINDOW_ENABLE> m_aStates;

				int m_iPixelFormatIndex;

				void ExitModal();
				Point CalculateCreatePosition(const Point &size);
				bool CreatePlatformWindow();
			public:
				bool isCreated() override;
				bool isVisible() override;
				bool isEnabled() override;
				bool isAcceptDragAndDrop() override;
				bool isAcceptDropFiles() override;
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
				bool hasProgressBar() override;

				bool setCaption(const String &value) override;
				bool setVisible(const bool value) override;
				bool setEnabled(const bool value) override;
				bool setAcceptDrawAndDrop(const bool value) override;
				bool setAcceptDropFiles(const bool value) override;
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
				bool setProgressType(const ProgressType value) override;
				bool setProgressValue(const float value) override;

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
				CWindow(PlatformHandle parent);
				virtual ~CWindow();

				static Key VirtualToKey(const int value); // Convert from virtual key code to Key enumeration
				static int KeyToVirtual(const Key value); // Convert from Key enumeration to virtual key code
			};
		}
	}
}
#endif