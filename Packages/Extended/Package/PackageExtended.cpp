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
	namespace extended
	{
	#pragma region Constructor & destructor
		CPackageExtended::CPackageExtended() :
			m_bCreatedComponentsSorted{ true },
			m_bCreatedControlsSorted{ true },
			m_pService{ nullptr }
		{
			
		}

		CPackageExtended::~CPackageExtended()
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

		void CPackageExtended::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Common information
		String CPackageExtended::getVendor()
		{
			return L"Nitisa";
		}

		String CPackageExtended::getName()
		{
			return L"Extended";
		}

		String CPackageExtended::getVersion()
		{
			return L"10.0.0";
		}

		String CPackageExtended::getDescription()
		{
			return L"Extended package installed by default";
		}

		String CPackageExtended::getVendorUrl()
		{
			return L"http://nitisa.com";
		}

		String CPackageExtended::getReferenceUrl()
		{
			return L"http://nitisa.com/reference/extended";
		}

		String CPackageExtended::getLicenseText()
		{
			return L"This package is free for use in any application until there are no modifications of the source code";
		}

		IPackage::LicenseType CPackageExtended::getLicense()
		{
			return LicenseType::Free;
		}

		bool CPackageExtended::hasStaticLinking()
		{
			return true;
		}

		bool CPackageExtended::hasDynamicLinking()
		{
			return true;
		}

		bool CPackageExtended::hasSourceCode()
		{
			return true;
		}

		int CPackageExtended::getDependencyCount()
		{
			return (int)m_aDependencies.size();
		}

		IPackage::Dependency CPackageExtended::getDependency(const int index)
		{
			if (index >= 0 && index < (int)m_aDependencies.size())
				return m_aDependencies[index];
			return Dependency{ L"", L"", L"" };
		}
	#pragma endregion

	#pragma region Supported platforms by components & controls(may be overwritten in control and components if they have another supported platform set)
		int CPackageExtended::getPlatformCount()
		{
			return (int)m_aPlatforms.size();
		}

		PlatformVersion CPackageExtended::getPlatform(const int index)
		{
			if (index >= 0 && index < (int)m_aPlatforms.size())
				return m_aPlatforms[index];
			return PlatformVersion{ PlatformType::None };
		}
	#pragma endregion

	#pragma region Components
		int CPackageExtended::getComponentCount()
		{
			return (int)m_aComponents.size();
		}

		IPackageComponent *CPackageExtended::getComponent(const int index)
		{
			if (index >= 0 && index < (int)m_aComponents.size())
				return m_aComponents[index];
			return nullptr;
		}

		IPackageComponent *CPackageExtended::getComponent(const String &class_name)
		{
			for (auto pos : m_aComponents)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageComponent *CPackageExtended::getComponent(IComponent *component)
		{
			SortCreatedComponents();
			m_sSearchComponent.Component = component;
			auto pos{ std::lower_bound(m_aCreatedComponents.begin(), m_aCreatedComponents.end(), m_sSearchComponent, [](const COMPONENT &a, const COMPONENT &b) {return a.Component < b.Component; }) };
			if (pos != m_aCreatedComponents.end() && pos->Component == component)
				return pos->PackageComponent;
			return nullptr;
		}

		void CPackageExtended::SortCreatedComponents()
		{
			if (!m_bCreatedComponentsSorted)
			{
				std::sort(m_aCreatedComponents.begin(), m_aCreatedComponents.end(), [](const COMPONENT &a, const COMPONENT &b) {return a.Component < b.Component; });
				m_bCreatedComponentsSorted = true;
			}
		}
	#pragma endregion

	#pragma region Created components
		int CPackageExtended::getCreatedComponentCount()
		{
			return (int)m_aCreatedComponents.size();
		}

		IComponent *CPackageExtended::getCreatedComponent(const int index)
		{
			if (index >= 0 && index < (int)m_aCreatedComponents.size())
			{
				SortCreatedComponents();
				return m_aCreatedComponents[index].Component;
			}
			return nullptr;
		}

		bool CPackageExtended::getCreatedComponent(const int index, IComponent **component, IPackageComponent **package_component, IPropertyList **properties, IEventList **events)
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
		int CPackageExtended::getControlCount()
		{
			return (int)m_aControls.size();
		}

		IPackageControl *CPackageExtended::getControl(const int index)
		{
			if (index >= 0 && index < (int)m_aControls.size())
				return m_aControls[index];
			return nullptr;
		}

		IPackageControl *CPackageExtended::getControl(const String &class_name)
		{
			for (auto pos : m_aControls)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageControl *CPackageExtended::getControl(IControl *control)
		{
			SortCreatedControls();
			m_sSearchControl.Control = control;
			auto pos{ std::lower_bound(m_aCreatedControls.begin(), m_aCreatedControls.end(), m_sSearchControl, [](const CONTROL &a, const CONTROL &b) {return a.Control < b.Control; }) };
			if (pos != m_aCreatedControls.end() && pos->Control == control)
				return pos->PackageControl;
			return nullptr;
		}

		void CPackageExtended::SortCreatedControls()
		{
			if (!m_bCreatedControlsSorted)
			{
				std::sort(m_aCreatedControls.begin(), m_aCreatedControls.end(), [](const CONTROL &a, const CONTROL &b) {return a.Control < b.Control; });
				m_bCreatedControlsSorted = true;
			}
		}
	#pragma endregion

	#pragma region Created controls
		int CPackageExtended::getCreatedControlCount()
		{
			return (int)m_aCreatedControls.size();
		}

		IControl *CPackageExtended::getCreatedControl(const int index)
		{
			if (index >= 0 && index < (int)m_aCreatedControls.size())
			{
				SortCreatedControls();
				return m_aCreatedControls[index].Control;
			}
			return nullptr;
		}

		bool CPackageExtended::getCreatedControl(const int index, IControl **control, IPackageControl **package_control, IPropertyList **properties, IEventList **events)
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
		int CPackageExtended::getListItemCount()
		{
			return (int)m_aListItems.size();
		}

		IPackageListItem *CPackageExtended::getListItem(const int index)
		{
			if (index >= 0 && index < (int)m_aListItems.size())
				return m_aListItems[index];
			return nullptr;
		}

		IPackageListItem *CPackageExtended::getListItem(const String &class_name)
		{
			for (auto pos : m_aListItems)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageListItem *CPackageExtended::getListItem(IListItem *listitem)
		{
			for (auto pos : m_aListItems)
				if (pos->isInstance(listitem))
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Forms
		int CPackageExtended::getFormCount()
		{
			return (int)m_aForms.size();
		}

		IPackageForm *CPackageExtended::getForm(const int index)
		{
			if (index >= 0 && index < (int)m_aForms.size())
				return m_aForms[index];
			return nullptr;
		}

		IPackageForm *CPackageExtended::getForm(const String &class_name)
		{
			for (auto pos : m_aForms)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Renderers
		int CPackageExtended::getRendererCount()
		{
			return (int)m_aRenderers.size();
		}

		IPackageRenderer *CPackageExtended::getRenderer(const int index)
		{
			if (index >= 0 && index < (int)m_aRenderers.size())
				return m_aRenderers[index];
			return nullptr;
		}

		IPackageRenderer *CPackageExtended::getRenderer(const String &class_name)
		{
			for (auto pos : m_aRenderers)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Property handlers
		int CPackageExtended::getPropertyHandlerCount()
		{
			return (int)m_aPropertyHandlers.size();
		}

		IPackagePropertyHandler *CPackageExtended::getPropertyHandler(const int index)
		{
			if (index >= 0 && index < (int)m_aPropertyHandlers.size())
				return m_aPropertyHandlers[index];
			return nullptr;
		}

		IPackagePropertyHandler *CPackageExtended::getPropertyHandler(const String &name)
		{
			for (auto pos : m_aPropertyHandlers)
				if (pos->Name == name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Styles
		int CPackageExtended::getStyleCount()
		{
			return (int)m_aStyles.size();
		}

		IPackageStyle *CPackageExtended::getStyle(const int index)
		{
			if (index >= 0 && index < (int)m_aStyles.size())
				return m_aStyles[index];
			return nullptr;
		}

		IPackageStyle *CPackageExtended::getStyle(const String &class_name)
		{
			for (auto pos : m_aStyles)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageStyle *CPackageExtended::getStyle(IStyle *style)
		{
			for (auto pos = m_aStyles.begin(); pos != m_aStyles.end(); pos++)
				if ((*pos)->getStyle() == style)
					return *pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Helpers
		IPackageService *CPackageExtended::QueryService()
		{
			if (!m_pService)
				m_pService = new CPackageExtendedService(this);
			return m_pService;
		}

		IPackage *CPackageExtended::Create(IApplication *application)
		{
			if (application)
				Application = application;
			return new CPackageExtended();
		}
	#pragma endregion
	}
}