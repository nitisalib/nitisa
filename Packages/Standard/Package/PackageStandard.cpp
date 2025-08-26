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
	namespace standard
	{
	#pragma region Constructor & destructor
		CPackageStandard::CPackageStandard() :
			m_bCreatedComponentsSorted{ true },
			m_bCreatedControlsSorted{ true },
			m_pService{ nullptr }
		{
			// Components																			TAB IN FORM BUILDER:
			Application->Editor->Register(Create<CPackageImageList>(m_aComponents));				// Standard
			Application->Editor->Register(Create<CPackageAdminRights>(m_aComponents));				// Additional
			Application->Editor->Register(Create<CPackageTimer>(m_aComponents));					// Standard
			Application->Editor->Register(Create<CPackageLogger>(m_aComponents));					// Additional
			Application->Editor->Register(Create<CPackageSimpleXML>(m_aComponents));				// Additional
			Application->Editor->Register(Create<CPackageColorDialog>(m_aComponents));				// Dialogs
			Application->Editor->Register(Create<CPackageFindDialog>(m_aComponents));				// Dialogs
			Application->Editor->Register(Create<CPackageReplaceDialog>(m_aComponents));			// Dialogs
			Application->Editor->Register(Create<CPackageSysBrowseFolderDialog>(m_aComponents));	// SysDialogs
			Application->Editor->Register(Create<CPackageSysColorDialog>(m_aComponents));			// SysDialogs
			Application->Editor->Register(Create<CPackageSysFontDialog>(m_aComponents));			// SysDialogs
			Application->Editor->Register(Create<CPackageSysOpenDialog>(m_aComponents));			// SysDialogs
			Application->Editor->Register(Create<CPackageSysOpenPictureDialog>(m_aComponents));		// SysDialogs
			Application->Editor->Register(Create<CPackageSysPageSetupDialog>(m_aComponents));		// SysDialogs
			Application->Editor->Register(Create<CPackageSysPrintDialog>(m_aComponents));			// SysDialogs
			Application->Editor->Register(Create<CPackageSysSaveDialog>(m_aComponents));			// SysDialogs
			Application->Editor->Register(Create<CPackageSysSavePictureDialog>(m_aComponents));		// SysDialogs
			Application->Editor->Register(Create<CPackageTaskBarProgress>(m_aComponents));			// Additional
			Application->Editor->Register(Create<CPackageTCPClient>(m_aComponents));				// Internet
			Application->Editor->Register(Create<CPackageTCPServer>(m_aComponents));				// Internet
			Application->Editor->Register(Create<CPackageTrayIcon>(m_aComponents));					// Additional

			// Controls
			Application->Editor->Register(Create<CPackageAlphaBar>(m_aControls));					// Additional
			Application->Editor->Register(Create<CPackageBevel>(m_aControls));						// Standard
			Application->Editor->Register(Create<CPackageBitBtn>(m_aControls));						// Standard
			Application->Editor->Register(Create<CPackageButton>(m_aControls));						// Standard
			Application->Editor->Register(Create<CPackageCheckBox>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageCheckListBox>(m_aControls));				// Standard
			Application->Editor->Register(Create<CPackageColorBox>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageColorListBox>(m_aControls));				// Standard
			Application->Editor->Register(Create<CPackageCoolBar>(m_aControls));					// Additional
			Application->Editor->Register(Create<CPackageContainer>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageDatePicker>(m_aControls));					// Additional
			Application->Editor->Register(Create<CPackageDialogBoxEx>(m_aControls));				// Additional
			Application->Editor->Register(Create<CPackageDirectoryTree>(m_aControls));				// Additional
			Application->Editor->Register(Create<CPackageDrawGrid>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageDriveDropDown>(m_aControls));				// Additional
			Application->Editor->Register(Create<CPackageDropDown>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageEdit>(m_aControls));						// Standard
			Application->Editor->Register(Create<CPackageEditCalc>(m_aControls));					// Additional
			Application->Editor->Register(Create<CPackageFileList>(m_aControls));					// Additional
			Application->Editor->Register(Create<CPackageFormStyleSolid>(m_aControls));				// Standard
			Application->Editor->Register(Create<CPackageFrame>(m_aControls));						// Standard
			Application->Editor->Register(Create<CPackageGradientEditor>(m_aControls));				// Additional
			Application->Editor->Register(Create<CPackageGroupBox>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageGroupFold>(m_aControls));					// Additional
			Application->Editor->Register(Create<CPackageHotKey>(m_aControls));						// Standard
			Application->Editor->Register(Create<CPackageHSVBar>(m_aControls));						// Additional
			Application->Editor->Register(Create<CPackageHSVPlane>(m_aControls));					// Additional
			Application->Editor->Register(Create<CPackageIconButton>(m_aControls));					// Additional
			Application->Editor->Register(Create<CPackageImage>(m_aControls));						// Standard
			Application->Editor->Register(Create<CPackageImageListEditor>(m_aControls));			// Additional
			Application->Editor->Register(Create<CPackageLabel>(m_aControls));						// Standard
			Application->Editor->Register(Create<CPackageListBox>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageMainMenu>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageMaskEdit>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageMemo>(m_aControls));						// Standard
			Application->Editor->Register(Create<CPackageMonthCalendar>(m_aControls));				// Additional
			Application->Editor->Register(Create<CPackageMultiButton>(m_aControls));				// Additional
			Application->Editor->Register(Create<CPackagePageControl>(m_aControls));				// Standard
			Application->Editor->Register(Create<CPackageTabSheet>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackagePaintBox>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackagePanel>(m_aControls));						// Standard
			Application->Editor->Register(Create<CPackagePasswordEdit>(m_aControls));				// Standard
			Application->Editor->Register(Create<CPackagePopupMenu>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageProgressBar>(m_aControls));				// Standard
			Application->Editor->Register(Create<CPackageRadioButton>(m_aControls));				// Standard
			Application->Editor->Register(Create<CPackageScrollBar>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageScrollBarLite>(m_aControls));				// Additional
			Application->Editor->Register(Create<CPackageScrollList>(m_aControls));					// Additional
			Application->Editor->Register(Create<CPackageScrollBox>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageSelect>(m_aControls));						// Additional
			Application->Editor->Register(Create<CPackageShape>(m_aControls));						// Additional
			Application->Editor->Register(Create<CPackageSpeedButton>(m_aControls));				// Standard
			Application->Editor->Register(Create<CPackageSplitter>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageStatusBar>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageStringGrid>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageTimePicker>(m_aControls));					// Additional
			Application->Editor->Register(Create<CPackageToggle>(m_aControls));						// Additional
			Application->Editor->Register(Create<CPackageToolBar>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageTrackBar>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageTrackRange>(m_aControls));					// Additional
			Application->Editor->Register(Create<CPackageTreeView>(m_aControls));					// Standard
			Application->Editor->Register(Create<CPackageUpDown>(m_aControls));						// Standard
			Application->Editor->Register(Create<CPackageUpDownEx>(m_aControls));					// Additional
			Application->Editor->Register(Create<CPackageValueListEditor>(m_aControls));			// Additional

			// Listitems
			Application->Editor->Register(Create<CPackageListItemCheckBox>(m_aListItems));
			Application->Editor->Register(Create<CPackageListItemColor>(m_aListItems));
			Application->Editor->Register(Create<CPackageListItemIcon>(m_aListItems));
			Application->Editor->Register(Create<CPackageListItemLabel>(m_aListItems));
			Application->Editor->Register(Create<CPackageListItemMenuCheckBox>(m_aListItems));
			Application->Editor->Register(Create<CPackageListItemMenuLabel>(m_aListItems));
			Application->Editor->Register(Create<CPackageListItemMenuRadioButton>(m_aListItems));
			Application->Editor->Register(Create<CPackageListItemMultiButton>(m_aListItems));
			Application->Editor->Register(Create<CPackageListItemMenuSeparator>(m_aListItems));
			Application->Editor->Register(Create<CPackageListItemSelectCategory>(m_aListItems));
			Application->Editor->Register(Create<CPackageListItemSelectLabel>(m_aListItems));
			Application->Editor->Register(Create<CPackageListItemStatusPanelLabel>(m_aListItems));
			Application->Editor->Register(Create<CPackageListItemTreeViewLabel>(m_aListItems));

			// Forms
			Application->Editor->Register(Create<CPackageFormBoolArray>(m_aForms));
			Application->Editor->Register(Create<CPackageFormBorderColor>(m_aForms));
			Application->Editor->Register(Create<CPackageFormColor>(m_aForms));
			Application->Editor->Register(Create<CPackageFormColorArray>(m_aForms));
			Application->Editor->Register(Create<CPackageFormFind>(m_aForms));
			Application->Editor->Register(Create<CPackageFormFloatArray>(m_aForms));
			Application->Editor->Register(Create<CPackageFormGradient>(m_aForms));
			Application->Editor->Register(Create<CPackageFormHotkey>(m_aForms));
			Application->Editor->Register(Create<CPackageFormHotkeyList>(m_aForms));
			Application->Editor->Register(Create<CPackageFormImage>(m_aForms));
			Application->Editor->Register(Create<CPackageFormImageList>(m_aForms));
			Application->Editor->Register(Create<CPackageFormIntegerArray>(m_aForms));
			Application->Editor->Register(Create<CPackageFormMask>(m_aForms));
			Application->Editor->Register(Create<CPackageFormMatrix>(m_aForms));
			Application->Editor->Register(Create<CPackageFormMemo>(m_aForms));
			Application->Editor->Register(Create<CPackageFormMenuListItem>(m_aForms));
			Application->Editor->Register(Create<CPackageFormPoint>(m_aForms));
			Application->Editor->Register(Create<CPackageFormPointB>(m_aForms));
			Application->Editor->Register(Create<CPackageFormPointD>(m_aForms));
			Application->Editor->Register(Create<CPackageFormPointF>(m_aForms));
			Application->Editor->Register(Create<CPackageFormPointL>(m_aForms));
			Application->Editor->Register(Create<CPackageFormRect>(m_aForms));
			Application->Editor->Register(Create<CPackageFormRectB>(m_aForms));
			Application->Editor->Register(Create<CPackageFormRectD>(m_aForms));
			Application->Editor->Register(Create<CPackageFormRectF>(m_aForms));
			Application->Editor->Register(Create<CPackageFormRectL>(m_aForms));
			Application->Editor->Register(Create<CPackageFormReplace>(m_aForms));
			Application->Editor->Register(Create<CPackageFormSelectListItem>(m_aForms));
			Application->Editor->Register(Create<CPackageFormTransform>(m_aForms));

			// Renderers

			// Property handlers
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerBool>(L"Bool", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerBoolArray>(L"BoolArray", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerColor>(L"Color", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerColorArray>(L"ColorArray", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerComponentImageList>(L"ComponentImageList", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerControlDirectoryTree>(L"ControlDirectoryTree", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerControlEdit>(L"ControlEdit", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerControlFileList>(L"ControlFileList", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerControlHSVPlane>(L"ControlHSVPlane", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerDouble>(L"Double", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerEnum>(L"Enum", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerFloat>(L"Float", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerFloatArray>(L"FloatArray", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerFont>(L"Font", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerGradient>(L"Gradient", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerHotkey>(L"Hotkey", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerHotkeyList>(L"HotkeyList", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerIdentifier>(L"Identifier", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerImage>(L"Image", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerImageList>(L"ImageList", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerInt64>(L"Int64", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerInteger>(L"Integer", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerIntegerArray>(L"IntegerArray", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerMask>(L"Mask", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerMatrix>(L"Matrix", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerPoint>(L"Point", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerPointB>(L"PointB", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerPointD>(L"PointD", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerPointF>(L"PointF", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerPointL>(L"PointL", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerRect>(L"Rect", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerRectB>(L"RectB", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerBorderColor>(L"BorderColor", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerRectD>(L"RectD", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerRectF>(L"RectF", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerRectL>(L"RectL", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerString>(L"String", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerStyle>(L"Style", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerText>(L"Text", m_aPropertyHandlers));
			Application->Editor->Register(CreatePropertyHandler<CPropertyHandlerTransform>(L"Transform", m_aPropertyHandlers));

			// Styles
		}

		CPackageStandard::~CPackageStandard()
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

		void CPackageStandard::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Common information
		String CPackageStandard::getVendor()
		{
			return L"Nitisa";
		}

		String CPackageStandard::getName()
		{
			return L"Standard";
		}

		String CPackageStandard::getVersion()
		{
			return L"10.0.0";
		}

		String CPackageStandard::getDescription()
		{
			return L"Standard package installed by default";
		}

		String CPackageStandard::getVendorUrl()
		{
			return L"http://nitisa.com";
		}

		String CPackageStandard::getReferenceUrl()
		{
			return L"http://nitisa.com/reference/standard";
		}

		String CPackageStandard::getLicenseText()
		{
			return L"This package is free for use in any application until there are no modifications of the source code";
		}

		IPackage::LicenseType CPackageStandard::getLicense()
		{
			return LicenseType::Free;
		}

		bool CPackageStandard::hasStaticLinking()
		{
			return true;
		}

		bool CPackageStandard::hasDynamicLinking()
		{
			return true;
		}

		bool CPackageStandard::hasSourceCode()
		{
			return true;
		}

		int CPackageStandard::getDependencyCount()
		{
			return (int)m_aDependencies.size();
		}

		IPackage::Dependency CPackageStandard::getDependency(const int index)
		{
			if (index >= 0 && index < (int)m_aDependencies.size())
				return m_aDependencies[index];
			return Dependency{ L"", L"", L"" };
		}
	#pragma endregion

	#pragma region Supported platforms by components & controls(may be overwritten in control and components if they have another supported platform set)
		int CPackageStandard::getPlatformCount()
		{
			return (int)m_aPlatforms.size();
		}

		PlatformVersion CPackageStandard::getPlatform(const int index)
		{
			if (index >= 0 && index < (int)m_aPlatforms.size())
				return m_aPlatforms[index];
			return PlatformVersion{ PlatformType::None };
		}
	#pragma endregion

	#pragma region Components
		int CPackageStandard::getComponentCount()
		{
			return (int)m_aComponents.size();
		}

		IPackageComponent *CPackageStandard::getComponent(const int index)
		{
			if (index >= 0 && index < (int)m_aComponents.size())
				return m_aComponents[index];
			return nullptr;
		}

		IPackageComponent *CPackageStandard::getComponent(const String &class_name)
		{
			for (auto pos : m_aComponents)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageComponent *CPackageStandard::getComponent(IComponent *component)
		{
			SortCreatedComponents();
			m_sSearchComponent.Component = component;
			auto pos{ std::lower_bound(m_aCreatedComponents.begin(), m_aCreatedComponents.end(), m_sSearchComponent, [](const COMPONENT &a, const COMPONENT &b) {return a.Component < b.Component; }) };
			if (pos != m_aCreatedComponents.end() && pos->Component == component)
				return pos->PackageComponent;
			return nullptr;
		}

		void CPackageStandard::SortCreatedComponents()
		{
			if (!m_bCreatedComponentsSorted)
			{
				std::sort(m_aCreatedComponents.begin(), m_aCreatedComponents.end(), [](const COMPONENT &a, const COMPONENT &b) {return a.Component < b.Component; });
				m_bCreatedComponentsSorted = true;
			}
		}
	#pragma endregion

	#pragma region Created components
		int CPackageStandard::getCreatedComponentCount()
		{
			return (int)m_aCreatedComponents.size();
		}

		IComponent *CPackageStandard::getCreatedComponent(const int index)
		{
			if (index >= 0 && index < (int)m_aCreatedComponents.size())
			{
				SortCreatedComponents();
				return m_aCreatedComponents[index].Component;
			}
			return nullptr;
		}

		bool CPackageStandard::getCreatedComponent(const int index, IComponent **component, IPackageComponent **package_component, IPropertyList **properties, IEventList **events)
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
		int CPackageStandard::getControlCount()
		{
			return (int)m_aControls.size();
		}

		IPackageControl *CPackageStandard::getControl(const int index)
		{
			if (index >= 0 && index < (int)m_aControls.size())
				return m_aControls[index];
			return nullptr;
		}

		IPackageControl *CPackageStandard::getControl(const String &class_name)
		{
			for (auto pos : m_aControls)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageControl *CPackageStandard::getControl(IControl *control)
		{
			SortCreatedControls();
			m_sSearchControl.Control = control;
			auto pos{ std::lower_bound(m_aCreatedControls.begin(), m_aCreatedControls.end(), m_sSearchControl, [](const CONTROL &a, const CONTROL &b) {return a.Control < b.Control; }) };
			if (pos != m_aCreatedControls.end() && pos->Control == control)
				return pos->PackageControl;
			return nullptr;
		}

		void CPackageStandard::SortCreatedControls()
		{
			if (!m_bCreatedControlsSorted)
			{
				std::sort(m_aCreatedControls.begin(), m_aCreatedControls.end(), [](const CONTROL &a, const CONTROL &b) {return a.Control < b.Control; });
				m_bCreatedControlsSorted = true;
			}
		}
	#pragma endregion

	#pragma region Created controls
		int CPackageStandard::getCreatedControlCount()
		{
			return (int)m_aCreatedControls.size();
		}

		IControl *CPackageStandard::getCreatedControl(const int index)
		{
			if (index >= 0 && index < (int)m_aCreatedControls.size())
			{
				SortCreatedControls();
				return m_aCreatedControls[index].Control;
			}
			return nullptr;
		}

		bool CPackageStandard::getCreatedControl(const int index, IControl **control, IPackageControl **package_control, IPropertyList **properties, IEventList **events)
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
		int CPackageStandard::getListItemCount()
		{
			return (int)m_aListItems.size();
		}

		IPackageListItem *CPackageStandard::getListItem(const int index)
		{
			if (index >= 0 && index < (int)m_aListItems.size())
				return m_aListItems[index];
			return nullptr;
		}

		IPackageListItem *CPackageStandard::getListItem(const String &class_name)
		{
			for (auto pos : m_aListItems)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageListItem *CPackageStandard::getListItem(IListItem *listitem)
		{
			for (auto pos : m_aListItems)
				if (pos->isInstance(listitem))
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Forms
		int CPackageStandard::getFormCount()
		{
			return (int)m_aForms.size();
		}

		IPackageForm *CPackageStandard::getForm(const int index)
		{
			if (index >= 0 && index < (int)m_aForms.size())
				return m_aForms[index];
			return nullptr;
		}

		IPackageForm *CPackageStandard::getForm(const String &class_name)
		{
			for (auto pos : m_aForms)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Renderers
		int CPackageStandard::getRendererCount()
		{
			return (int)m_aRenderers.size();
		}

		IPackageRenderer *CPackageStandard::getRenderer(const int index)
		{
			if (index >= 0 && index < (int)m_aRenderers.size())
				return m_aRenderers[index];
			return nullptr;
		}

		IPackageRenderer *CPackageStandard::getRenderer(const String &class_name)
		{
			for (auto pos : m_aRenderers)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Property handlers
		int CPackageStandard::getPropertyHandlerCount()
		{
			return (int)m_aPropertyHandlers.size();
		}

		IPackagePropertyHandler *CPackageStandard::getPropertyHandler(const int index)
		{
			if (index >= 0 && index < (int)m_aPropertyHandlers.size())
				return m_aPropertyHandlers[index];
			return nullptr;
		}

		IPackagePropertyHandler *CPackageStandard::getPropertyHandler(const String &name)
		{
			for (auto pos : m_aPropertyHandlers)
				if (pos->Name == name)
					return pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Styles
		int CPackageStandard::getStyleCount()
		{
			return (int)m_aStyles.size();
		}

		IPackageStyle *CPackageStandard::getStyle(const int index)
		{
			if (index >= 0 && index < (int)m_aStyles.size())
				return m_aStyles[index];
			return nullptr;
		}

		IPackageStyle *CPackageStandard::getStyle(const String &class_name)
		{
			for (auto pos : m_aStyles)
				if (pos->getClassName() == class_name)
					return pos;
			return nullptr;
		}

		IPackageStyle *CPackageStandard::getStyle(IStyle *style)
		{
			for (auto pos = m_aStyles.begin(); pos != m_aStyles.end(); pos++)
				if ((*pos)->getStyle() == style)
					return *pos;
			return nullptr;
		}
	#pragma endregion

	#pragma region Helpers
		IPackageService *CPackageStandard::QueryService()
		{
			if (!m_pService)
				m_pService = new CPackageStandardService(this);
			return m_pService;
		}

		IPackage *CPackageStandard::Create(IApplication *application)
		{
			if (application)
				Application = application;
			return new CPackageStandard();
		}
	#pragma endregion
	}
}