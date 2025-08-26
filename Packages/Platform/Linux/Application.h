// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/CloseAction.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Styles.h"
#include "Nitisa/Core/Translate.h"
#include "Nitisa/Interfaces/IApplication.h"
#include "../Core/Db.h"
#include "Dialogs.h"
#include "FileSystem.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Network.h"
#include "Picture.h"
#include "Screen.h"
#include "System.h"
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	class IApplicationService;
	class IFeature;
	class IForm;
	class IThread;
	class IThreadListener;
	class ITimerListener;
	class IWindow;

	class CRenderer;

	namespace platform
	{
		namespace linux
		{
			class CApplicationService;
			class CWindow;

			namespace opengl
			{
				class CBaseRenderer;
			}

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

			class CApplication :public virtual IApplication
			{
				friend CApplicationService;
				friend CDialogs;
				friend CKeyboard;
				friend CMouse;
				friend CScreen;
				friend CWindow;
				friend nitisa::CRenderer;
				friend opengl::CBaseRenderer;
				friend opengl31d::CRenderer;
				friend opengl31r::CRenderer;
				friend opengl45d::CRenderer;
				friend opengl45r::CRenderer;
			public:
				struct FONT_FACE // Describe loaded font face
				{
					void *Face;
					String Name;
					int RefCount;
					bool Default;
				};
			private:
				struct WINDOW
				{
					PlatformHandle Handle;
					IWindow *Wnd;
					IForm *Form;
					bool Enabled;
				};

				struct TIMER
				{
					PlatformHandle Id;
					float Interval;
					IWindow *Wnd;
					ITimerListener *Listener;
					std::chrono::steady_clock::time_point Start;
				};
			private:
				bool m_bTerminated;
				IApplicationService *m_pService;
				CKeyboard m_cKeyboard;
				CMouse m_cMouse;
				CTranslate m_cTranslate;
				CStyles m_cStyles;
				CScreen m_cScreen;
				CSystem m_cSystem;
				CPicture m_cPicture;
				CDialogs m_cDialogs;
				CFileSystem m_cFileSystem;
				CNetwork m_cNetwork;
				CDb m_cDb;
				int m_iExitCode;
				String m_sClipboardString;
				std::vector<FONT_FACE*> m_aFontFaces;
				PlatformHandle m_iTimerID;
				WINDOW m_sSearchWindow;
				bool m_bWindowsSorted;
				std::vector<WINDOW> m_aWindows;
				std::vector<TIMER> m_aTimers;
				std::vector<IFeature *> m_aFeatures;
				PlatformHandle m_aCursors[(int)CursorType::Wait + 1];
				PlatformHandle m_hRootWindow;
				PlatformHandle m_hClipboardWindow;
				PlatformHandle m_hInputMethod;
				PlatformHandle m_hInputContext;
				PlatformHandle m_hUTF8_STRING;
				PlatformHandle m_hCLIPBOARD;
				PlatformHandle m_hTIMER;
				PlatformHandle m_hWM_PROTOCOLS;
				PlatformHandle m_hWM_DELETE_WINDOW;
				PlatformHandle m_h_NET_WM_NAME;
				PlatformHandle m_h_NET_WM_STATE;
				PlatformHandle m_h_NET_WM_STATE_MODAL;
				PlatformHandle m_h_NET_WM_STATE_HIDDEN;
				PlatformHandle m_h_NET_WM_STATE_ABOVE;
				PlatformHandle m_h_NET_WM_STATE_MAXIMIZED_VERT;
				PlatformHandle m_h_NET_WM_STATE_MAXIMIZED_HORZ;
				PlatformHandle m_h_NET_WM_STATE_SKIP_TASKBAR;
				PlatformHandle m_h_NET_WM_STATE_SKIP_PAGER;
				PlatformHandle m_h_NET_WM_WINDOW_TYPE;
				PlatformHandle m_h_NET_WM_WINDOW_TYPE_NORMAL;
				PlatformHandle m_h_NET_WM_WINDOW_TYPE_DIALOG;
				PlatformHandle m_h_NET_REQUEST_FRAME_EXTENTS;
				PlatformHandle m_h_NET_FRAME_EXTENTS;
				PlatformHandle m_h_NET_ACTIVE_WINDOW;
				PlatformHandle m_h_NET_CLOSE_WINDOW;

				static const long _NET_WM_STATE_REMOVE{ 0 };
				static const long _NET_WM_STATE_ADD{ 1 };
				static const long _NET_WM_STATE_TOGGLE{ 2 };

				bool ProcessMessage(IWindow *modal);
				void ReceiveApplicationPath();
				void ReceiveModulePath();
				void ProcessSelectionRequest(const void *ev);
				void ProcessSelectionNotify(const void *ev);
				FONT_FACE *FindFontFace(const String &name, bool is_default);
				PlatformHandle CreateTimer(IWindow *window, ITimerListener *listener, const float interval);
				bool ResetTimer(const PlatformHandle id, const float interval);
				bool DeleteTimer(const PlatformHandle id);
				bool DeleteTimers(IWindow *window);
				void DeleteTimers();
				void ProcessTimers();
				void SortWindows();
				static unsigned long CursorTypeToShape(const CursorType type);
				PlatformHandle getHandle(const int index);
				bool hasWindow(IWindow *window) const;
				bool setForm(const int index, IForm *form);
				int AddWindow(PlatformHandle handle, IWindow *window, IForm *form, bool enabled);
				bool DeleteWindow(const int index);
				int FindWindowIndex(PlatformHandle handle);
				PlatformHandle CreateCursor(const CursorType type);
				void FreeCursors();
				String ReadUTF8Property(PlatformHandle handle, PlatformHandle name, bool &succeeded);
				bool UpdateUTF8Property(PlatformHandle handle, PlatformHandle name, const String &value);
				PlatformHandle getActiveWindow(bool &succeeded);
			public:
				void(*OnDestroyLastWindow)(); // Event called right after destroying the last window in application windows list

				int getWindowCount() override;
				IWindow *getWindow(const int index) override;
				IForm *getWindowForm(const int index) override;
				int getFeatureCount() override;
				IFeature *getFeature(const int index) override;
				IFeature *getFeature(const String &name) override;

				bool setMainForm(IForm *value) override;

				int Run() override;
				void ProcessMessages() override;
				void RepaintAll() override;
				IApplicationService *QueryService() override;
				IThread *CreateThread(const bool paused, IThreadListener *listener) override;
				bool RegisterFeature(IFeature *feature) override;
				bool UnregisterFeature(const int index) override;
				bool UnregisterFeature(IFeature *feature) override;
				bool UnregisterFeature(const String &name) override;
				bool UnregisterFeatures() override;

				CApplication();
				virtual ~CApplication();

				CloseAction getCloseAction(IWindow *window); // Return default close action for specified window. caFree by default. But if handle belongs to form and this form isn't same as main form, than close action is hide
				FONT_FACE *LoadFontFace(const String &filename); // Load font or return existing one
				FONT_FACE *LoadDefaultFontFace(const String &filename); // Load default font or return existing one
				void FreeFontFace(FONT_FACE *face); // Free font if it is not used anymore. Each call of LoadFontFace/LoadDefaultFontFace should correspond the same count of calls of FreeFontFace
			};
		}
	}
}
#endif