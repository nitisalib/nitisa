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
	namespace platform
	{
	#pragma region Constructor & destructor
		CPackagePlatform::CPackagePlatform() :
			m_bCreatedComponentsSorted{ true },
			m_bCreatedControlsSorted{ true },
			m_pService{ nullptr }
		{
			// Components																				TAB IN FORM BUILDER:

			// Controls

			// Listitems

			// Forms

			// Renderers
			Application->Editor->Register(Create<CPackageRendererAndroidGLES31d>(m_aRenderers));
			Application->Editor->Register(Create<CPackageRendererAndroidGLES31r>(m_aRenderers));
			Application->Editor->Register(Create<CPackageRendererLinuxOpenGL31d>(m_aRenderers));
			Application->Editor->Register(Create<CPackageRendererLinuxOpenGL31r>(m_aRenderers));
			Application->Editor->Register(Create<CPackageRendererLinuxOpenGL45d>(m_aRenderers));
			Application->Editor->Register(Create<CPackageRendererLinuxOpenGL45r>(m_aRenderers));
			Application->Editor->Register(Create<CPackageRendererWindowsOpenGL31d>(m_aRenderers));
			Application->Editor->Register(Create<CPackageRendererWindowsOpenGL31r>(m_aRenderers));
			Application->Editor->Register(Create<CPackageRendererWindowsOpenGL45d>(m_aRenderers));
			Application->Editor->Register(Create<CPackageRendererWindowsOpenGL45r>(m_aRenderers));

			// Property handlers

			// Styles
		}

		CPackagePlatform::~CPackagePlatform()
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

		void CPackagePlatform::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Common information
		String CPackagePlatform::getVendor()
		{
			return L"Nitisa";
		}

		String CPackagePlatform::getName()
		{
			return L"Platform";
		}

		String CPackagePlatform::getVersion()
		{
			return L"10.0.0";
		}

		String CPackagePlatform::getDescription()
		{
			return L"Package with platform dependent classes";
		}

		String CPackagePlatform::getVendorUrl()
		{
			return L"http://nitisa.com";
		}

		String CPackagePlatform::getReferenceUrl()
		{
			return L"http://nitisa.com/reference/platform";
		}

		String CPackagePlatform::getLicenseText()
		{
			return L"This package is free for use in any application until there are no modifications of the source code";
		}

		IPackage::LicenseType CPackagePlatform::getLicense()
		{
			return LicenseType::Free;
		}

		bool CPackagePlatform::hasStaticLinking()
		{
			return true;
		}

		bool CPackagePlatform::hasDynamicLinking()
		{
			return true;
		}

		bool CPackagePlatform::hasSourceCode()
		{
			return true;
		}

		int CPackagePlatform::getDependencyCount()
		{
			return (int)m_aDependencies.size();
		}

		IPackage::Dependency CPackagePlatform::getDependency(const int index)
		{
			if (index >= 0 && index < (int)m_aDependencies.size())
				return m_aDependencies[index];
			return Dependency{ L"", L"", L"" };
		}
	#pragma endregion

	#pragma region Supported platforms by components & controls(may be overwritten in control and components if they have another supported platform set)
		int CPackagePlatform::getPlatformCount()
		{
			return (int)m_aPlatforms.size();
		}

		PlatformVersion CPackagePlatform::getPlatform(const int index)
		{
			if (index >= 0 && index < (int)m_aPlatforms.size())
				return m_aPlatforms[index];
			return PlatformVersion{ PlatformType::None };
		}
	#pragma endregion

	#pragma region Components
		int CPackagePlatform::getComponentCount()
		{
			return (int)m_aComponents.size();
		}

		IPackageComponent *CPackagePlatform::getComponent(const int index)
		{
			if (index >= 0 && index < (int)m_aComponents.size())
				return m_aComponents[index];
			return nullptr;
		}

		IPackageComponent *CPackagePlatform::getComponent(const String &class_name)
		{
			for (auto pos : m_aComponents)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageComponent *CPackagePlatform::getComponent(IComponent *component)
		{
			SortCreatedComponents();
			m_sSearchComponent.Component = component;
			auto pos{ std::lower_bound(m_aCreatedComponents.begin(), m_aCreatedComponents.end(), m_sSearchComponent, [](const COMPONENT &a, const COMPONENT &b) {return a.Component < b.Component; }) };
			if (pos != m_aCreatedComponents.end() && pos->Component == component)
				return pos->PackageComponent;
			return nullptr;
		}

		void CPackagePlatform::SortCreatedComponents()
		{
			if (!m_bCreatedComponentsSorted)
			{
				std::sort(m_aCreatedComponents.begin(), m_aCreatedComponents.end(), [](const COMPONENT &a, const COMPONENT &b) {return a.Component < b.Component; });
				m_bCreatedComponentsSorted = true;
			}
		}
	#pragma endregion

	#pragma region Created components
		int CPackagePlatform::getCreatedComponentCount()
		{
			return (int)m_aCreatedComponents.size();
		}

		IComponent *CPackagePlatform::getCreatedComponent(const int index)
		{
			if (index >= 0 && index < (int)m_aCreatedComponents.size())
			{
				SortCreatedComponents();
				return m_aCreatedComponents[index].Component;
			}
			return nullptr;
		}

		bool CPackagePlatform::getCreatedComponent(const int index, IComponent **component, IPackageComponent **package_component, IPropertyList **properties, IEventList **events)
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
		int CPackagePlatform::getControlCount()
		{
			return (int)m_aControls.size();
		}

		IPackageControl *CPackagePlatform::getControl(const int index)
		{
			if (index >= 0 && index < (int)m_aControls.size())
				return m_aControls[index];
			return nullptr;
		}

		IPackageControl *CPackagePlatform::getControl(const String &class_name)
		{
			for (auto pos : m_aControls)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageControl *CPackagePlatform::getControl(IControl *control)
		{
			SortCreatedControls();
			m_sSearchControl.Control = control;
			auto pos{ std::lower_bound(m_aCreatedControls.begin(), m_aCreatedControls.end(), m_sSearchControl, [](const CONTROL &a, const CONTROL &b) {return a.Control < b.Control; }) };
			if (pos != m_aCreatedControls.end() && pos->Control == control)
				return pos->PackageControl;
			return nullptr;
		}

		void CPackagePlatform::SortCreatedControls()
		{
			if (!m_bCreatedControlsSorted)
			{
				std::sort(m_aCreatedControls.begin(), m_aCreatedControls.end(), [](const CONTROL &a, const CONTROL &b) {return a.Control < b.Control; });
				m_bCreatedControlsSorted = true;
			}
		}
	#pragma endregion

	#pragma region Created controls
		int CPackagePlatform::getCreatedControlCount()
		{
			return (int)m_aCreatedControls.size();
		}

		IControl *CPackagePlatform::getCreatedControl(const int index)
		{
			if (index >= 0 && index < (int)m_aCreatedControls.size())
			{
				SortCreatedControls();
				return m_aCreatedControls[index].Control;
			}
			return nullptr;
		}

		bool CPackagePlatform::getCreatedControl(const int index, IControl **control, IPackageControl **package_control, IPropertyList **properties, IEventList **events)
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
		int CPackagePlatform::getListItemCount()
		{
			return (int)m_aListItems.size();
		}

		IPackageListItem *CPackagePlatform::getListItem(const int index)
		{
			if (index >= 0 && index < (int)m_aListItems.size())
				return m_aListItems[index];
			return nullptr;
		}

		IPackageListItem *CPackagePlatform::getListItem(const String &class_name)
		{
			for (auto pos : m_aListItems)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageListItem *CPackagePlatform::getListItem(IListItem *listitem)
		{
			for (auto pos : m_aListItems)
				if (pos->isInstance(listitem))
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Forms
		int CPackagePlatform::getFormCount()
		{
			return (int)m_aForms.size();
		}

		IPackageForm *CPackagePlatform::getForm(const int index)
		{
			if (index >= 0 && index < (int)m_aForms.size())
				return m_aForms[index];
			return nullptr;
		}

		IPackageForm *CPackagePlatform::getForm(const String &class_name)
		{
			for (auto pos : m_aForms)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Renderers
		int CPackagePlatform::getRendererCount()
		{
			return (int)m_aRenderers.size();
		}

		IPackageRenderer *CPackagePlatform::getRenderer(const int index)
		{
			if (index >= 0 && index < (int)m_aRenderers.size())
				return m_aRenderers[index];
			return nullptr;
		}

		IPackageRenderer *CPackagePlatform::getRenderer(const String &class_name)
		{
			for (auto pos : m_aRenderers)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Property handlers
		int CPackagePlatform::getPropertyHandlerCount()
		{
			return (int)m_aPropertyHandlers.size();
		}

		IPackagePropertyHandler *CPackagePlatform::getPropertyHandler(const int index)
		{
			if (index >= 0 && index < (int)m_aPropertyHandlers.size())
				return m_aPropertyHandlers[index];
			return nullptr;
		}

		IPackagePropertyHandler *CPackagePlatform::getPropertyHandler(const String &name)
		{
			for (auto pos : m_aPropertyHandlers)
				if (pos->Name == name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Styles
		int CPackagePlatform::getStyleCount()
		{
			return (int)m_aStyles.size();
		}

		IPackageStyle *CPackagePlatform::getStyle(const int index)
		{
			if (index >= 0 && index < (int)m_aStyles.size())
				return m_aStyles[index];
			return nullptr;
		}

		IPackageStyle *CPackagePlatform::getStyle(const String &class_name)
		{
			for (auto pos : m_aStyles)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageStyle *CPackagePlatform::getStyle(IStyle *style)
		{
			for (auto pos = m_aStyles.begin(); pos != m_aStyles.end(); pos++)
				if ((*pos)->getStyle() == style)
					return *pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Helpers
		IPackageService *CPackagePlatform::QueryService()
		{
			if (!m_pService)
				m_pService = new CPackagePlatformService(this);
			return m_pService;
		}

		IPackage *CPackagePlatform::Create(IApplication *application)
		{
			if (application)
				Application = application;
			return new CPackagePlatform();
		}
	#pragma endregion
	}
}