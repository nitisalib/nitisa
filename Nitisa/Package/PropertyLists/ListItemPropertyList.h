// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/PropertyList.h"

namespace nitisa
{
	class IListItem;
	class IPackage;
	class IPackageEntity;

	class CListItemPropertyList :public CPropertyList
	{
	public:
		CListItemPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity);
	};
}