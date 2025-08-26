// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/CloseAction.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Variant.h"
#include "Nitisa/Math/Rect.h"
#include "Nitisa/Package/Interfaces/IPackageComponentListener.h"
#include "Nitisa/Package/Interfaces/IPackageControlListener.h"
#include "../../Core/Types.h"
#include "../Empty/FormEmpty.h"
#include "IFormMain.h"
#include <vector>
#ifdef VS_INTEGRATION
#include <Windows.h>
#endif

namespace nitisa
{
	class IClass;
	class IComponent;
	class IControl;
	class IDialogBox;
	class IEventList;
	class IFormService;
	class IListItem;
	class IPackageComponent;
	class IPackageControl;
	class IPackageEntity;
	class IPropertyList;

	namespace standard
	{
		class CSpeedButton;
		class CTabSheet;
	}

	namespace ide
	{
		class IFormEditor;
		class IEventEditor;
		class IListItemHierarchyEditor;
		class IPropertyEditor;
	}

	namespace fb
	{
		class IExporter;
		class ISaver;
		class ILoader;

		class CComponentList;
		class CControlList;
		class CFormMainService;
	#if defined(VS_INTEGRATION) || defined(USE_DIALOGBOXES)
		class CDialogBoxConfiguration;
	#endif

		class CFormMain :public IFormMain
		{
			friend CFormMainService;
		private:
			class CPackageComponentListener :public virtual IPackageComponentListener
			{
			private:
				CFormMain *m_pForm;
			public:
				ide::IListItemHierarchyEditor *m_pActive;

				void OnCreateListItem(IPackageComponent *sender, IListItem *parent, IListItem *item) override;

				CPackageComponentListener(CFormMain *form);
			};

			class CPackageControlListener :public virtual IPackageControlListener
			{
			private:
				CFormMain *m_pForm;
			public:
				ide::IListItemHierarchyEditor *m_pActive;
				CONTROL_INFO *m_pInfo;
				CONTROL_INFO m_sChild;

				void OnCreateChild(IPackageControl *sender, IControl *parent, IControl *control) override;
				void OnCreateListItem(IPackageControl *sender, IListItem *parent, IListItem *item) override;

				CPackageControlListener(CFormMain *form);
			};

			struct FORMVIEW_LAYOUT
			{
				String Title;
				String FileName;
			};
		private:
			static const int ICON_COMPONENT{ 19 };
			static const int ICON_CONTROL{ 20 };
			static const int ICON_LISTITEM{ 21 };

			CFormEmpty m_cFormEmpty;
			IPropertyList *m_pFormPropertyList;
			IEventList *m_pFormEventList;

			IFormService *m_pService;
			String m_sFileName;
			bool m_bIsModified;
			bool m_bIgnoreDeselectListItemsInHierarchy;
			bool m_bIgnoreAttach;
			CComponentList *m_pComponents;
			CControlList *m_pControls;
			IExporter *m_pExporterForm;
			IExporter *m_pExporterDialogBox;
			ISaver *m_pSaver;
			ILoader *m_pLoaderDefault;
			bool m_bSettingsWidgetsInited;
			CPackageComponentListener m_cPackageComponentListener;
			CPackageControlListener m_cPackageControlListener;

		#if defined(VS_INTEGRATION) || defined(USE_DIALOGBOXES)
			CDialogBoxConfiguration *m_pDialogBoxConfiguration;
		#endif

			std::vector<FORMVIEW_LAYOUT> m_aFormViewLayouts;
			int m_iFormViewLayout;

			// SpeedButton callbacks
			static void SpeedButton_OnDown(IControl *sender);

			// EmptyForm callbacks
			static void EmptyForm_OnStyleChange(IForm *sender);
			static void EmptyForm_OnFontChange(IForm *sender);
			static void EmptyForm_OnBackgroundChange(IForm *sender);
			static void EmptyForm_OnPaddingChange(IForm *sender);

			// Loading callbacks
			static void OnLoadComponent(IForm *sender, COMPONENT_INFO *info);
			static void OnLoadControl(IForm *sender, CONTROL_INFO *info);

		#if defined(VS_INTEGRATION) || defined(USE_DIALOGBOXES)
			// Dialog box callbacks
			static void DialogBoxConfiguration_OnClose(IDialogBox *sender, CloseAction &action);
		#endif

			// Initialization
			void LoadFormViewLayouts();
			void InitInterface();
			void InitPackages();
			void InitSettingsWidgets();

			// Helpers
			standard::CTabSheet *FindTabSheet(const String &caption);
			void UndownSpeedButtons(const bool skip_active);
			standard::CSpeedButton *FindDownSpeedButton();
			void HierarchyAddItems(IComponent *component, const bool clear);
			void HierarchyAddItems(IComponent *component, IControl *control, ide::IListItemHierarchyEditor *parent_h, IListItem *parent);
			void SetDefaultFormViewLayout();
			void NotifyOnComponentAttach(IComponent *component);
			void NotifyOnControlAttach(IControl *control);
			String BuildHint(IPackageEntity *entity);
			String BuildHintPlatforms(IPackageEntity *entity);
			void ShowInitializationStatus();

			// Settings
			void LoadSettings();
			void SaveSettings();
			void ApplySettings();

			// Actions
			void ActionNew();
			void ActionSave(const bool prompt);
			void ActionOpen();

			// Create events
			void OnCreateListItem(IListItem *child, ide::IListItemHierarchyEditor *active);
			void OnCreateChild(CONTROL_INFO *info, IControl *control, ide::IListItemHierarchyEditor *active);
		protected:
			// Form events
			void FormMain_OnKeyDown(IForm *sender, const MessageKey &m) override;
			void FormMain_OnDestroy(IForm *sender) override;
			void FormMain_OnClose(IForm *sender, CloseAction &action) override;

			// Update timer events
			void TimerCheckUpdate_OnTimer(IComponent *sender) override;

			// Icon buttons events
			void IconButtonNew_OnClick(IControl *sender) override;
			void IconButtonOpen_OnClick(IControl *sender) override;
			void IconButtonSave_OnClick(IControl *sender) override;
			void IconButtonSaveAs_OnClick(IControl *sender) override;
			void IconButtonConfiguration_OnClick(IControl *sender) override;
			void IconButtonFoldAll_OnClick(IControl *sender) override;
			void IconButtonUnfoldAll_OnClick(IControl *sender) override;
			void IconButtonAdd_OnClick(IControl *sender) override;
			void IconButtonDelete_OnClick(IControl *sender) override;
			void IconButtonUp_OnClick(IControl *sender) override;
			void IconButtonDown_OnClick(IControl *sender) override;

			// Hierarchy editor events
			void HierarchyEditor_OnKeyDown(IControl *sender, const MessageKey &m, bool &processed) override;
			void HierarchyEditor_OnSelectItem(IControl *sender, IListItem *item) override;
			void HierarchyEditor_OnDeselectItem(IControl *sender, IListItem *item) override;
			void HierarchyEditor_OnActivateItem(IControl *sender, IListItem *item) override;
			void HierarchyEditor_OnDeactivateItem(IControl *sender, IListItem *item) override;
			void HierarchyEditor_OnMovingSelection(IControl *sender, IListItem *dest) override;
			void HierarchyEditor_OnMoveSelection(IControl *sender, IListItem *dest) override;
			
			// Property editor events
			void PropertyEditor_OnPropertyChange(ide::IPropertyEditor *sender, IProperty *property, IPropertyList *property_list, IClass *parent) override;
			
			// Event editor events
			void EventEditor_OnEventChange(ide::IEventEditor *sender, IEvent *event, IEventList *event_list, IClass *parent) override;
			
			// Form editor events
			void FormEditor_OnResize(IControl *sender) override;
			void FormEditor_OnSelectControl(ide::IFormEditor *sender, IControl *control) override;
			void FormEditor_OnDeselectControl(ide::IFormEditor *sender, IControl *control) override;
			void FormEditor_OnSelectComponent(ide::IFormEditor *sender, IComponent *component) override;
			void FormEditor_OnDeselectComponent(ide::IFormEditor *sender, IComponent *component) override;
			void FormEditor_OnCheckComponentAllowed(ide::IFormEditor *sender, IComponent *component, bool &allowed) override;
			void FormEditor_OnComponentTransform(ide::IFormEditor *sender, IComponent *component) override;
			void FormEditor_OnControlTransform(ide::IFormEditor *sender, IComponent *component) override;
			void FormEditor_OnControlResize(ide::IFormEditor *sender, IComponent *component) override;
			void FormEditor_OnMouseDown(ide::IFormEditor *sender, const MessageMouse &m, bool &processed) override;
			
			// Layout dropdown events
			void DropDownLayout_OnSelect(IControl *sender, const int index) override;
		public:
		#ifdef VS_INTEGRATION
			void *UserData;
			void(*OnUpdateIsModified)(CFormMain *sender, const bool is_modified);
		#endif
			bool setInputControl(IControl *value) override;
			bool setBorderWidth(const RectF &value) override;

			IFormService *QueryService() override;

		#ifndef VS_INTEGRATION
			CFormMain();
		#else
			CFormMain(HWND parent, HWND *window, const Rect &area);
		#endif
			~CFormMain() override;

			void UpdateIsModified(const bool is_modified);
			String Save(const String &filename);
			void Load(Variant &data, const String &filename);
			void Export();
		};

		extern CFormMain *FormMain;
	}
}