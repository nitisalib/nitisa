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
#include "../ListItems/IListItemColor.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	namespace standard
	{
		class IColorListBox :public virtual IControl, public virtual IComponentItemList
		{
		protected:
			IColorListBox() = default;
			~IColorListBox() = default;
			IColorListBox(const IColorListBox &other) = delete;
			IColorListBox(IColorListBox &&other) = delete;
			IColorListBox &operator=(const IColorListBox &other) = delete;
			IColorListBox &operator=(IColorListBox &&other) = delete;
		public:
			virtual IListItemColor *getItem(const int index) = 0; // Return item by index
			virtual int getActiveIndex() = 0; // Return active item index

			virtual bool setActiveIndex(const int value) = 0; // Set active item

			virtual bool Add(IListItemColor *item) = 0; // Add item
			virtual bool Insert(IListItemColor *item, const int before) = 0; // Insert item before specified one
			virtual bool Delete(const int index) = 0; // Delete item by index
			virtual bool Clear() = 0; // Delete all items
		};
	}
}