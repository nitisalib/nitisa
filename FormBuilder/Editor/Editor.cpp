// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	CEditor *Editor{ nullptr };

#pragma region Constructor & destructor
	CEditor::CEditor():
		m_iRefCounter{ 1 }
	{
		Editor = this;
		cast<fb::CApplication*>(Application)->setEditor(this);
		LoadSettings();
	#if defined(VS_INTEGRATION) || defined(USE_DIALOGBOXES)
		CreatePackages();
	#else
		LoadPackages();
	#endif
	}

	CEditor::~CEditor()
	{
		for (auto pos : m_aPackages)
		{
			pos.Package->Release();
			if (pos.Handle)
				FreeLibrary(pos.Handle);
		}
		Editor = nullptr;
	}

	IEditor *CEditor::Create()
	{
		if (Editor)
		{
			Editor->m_iRefCounter++;
			return Editor;
		}
		return new CEditor();
	}

	void CEditor::Release()
	{
		m_iRefCounter--;
		if (m_iRefCounter <= 0)
			delete this;
	}
#pragma endregion

#pragma region Packages
	int CEditor::getPackageCount()
	{
		return (int)m_aPackages.size();
	}

	IPackage *CEditor::getPackage(const int index)
	{
		if (index >= 0 && index < (int)m_aPackages.size())
			return m_aPackages[index].Package;
		return nullptr;
	}

	IPackage *CEditor::getPackage(const String &name)
	{
		for (auto pos : m_aPackages)
			if (pos.Package->getName() == name)
				return pos.Package;
		return nullptr;
	}

	bool CEditor::isPackageVisible(const int index)
	{
		if (index >= 0 && index < (int)m_aPackages.size())
			return m_aPackages[index].Visible;
		return false;
	}

	bool CEditor::isPackageVisible(const String &name)
	{
		for (auto pos : m_aPackages)
			if (pos.Package->getName() == name)
				return pos.Visible;
		return false;
	}
#pragma endregion

#pragma region Components
	int CEditor::getComponentCount()
	{
		return (int)m_aComponents.size();
	}

	IPackageComponent *CEditor::getComponent(const int index)
	{
		if (index >= 0 && index < (int)m_aComponents.size())
			return m_aComponents[index].Component;
		return nullptr;
	}

	IPackageComponent *CEditor::getComponent(const String &package, const String &class_name)
	{
		for (auto pos : m_aComponents)
			if (pos.Component->getClassName() == class_name && pos.Component->getPackage()->getName() == package)
				return pos.Component;
		return nullptr;
	}

	IPackageComponent *CEditor::getComponent(IComponent *component)
	{
		if (component)
			for (auto pos : m_aComponents)
				if (pos.Component->isInstance(component))
					return pos.Component;
		return nullptr;
	}

	bool CEditor::isComponentVisible(const int index)
	{
		if (index >= 0 && index < (int)m_aComponents.size())
			return isPackageVisible(m_aComponents[index].Component->getPackage()->getName()) && m_aComponents[index].Visible;
		return false;
	}

	bool CEditor::isComponentVisible(const String &package, const String &class_name)
	{
		for (auto pos : m_aComponents)
			if (pos.Component->getClassName() == class_name && pos.Component->getPackage()->getName() == package)
				return isPackageVisible(pos.Component->getPackage()->getName()) && pos.Visible;
		return false;
	}
#pragma endregion

#pragma region Controls
	int CEditor::getControlCount()
	{
		return (int)m_aControls.size();
	}

	IPackageControl *CEditor::getControl(const int index)
	{
		if (index >= 0 && index < (int)m_aControls.size())
			return m_aControls[index].Control;
		return nullptr;
	}

	IPackageControl *CEditor::getControl(const String &package, const String &class_name)
	{
		for (auto pos : m_aControls)
			if (pos.Control->getClassName() == class_name && pos.Control->getPackage()->getName() == package)
				return pos.Control;
		return nullptr;
	}

	IPackageControl *CEditor::getControl(IControl *control)
	{
		if (control)
			for (auto pos : m_aControls)
				if (pos.Control->isInstance(control))
					return pos.Control;
		return nullptr;
	}

	bool CEditor::isControlVisible(const int index)
	{
		if (index >= 0 && index < (int)m_aControls.size())
			return isPackageVisible(m_aControls[index].Control->getPackage()->getName()) && m_aControls[index].Visible;
		return false;
	}

	bool CEditor::isControlVisible(const String &package, const String &class_name)
	{
		for (auto pos : m_aControls)
			if (pos.Control->getClassName() == class_name && pos.Control->getPackage()->getName() == package)
				return isPackageVisible(pos.Control->getPackage()->getName()) && pos.Visible;
		return false;
	}
#pragma endregion

#pragma region Listitems
	int CEditor::getListItemCount()
	{
		return (int)m_aListItems.size();
	}

	IPackageListItem *CEditor::getListItem(const int index)
	{
		if (index >= 0 && index < (int)m_aListItems.size())
			return m_aListItems[index].ListItem;
		return nullptr;
	}

	IPackageListItem *CEditor::getListItem(const String &package, const String &class_name)
	{
		for (auto pos : m_aListItems)
			if (pos.ListItem->getClassName() == class_name && pos.ListItem->getPackage()->getName() == package)
				return pos.ListItem;
		return nullptr;
	}

	IPackageListItem *CEditor::getListItem(IListItem *listitem)
	{
		if (listitem)
			for (auto pos : m_aListItems)
				if (pos.ListItem->isInstance(listitem))
					return pos.ListItem;
		return nullptr;
	}
#pragma endregion

#pragma region Forms
	int CEditor::getFormCount()
	{
		return (int)m_aForms.size();
	}

	IPackageForm *CEditor::getForm(const int index)
	{
		if (index >= 0 && index < (int)m_aForms.size())
			return m_aForms[index].Form;
		return nullptr;
	}

	IPackageForm *CEditor::getForm(const String &package, const String &class_name)
	{
		for (auto pos : m_aForms)
			if (pos.Form->getClassName() == class_name && pos.Form->getPackage()->getName() == package)
				return pos.Form;
		return nullptr;
	}

	bool CEditor::isFormVisible(const int index)
	{
		if (index >= 0 && index < (int)m_aForms.size())
			return isPackageVisible(m_aForms[index].Form->getPackage()->getName()) && m_aForms[index].Visible;
		return false;
	}

	bool CEditor::isFormVisible(const String &package, const String &class_name)
	{
		for (auto pos : m_aForms)
			if (pos.Form->getClassName() == class_name && pos.Form->getPackage()->getName() == package)
				return isPackageVisible(pos.Form->getPackage()->getName()) && pos.Visible;
		return false;
	}
#pragma endregion

#pragma region Renderers
	int CEditor::getRendererCount()
	{
		return (int)m_aRenderers.size();
	}

	IPackageRenderer *CEditor::getRenderer(const int index)
	{
		if (index >= 0 && index < (int)m_aRenderers.size())
			return m_aRenderers[index].Renderer;
		return nullptr;
	}

	IPackageRenderer *CEditor::getRenderer(const String &package, const String &class_name)
	{
		for (auto pos : m_aRenderers)
			if (pos.Renderer->getClassName() == class_name && pos.Renderer->getPackage()->getName() == package)
				return pos.Renderer;
		return nullptr;
	}

	bool CEditor::isRendererVisible(const int index)
	{
		if (index >= 0 && index < (int)m_aRenderers.size())
			return isPackageVisible(m_aRenderers[index].Renderer->getPackage()->getName()) && m_aRenderers[index].Visible;
		return false;
	}

	bool CEditor::isRendererVisible(const String &package, const String &class_name)
	{
		for (auto pos : m_aRenderers)
			if (pos.Renderer->getClassName() == class_name && pos.Renderer->getPackage()->getName() == package)
				return isPackageVisible(pos.Renderer->getPackage()->getName()) && pos.Visible;
		return false;
	}
#pragma endregion

#pragma region PropertyHandlers
	int CEditor::getPropertyHandlerCount()
	{
		return (int)m_aPropertyHandlers.size();
	}

	IPackagePropertyHandler *CEditor::getPropertyHandler(const int index)
	{
		if (index >= 0 && index < (int)m_aPropertyHandlers.size())
			return m_aPropertyHandlers[index].PropertyHandler;
		return nullptr;
	}

	IPackagePropertyHandler* CEditor::getPropertyHandler(const String &package, const String &name)
	{
		for (auto pos : m_aPropertyHandlers)
			if (pos.PropertyHandler->Name == name && pos.PropertyHandler->Package->getName() == package)
				return pos.PropertyHandler;
		return nullptr;
	}

	IPackagePropertyHandler* CEditor::getPropertyHandler(const String &name)
	{
		for (auto pos = m_aPropertyHandlers.rbegin(); pos != m_aPropertyHandlers.rend(); pos++)
			if (pos->Enabled && pos->PropertyHandler->Name == name)
				return pos->PropertyHandler;
		return nullptr;
	}

	bool CEditor::isPropertyHandlerEnabled(const int index)
	{
		if (index >= 0 && index < (int)m_aPropertyHandlers.size())
			return m_aPropertyHandlers[index].Enabled;
		return false;
	}

	bool CEditor::isPropertyHandlerEnabled(const String &package, const String &name)
	{
		for (auto pos : m_aPropertyHandlers)
			if (pos.PropertyHandler->Name == name && pos.PropertyHandler->Package->getName() == package)
				return pos.Enabled;
		return false;
	}
#pragma endregion

#pragma region Styles
	int CEditor::getStyleCount()
	{
		return (int)m_aStyles.size();
	}

	IPackageStyle *CEditor::getStyle(const int index)
	{
		if (index >= 0 && index < (int)m_aStyles.size())
			return m_aStyles[index].Style;
		return nullptr;
	}

	IPackageStyle *CEditor::getStyle(const String &package, const String &class_name)
	{
		for (auto pos : m_aStyles)
			if (pos.Style->getClassName() == class_name && pos.Style->getPackage()->getName() == package)
				return pos.Style;
		return nullptr;
	}

	IPackageStyle *CEditor::getStyle(IStyle *style)
	{
		if (style)
			for (auto pos : m_aStyles)
				if (pos.Style->getStyle() == style)
					return pos.Style;
		return nullptr;
	}

	bool CEditor::isStyleVisible(const int index)
	{
		if (index >= 0 && index < (int)m_aStyles.size())
			return isPackageVisible(m_aStyles[index].Style->getPackage()->getName()) && m_aStyles[index].Visible;
		return false;
	}

	bool CEditor::isStyleVisible(const String &package, const String &class_name)
	{
		for (auto pos : m_aStyles)
			if (pos.Style->getClassName() == class_name && pos.Style->getPackage()->getName() == package)
				return isPackageVisible(pos.Style->getPackage()->getName()) && pos.Visible;
		return nullptr;
	}
#pragma endregion

#pragma region Register
	bool CEditor::Register(IPackageComponent *component)
	{
		if (component && !getComponent(component->getPackage()->getName(), component->getClassName()))
		{
			m_aComponents.push_back(COMPONENT{ component, true, false, L"" });
			return true;
		}
		return false;
	}

	bool CEditor::Register(IPackageControl *control)
	{
		if (control && !getControl(control->getPackage()->getName(), control->getClassName()))
		{
			m_aControls.push_back(CONTROL{ control, true, false, L"" });
			return true;
		}
		return false;
	}

	bool CEditor::Register(IPackageListItem *listitem)
	{
		if (listitem && !getListItem(listitem->getPackage()->getName(), listitem->getClassName()))
		{
			m_aListItems.push_back(LISTITEM{ listitem });
			return true;
		}
		return false;
	}

	bool CEditor::Register(IPackageForm *form)
	{
		if (form && !getForm(form->getPackage()->getName(), form->getClassName()))
		{
			m_aForms.push_back(FORM{ form, true });
			return true;
		}
		return false;
	}

	bool CEditor::Register(IPackageStyle *style)
	{
		if (style && !getStyle(style->getPackage()->getName(), style->getClassName()))
		{
			m_aStyles.push_back(STYLE{ style, true });
			return true;
		}
		return false;
	}

	bool CEditor::Register(IPackageRenderer *renderer)
	{
		if (renderer && !getRenderer(renderer->getPackage()->getName(), renderer->getClassName()))
		{
			m_aRenderers.push_back(RENDERER{ renderer, true });
			return true;
		}
		return false;
	}

	bool CEditor::Register(IPackagePropertyHandler *handler)
	{
		if (handler && !getPropertyHandler(handler->Package->getName(), handler->Name))
		{
			m_aPropertyHandlers.push_back(HANDLER{ handler, true });
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Initialization
	void CEditor::LoadSettings()
	{
		json_decode(GetUTF8FileContent(Application->ModuleDirectory + L"packages.json"), m_sSettings);
	}

#if defined(VS_INTEGRATION) || defined(USE_DIALOGBOXES)
	void CEditor::CreatePackages()
	{
		m_aPackages.push_back(PACKAGE{ new platform::CPackagePlatform(), true, 0 });
		m_aPackages.push_back(PACKAGE{ new standard::CPackageStandard(), true, 0 });
		m_aPackages.push_back(PACKAGE{ new extended::CPackageExtended(), true, 0 });
		m_aPackages.push_back(PACKAGE{ new opengl::CPackageOpenGL(), true, 0 });
		m_aPackages.push_back(PACKAGE{ new charts::CPackageCharts(), true, 0 });
		m_aPackages.push_back(PACKAGE{ new ide::CPackageIde(), true, 0 });
	}
#else
	void CEditor::LoadPackages()
	{
		// Package libraries
		IFileSystem::SearchFilesResult files;
		Application->FileSystem->SearchFiles(Application->ModuleDirectory + L"Package.*.dll", files);
		for (auto file : files)
		{
			HMODULE handle{ LoadLibraryW((Application->ModuleDirectory + file.Name).c_str()) };
			if (handle)
			{
				FGetPackage get_package{ (FGetPackage)GetProcAddress(handle, "GetPackage") };
				IPackage *package;
				bool visible{ true }, has_info{ false };
				Variant info;
				if (m_sSettings.isSet(L"packages") && m_sSettings.get(L"packages").getType() == Variant::VariantType::Array)
					for (auto pos : m_sSettings.get(L"packages"))
						if (pos.second.isSet(L"filename") && (String)pos.second.get(L"filename") == file.Name)
						{
							info = pos.second;
							has_info = true;
							break;
						}
				if (has_info)
					visible = !(bool)info[L"hidden"];
				if (get_package && (package = get_package(Application)))
				{
					m_aPackages.push_back(PACKAGE{ package, visible, handle });
					if (has_info)
					{
						for (auto pos : info[L"components"])
							for (auto &p : m_aComponents)
								if (p.Component->getClassName() == (String)pos.second && p.Component->getPackage() == package)
								{
									p.Visible = false;
									break;
								}
						for (auto pos : info[L"controls"])
							for (auto &p : m_aControls)
								if (p.Control->getClassName() == (String)pos.second && p.Control->getPackage() == package)
								{
									p.Visible = false;
									break;
								}
						for (auto pos : info[L"forms"])
							for (auto &p : m_aForms)
								if (p.Form->getClassName() == (String)pos.second && p.Form->getPackage() == package)
								{
									p.Visible = false;
									break;
								}
						for (auto pos : info[L"renderers"])
							for (auto &p : m_aRenderers)
								if (p.Renderer->getClassName() == (String)pos.second && p.Renderer->getPackage() == package)
								{
									p.Visible = false;
									break;
								}
						for (auto pos : info[L"styles"])
							for (auto &p : m_aStyles)
								if (p.Style->getClassName() == (String)pos.second && p.Style->getPackage() == package)
								{
									p.Visible = false;
									break;
								}
						for (auto pos : info[L"handlers"])
							for (auto &p : m_aPropertyHandlers)
								if (p.PropertyHandler->Name == (String)pos.second && p.PropertyHandler->Package == package)
								{
									p.Enabled = false;
									break;
								}
					}
				}
				else
					FreeLibrary(handle);
			}
		}
	}
#endif
#pragma endregion

#pragma region Overwrite component namespace
	void CEditor::OverwriteComponentNamespace(const int index, const String &ns)
	{
		if (index >= 0 && index < (int)m_aComponents.size())
		{
			if (!m_aComponents[index].NamespaceOverwritten)
				m_aComponents[index].OldNamespace = m_aComponents[index].Component->getNamespace();
			m_aComponents[index].Component->setNamespace(ns);
			m_aComponents[index].NamespaceOverwritten = true;
		}
	}

	void CEditor::RestoreComponentNamespace(const int index)
	{
		if (index >= 0 && index < (int)m_aComponents.size() && m_aComponents[index].NamespaceOverwritten)
		{
			m_aComponents[index].Component->setNamespace(m_aComponents[index].OldNamespace);
			m_aComponents[index].NamespaceOverwritten = false;
		}
	}
#pragma endregion

#pragma region Overwrite control namespace
	void CEditor::OverwriteControlNamespace(const int index, const String &ns)
	{
		if (index >= 0 && index < (int)m_aControls.size())
		{
			if (!m_aControls[index].NamespaceOverwritten)
				m_aControls[index].OldNamespace = m_aControls[index].Control->getNamespace();
			m_aControls[index].Control->setNamespace(ns);
			m_aControls[index].NamespaceOverwritten = true;
		}
	}

	void CEditor::RestoreControlNamespace(const int index)
	{
		if (index >= 0 && index < (int)m_aControls.size() && m_aControls[index].NamespaceOverwritten)
		{
			m_aControls[index].Control->setNamespace(m_aControls[index].OldNamespace);
			m_aControls[index].NamespaceOverwritten = false;
		}
	}
#pragma endregion
}