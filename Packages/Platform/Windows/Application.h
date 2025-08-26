// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef _WIN32
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/CloseAction.h"
#include "Nitisa/Core/Translate.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Styles.h"
#include "Nitisa/Interfaces/IApplication.h"
#include "Nitisa/Interfaces/IWindow.h"
#include "../Core/Db.h"
#include "Dialogs.h"
#include "FileSystem.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Network.h"
#include "Picture.h"
#include "Screen.h"
#include "System.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class IApplicationService;
	class IFeature;
	class IForm;
	class IThread;
	class IThreadListener;
	class IWindow;

	namespace platform
	{
		namespace windows
		{
			class CApplicationService;
			class CWindow;

			struct PD_APPLICATION;

			// Responsible for adding IWindow object to list if window has pointer to it in creation parameters
			// Responsible for deleting IWindow object from list when window is about to be destroyed
			// Responsible for deleting all windows if first(main) one was destroyed
			class CApplication :public virtual IApplication
			{
				friend CApplicationService;
				friend CWindow;
				friend PD_APPLICATION;
			private:
				struct WINDOW
				{
					PlatformHandle Handle;
					IWindow *Window;
					IForm *Form;
					bool Enabled;
				};
			private:
				void *m_pPlatformData;
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
				std::vector<WINDOW> m_aWindows;
				std::vector<IFeature *> m_aFeatures;
				bool m_bWindowsSorted;
				WINDOW m_sSearchWindow;

				bool ProcessMessage();
				void ReceiveApplicationPath();
				void ReceiveModulePath();
				bool SetProgressState(CWindow *window, const IWindow::ProgressType value);
				bool SetProgressValue(CWindow *window, const float value);
				ModalResult ShowModal(CWindow *window);
				void ExitModal(CWindow *window);
				int FindWindowIndex(const PlatformHandle handle);
				void SortWindows();
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
				bool hasTaskBar() const;
			};

			extern const String DefaultWindowClassName; // Specified default window class name. Used in window class implementation
		}
	}
}
#endif