// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IListItemCaption.h"
#include "Nitisa/Interfaces/IListItemOwner.h"

namespace nitisa
{
	namespace standard
	{
		class IImageList;

		class IListItemOwnerTreeViewLabel :public virtual IListItemOwner
		{
		protected:
			IListItemOwnerTreeViewLabel() = default;
			~IListItemOwnerTreeViewLabel() = default;
			IListItemOwnerTreeViewLabel(const IListItemOwnerTreeViewLabel &other) = delete;
			IListItemOwnerTreeViewLabel(IListItemOwnerTreeViewLabel &&other) = delete;
			IListItemOwnerTreeViewLabel &operator=(const IListItemOwnerTreeViewLabel &other) = delete;
			IListItemOwnerTreeViewLabel &operator=(IListItemOwnerTreeViewLabel &&other) = delete;
		public:
			virtual IImageList *getImageList() = 0; // Return image list
		};

		class IListItemTreeViewLabel :public virtual IListItemCaption
		{
		protected:
			IListItemTreeViewLabel() = default;
			~IListItemTreeViewLabel() = default;
			IListItemTreeViewLabel(const IListItemTreeViewLabel &other) = delete;
			IListItemTreeViewLabel(IListItemTreeViewLabel &&other) = delete;
			IListItemTreeViewLabel &operator=(const IListItemTreeViewLabel &other) = delete;
			IListItemTreeViewLabel &operator=(IListItemTreeViewLabel &&other) = delete;
		public:
			virtual IListItemTreeViewLabel *getSpecificItem(const int index) = 0; // Return item by index
			virtual int getIconIndex() = 0; // Return icon index

			virtual bool setIconIndex(const int value) = 0; // Set icon index

			virtual bool Add(const String &caption) = 0; // Add item
			virtual bool Add(IListItemTreeViewLabel *item) = 0; // Add item
			virtual bool Insert(const String &caption, const int before) = 0; // Insert item before specified one
			virtual bool Insert(IListItemTreeViewLabel *item, const int before) = 0; // Insert item before specified one
		};
	}
}