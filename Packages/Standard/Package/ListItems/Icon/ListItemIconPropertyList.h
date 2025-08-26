// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/ListItemPropertyList.h"
#include "../../../ListItems/Icon/ListItemIcon.h"

namespace nitisa
{
	class IListItem;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CListItemIconPropertyList :public CListItemPropertyList
		{
		private:
			static StringArray StateItems();
			static CListItemIcon::State StringToState(const String &state);
		public:
			CListItemIconPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity);
		};
	}
}