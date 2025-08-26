// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Standard/Controls/TreeView/CustomTreeView.h"
#include "Standard/Controls/TreeView/CustomTreeViewListItemOwner.h"
#include "Standard/ListItems/IListItemTreeViewLabel.h"
#include "../IHierarchyEditor.h"
#include <vector>

namespace nitisa
{
	class IComponent;
	class IControl;
	class IForm;
	class IListItem;
	class IListItemOwner;

	namespace standard
	{
		class IImageList;
	}

	namespace ide
	{
		class CHierarchyEditorService;

		class CHierarchyEditor :public virtual IHierarchyEditor, public standard::CCustomTreeView
		{
			friend CHierarchyEditorService;
		private:
			class CListItemOwner :public virtual standard::IListItemOwnerTreeViewLabel, public standard::CCustomTreeViewListItemOwner
			{
			private:
				CHierarchyEditor *m_pEditor;
			public:
				standard::IImageList *getImageList() override;

				CListItemOwner(CHierarchyEditor *editor);
			};
		private:
			IListItemOwner *m_pOwner;
			standard::IImageList *m_pImageList;

			bool Add(IListItem *parent, IListItemHierarchyEditor *item, IControl *parent_control, const bool unfold);
			IListItemHierarchyEditor *Find(IListItem *parent, IListItem *item);
			IListItemHierarchyEditor *Find(IListItem *parent, IComponent *component, IControl *control);
			void CollectSelected(IListItem *parent, std::vector<IListItemHierarchyEditor*> &items);
			bool DeselectAllListItems(IListItem *parent);
			bool DeselectAll(IListItem *parent);
			bool DeleteSelected(IListItem *parent);
		protected:
			void BeforeRelease() override;
		public:
			int getItemCount() override;
			IListItemHierarchyEditor *getItem(const int index) override;

			IListItemHierarchyEditor *Add(IListItemHierarchyEditor *item) override;
			IListItemHierarchyEditor *Add(const String &caption, IComponent *component, IControl *control, IListItem *item) override;
			IListItemHierarchyEditor *Add(const String &caption, IComponent *component, IControl *control, IListItem *item, IControl *parent, const bool unfold) override;
			bool Delete(const int index) override;
			bool Clear() override;

			IListItemOwner *QueryListItemOwner() override;

			CHierarchyEditor();
			CHierarchyEditor(IControl *parent);
			CHierarchyEditor(IForm *parent);
			~CHierarchyEditor() override;

			standard::IImageList *getImageList(); // Return assigned image list

			bool setImageList(standard::IImageList *value); // Assign image list

			IListItemHierarchyEditor *Find(IComponent *component, IControl *control, IListItem *item); // Find item with assigned component, control, item
			bool DeleteEx(IComponent *component, IControl *control, IListItem *item); // Delete element with assigned component, control, item
			bool SelectEx(IComponent *component, IControl *control, IListItem *item, const bool selected, const bool active); // Select item
			bool isMovable(IListItemHierarchyEditor *target); // Check if item is movable. Only ItemLists of same level are selected, or only controls and/or components of same level are selected and target accept it
			bool isMovable(IListItemHierarchyEditor *target, std::vector<IListItemHierarchyEditor*> &items, bool &move_items); // Check if items are movable
			bool DeselectAllListItems(); // Deselect all list items
			bool DeselectAll();  // Deselect all items
			bool DeleteSelected(); // Delete all selected items
		};
	}
}