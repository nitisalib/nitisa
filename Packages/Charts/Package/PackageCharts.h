// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/PlatformVersion.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/Core/PackagePropertyHandler.h"
#include "Nitisa/Package/Interfaces/IPackage.h"
#include <vector>

namespace nitisa
{
	class IApplication;
	class IComponent;
	class IControl;
	class IEventList;
	class IListItem;
	class IPackageComponent;
	class IPackageControl;
	class IPackageForm;
	class IPackageListItem;
	class IPackageRenderer;
	class IPackageService;
	class IPackagePropertyHandler;
	class IPropertyList;
	class IStyle;

	namespace charts
	{
		class CPackageChartsService;

		class CPackageCharts :public virtual IPackage
		{
			friend CPackageChartsService;
		private:
			struct COMPONENT
			{
				IComponent *Component;
				IPackageComponent *PackageComponent;
				IPropertyList *Properties;
				IEventList *Events;
			};

			struct CONTROL
			{
				IControl *Control;
				IPackageControl *PackageControl;
				IPropertyList *Properties;
				IEventList *Events;
			};

			std::vector<PlatformVersion> m_aPlatforms;
			std::vector<IPackageComponent*> m_aComponents;
			std::vector<IPackageControl*> m_aControls;
			std::vector<IPackageListItem*> m_aListItems;
			std::vector<IPackageForm*> m_aForms;
			std::vector<IPackageRenderer*> m_aRenderers;
			std::vector<IPackagePropertyHandler*> m_aPropertyHandlers;
			std::vector<Dependency> m_aDependencies;
			std::vector<IPackageStyle*> m_aStyles;

			std::vector<COMPONENT> m_aCreatedComponents;
			std::vector<CONTROL> m_aCreatedControls;
			bool m_bCreatedComponentsSorted;
			bool m_bCreatedControlsSorted;
			IPackageService *m_pService;
			COMPONENT m_sSearchComponent;
			CONTROL m_sSearchControl;

			void SortCreatedComponents();
			void SortCreatedControls();
			template<class Class, class Interface> Class *Create(std::vector<Interface*> &list)
			{
				Class *result{ new Class(this) };
				list.push_back(result);
				return result;
			}

			template<class PropertyHandlerClass> CPackagePropertyHandler<PropertyHandlerClass> *CreatePropertyHandler(const String &name, std::vector<IPackagePropertyHandler*> &list)
			{
				CPackagePropertyHandler<PropertyHandlerClass> *result{ new CPackagePropertyHandler<PropertyHandlerClass>(this, name) };
				list.push_back(result);
				return result;
			}
		public:
			// Common information
			String getVendor() override;
			String getName() override;
			String getVersion() override;
			String getDescription() override;
			String getVendorUrl() override;
			String getReferenceUrl() override;
			String getLicenseText() override;
			LicenseType getLicense() override;
			bool hasStaticLinking() override;
			bool hasDynamicLinking() override;
			bool hasSourceCode() override;
			int getDependencyCount() override;
			Dependency getDependency(const int index) override;

			// Supported platforms by components & controls(may be overwritten in control and components if they have another supported platform set)
			int getPlatformCount() override;
			PlatformVersion getPlatform(const int index) override;

			// Components
			int getComponentCount() override;
			IPackageComponent *getComponent(const int index) override;
			IPackageComponent *getComponent(const String &class_name) override;
			IPackageComponent *getComponent(IComponent *component) override;

			// Created components
			int getCreatedComponentCount() override;
			IComponent *getCreatedComponent(const int index) override;
			bool getCreatedComponent(const int index, IComponent **component, IPackageComponent **package_component, IPropertyList **properties, IEventList **events) override;

			// Controls
			int getControlCount() override;
			IPackageControl *getControl(const int index) override;
			IPackageControl *getControl(const String &class_name) override;
			IPackageControl *getControl(IControl *control) override;

			// Created controls
			int getCreatedControlCount() override;
			IControl *getCreatedControl(const int index) override;
			bool getCreatedControl(const int index, IControl **control, IPackageControl **package_control, IPropertyList **properties, IEventList **events) override;

			// Listitems
			int getListItemCount() override;
			IPackageListItem *getListItem(const int index) override;
			IPackageListItem *getListItem(const String &class_name) override;
			IPackageListItem *getListItem(IListItem *listitem) override;

			// Forms
			int getFormCount() override;
			IPackageForm *getForm(const int index) override;
			IPackageForm *getForm(const String &class_name) override;

			// Renderers
			int getRendererCount() override;
			IPackageRenderer *getRenderer(const int index) override;
			IPackageRenderer *getRenderer(const String &class_name) override;

			// Property handlers
			int getPropertyHandlerCount() override;
			IPackagePropertyHandler *getPropertyHandler(const int index) override;
			IPackagePropertyHandler *getPropertyHandler(const String &name) override;

			// Styles
			int getStyleCount() override;
			IPackageStyle *getStyle(const int index) override;
			IPackageStyle *getStyle(const String &class_name) override;
			IPackageStyle *getStyle(IStyle *style) override;

			void Release() override;
			IPackageService *QueryService() override;

			CPackageCharts();
			virtual ~CPackageCharts();

			static IPackage *Create(IApplication *application);
		};
	}
}