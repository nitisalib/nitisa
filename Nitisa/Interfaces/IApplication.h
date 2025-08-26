// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "../Core/Strings.h"

namespace nitisa
{
	class IApplicationService;
	class IDb;
	class IDialogs;
	class IEditor;
	class IFeature;
	class IFileSystem;
	class IForm;
	class IKeyboard;
	class IMouse;
	class INetwork;
	class IPicture;
	class IScreen;
	class IStyles;
	class ISystem;
	class ITranslate;
	class IThread;
	class IThreadListener;
	class IWindow;

	// Should delete window object after system window was destroyed
	// If form required to be created outside of application, just use it's constructor to create instance
	// If form should be handled by application, use IApplication->CreateForm() to create the form. The form created first will be main one. After main form window destruction,
	// all other windows will be destroyed and application finish it's work
	class IApplication
	{
	protected:
		IApplication() = default;
		~IApplication() = default;
		IApplication(const IApplication &other) = delete;
		IApplication(IApplication &&other) = delete;
		IApplication &operator=(const IApplication &other) = delete;
		IApplication &operator=(IApplication &&other) = delete;
	protected:
		PlatformHandle m_hHandle;
		String m_sApplicationFileName;
		String m_sApplicationDirectory;
		String m_sModuleFileName;
		String m_sModuleDirectory;
		bool m_bDialogBoxes;
		bool m_bGlobal;
		IForm *m_pMainForm;
		IKeyboard *m_pKeyboard;
		IMouse *m_pMouse;
		ITranslate *m_pTranslate;
		IStyles *m_pStyles;
		IScreen *m_pScreen;
		ISystem *m_pSystem;
		IPicture *m_pPicture;
		IDialogs *m_pDialogs;
		IFileSystem *m_pFileSystem;
		INetwork *m_pNetwork;
		IEditor *m_pEditor;
		IDb *m_pDb;
	public:
		PlatformHandle const &Handle{ m_hHandle };
		String const &ApplicationFileName{ m_sApplicationFileName }; // Application file name without path. Use to get *.exe file name
		String const &ApplicationDirectory{ m_sApplicationDirectory }; // Application directory name with directory separator at the end. Use to get *.exe directory name
		String const &ModuleFileName{ m_sModuleFileName }; // Module file name without path. Use to get *.dll(if application is created in dll) or *.exe file name
		String const &ModuleDirectory{ m_sModuleDirectory }; // Module directory name with directory separator at the end. Use to get *.dll(if application is created in dll) or *.exe directory name
		bool const &DialogBoxes{ m_bDialogBoxes }; // True if application should try to use forms in form of dialog boxes if possible. All forms from standard packages can do it. By default return false which means standard standalone forms will be used
		bool const &Global{ m_bGlobal }; // Whether this application object controls entire application. By default true, which means application will be closed automatically when last form/window is closed. False should be returned only if the application is actually a part of bigger one and is used to show/manage as build-in interface of that bigger application. The example where application returns FALSE is integration of Form Builder with Visual Studio
		IForm* const &MainForm{ m_pMainForm }; // Main form
		IKeyboard* const &Keyboard{ m_pKeyboard }; // Keyboard interface
		IMouse* const &Mouse{ m_pMouse }; // Mouse interface
		ITranslate* const &Translate{ m_pTranslate }; // Translation interface
		IStyles* const &Styles{ m_pStyles }; // Styles interface
		IScreen* const &Screen{ m_pScreen }; // Screen interface
		ISystem* const &System{ m_pSystem }; // System interface
		IPicture* const &Picture{ m_pPicture }; // Picture interface
		IDialogs* const &Dialogs{ m_pDialogs }; // System dialogs interface
		IFileSystem* const &FileSystem{ m_pFileSystem }; // Interface for working with file system
		INetwork* const &Network{ m_pNetwork }; // Interfaces for working with network connections
		IEditor* const &Editor{ m_pEditor }; // Editor. Return nullptr almost always. Return instance of editor when the code is running under Form Builder
		IDb* const &Db{ m_pDb }; // DataBase manager

		void(*OnIdle)(); // Idle event callback. Called each time when application do nothing

		virtual int getWindowCount() = 0; // Return count of registered windows in application
		virtual IWindow *getWindow(const int index) = 0; // Return window by index
		virtual IForm *getWindowForm(const int index) = 0; // Return form of window specified by index
		virtual int getFeatureCount() = 0; // Return number of registered features
		virtual IFeature *getFeature(const int index) = 0; // Return feature by index
		virtual IFeature *getFeature(const String &name) = 0; // Return feature by name

		virtual bool setMainForm(IForm *value) = 0; // Set main form

		virtual int Run() = 0; // Run application. Return exit code(use it to return from WinMain)
		virtual void ProcessMessages() = 0; // Receive and process all available for application messages from system
		virtual void RepaintAll() = 0; // Repaint all visible forms
		virtual IApplicationService *QueryService() = 0; // Return service
		virtual IThread *CreateThread(const bool paused, IThreadListener *listener) = 0; // Create thread. Return nullptr if failed
		virtual bool RegisterFeature(IFeature *feature) = 0; // Register feature
		virtual bool UnregisterFeature(const int index) = 0; // Unregister feature by index
		virtual bool UnregisterFeature(IFeature *feature) = 0; // Unregister feature
		virtual bool UnregisterFeature(const String &name) = 0; // Unregister feature name
		virtual bool UnregisterFeatures() = 0; // Unregister all features

		template<class TForm> void CreateForm(TForm **var) // Create a form
		{
			*var = new TForm();
		}
	};

	extern IApplication *Application; // Global variable filled when application instance is created or by GetPackage function in package. Only one instance should exists in entire application.
}