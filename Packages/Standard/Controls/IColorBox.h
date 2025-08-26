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
		class IColorBox :public virtual IControl, public virtual IComponentItemList
		{
		protected:
			IColorBox() = default;
			~IColorBox() = default;
			IColorBox(const IColorBox &other) = delete;
			IColorBox(IColorBox &&other) = delete;
			IColorBox &operator=(const IColorBox &other) = delete;
			IColorBox &operator=(IColorBox &&other) = delete;
		public:
			virtual IListItemColor *getItem(const int index) = 0; // Return item by index
			virtual int getActiveIndex() = 0; // Return selected item index

			virtual bool setActiveIndex(const int value) = 0; // Select item

			virtual bool Add(IListItemColor *item) = 0; // Add item
			virtual bool Insert(IListItemColor *item, const int before) = 0; // Insert item before specified one
			virtual bool Delete(const int index) = 0; // Delete item by index
			virtual bool Clear() = 0; // Delete all items

			virtual bool Open() = 0; // Open list
			virtual bool Close() = 0; // Close list
		};
	}
}