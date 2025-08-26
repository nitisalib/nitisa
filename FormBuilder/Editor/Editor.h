// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Variant.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IEditor.h"
#include <vector>
#include <Windows.h>

namespace nitisa
{
	class IApplication;
	class IPackage;
	class IPackageComponent;
	class IPackageControl;
	class IPackageForm;
	class IPackageListItem;
	class IPackageRenderer;
	class IPackageStyle;
	class IPackagePropertyHandler;

	class CEditor :public virtual IEditor
	{
	private:
		struct PACKAGE
		{
			IPackage *Package;
			bool Visible;
			HMODULE Handle;
		};

		struct COMPONENT
		{
			IPackageComponent *Component;
			bool Visible;
			bool NamespaceOverwritten;
			String OldNamespace;
		};

		struct CONTROL
		{
			IPackageControl *Control;
			bool Visible;
			bool NamespaceOverwritten;
			String OldNamespace;
		};

		struct LISTITEM
		{
			IPackageListItem *ListItem;
		};

		struct FORM
		{
			IPackageForm *Form;
			bool Visible;
		};

		struct RENDERER
		{
			IPackageRenderer *Renderer;
			bool Visible;
		};

		struct HANDLER
		{
			IPackagePropertyHandler *PropertyHandler;
			bool Enabled;
		};

		struct STYLE
		{
			IPackageStyle *Style;
			bool Visible;
		};

		using FGetPackage = IPackage*(_stdcall *)(IApplication *application);

		std::vector<PACKAGE> m_aPackages;
		std::vector<COMPONENT> m_aComponents;
		std::vector<CONTROL> m_aControls;
		std::vector<LISTITEM> m_aListItems;
		std::vector<FORM> m_aForms;
		std::vector<RENDERER> m_aRenderers;
		std::vector<HANDLER> m_aPropertyHandlers;
		std::vector<STYLE> m_aStyles;
		Variant m_sSettings;
		int m_iRefCounter;

		void LoadSettings();
	#if defined(VS_INTEGRATION) || defined(USE_DIALOGBOXES)
		void CreatePackages();
	#else
		void LoadPackages();
	#endif

		CEditor();
		~CEditor();
	public:
		// All registered packages
		int getPackageCount() override;
		IPackage *getPackage(const int index) override;
		IPackage *getPackage(const String &name) override;
		bool isPackageVisible(const int index) override;
		bool isPackageVisible(const String &name) override;

		// All registered package components
		int getComponentCount() override;
		IPackageComponent *getComponent(const int index) override;
		IPackageComponent *getComponent(const String &package, const String &class_name) override;
		IPackageComponent *getComponent(IComponent *component) override;
		bool isComponentVisible(const int index) override;
		bool isComponentVisible(const String &package, const String &class_name) override;

		// All registered package controls
		int getControlCount() override;
		IPackageControl *getControl(const int index) override;
		IPackageControl *getControl(const String &package, const String &class_name) override;
		IPackageControl *getControl(IControl *control) override;
		bool isControlVisible(const int index) override;
		bool isControlVisible(const String &package, const String &class_name) override;

		// All registered listitems
		int getListItemCount() override;
		IPackageListItem *getListItem(const int index) override;
		IPackageListItem *getListItem(const String &package, const String &class_name) override;
		IPackageListItem *getListItem(IListItem *listitem) override;

		// All registered package forms
		int getFormCount() override;
		IPackageForm *getForm(const int index) override;
		IPackageForm *getForm(const String &package, const String &class_name) override;
		bool isFormVisible(const int index) override;
		bool isFormVisible(const String &package, const String &class_name) override;

		// All registered package renderers
		int getRendererCount() override;
		IPackageRenderer *getRenderer(const int index) override;
		IPackageRenderer *getRenderer(const String &package, const String &class_name) override;
		bool isRendererVisible(const int index) override;
		bool isRendererVisible(const String &package, const String &class_name) override;

		// All registered property handlers
		int getPropertyHandlerCount() override;
		IPackagePropertyHandler *getPropertyHandler(const int index) override;
		IPackagePropertyHandler* getPropertyHandler(const String &package, const String &name) override;
		IPackagePropertyHandler* getPropertyHandler(const String &name) override;
		bool isPropertyHandlerEnabled(const int index) override;
		bool isPropertyHandlerEnabled(const String &package, const String &name) override;

		// All registered package styles
		int getStyleCount() override;
		IPackageStyle *getStyle(const int index) override;
		IPackageStyle *getStyle(const String &package, const String &class_name) override;
		IPackageStyle *getStyle(IStyle *style) override;
		bool isStyleVisible(const int index) override;
		bool isStyleVisible(const String &package, const String &class_name) override;

		bool Register(IPackageComponent *component) override;
		bool Register(IPackageControl *control) override;
		bool Register(IPackageListItem *listitem) override;
		bool Register(IPackageForm *form) override;
		bool Register(IPackageStyle *style) override;
		bool Register(IPackageRenderer *renderer) override;
		bool Register(IPackagePropertyHandler *handler) override;

		void Release() override;

		static IEditor *Create();

		void OverwriteComponentNamespace(const int index, const String &ns);
		void RestoreComponentNamespace(const int index);

		void OverwriteControlNamespace(const int index, const String &ns);
		void RestoreControlNamespace(const int index);
	};

	extern CEditor *Editor;
}