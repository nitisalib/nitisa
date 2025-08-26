// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "IComponentService.h"

namespace nitisa
{
	class IListItem;

	class IComponentItemListService : public virtual IComponentService
	{
	protected:
		IComponentItemListService() = default;
		~IComponentItemListService() = default;
		IComponentItemListService(const IComponentItemListService &other) = delete;
		IComponentItemListService(IComponentItemListService &&other) = delete;
		IComponentItemListService &operator=(const IComponentItemListService &other) = delete;
		IComponentItemListService &operator=(IComponentItemListService &&other) = delete;
	public:
		virtual bool MoveItem(IListItem *item, const int before) = 0; // Change item position in list. Index should be in range 0..ItemCount, item should be child and it's index should not be equal to index
	};
}