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
#include "Nitisa/Math/PointF.h"

namespace nitisa
{
	class IListItem;

	namespace standard
	{
		class IPopupMenu :public virtual IControl, public virtual IComponentItemTree
		{
		protected:
			IPopupMenu() = default;
			~IPopupMenu() = default;
			IPopupMenu(const IPopupMenu &other) = delete;
			IPopupMenu(IPopupMenu &&other) = delete;
			IPopupMenu &operator=(const IPopupMenu &other) = delete;
			IPopupMenu &operator=(IPopupMenu &&other) = delete;
		public:
			virtual int getItemCount(const bool total = false) = 0; // Return item count(only direct or entire hierarchy)
			virtual IListItem *getItem(const int index) = 0; // Return item by index

			virtual bool Add(IListItem *item) = 0; // Add item
			virtual bool Insert(IListItem *item, const int before) = 0; // Insert item before specified one
			virtual bool Delete(const int index) = 0; // Delete item by index
			virtual bool Clear() = 0; // Delete all items

			virtual bool Show(const PointF &position) = 0; // Show at specified position
			virtual bool Hide() = 0; // Hide
		};
	}
}