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
#include "../../../ListItems/TreeViewLabel/ListItemTreeViewLabel.h"

namespace nitisa
{
	class IListItem;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CListItemTreeViewLabelPropertyList :public CListItemPropertyList
		{
		private:
			static StringArray StateItems();
			static CListItemTreeViewLabel::State StringToState(const String &state);
		public:
			CListItemTreeViewLabelPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity);
		};
	}
}