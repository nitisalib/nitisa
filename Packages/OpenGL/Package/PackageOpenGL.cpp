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
	namespace opengl
	{
	#pragma region Constructor & destructor
		CPackageOpenGL::CPackageOpenGL() :
			m_bCreatedComponentsSorted{ true },
			m_bCreatedControlsSorted{ true },
			m_pService{ nullptr }
		{
			m_aPlatforms.push_back(PlatformVersion{ PlatformType::Windows, L"", L"" });

			// Components																			TAB IN FORM BUILDER:

			// Controls
			Application->Editor->Register(Create<CPackageView>(m_aControls));					// 3D
			
			Application->Editor->Register(Create<CPackagePlane>(m_aControls));					// 3D
			Application->Editor->Register(Create<CPackageCircle>(m_aControls));					// 3D
			Application->Editor->Register(Create<CPackageDisk>(m_aControls));					// 3D

			Application->Editor->Register(Create<CPackageBox>(m_aControls));					// 3D
			Application->Editor->Register(Create<CPackagePyramid>(m_aControls));				// 3D
			Application->Editor->Register(Create<CPackageCone>(m_aControls));					// 3D
			Application->Editor->Register(Create<CPackageCylinder>(m_aControls));				// 3D
			Application->Editor->Register(Create<CPackageTube>(m_aControls));					// 3D
			Application->Editor->Register(Create<CPackageSphere>(m_aControls));					// 3D
			Application->Editor->Register(Create<CPackageTorus>(m_aControls));					// 3D

			Application->Editor->Register(Create<CPackageHeightmap>(m_aControls));				// 3D
			Application->Editor->Register(Create<CPackageJsonMesh>(m_aControls));				// 3D
			Application->Editor->Register(Create<CPackageMesh>(m_aControls));					// 3D
			Application->Editor->Register(Create<CPackage3DObject>(m_aControls));				// 3D

			Application->Editor->Register(Create<CPackageSolidMaterial>(m_aControls));			// 3D Materials
			Application->Editor->Register(Create<CPackageCheckerMaterial>(m_aControls));		// 3D Materials
			Application->Editor->Register(Create<CPackageGouraudMaterial>(m_aControls));		// 3D Materials
			Application->Editor->Register(Create<CPackagePhongMaterial>(m_aControls));			// 3D Materials
			Application->Editor->Register(Create<CPackageBlinnPhongMaterial>(m_aControls));		// 3D Materials
			Application->Editor->Register(Create<CPackageRimMaterial>(m_aControls));			// 3D Materials
			Application->Editor->Register(Create<CPackageCustomMaterial>(m_aControls));			// 3D Materials
			
			// Listitems

			// Forms

			// Renderers

			// Property handlers
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerControlMaterial>(L"ControlMaterial", m_aPropertyHandlers));

			// Styles

		}

		CPackageOpenGL::~CPackageOpenGL()
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

		void CPackageOpenGL::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Common information
		String CPackageOpenGL::getVendor()
		{
			return L"Nitisa";
		}

		String CPackageOpenGL::getName()
		{
			return L"OpenGL";
		}

		String CPackageOpenGL::getVersion()
		{
			return L"10.0.0"; // First introduced in 6.0.0 release. Now it is the same as entire framework
		}

		String CPackageOpenGL::getDescription()
		{
			return L"OpenGL 3D controls";
		}

		String CPackageOpenGL::getVendorUrl()
		{
			return L"http://nitisa.com";
		}

		String CPackageOpenGL::getReferenceUrl()
		{
			return L"http://nitisa.com/reference/opengl";
		}

		String CPackageOpenGL::getLicenseText()
		{
			return L"This package is free for usa in any applications until there are no modifications of the source code";
		}

		IPackage::LicenseType CPackageOpenGL::getLicense()
		{
			return LicenseType::Free;
		}

		bool CPackageOpenGL::hasStaticLinking()
		{
			return true;
		}

		bool CPackageOpenGL::hasDynamicLinking()
		{
			return true;
		}

		bool CPackageOpenGL::hasSourceCode()
		{
			return true;
		}

		int CPackageOpenGL::getDependencyCount()
		{
			return (int)m_aDependencies.size();
		}

		IPackage::Dependency CPackageOpenGL::getDependency(const int index)
		{
			if (index >= 0 && index < (int)m_aDependencies.size())
				return m_aDependencies[index];
			return Dependency{ L"", L"", L"" };
		}
	#pragma endregion

	#pragma region Supported platforms by components & controls(may be overwritten in control and components if they have another supported platform set)
		int CPackageOpenGL::getPlatformCount()
		{
			return (int)m_aPlatforms.size();
		}

		PlatformVersion CPackageOpenGL::getPlatform(const int index)
		{
			if (index >= 0 && index < (int)m_aPlatforms.size())
				return m_aPlatforms[index];
			return PlatformVersion{ PlatformType::None };
		}
	#pragma endregion

	#pragma region Components
		int CPackageOpenGL::getComponentCount()
		{
			return (int)m_aComponents.size();
		}

		IPackageComponent *CPackageOpenGL::getComponent(const int index)
		{
			if (index >= 0 && index < (int)m_aComponents.size())
				return m_aComponents[index];
			return nullptr;
		}

		IPackageComponent *CPackageOpenGL::getComponent(const String &class_name)
		{
			for (auto pos : m_aComponents)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageComponent *CPackageOpenGL::getComponent(IComponent *component)
		{
			SortCreatedComponents();
			m_sSearchComponent.Component = component;
			auto pos{ std::lower_bound(m_aCreatedComponents.begin(), m_aCreatedComponents.end(), m_sSearchComponent, [](const COMPONENT &a, const COMPONENT &b) {return a.Component < b.Component; }) };
			if (pos != m_aCreatedComponents.end() && pos->Component == component)
				return pos->PackageComponent;
			return nullptr;
		}

		void CPackageOpenGL::SortCreatedComponents()
		{
			if (!m_bCreatedComponentsSorted)
			{
				std::sort(m_aCreatedComponents.begin(), m_aCreatedComponents.end(), [](const COMPONENT &a, const COMPONENT &b) {return a.Component < b.Component; });
				m_bCreatedComponentsSorted = true;
			}
		}
	#pragma endregion

	#pragma region Created components
		int CPackageOpenGL::getCreatedComponentCount()
		{
			return (int)m_aCreatedComponents.size();
		}

		IComponent *CPackageOpenGL::getCreatedComponent(const int index)
		{
			if (index >= 0 && index < (int)m_aCreatedComponents.size())
			{
				SortCreatedComponents();
				return m_aCreatedComponents[index].Component;
			}
			return nullptr;
		}

		bool CPackageOpenGL::getCreatedComponent(const int index, IComponent **component, IPackageComponent **package_component, IPropertyList **properties, IEventList **events)
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
		int CPackageOpenGL::getControlCount()
		{
			return (int)m_aControls.size();
		}

		IPackageControl *CPackageOpenGL::getControl(const int index)
		{
			if (index >= 0 && index < (int)m_aControls.size())
				return m_aControls[index];
			return nullptr;
		}

		IPackageControl *CPackageOpenGL::getControl(const String &class_name)
		{
			for (auto pos : m_aControls)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageControl *CPackageOpenGL::getControl(IControl *control)
		{
			SortCreatedControls();
			m_sSearchControl.Control = control;
			auto pos{ std::lower_bound(m_aCreatedControls.begin(), m_aCreatedControls.end(), m_sSearchControl, [](const CONTROL &a, const CONTROL &b) {return a.Control < b.Control; }) };
			if (pos != m_aCreatedControls.end() && pos->Control == control)
				return pos->PackageControl;
			return nullptr;
		}

		void CPackageOpenGL::SortCreatedControls()
		{
			if (!m_bCreatedControlsSorted)
			{
				std::sort(m_aCreatedControls.begin(), m_aCreatedControls.end(), [](const CONTROL &a, const CONTROL &b) {return a.Control < b.Control; });
				m_bCreatedControlsSorted = true;
			}
		}
	#pragma endregion

	#pragma region Created controls
		int CPackageOpenGL::getCreatedControlCount()
		{
			return (int)m_aCreatedControls.size();
		}

		IControl *CPackageOpenGL::getCreatedControl(const int index)
		{
			if (index >= 0 && index < (int)m_aCreatedControls.size())
			{
				SortCreatedControls();
				return m_aCreatedControls[index].Control;
			}
			return nullptr;
		}

		bool CPackageOpenGL::getCreatedControl(const int index, IControl **control, IPackageControl **package_control, IPropertyList **properties, IEventList **events)
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
		int CPackageOpenGL::getListItemCount()
		{
			return (int)m_aListItems.size();
		}

		IPackageListItem *CPackageOpenGL::getListItem(const int index)
		{
			if (index >= 0 && index < (int)m_aListItems.size())
				return m_aListItems[index];
			return nullptr;
		}

		IPackageListItem *CPackageOpenGL::getListItem(const String &class_name)
		{
			for (auto pos : m_aListItems)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageListItem *CPackageOpenGL::getListItem(IListItem *listitem)
		{
			for (auto pos : m_aListItems)
				if (pos->isInstance(listitem))
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Forms
		int CPackageOpenGL::getFormCount()
		{
			return (int)m_aForms.size();
		}

		IPackageForm *CPackageOpenGL::getForm(const int index)
		{
			if (index >= 0 && index < (int)m_aForms.size())
				return m_aForms[index];
			return nullptr;
		}

		IPackageForm *CPackageOpenGL::getForm(const String &class_name)
		{
			for (auto pos : m_aForms)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Renderers
		int CPackageOpenGL::getRendererCount()
		{
			return (int)m_aRenderers.size();
		}

		IPackageRenderer *CPackageOpenGL::getRenderer(const int index)
		{
			if (index >= 0 && index < (int)m_aRenderers.size())
				return m_aRenderers[index];
			return nullptr;
		}

		IPackageRenderer *CPackageOpenGL::getRenderer(const String &class_name)
		{
			for (auto pos : m_aRenderers)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Property handlers
		int CPackageOpenGL::getPropertyHandlerCount()
		{
			return (int)m_aPropertyHandlers.size();
		}

		IPackagePropertyHandler *CPackageOpenGL::getPropertyHandler(const int index)
		{
			if (index >= 0 && index < (int)m_aPropertyHandlers.size())
				return m_aPropertyHandlers[index];
			return nullptr;
		}

		IPackagePropertyHandler *CPackageOpenGL::getPropertyHandler(const String &name)
		{
			for (auto pos : m_aPropertyHandlers)
				if (pos->Name == name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Styles
		int CPackageOpenGL::getStyleCount()
		{
			return (int)m_aStyles.size();
		}

		IPackageStyle *CPackageOpenGL::getStyle(const int index)
		{
			if (index >= 0 && index < (int)m_aStyles.size())
				return m_aStyles[index];
			return nullptr;
		}

		IPackageStyle *CPackageOpenGL::getStyle(const String &class_name)
		{
			for (auto pos : m_aStyles)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageStyle *CPackageOpenGL::getStyle(IStyle *style)
		{
			for (auto pos = m_aStyles.begin(); pos != m_aStyles.end(); pos++)
				if ((*pos)->getStyle() == style)
					return *pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Helpers
		IPackageService *CPackageOpenGL::QueryService()
		{
			if (!m_pService)
				m_pService = new CPackageOpenGLService(this);
			return m_pService;
		}

		IPackage *CPackageOpenGL::Create(IApplication *application)
		{
			if (application)
				Application = application;
			return new CPackageOpenGL();
		}
	#pragma endregion
	}
}