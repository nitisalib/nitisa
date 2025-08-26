// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Key.h"
#include "Nitisa/Core/Messages.h"
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
#include <vector>

struct AAssetManager;
struct AConfiguration;
struct AInputEvent;

namespace nitisa
{
	class IApplicationService;
	class IFeature;
	class IForm;
	class IRenderer;
	class IThread;
	class IThreadListener;
	class ITimerListener;
	class IWindow;
	class IWindowListener;

	class CRenderer;

	namespace platform
	{
		namespace android
		{
			class CApplicationService;
			class CWindow;
			class CWindowService;

			namespace gles
			{
				class CBaseRenderer;
				class CRenderer;
			}

			namespace gles31d
			{
				class CRenderer;
			}

			namespace gles31r
			{
				class CRenderer;
			}

			class CApplication :public virtual IApplication
			{
				friend CApplicationService;
				friend CRenderer;
				friend CWindow;
				friend CWindowService;
				friend gles::CBaseRenderer;
				friend gles::CRenderer;
				friend gles31d::CRenderer;
				friend gles31r::CRenderer;
			public:
				struct FONT_FACE // Describe loaded font face
				{
					void *Face;
					String Name;
					int RefCount;
					bool Default;
				};

				struct MESSAGE_KEY_ANDROID :public MessageKey // Key message extension
				{
					int32_t KeyCode; // Android system key code
				};
			private:
				struct WINDOW
				{
					IWindow *Window;
					IForm *Form;
					bool Enabled;
				};

				struct TIMER
				{
					ITimerListener *Listener;
					float Interval;
					PlatformHandle Id;
					std::chrono::high_resolution_clock::time_point Last;
				};

				CSystem m_cSystem;
				CScreen m_cScreen;
				CMouse m_cMouse;
				CKeyboard m_cKeyboard;
				CPicture m_cPicture;
				CTranslate m_cTranslate;
				CStyles m_cStyles;
				CDialogs m_cDialogs;
				CFileSystem m_cFileSystem;
				CNetwork m_cNetwork;
				CDb m_cDb;
				std::vector<WINDOW> m_aWindows;
				std::vector<TIMER> m_aTimers;
				std::vector<IFeature *> m_aFeatures;
				IApplicationService *m_pService;
				PlatformHandle m_iLastTimerId;
				std::vector<FONT_FACE*> m_aFontFaces;
				IRenderer *m_pRenderer;

				bool ProcessMessage();
				void ProcessMessageMain();
				void ProcessMessageInput();
				void ProcessTimers();
				void CommandInitialize();
				void CommandTerminate();
				void CommandResize();
				void CommandPaint();
				void CommandSetFocus();
				void CommandKillFocus();
				void CommandResume();
				void CommandPause();
				void CommandConfigChanged();
				void CommandDestroy();
				void CommandStart();
				void CommandStop();
				void CommandRectChanged();
				void CommandInputChanged();
				void CommandSaveState();
				void CommandLowMemory();
				bool ProcessInput(AInputEvent *e);
				bool ProcessInputKey(AInputEvent *e, IWindowListener *listener);
				bool ProcessInputMotion(AInputEvent *e, IWindowListener *listener);
				Key KeyCodeToKey(const int32_t code);
				void CleanUp();
				FONT_FACE *FindFontFace(const String &name, bool is_default);
			public:
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

				void(*OnSaveState)(CApplication *sender); // Event called when android informs about need of saving application state before closing
				void(*OnLowMemory)(CApplication *sender); // Event called when android inform application about low free memory

				AConfiguration *getConfiguration(); // Return application configuration
				AAssetManager *getAssetManager(); // Return asset manager

				FONT_FACE *LoadFontFace(const String &filename); // Load font or return existing one. Load from application assets
				FONT_FACE *LoadDefaultFontFace(const String &filename); // Load default font or return existing one
				void FreeFontFace(FONT_FACE *face); // Free font if it is not used anymore. Each call of LoadFontFace/LoadDefaultFontFace should correspond the same count of calls of FreeFontFace
			};
		}
	}
}
#endif