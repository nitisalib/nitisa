// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace ide
	{
	#pragma region Constructor & destructor
		CPackageIde::CPackageIde() :
			m_bCreatedComponentsSorted{ true },
			m_bCreatedControlsSorted{ true },
			m_pService{ nullptr }
		{
			// Components																			TAB IN FORM BUILDER:

			// Controls
			Application->Editor->Register(Create<CPackageEventEditor>(m_aControls));			// IDE
			Application->Editor->Register(Create<CPackagePropertyEditor>(m_aControls));			// IDE
			Application->Editor->Register(Create<CPackageFormView>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageFormEditor>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageHierarchyEditor>(m_aControls));		// IDE
			Application->Editor->Register(Create<CPackageViewCross>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewH1H2>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewH1H2L>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewH1H2R>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewH1H3>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewH2>(m_aControls));					// IDE
			Application->Editor->Register(Create<CPackageViewH2H1>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewH2H2>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewH2LH1>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewH2RH1>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewH3>(m_aControls));					// IDE
			Application->Editor->Register(Create<CPackageViewH3H1>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewV1V2>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewV1V2B>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewV1V2T>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewV1V3>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewV2>(m_aControls));					// IDE
			Application->Editor->Register(Create<CPackageViewV2BV1>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewV2TV1>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewV2V1>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewV2V2>(m_aControls));				// IDE
			Application->Editor->Register(Create<CPackageViewV3>(m_aControls));					// IDE
			Application->Editor->Register(Create<CPackageViewV3V1>(m_aControls));				// IDE
			
			// Listitems

			// Forms
			
			// Renderers

			// Property handlers

			// Styles
		}

		CPackageIde::~CPackageIde()
		{
			for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
				(*pos)->Release();
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				(*pos)->Release();
			for (auto pos = m_aListItems.begin(); pos != m_aListItems.end(); pos++)
				(*pos)->Release();
			for (auto pos = m_aForms.begin(); pos != m_aForms.end(); pos++)
				(*pos)->Release();
			for (auto pos = m_aRenderers.begin(); pos != m_aRenderers.end(); pos++)
				(*pos)->Release();
			for (auto pos = m_aPropertyHandlers.begin(); pos != m_aPropertyHandlers.end(); pos++)
				(*pos)->Release();
			for (auto pos = m_aStyles.begin(); pos != m_aStyles.end(); pos++)
				(*pos)->Release();
			if (m_pService)
				m_pService->Release();
		}

		void CPackageIde::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Common information
		String CPackageIde::getVendor()
		{
			return L"Nitisa";
		}

		String CPackageIde::getName()
		{
			return L"Ide";
		}

		String CPackageIde::getVersion()
		{
			return L"10.0.0";
		}

		String CPackageIde::getDescription()
		{
			return L"Package containing widgets useful in IDE creation project";
		}

		String CPackageIde::getVendorUrl()
		{
			return L"http://nitisa.com";
		}

		String CPackageIde::getReferenceUrl()
		{
			return L"http://nitisa.com/reference/ide";
		}

		String CPackageIde::getLicenseText()
		{
			return L"This package is free for use in any application until there are no modifications of the source code";
		}

		IPackage::LicenseType CPackageIde::getLicense()
		{
			return LicenseType::Free;
		}

		bool CPackageIde::hasStaticLinking()
		{
			return true;
		}

		bool CPackageIde::hasDynamicLinking()
		{
			return true;
		}

		bool CPackageIde::hasSourceCode()
		{
			return true;
		}

		int CPackageIde::getDependencyCount()
		{
			return (int)m_aDependencies.size();
		}

		IPackage::Dependency CPackageIde::getDependency(const int index)
		{
			if (index >= 0 && index < (int)m_aDependencies.size())
				return m_aDependencies[index];
			return Dependency{ L"", L"", L"" };
		}
	#pragma endregion

	#pragma region Supported platforms by components & controls(may be overwritten in control and components if they have another supported platform set)
		int CPackageIde::getPlatformCount()
		{
			return (int)m_aPlatforms.size();
		}

		PlatformVersion CPackageIde::getPlatform(const int index)
		{
			if (index >= 0 && index < (int)m_aPlatforms.size())
				return m_aPlatforms[index];
			return PlatformVersion{ PlatformType::None };
		}
	#pragma endregion

	#pragma region Components
		int CPackageIde::getComponentCount()
		{
			return (int)m_aComponents.size();
		}

		IPackageComponent *CPackageIde::getComponent(const int index)
		{
			if (index >= 0 && index < (int)m_aComponents.size())
				return m_aComponents[index];
			return nullptr;
		}

		IPackageComponent *CPackageIde::getComponent(const String &class_name)
		{
			for (auto pos : m_aComponents)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageComponent *CPackageIde::getComponent(IComponent *component)
		{
			SortCreatedComponents();
			m_sSearchComponent.Component = component;
			auto pos{ std::lower_bound(m_aCreatedComponents.begin(), m_aCreatedComponents.end(), m_sSearchComponent, [](const COMPONENT &a, const COMPONENT &b) {return a.Component < b.Component; }) };
			if (pos != m_aCreatedComponents.end() && pos->Component == component)
				return pos->PackageComponent;
			return nullptr;
		}

		void CPackageIde::SortCreatedComponents()
		{
			if (!m_bCreatedComponentsSorted)
			{
				std::sort(m_aCreatedComponents.begin(), m_aCreatedComponents.end(), [](const COMPONENT &a, const COMPONENT &b) {return a.Component < b.Component; });
				m_bCreatedComponentsSorted = true;
			}
		}
	#pragma endregion

	#pragma region Created components
		int CPackageIde::getCreatedComponentCount()
		{
			return (int)m_aCreatedComponents.size();
		}

		IComponent *CPackageIde::getCreatedComponent(const int index)
		{
			if (index >= 0 && index < (int)m_aCreatedComponents.size())
			{
				SortCreatedComponents();
				return m_aCreatedComponents[index].Component;
			}
			return nullptr;
		}

		bool CPackageIde::getCreatedComponent(const int index, IComponent **component, IPackageComponent **package_component, IPropertyList **properties, IEventList **events)
		{
			if (index >= 0 && index < (int)m_aCreatedComponents.size())
			{
				SortCreatedComponents();
				*component = m_aCreatedComponents[index].Component;
				*package_component = m_aCreatedComponents[index].PackageComponent;
				*properties = m_aCreatedComponents[index].Properties;
				*events = m_aCreatedComponents[index].Events;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Controls
		int CPackageIde::getControlCount()
		{
			return (int)m_aControls.size();
		}

		IPackageControl *CPackageIde::getControl(const int index)
		{
			if (index >= 0 && index < (int)m_aControls.size())
				return m_aControls[index];
			return nullptr;
		}

		IPackageControl *CPackageIde::getControl(const String &class_name)
		{
			for (auto pos : m_aControls)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageControl *CPackageIde::getControl(IControl *control)
		{
			SortCreatedControls();
			m_sSearchControl.Control = control;
			auto pos{ std::lower_bound(m_aCreatedControls.begin(), m_aCreatedControls.end(), m_sSearchControl, [](const CONTROL &a, const CONTROL &b) {return a.Control < b.Control; }) };
			if (pos != m_aCreatedControls.end() && pos->Control == control)
				return pos->PackageControl;
			return nullptr;
		}

		void CPackageIde::SortCreatedControls()
		{
			if (!m_bCreatedControlsSorted)
			{
				std::sort(m_aCreatedControls.begin(), m_aCreatedControls.end(), [](const CONTROL &a, const CONTROL &b) {return a.Control < b.Control; });
				m_bCreatedControlsSorted = true;
			}
		}
	#pragma endregion

	#pragma region Created controls
		int CPackageIde::getCreatedControlCount()
		{
			return (int)m_aCreatedControls.size();
		}

		IControl *CPackageIde::getCreatedControl(const int index)
		{
			if (index >= 0 && index < (int)m_aCreatedControls.size())
			{
				SortCreatedControls();
				return m_aCreatedControls[index].Control;
			}
			return nullptr;
		}

		bool CPackageIde::getCreatedControl(const int index, IControl **control, IPackageControl **package_control, IPropertyList **properties, IEventList **events)
		{
			if (index >= 0 && index < (int)m_aCreatedControls.size())
			{
				SortCreatedControls();
				*control = m_aCreatedControls[index].Control;
				*package_control = m_aCreatedControls[index].PackageControl;
				*properties = m_aCreatedControls[index].Properties;
				*events = m_aCreatedControls[index].Events;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Listitems
		int CPackageIde::getListItemCount()
		{
			return (int)m_aListItems.size();
		}

		IPackageListItem *CPackageIde::getListItem(const int index)
		{
			if (index >= 0 && index < (int)m_aListItems.size())
				return m_aListItems[index];
			return nullptr;
		}

		IPackageListItem *CPackageIde::getListItem(const String &class_name)
		{
			for (auto pos : m_aListItems)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageListItem *CPackageIde::getListItem(IListItem *listitem)
		{
			for (auto pos : m_aListItems)
				if (pos->isInstance(listitem))
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Forms
		int CPackageIde::getFormCount()
		{
			return (int)m_aForms.size();
		}

		IPackageForm *CPackageIde::getForm(const int index)
		{
			if (index >= 0 && index < (int)m_aForms.size())
				return m_aForms[index];
			return nullptr;
		}

		IPackageForm *CPackageIde::getForm(const String &class_name)
		{
			for (auto pos : m_aForms)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Renderers
		int CPackageIde::getRendererCount()
		{
			return (int)m_aRenderers.size();
		}

		IPackageRenderer *CPackageIde::getRenderer(const int index)
		{
			if (index >= 0 && index < (int)m_aRenderers.size())
				return m_aRenderers[index];
			return nullptr;
		}

		IPackageRenderer *CPackageIde::getRenderer(const String &class_name)
		{
			for (auto pos : m_aRenderers)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Property handlers
		int CPackageIde::getPropertyHandlerCount()
		{
			return (int)m_aPropertyHandlers.size();
		}

		IPackagePropertyHandler *CPackageIde::getPropertyHandler(const int index)
		{
			if (index >= 0 && index < (int)m_aPropertyHandlers.size())
				return m_aPropertyHandlers[index];
			return nullptr;
		}

		IPackagePropertyHandler *CPackageIde::getPropertyHandler(const String &name)
		{
			for (auto pos : m_aPropertyHandlers)
				if (pos->Name == name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Styles
		int CPackageIde::getStyleCount()
		{
			return (int)m_aStyles.size();
		}

		IPackageStyle *CPackageIde::getStyle(const int index)
		{
			if (index >= 0 && index < (int)m_aStyles.size())
				return m_aStyles[index];
			return nullptr;
		}

		IPackageStyle *CPackageIde::getStyle(const String &class_name)
		{
			for (auto pos : m_aStyles)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageStyle *CPackageIde::getStyle(IStyle *style)
		{
			for (auto pos = m_aStyles.begin(); pos != m_aStyles.end(); pos++)
				if ((*pos)->getStyle() == style)
					return *pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Helpers
		IPackageService *CPackageIde::QueryService()
		{
			if (!m_pService)
				m_pService = new CPackageIdeService(this);
			return m_pService;
		}

		IPackage *CPackageIde::Create(IApplication *application)
		{
			if (application)
				Application = application;
			return new CPackageIde();
		}
	#pragma endregion
	}
}