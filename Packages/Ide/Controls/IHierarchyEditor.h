// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IControl.h"
#include "Nitisa/Interfaces/IComponentItemTree.h"
#include "Standard/ListItems/IListItemTreeViewLabel.h"

namespace nitisa
{
	class IComponent;
	class IControl;
	class IListItem;
	class IPropertyList;

	namespace ide
	{
		class IListItemHierarchyEditor :public virtual standard::IListItemTreeViewLabel
		{
		protected:
			IListItemHierarchyEditor() = default;
			~IListItemHierarchyEditor() = default;
			IListItemHierarchyEditor(const IListItemHierarchyEditor &other) = delete;
			IListItemHierarchyEditor(IListItemHierarchyEditor &&other) = delete;
			IListItemHierarchyEditor &operator=(const IListItemHierarchyEditor &other) = delete;
			IListItemHierarchyEditor &operator=(IListItemHierarchyEditor &&other) = delete;
		public:
			virtual IComponent *getAssignedComponent() = 0; // Return assigned component
			virtual IControl *getAssignedControl() = 0; // Return assigned control
			virtual IListItem *getAssignedListItem() = 0; // Return assigned list item
			virtual IPropertyList *getPropertyList() = 0; // Return property list

			virtual void setPropertyList(IPropertyList *value) = 0; // Assign property list
		};

		class IHierarchyEditor :public virtual IControl, public virtual IComponentItemTree
		{
		protected:
			IHierarchyEditor() = default;
			~IHierarchyEditor() = default;
			IHierarchyEditor(const IHierarchyEditor &other) = delete;
			IHierarchyEditor(IHierarchyEditor &&other) = delete;
			IHierarchyEditor &operator=(const IHierarchyEditor &other) = delete;
			IHierarchyEditor &operator=(IHierarchyEditor &&other) = delete;
		public:
			virtual int getItemCount() = 0; // Return item count
			virtual IListItemHierarchyEditor *getItem(const int index) = 0; // Return item by index

			virtual IListItemHierarchyEditor *Add(IListItemHierarchyEditor *item) = 0; // Add item
			virtual IListItemHierarchyEditor *Add(const String &caption, IComponent *component, IControl *control, IListItem *item) = 0; // Add item
			virtual IListItemHierarchyEditor *Add(const String &caption, IComponent *component, IControl *control, IListItem *item, IControl *parent, const bool unfold) = 0; // Add item
			virtual bool Delete(const int index) = 0; // Delete item by index
			virtual bool Clear() = 0; // Delete all items
		};
	}
}