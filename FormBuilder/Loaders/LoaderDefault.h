// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Variant.h"
#include "../Interfaces/ILoader.h"
#include <vector>

namespace nitisa
{
	class IComponent;
	class IControl;
	class IForm;
	class IEventList;
	class IPackageComponent;
	class IPackageControl;
	class IPropertyList;

	namespace ide
	{
		class IFormEditor;
	}

	namespace fb
	{
		class CComponentList;
		class CControlList;

		class CLoaderDefault :public virtual ILoader
		{
		private:
			struct LOAD_COMPONENT : public COMPONENT_INFO
			{
				Variant Src;

				LOAD_COMPONENT(IComponent *component, IEventList *events, IPropertyList *properties, IPackageComponent *package_component, const int index, const Variant &src) :
					COMPONENT_INFO{ component, events, properties, package_component, index },
					Src{ src }
				{

				}
			};

			struct LOAD_CONTROL : public CONTROL_INFO
			{
				Variant Src;

				LOAD_CONTROL(IControl *control, IEventList *events, IPropertyList *properties, IPackageControl *package_control, const int index, const Variant &src) :
					CONTROL_INFO{ control, events, properties, package_control, index },
					Src{ src }
				{

				}
			};
		private:
			ErrorType m_eLastError;

			void LoadForm(const Variant &data, Form &form);
			void LoadWidgets(const Variant &data, bool &ignore_attach, CComponentList *components, CControlList *controls, IForm *form, ide::IFormEditor *form_editor,
				OnLoadComponent on_load_component, OnLoadControl on_load_control);
			void LoadComponent(std::vector<LOAD_COMPONENT> &load_components, const Variant &data, CComponentList *components, IForm *form, ide::IFormEditor *form_editor);
			void LoadControl(std::vector<LOAD_CONTROL> &load_controls, const Variant &data, IControl *parent, CControlList *controls, ide::IFormEditor *form_editor);
		public:
			String getName() const override;
			String getDescription() const override;
			String getVersion() const override;
			ErrorType getLastError() const override;

			void Release() override;

			bool Load(
				Variant &data,
				CComponentList *components,
				CControlList *controls,
				Form &form,
				ide::IFormEditor *form_editor,
				bool &ignore_attach,
				OnLoadComponent on_load_component,
				OnLoadControl on_load_control) override;

			CLoaderDefault();
			virtual ~CLoaderDefault() = default;
		};
	}
}