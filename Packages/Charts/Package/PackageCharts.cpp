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
	namespace charts
	{
	#pragma region Constructor & destructor
		CPackageCharts::CPackageCharts() :
			m_bCreatedComponentsSorted{ true },
			m_bCreatedControlsSorted{ true },
			m_pService{ nullptr }
		{
			// Components																			TAB IN FORM BUILDER:

			// Controls
			Application->Editor->Register(Create<CPackageLineChart>(m_aControls));				// Charts
			Application->Editor->Register(Create<CPackageSplineChart>(m_aControls));			// Charts
			Application->Editor->Register(Create<CPackageSteppedLineChart>(m_aControls));		// Charts
			Application->Editor->Register(Create<CPackageBarChart>(m_aControls));				// Charts
			Application->Editor->Register(Create<CPackageMultiBarChart>(m_aControls));			// Charts
			Application->Editor->Register(Create<CPackageStackedBarChart>(m_aControls));		// Charts
			Application->Editor->Register(Create<CPackageForexChart>(m_aControls));			// Charts
			Application->Editor->Register(Create<CPackageDoughnutChart>(m_aControls));			// Charts
			Application->Editor->Register(Create<CPackageSemiDoughnutChart>(m_aControls));		// Charts
			Application->Editor->Register(Create<CPackagePieChart>(m_aControls));				// Charts
			Application->Editor->Register(Create<CPackageSemiPieChart>(m_aControls));			// Charts
			Application->Editor->Register(Create<CPackagePolarAreaChart>(m_aControls));		// Charts
			Application->Editor->Register(Create<CPackageRadarChart>(m_aControls));			// Charts
			
			// Listitems

			// Forms
			Application->Editor->Register(Create<CPackageFormChartDataSet>(m_aForms));
			Application->Editor->Register(Create<CPackageFormForexChartData>(m_aForms));
			Application->Editor->Register(Create<CPackageFormLineInterpolationPositionArray>(m_aForms));

			// Renderers

			// Property handlers
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerChartDataSet>(L"ChartDataSet", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerForexChartData>(L"ForexChartData", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerLineInterpolationPositionArray>(L"LineInterpolationPositionArray", m_aPropertyHandlers));

			// Styles
		}

		CPackageCharts::~CPackageCharts()
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

		void CPackageCharts::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Common information
		String CPackageCharts::getVendor()
		{
			return L"Nitisa";
		}

		String CPackageCharts::getName()
		{
			return L"Charts";
		}

		String CPackageCharts::getVersion()
		{
			return L"10.0.0";
		}

		String CPackageCharts::getDescription()
		{
			return L"Package containing different chart widgets";
		}

		String CPackageCharts::getVendorUrl()
		{
			return L"http://nitisa.com";
		}

		String CPackageCharts::getReferenceUrl()
		{
			return L"http://nitisa.com/reference/charts";
		}

		String CPackageCharts::getLicenseText()
		{
			return L"This package is free for use in any application until there are no modifications of the source code";
		}

		IPackage::LicenseType CPackageCharts::getLicense()
		{
			return LicenseType::Free;
		}

		bool CPackageCharts::hasStaticLinking()
		{
			return true;
		}

		bool CPackageCharts::hasDynamicLinking()
		{
			return true;
		}

		bool CPackageCharts::hasSourceCode()
		{
			return true;
		}

		int CPackageCharts::getDependencyCount()
		{
			return (int)m_aDependencies.size();
		}

		IPackage::Dependency CPackageCharts::getDependency(const int index)
		{
			if (index >= 0 && index < (int)m_aDependencies.size())
				return m_aDependencies[index];
			return Dependency{ L"", L"", L"" };
		}
	#pragma endregion

	#pragma region Supported platforms by components & controls(may be overwritten in control and components if they have another supported platform set)
		int CPackageCharts::getPlatformCount()
		{
			return (int)m_aPlatforms.size();
		}

		PlatformVersion CPackageCharts::getPlatform(const int index)
		{
			if (index >= 0 && index < (int)m_aPlatforms.size())
				return m_aPlatforms[index];
			return PlatformVersion{ PlatformType::None };
		}
	#pragma endregion

	#pragma region Components
		int CPackageCharts::getComponentCount()
		{
			return (int)m_aComponents.size();
		}

		IPackageComponent *CPackageCharts::getComponent(const int index)
		{
			if (index >= 0 && index < (int)m_aComponents.size())
				return m_aComponents[index];
			return nullptr;
		}

		IPackageComponent *CPackageCharts::getComponent(const String &class_name)
		{
			for (auto pos : m_aComponents)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageComponent *CPackageCharts::getComponent(IComponent *component)
		{
			SortCreatedComponents();
			m_sSearchComponent.Component = component;
			auto pos{ std::lower_bound(m_aCreatedComponents.begin(), m_aCreatedComponents.end(), m_sSearchComponent, [](const COMPONENT &a, const COMPONENT &b) {return a.Component < b.Component; }) };
			if (pos != m_aCreatedComponents.end() && pos->Component == component)
				return pos->PackageComponent;
			return nullptr;
		}

		void CPackageCharts::SortCreatedComponents()
		{
			if (!m_bCreatedComponentsSorted)
			{
				std::sort(m_aCreatedComponents.begin(), m_aCreatedComponents.end(), [](const COMPONENT &a, const COMPONENT &b) {return a.Component < b.Component; });
				m_bCreatedComponentsSorted = true;
			}
		}
	#pragma endregion

	#pragma region Created components
		int CPackageCharts::getCreatedComponentCount()
		{
			return (int)m_aCreatedComponents.size();
		}

		IComponent *CPackageCharts::getCreatedComponent(const int index)
		{
			if (index >= 0 && index < (int)m_aCreatedComponents.size())
			{
				SortCreatedComponents();
				return m_aCreatedComponents[index].Component;
			}
			return nullptr;
		}

		bool CPackageCharts::getCreatedComponent(const int index, IComponent **component, IPackageComponent **package_component, IPropertyList **properties, IEventList **events)
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
		int CPackageCharts::getControlCount()
		{
			return (int)m_aControls.size();
		}

		IPackageControl *CPackageCharts::getControl(const int index)
		{
			if (index >= 0 && index < (int)m_aControls.size())
				return m_aControls[index];
			return nullptr;
		}

		IPackageControl *CPackageCharts::getControl(const String &class_name)
		{
			for (auto pos : m_aControls)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageControl *CPackageCharts::getControl(IControl *control)
		{
			SortCreatedControls();
			m_sSearchControl.Control = control;
			auto pos{ std::lower_bound(m_aCreatedControls.begin(), m_aCreatedControls.end(), m_sSearchControl, [](const CONTROL &a, const CONTROL &b) {return a.Control < b.Control; }) };
			if (pos != m_aCreatedControls.end() && pos->Control == control)
				return pos->PackageControl;
			return nullptr;
		}

		void CPackageCharts::SortCreatedControls()
		{
			if (!m_bCreatedControlsSorted)
			{
				std::sort(m_aCreatedControls.begin(), m_aCreatedControls.end(), [](const CONTROL &a, const CONTROL &b) {return a.Control < b.Control; });
				m_bCreatedControlsSorted = true;
			}
		}
	#pragma endregion

	#pragma region Created controls
		int CPackageCharts::getCreatedControlCount()
		{
			return (int)m_aCreatedControls.size();
		}

		IControl *CPackageCharts::getCreatedControl(const int index)
		{
			if (index >= 0 && index < (int)m_aCreatedControls.size())
			{
				SortCreatedControls();
				return m_aCreatedControls[index].Control;
			}
			return nullptr;
		}

		bool CPackageCharts::getCreatedControl(const int index, IControl **control, IPackageControl **package_control, IPropertyList **properties, IEventList **events)
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
		int CPackageCharts::getListItemCount()
		{
			return (int)m_aListItems.size();
		}

		IPackageListItem *CPackageCharts::getListItem(const int index)
		{
			if (index >= 0 && index < (int)m_aListItems.size())
				return m_aListItems[index];
			return nullptr;
		}

		IPackageListItem *CPackageCharts::getListItem(const String &class_name)
		{
			for (auto pos : m_aListItems)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageListItem *CPackageCharts::getListItem(IListItem *listitem)
		{
			for (auto pos : m_aListItems)
				if (pos->isInstance(listitem))
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Forms
		int CPackageCharts::getFormCount()
		{
			return (int)m_aForms.size();
		}

		IPackageForm *CPackageCharts::getForm(const int index)
		{
			if (index >= 0 && index < (int)m_aForms.size())
				return m_aForms[index];
			return nullptr;
		}

		IPackageForm *CPackageCharts::getForm(const String &class_name)
		{
			for (auto pos : m_aForms)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Renderers
		int CPackageCharts::getRendererCount()
		{
			return (int)m_aRenderers.size();
		}

		IPackageRenderer *CPackageCharts::getRenderer(const int index)
		{
			if (index >= 0 && index < (int)m_aRenderers.size())
				return m_aRenderers[index];
			return nullptr;
		}

		IPackageRenderer *CPackageCharts::getRenderer(const String &class_name)
		{
			for (auto pos : m_aRenderers)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Property handlers
		int CPackageCharts::getPropertyHandlerCount()
		{
			return (int)m_aPropertyHandlers.size();
		}

		IPackagePropertyHandler *CPackageCharts::getPropertyHandler(const int index)
		{
			if (index >= 0 && index < (int)m_aPropertyHandlers.size())
				return m_aPropertyHandlers[index];
			return nullptr;
		}

		IPackagePropertyHandler *CPackageCharts::getPropertyHandler(const String &name)
		{
			for (auto pos : m_aPropertyHandlers)
				if (pos->Name == name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Styles
		int CPackageCharts::getStyleCount()
		{
			return (int)m_aStyles.size();
		}

		IPackageStyle *CPackageCharts::getStyle(const int index)
		{
			if (index >= 0 && index < (int)m_aStyles.size())
				return m_aStyles[index];
			return nullptr;
		}

		IPackageStyle *CPackageCharts::getStyle(const String &class_name)
		{
			for (auto pos : m_aStyles)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageStyle *CPackageCharts::getStyle(IStyle *style)
		{
			for (auto pos = m_aStyles.begin(); pos != m_aStyles.end(); pos++)
				if ((*pos)->getStyle() == style)
					return *pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Helpers
		IPackageService *CPackageCharts::QueryService()
		{
			if (!m_pService)
				m_pService = new CPackageChartsService(this);
			return m_pService;
		}

		IPackage *CPackageCharts::Create(IApplication *application)
		{
			if (application)
				Application = application;
			return new CPackageCharts();
		}
	#pragma endregion
	}
}