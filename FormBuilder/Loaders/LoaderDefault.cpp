// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace fb
	{
	#pragma region Constructor & destructor
		CLoaderDefault::CLoaderDefault() :
			m_eLastError{ ErrorType::None }
		{

		}

		void CLoaderDefault::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Getters
		String CLoaderDefault::getName() const
		{
			return L"Load *.nfr of default format";
		}

		String CLoaderDefault::getDescription() const
		{
			return L"Load Nitisa Form Resource files in default format";
		}

		String CLoaderDefault::getVersion() const
		{
			return L"1.0.0";
		}

		ILoader::ErrorType CLoaderDefault::getLastError() const
		{
			return m_eLastError;
		}
	#pragma endregion

	#pragma region Loading
		bool CLoaderDefault::Load(
			Variant &data,
			CComponentList *components,
			CControlList *controls,
			Form &form,
			ide::IFormEditor *form_editor,
			bool &ignore_attach,
			OnLoadComponent on_load_component,
			OnLoadControl on_load_control)
		{
			m_eLastError = ErrorType::None;
			LoadForm(data, form);
			LoadWidgets(data, ignore_attach, components, controls, form.Form, form_editor, on_load_component, on_load_control);
			return true;
		}

		void CLoaderDefault::LoadForm(const Variant &data, Form &form)
		{
			if (data.isSet(L"Form"))
			{
				Variant src{ data.get(L"Form") };
				form.Properties->Load(src);
				form.Events->Load(src);
			}
		}

		void CLoaderDefault::LoadWidgets(const Variant &data, bool &ignore_attach, CComponentList *components, CControlList *controls, IForm *form, ide::IFormEditor *form_editor,
			OnLoadComponent on_load_component, OnLoadControl on_load_control)
		{
			ignore_attach = false;
			std::vector<LOAD_COMPONENT> load_components;
			std::vector<LOAD_CONTROL> load_controls;
			if (data.isSet(L"Components"))
			{
				Variant src{ data.get(L"Components") };
				for (auto pos : src)
					LoadComponent(load_components, pos.second, components, form, form_editor);
			}
			if (data.isSet(L"Controls"))
			{
				Variant src{ data.get(L"Controls") };
				for (auto pos : src)
					LoadControl(load_controls, pos.second, form_editor, controls, form_editor);
			}
			ignore_attach = true;
			for (auto pos : load_components)
			{
				pos.PackageComponent->Load(pos.Src, pos.Properties, pos.Events);
				on_load_component(form, &pos);
			}
			for (auto pos : load_controls)
			{
				pos.PackageControl->Load(pos.Src, pos.Properties, pos.Events);
				on_load_control(form, &pos);
			}
		}

		void CLoaderDefault::LoadComponent(std::vector<LOAD_COMPONENT> &load_components, const Variant &data, CComponentList *components, IForm *form, ide::IFormEditor *form_editor)
		{
			if (data.isSet(L"Package") && data.isSet(L"ClassName"))
			{
				IPackageComponent *package_component{ Application->Editor->getComponent((String)data.get(L"Package"), (String)data.get(L"ClassName")) };
				if (!package_component)
				{
					Application->Dialogs->Error(L"Component with class name <" + (String)data.get(L"ClassName") + L"> isn't found in package <" + (String)data.get(L"Package") + L">");
					return;
				}
				IEventList *events;
				IPropertyList *properties;
				IComponent *component{ package_component->Create(&properties, &events) };
				if (!component)
				{
					Application->Dialogs->Error(L"Component with class name <" + (String)data.get(L"ClassName") + L"> is failed creating");
					return;
				}

				int index{ -1 };
				for (int i = 0; i < Application->Editor->getComponentCount(); i++)
					if (Application->Editor->getComponent(i) == package_component)
					{
						index = i;
						break;
					}
				// Preload name before any other properties
				if (data.isSet(L"Name"))
					properties->getProperty(L"Name")->Load(data.get(L"Name"));

				load_components.push_back(LOAD_COMPONENT{ component, events, properties, package_component, index, data });
				components->Add(component, events, properties, package_component, index);
				component->setForm(form);
				form_editor->setComponentPosition(component, PointF{ (float)data.get(L"Position").get(0), (float)data.get(L"Position").get(1) });
			}
		}

		void CLoaderDefault::LoadControl(std::vector<LOAD_CONTROL> &load_controls, const Variant &data, IControl *parent, CControlList *controls, ide::IFormEditor *form_editor)
		{
			if (data.isSet(L"Package") && data.isSet(L"ClassName"))
			{
				IPackageControl *package_control{ Application->Editor->getControl((String)data.get(L"Package"), (String)data.get(L"ClassName")) };
				if (!package_control)
				{
					Application->Dialogs->Error(L"Control with class name <" + (String)data.get(L"ClassName") + L"> isn't found in package <" + (String)data.get(L"Package") + L">");
					return;
				}
				IEventList *events;
				IPropertyList *properties;
				IControl *control{ package_control->Create(&properties, &events) };
				if (!control)
				{
					Application->Dialogs->Error(L"Control with class name <" + (String)data.get(L"ClassName") + L"> is failed creating");
					return;
				}

				// Preload name and placement before any other properties
				if (data.isSet(L"Name"))
					properties->getProperty(L"Name")->Load(data.get(L"Name"));
				if (data.isSet(L"Align"))
					properties->getProperty(L"Align")->Load(data.get(L"Align"));
				if (data.isSet(L"Transform"))
					properties->getProperty(L"Transform")->Load(data.get(L"Transform"));

				int index{ -1 };
				for (int i = 0; i < Application->Editor->getControlCount(); i++)
					if (Application->Editor->getControl(i) == package_control)
					{
						index = i;
						break;
					}

				load_controls.push_back(LOAD_CONTROL{ control, events, properties, package_control, index, data });
				controls->Add(control, events, properties, package_control, index);
				control->setParent(parent);
				if (package_control->isDisplayIcon())
					form_editor->setControlPosition(control, PointF{ (float)data.get(L"Position").get(0), (float)data.get(L"Position").get(1) });
				if (data.isSet(L"Controls"))
				{
					Variant src{ data.get(L"Controls") };
					for (auto pos : src)
						LoadControl(load_controls, pos.second, control, controls, form_editor);
				}
			}
		}
	#pragma endregion
	}
}