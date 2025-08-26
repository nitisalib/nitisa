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

	namespace coolwidgets
	{
		class CPackageCoolWidgetsService;

		class CPackageCoolWidgets :public virtual IPackage
		{
			friend CPackageCoolWidgetsService;
		private:
			struct CONTROL
			{
				IControl *Control;
				IPackageControl *PackageControl;
				IPropertyList *Properties;
				IEventList *Events;
			};

			std::vector<IPackageControl*> m_aControls;
			std::vector<IPackageForm*> m_aForms;
			std::vector<IPackagePropertyHandler*> m_aPropertyHandlers;

			std::vector<CONTROL> m_aCreatedControls;
			bool m_bCreatedControlsSorted;
			IPackageService *m_pService;
			CONTROL m_sSearchControl;

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

			// Supported platforms
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

			// List items
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

			CPackageCoolWidgets();
			virtual ~CPackageCoolWidgets();

			static IPackage *Create(IApplication *application);
		};
	}
}