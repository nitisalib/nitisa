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
#include "Nitisa/Interfaces/IComponentItemTree.h"

namespace nitisa
{
	namespace standard
	{
		class IListItemTreeViewLabel;

		class ITreeView :public virtual IControl, public virtual IComponentItemTree
		{
		protected:
			ITreeView() = default;
			~ITreeView() = default;
			ITreeView(const ITreeView &other) = delete;
			ITreeView(ITreeView &&other) = delete;
			ITreeView &operator=(const ITreeView &other) = delete;
			ITreeView &operator=(ITreeView &&other) = delete;
		public:
			virtual int getItemCount() = 0; // Return item count
			virtual IListItemTreeViewLabel *getItem(const int index) = 0; // Return item by index

			virtual bool Add(IListItemTreeViewLabel *item) = 0; // Add item
			virtual bool Add(const String &caption) = 0; // Add item
			virtual bool Delete(const int index) = 0; // Delete item by index
			virtual bool Clear() = 0; // Delete all items
		};
	}
}