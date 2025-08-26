// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../../../ListItems/MenuRadioButton/ListItemMenuRadioButton.h"
#include "../Menu/ListItemMenuPropertyList.h"

namespace nitisa
{
	class IListItem;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CListItemMenuRadioButtonPropertyList :public CListItemMenuPropertyList
		{
		private:
			static StringArray StateItems();
			static CListItemMenuRadioButton::State StringToState(const String &state);
		public:
			CListItemMenuRadioButtonPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity);
		};
	}
}