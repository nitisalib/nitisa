// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "../Interfaces/IBuiltInControl.h"
#include "../Math/PointF.h"

namespace nitisa
{
	class IBuiltInScroll;
	class IBuiltInTextInput;
	class IListItem;
	class IListItemOwner;

	class IBuiltInDropDown :public virtual IBuiltInControl
	{
	protected:
		IBuiltInDropDown() = default;
		~IBuiltInDropDown() = default;
		IBuiltInDropDown(const IBuiltInDropDown &other) = delete;
		IBuiltInDropDown(IBuiltInDropDown &&other) = delete;
		IBuiltInDropDown &operator=(const IBuiltInDropDown &other) = delete;
		IBuiltInDropDown &operator=(IBuiltInDropDown &&other) = delete;
	public:
		using FCompare = bool(*)(IListItem *a, IListItem *b); // Item comparison function prototype
		using FGetItemText = String(*)(IListItem *item); // Prototype of function which returns name or caption of specified item
		using FSearch = int(*)(IBuiltInDropDown *dropdown, const String &search); // Search function prototype. Should return item index started/having "search" in name/caption
	public:
		virtual int getItemCount() = 0; // Return item count
		virtual IListItem *getItem(const int index) = 0; // Return item by index
		virtual int getItemIndex(IListItem *item) = 0; // Return item index or -1
		virtual bool isEditable() = 0; // Whether drop down has input area or not
		virtual bool isOpened() = 0; // Whether drop down is opened(item list is shown)
		virtual bool isSortable() = 0; // Whether drop down items should be ordered
		virtual String getText() = 0; // Return currently displayed text
		virtual int getActiveIndex() = 0; // Return index of active item or -1
		virtual FCompare getCompareFunc() = 0; // Return items compare function
		virtual FGetItemText getItemTextFunc() = 0; // Return receiving item caption function
		virtual FSearch getSearchFunc() = 0; // Return search function
		virtual PointF getMousePosition() = 0; // Return mouse pointer coordinates in drop down coordinate system
		virtual IBuiltInTextInput *getTextInput() = 0; // Return associated text input
		virtual bool isLoopActiveItemOnDoubleClick() = 0; // Return whether active item will be changed to the next one on double click in non-editable mode

		virtual bool setTextInput(IBuiltInTextInput *value) = 0; // Set another text input
		virtual bool setScroll(IBuiltInScroll *value) = 0; // Set another scroll
		virtual bool setEditable(const bool value) = 0; // Set whether drop down has text input or not
		virtual bool setSortable(const bool value) = 0; // Set whether items should be ordered
		virtual bool setText(const String &value) = 0; // Set currently displayed text
		virtual bool setActiveIndex(const int value) = 0; // Set active item by index
		virtual bool setCompareFunc(FCompare value) = 0; // Set item comparison function
		virtual bool setGetItemTextFunc(FGetItemText value) = 0; // Set receiving item caption function
		virtual bool setSearchFunc(FSearch value) = 0; // Set search function
		virtual bool setLoopActiveItemOnDoubleClick(const bool value) = 0; // Set whether active item will be changed to the next one on double click in non-editable mode

		virtual bool AddItem(IListItem *item) = 0; // Add item
		virtual bool InsertItem(IListItem *item, const int before) = 0; // Insert item before specified one
		virtual bool DeleteItem(const int index) = 0; // Delete item by index
		virtual bool DeleteItem(IListItem *item) = 0; // Delete specified item
		virtual bool DeleteItems() = 0; // Delete all items
		virtual bool MoveItem(IListItem *item, const int before) = 0; // Move(if possible) specified item in position before specified one

		virtual bool Open() = 0; // Open drop down(show item list)
		virtual bool Close() = 0; // Close drop down(hide item list)
		virtual IListItemOwner *QueryListItemOwner() = 0; // Return list item owner
	};
}