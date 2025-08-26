// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../../../ListItems/MenuLabel/ListItemMenuLabel.h"
#include "../Menu/ListItemMenuPropertyList.h"

namespace nitisa
{
	class IListItem;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CListItemMenuLabelPropertyList :public CListItemMenuPropertyList
		{
		private:
			static StringArray StateItems();
			static CListItemMenuLabel::State StringToState(const String &state);
		public:
			CListItemMenuLabelPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity);
		};
	}
}