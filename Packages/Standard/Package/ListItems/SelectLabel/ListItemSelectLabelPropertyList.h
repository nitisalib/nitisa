// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Label/ListItemLabelPropertyList.h"

namespace nitisa
{
	class IListItem;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CListItemSelectLabelPropertyList :public CListItemLabelPropertyList
		{
		public:
			CListItemSelectLabelPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity);
		};
	}
}