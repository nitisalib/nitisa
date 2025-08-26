// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "IComponent.h"

namespace nitisa
{
	class IListItem;
	class IListItemOwner;

	class IComponentItemTree: public virtual IComponent
	{
	protected:
		IComponentItemTree() = default;
		~IComponentItemTree() = default;
		IComponentItemTree(const IComponentItemTree &other) = delete;
		IComponentItemTree(IComponentItemTree &&other) = delete;
		IComponentItemTree &operator=(const IComponentItemTree &other) = delete;
		IComponentItemTree &operator=(IComponentItemTree &&other) = delete;
	public:
		virtual IListItem *getRootItem() = 0; // Return root item in item tree. This item has only function of storage for the tree of items. It is never displayed. Thus it could have only a simple implementation and could be different type from all other items

		virtual IListItemOwner *QueryListItemOwner() = 0; // Return list item owner. Use only this method to get list item owner
	};
}