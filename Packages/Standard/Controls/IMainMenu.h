// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"
#include "Nitisa/Interfaces/IComponentItemTree.h"

namespace nitisa
{
	class IListItem;

	namespace standard
	{
		class IMainMenu :public virtual IControl, public virtual IComponentItemTree
		{
		protected:
			IMainMenu() = default;
			~IMainMenu() = default;
			IMainMenu(const IMainMenu &other) = delete;
			IMainMenu(IMainMenu &&other) = delete;
			IMainMenu &operator=(const IMainMenu &other) = delete;
			IMainMenu &operator=(IMainMenu &&other) = delete;
		public:
			virtual int getItemCount(const bool total = false) = 0; // Return item count
			virtual IListItem *getItem(const int index) = 0; // Return item by index

			virtual bool Add(IListItem *item) = 0; // Add item
			virtual bool Insert(IListItem *item, const int before) = 0; // Insert item before specified one
			virtual bool Delete(const int index) = 0; // Delete item by index
			virtual bool Clear() = 0; // Delete all items
		};
	}
}