// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "IComponent.h"

namespace nitisa
{
	class IListItem;
	class IListItemOwner;

	class IComponentItemList: public virtual IComponent
	{
	protected:
		IComponentItemList() = default;
		~IComponentItemList() = default;
		IComponentItemList(const IComponentItemList &other) = delete;
		IComponentItemList(IComponentItemList &&other) = delete;
		IComponentItemList &operator=(const IComponentItemList &other) = delete;
		IComponentItemList &operator=(IComponentItemList &&other) = delete;
	protected:
		virtual void SortItems() = 0; // Sort items
	public:
		virtual int getItemCount() = 0; // Return item count
		virtual IListItem *getItem(const int index) = 0; // Return item by index
		virtual int getItemIndex(IListItem *item) = 0; // Return item index in list or -1
		virtual bool isAcceptItem(IListItem *item) = 0; // Return whether it could accept specified list item to be added to list. By default return true

		virtual bool AddItem(IListItem *item) = 0; // Add item to list
		virtual bool InsertItem(IListItem *item, const int before) = 0; // Insert item in list before specified item index
		virtual bool DeleteItem(const int index) = 0; // Delete item from list by index
		virtual bool DeleteItem(IListItem *item) = 0; // Delete specified item from list
		virtual bool DeleteItems() = 0; // Delete all items form list

		virtual IListItemOwner *QueryListItemOwner() = 0; // Return list item owner. Use only this method to get list item owner
	};
}