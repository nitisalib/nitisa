// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"
#include "Nitisa/Interfaces/IComponentItemList.h"
#include "../ListItems/IListItemCheckBox.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	namespace standard
	{
		class ICheckListBox :public virtual IControl, public virtual IComponentItemList
		{
		protected:
			ICheckListBox() = default;
			~ICheckListBox() = default;
			ICheckListBox(const ICheckListBox &other) = delete;
			ICheckListBox(ICheckListBox &&other) = delete;
			ICheckListBox &operator=(const ICheckListBox &other) = delete;
			ICheckListBox &operator=(ICheckListBox &&other) = delete;
		public:
			virtual IListItemCheckBox *getItem(const int index) = 0; // Return item count
			virtual int getActiveIndex() = 0; // Return active item index
			virtual bool isChecked(const int index) = 0; // Whether specified item is checked

			virtual bool setActiveIndex(const int value) = 0; // Set active item
			virtual bool setChecked(const int index, const bool value) = 0; // Set item checked/unchecked

			virtual bool Add(IListItemCheckBox *item) = 0; // Add item
			virtual bool Insert(IListItemCheckBox *item, const int before) = 0; // Insert item before specified one
			virtual bool Delete(const int index) = 0; // Delete item by index
			virtual bool Clear() = 0; // Delete all items
		};
	}
}