// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Variant.h"
#include "Nitisa/Image/Image.h"
#include "Nitisa/Interfaces/IDialogBox.h"
#include "Nitisa/Package/Core/PackageControl.h"
#include <iostream>

namespace nitisa
{
	class IComponent;
	class IControl;
	class IEventList;
	class IListItem;
	class IPackage;
	class IPackageControlListener;
	class IPropertyList;

	namespace standard
	{
		class IMainMenu;

		class CDialogBoxMenuListItem;

		class CPackageMainMenu :public virtual IDialogBoxListener, public CPackageControl
		{
		private:
			struct CREATE_LIST_ITEM_PARAMS
			{
				IComponent *Component;
				IMainMenu *Control;
				IListItem *Parent;
				IListItem **Item;
				IPackageControlListener *Listener;
			};
		private:
			const Image m_cIcon;
			CREATE_LIST_ITEM_PARAMS m_sCreateListItemParams;
			bool m_bDialogBoxResized;

			void SaveListItem(Variant &dest, IListItem *item);
			void LoadListItem(const Variant &src, IListItem *parent);
			void ExportListItem(std::wofstream &f, const String &shift, const String &parent, IListItem *item, const int level);
			CDialogBoxMenuListItem *getDialogBox(IComponent *component);
		public:
			String getNamespace() override;
			String getCategory() override;
			String getClassName() override;
			String getTitle() override;
			String getDescription() override;
			String getReferenceUrl() override;
			const Image *getIcon() override;
			bool isVisible() override;
			bool isDisplayIcon() override;
			bool isInstance(IControl *control) override;
			bool isTransformable() override;

			IControl *Create(IPropertyList **properties, IEventList **events) override;
			IPropertyList *CreatePropertyList(IControl *control) override;
			IEventList *CreateEventList(IControl *control) override;
			bool CreateListItem(IComponent *component, IListItem *parent, IListItem **item, IPackageControlListener *listener = nullptr) override;
			void Save(Variant &dest, IPropertyList *properties, IEventList *events) override;
			void Load(const Variant &src, IPropertyList *properties, IEventList *events) override;
			void Export(std::wofstream &f, const String &shift, const String &owner, IPropertyList *properties, IEventList *events, const String &form, const String &dialog_box) override;

			void OnClose(IDialogBox *sender) override;
			void OnRestore(IDialogBox *sender) override;
			void OnMinimize(IDialogBox *sender) override;
			void OnMaximize(IDialogBox *sender) override;

			CPackageMainMenu(IPackage *package);
		};
	}
}