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
#include "Nitisa/Interfaces/IComponentItemList.h"
#include "../ListItems/IListItemLabel.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	namespace standard
	{
		class IDropDown :public virtual IControl, public virtual IComponentItemList
		{
		protected:
			IDropDown() = default;
			~IDropDown() = default;
			IDropDown(const IDropDown &other) = delete;
			IDropDown(IDropDown &&other) = delete;
			IDropDown &operator=(const IDropDown &other) = delete;
			IDropDown &operator=(IDropDown &&other) = delete;
		public:
			virtual IListItemLabel *getItem(const int index) = 0; // Return item by index
			virtual String getText() = 0; // Return text
			virtual int getActiveIndex() = 0; // Return active item index

			virtual bool setText(const String &value) = 0; // Set text
			virtual bool setActiveIndex(const int value) = 0; // Set active item

			virtual bool Add(IListItemLabel *item) = 0; // Add item
			virtual bool Insert(IListItemLabel *item, const int before) = 0; // Insert item before specified one
			virtual bool Delete(const int index) = 0; // Delete item by index
			virtual bool Clear() = 0; // Delete all items

			virtual bool Open() = 0; // Open list
			virtual bool Close() = 0; // Close list
		};
	}
}