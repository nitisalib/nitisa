// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "../Math/PointF.h"
#include "IClass.h"

namespace nitisa
{
	class IControl;
	class IFont;
	class IRenderer;
	class IListItemService;

	// Common interface for all items for controls that handle item lists(like, PopupMenu, MainMemu, DropDown, ListBox)
	// Hovered state is used as called - for identifying if item is under mouse pointer
	// Active state is usually used for identification the only one active item(it is used in menus and lists)
	class IListItem :public virtual IClass
	{
	protected:
		IListItem() = default;
		~IListItem() = default;
		IListItem(const IListItem &other) = delete;
		IListItem(IListItem &&other) = delete;
		IListItem &operator=(const IListItem &other) = delete;
		IListItem &operator=(IListItem &&other) = delete;
	public:
		virtual IListItem *getParent() = 0; // Return parent item
		virtual PointF getSize() = 0; // Return size
		virtual PointF getPosition() = 0; // Return position relative to parent
		virtual int getItemCount(const bool total = false) = 0; // Return child item count
		virtual IListItem *getItem(const int index) = 0; // Return child item by index
		virtual IListItem *getItem(const String &name) = 0; // Return child item by name
		virtual IListItem *getItem(const PointF &position) = 0; // Return child(or this one) item at specified position
		virtual int getItemIndex(IListItem *item) = 0; // Return item index or -1
		virtual IFont *getFont() = 0; // Return font if list item has one, otherwise return nullptr and default (control's) font will be used
		virtual bool isVisible() = 0; // Return visibility flag value
		virtual bool isEnabled() = 0; // Return enabled/disabled flag value
		virtual bool isHovered() = 0; // Return hovered flag value
		virtual bool isSelected() = 0; // Return selection flag value
		virtual bool isActive() = 0; // Return active/inactive flag value
		virtual bool hasItem(IListItem *item) = 0; // Return if item exists in children hierarchy
		virtual bool isAcceptItems() = 0; // Whether other items can be added to this one
		virtual bool isAcceptItem(IListItem *item) = 0; // Whether specified item can be added to this one. By default return same as isAcceptItems(). Overwrite to allow only specific type items

		virtual bool setVisible(const bool value) = 0; // Change visibility flag and notify owner via OnShow and OnHide notifications
		virtual bool setEnabled(const bool value) = 0; // Change availability flag an notify owner via OnEnable and OnDisable notifications
		virtual bool setSelected(const bool value) = 0; // Change selection flag and notify owner via OnSelect and OnDeselect notifications
		virtual bool setActive(const bool value) = 0; // Change active/inactive state and notify owner via OnActive and OnDeactivate notifications

		virtual bool AddItem(IListItem *item) = 0; // Add child item
		virtual bool InsertItem(IListItem *item, const int before) = 0; // Insert child item before specified position
		virtual bool DeleteItem(const int index) = 0; // Delete child item by index
		virtual bool DeleteItem(IListItem *item) = 0; // Delete specified child item
		virtual bool DeleteItems() = 0; // Delete all child items
		virtual bool DetachItem(IListItem *item) = 0; // Delete child item from list but don't destroy it

		virtual IListItem *Clone() = 0; // Should create copy of this item with empty parent and owner
		virtual bool Copy(IListItem *dest) = 0; // Should copy properties to specified destination list item

		virtual IListItemService *QueryService() = 0; // Return service interface
		virtual void Release() = 0; // Destroy instance

		virtual bool BringToFront() = 0; // Change item position in list or items on parent item/control
		virtual bool BringUp() = 0; // Change item position in parent list to 1 position up
		virtual bool BringDown() = 0; // Change item position in parent list to 1 position down
		virtual bool BringBefore(IListItem *item) = 0; // Change item position in parent list setting it before specified item
		virtual bool BringBefore(const int index) = 0; // Change item position in parent list setting it before specified index
		virtual bool BringAfter(IListItem *item) = 0; // Change item position in parent list setting it after specified item
		virtual bool BringAfter(const int index) = 0; // Change item position in parent list setting it after specified index
	};
}