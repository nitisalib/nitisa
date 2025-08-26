#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
	#pragma region Constructor & destructor
		CPackageCoolWidgets::CPackageCoolWidgets() :
			m_bCreatedControlsSorted{ true },
			m_pService{ nullptr }
		{
			Application->Editor->Register(Create<CPackageRegistration>(m_aControls));
			Application->Editor->Register(Create<CPackageFormRegistrationData>(m_aForms));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerRegistrationData>(PropertyHandlerRegistrationData, m_aPropertyHandlers));
		}

		CPackageCoolWidgets::~CPackageCoolWidgets()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				(*pos)->Release();
			for (auto pos = m_aForms.begin(); pos != m_aForms.end(); pos++)
				(*pos)->Release();
			for (auto pos = m_aPropertyHandlers.begin(); pos != m_aPropertyHandlers.end(); pos++)
				(*pos)->Release();
			if (m_pService)
				m_pService->Release();
		}

		void CPackageCoolWidgets::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Common information
		String CPackageCoolWidgets::getVendor()
		{
			return L"I am";
		}

		String CPackageCoolWidgets::getName()
		{
			return L"CoolWidgets";
		}

		String CPackageCoolWidgets::getVersion()
		{
			return L"1.0.0";
		}

		String CPackageCoolWidgets::getDescription()
		{
			return L"Tutorial package";
		}

		String CPackageCoolWidgets::getVendorUrl()
		{
			return L"";
		}

		String CPackageCoolWidgets::getReferenceUrl()
		{
			return L"";
		}

		String CPackageCoolWidgets::getLicenseText()
		{
			return L"This package is free for use in any application until there are no modifications of the source code";
		}

		IPackage::LicenseType CPackageCoolWidgets::getLicense()
		{
			return LicenseType::Free;
		}

		bool CPackageCoolWidgets::hasStaticLinking()
		{
			return true;
		}

		bool CPackageCoolWidgets::hasDynamicLinking()
		{
			return true;
		}

		bool CPackageCoolWidgets::hasSourceCode()
		{
			return true;
		}

		int CPackageCoolWidgets::getDependencyCount()
		{
			return 0;
		}

		IPackage::Dependency CPackageCoolWidgets::getDependency(const int index)
		{
			return Dependency{ L"", L"", L"" };
		}
	#pragma endregion

	#pragma region Supported platforms
		int CPackageCoolWidgets::getPlatformCount()
		{
			return 0;
		}

		PlatformVersion CPackageCoolWidgets::getPlatform(const int index)
		{
			return PlatformVersion{ PlatformType::None };
		}
	#pragma endregion

	#pragma region Components
		int CPackageCoolWidgets::getComponentCount()
		{
			return 0;
		}

		IPackageComponent *CPackageCoolWidgets::getComponent(const int index)
		{
			return nullptr;
		}

		IPackageComponent *CPackageCoolWidgets::getComponent(const String &class_name)
		{
			return nullptr;
		}

		IPackageComponent *CPackageCoolWidgets::getComponent(IComponent *component)
		{
			return nullptr;
		}
	#pragma endregion

	#pragma region Created components
		int CPackageCoolWidgets::getCreatedComponentCount()
		{
			return 0;
		}

		IComponent *CPackageCoolWidgets::getCreatedComponent(const int index)
		{
			return nullptr;
		}

		bool CPackageCoolWidgets::getCreatedComponent(const int index, IComponent **component, IPackageComponent **package_component, IPropertyList **properties, IEventList **events)
		{
			return false;
		}
	#pragma endregion

	#pragma region Controls
		int CPackageCoolWidgets::getControlCount()
		{
			return (int)m_aControls.size();
		}

		IPackageControl *CPackageCoolWidgets::getControl(const int index)
		{
			if (index >= 0 && index < (int)m_aControls.size())
				return m_aControls[index];
			return nullptr;
		}

		IPackageControl *CPackageCoolWidgets::getControl(const String &class_name)
		{
			for (auto pos : m_aControls)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageControl *CPackageCoolWidgets::getControl(IControl *control)
		{
			SortCreatedControls();
			m_sSearchControl.Control = control;
			auto pos{ std::lower_bound(m_aCreatedControls.begin(), m_aCreatedControls.end(), m_sSearchControl, [](const CONTROL &a, const CONTROL &b) {return a.Control < b.Control; }) };
			if (pos != m_aCreatedControls.end() && pos->Control == control)
				return pos->PackageControl;
			return nullptr;
		}

		void CPackageCoolWidgets::SortCreatedControls()
		{
			if (!m_bCreatedControlsSorted)
			{
				std::sort(m_aCreatedControls.begin(), m_aCreatedControls.end(), [](const CONTROL &a, const CONTROL &b) {return a.Control < b.Control; });
				m_bCreatedControlsSorted = true;
			}
		}
	#pragma endregion

	#pragma region Created controls
		int CPackageCoolWidgets::getCreatedControlCount()
		{
			return (int)m_aCreatedControls.size();
		}

		IControl *CPackageCoolWidgets::getCreatedControl(const int index)
		{
			if (index >= 0 && index < (int)m_aCreatedControls.size())
			{
				SortCreatedControls();
				return m_aCreatedControls[index].Control;
			}
			return nullptr;
		}

		bool CPackageCoolWidgets::getCreatedControl(const int index, IControl **control, IPackageControl **package_control, IPropertyList **properties, IEventList **events)
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
		int CPackageCoolWidgets::getListItemCount()
		{
			return 0;
		}

		IPackageListItem *CPackageCoolWidgets::getListItem(const int index)
		{
			return nullptr;
		}

		IPackageListItem *CPackageCoolWidgets::getListItem(const String &class_name)
		{
			return nullptr;
		}

		IPackageListItem *CPackageCoolWidgets::getListItem(IListItem *listitem)
		{
			return nullptr;
		}
	#pragma endregion

	#pragma region Forms
		int CPackageCoolWidgets::getFormCount()
		{
			return (int)m_aForms.size();
		}

		IPackageForm *CPackageCoolWidgets::getForm(const int index)
		{
			if (index >= 0 && index < (int)m_aForms.size())
				return m_aForms[index];
			return nullptr;
		}

		IPackageForm *CPackageCoolWidgets::getForm(const String &class_name)
		{
			for (auto pos : m_aForms)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Renderers
		int CPackageCoolWidgets::getRendererCount()
		{
			return 0;
		}

		IPackageRenderer *CPackageCoolWidgets::getRenderer(const int index)
		{
			return nullptr;
		}

		IPackageRenderer *CPackageCoolWidgets::getRenderer(const String &class_name)
		{
			return nullptr;
		}
	#pragma endregion

	#pragma region Property handlers
		int CPackageCoolWidgets::getPropertyHandlerCount()
		{
			return (int)m_aPropertyHandlers.size();
		}

		IPackagePropertyHandler *CPackageCoolWidgets::getPropertyHandler(const int index)
		{
			if (index >= 0 && index < (int)m_aPropertyHandlers.size())
				return m_aPropertyHandlers[index];
			return nullptr;
		}

		IPackagePropertyHandler *CPackageCoolWidgets::getPropertyHandler(const String &name)
		{
			for (auto pos : m_aPropertyHandlers)
				if (pos->Name == name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Styles
		int CPackageCoolWidgets::getStyleCount()
		{
			return 0;
		}

		IPackageStyle *CPackageCoolWidgets::getStyle(const int index)
		{
			return nullptr;
		}

		IPackageStyle *CPackageCoolWidgets::getStyle(const String &class_name)
		{
			return nullptr;
		}

		IPackageStyle *CPackageCoolWidgets::getStyle(IStyle *style)
		{
			return nullptr;
		}
	#pragma endregion

	#pragma region Helpers
		IPackageService *CPackageCoolWidgets::QueryService()
		{
			if (!m_pService)
				m_pService = new CPackageCoolWidgetsService(this);
			return m_pService;
		}

		IPackage *CPackageCoolWidgets::Create(IApplication *application)
		{
			if (application)
				Application = application;
			return new CPackageCoolWidgets();
		}
	#pragma endregion
	}
}