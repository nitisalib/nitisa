// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Package/PropertyLists/ListItemPropertyList.h"

namespace nitisa
{
	class IListItem;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CListItemMultiButtonPropertyList :public CListItemPropertyList
		{
		public:
			CListItemMultiButtonPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity);
		};
	}
}