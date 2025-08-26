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
#include "../ListItems/IListItemLabel.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	namespace standard
	{
		class IListBox :public virtual IControl, public virtual IComponentItemList
		{
		protected:
			IListBox() = default;
			~IListBox() = default;
			IListBox(const IListBox &other) = delete;
			IListBox(IListBox &&other) = delete;
			IListBox &operator=(const IListBox &other) = delete;
			IListBox &operator=(IListBox &&other) = delete;
		public:
			virtual IListItemLabel *getItem(const int index) = 0; // Return item by index
			virtual int getActiveIndex() = 0; // Return active item index

			virtual bool setActiveIndex(const int value) = 0; // Set active item

			virtual bool Add(IListItemLabel *item) = 0; // Add item
			virtual bool Insert(IListItemLabel *item, const int before) = 0; // Insert item before specified one
			virtual bool Delete(const int index) = 0; // Delete item by index
			virtual bool Clear() = 0; // Delete all items
		};
	}
}