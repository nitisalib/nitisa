// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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

	class IBuiltInSelect :public virtual IBuiltInControl
	{
	protected:
		IBuiltInSelect() = default;
		~IBuiltInSelect() = default;
		IBuiltInSelect(const IBuiltInSelect &other) = delete;
		IBuiltInSelect(IBuiltInSelect &&other) = delete;
		IBuiltInSelect &operator=(const IBuiltInSelect &other) = delete;
		IBuiltInSelect &operator=(IBuiltInSelect &&other) = delete;
	public:
		virtual int getItemCount() = 0; // Return item count
		virtual IListItem *getItem(const int index) = 0; // Return item by index
		virtual int getItemIndex(IListItem *item) = 0; // Return item index or -1
		virtual bool isOpened() = 0; // Whether drop down is opened(item list is shown)
		virtual String getFilter() = 0; // Return currently active filter
		virtual int getActiveIndex() = 0; // Return index of active item or -1
		virtual PointF getMousePosition() = 0; // Return mouse pointer coordinates in drop down coordinate system
		virtual IBuiltInScroll *getScroll() = 0; // Return associated scroll
		virtual IBuiltInTextInput *getTextInput() = 0; // Return associated text input

		virtual bool setFilter(const String &value) = 0; // Set filter
		virtual bool setActiveIndex(const int value) = 0; // Set active item by index
		virtual bool setScroll(IBuiltInScroll *value) = 0; // Set another scroll
		virtual bool setTextInput(IBuiltInTextInput *value) = 0; // Set another text input

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