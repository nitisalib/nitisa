// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace standard
	{
		CListItemMenuSeparatorPropertyList::CListItemMenuSeparatorPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity) :
			CListItemMenuPropertyList(package, listitem, entity)
		{
			Delete(L"Enabled");
			Delete(L"Selected");
			Delete(L"Active");
			Delete(L"Hotkeys");

			Add(new CPropertyFloat(this, listitem, L"Height", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuSeparator*>(parent)->getHeight(); },
				[](IClass *parent, const float value) {return cast<CListItemMenuSeparator*>(parent)->setHeight(value); }))->
				setMin(0);
			Add(new CPropertyColor(this, listitem, L"Color", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuSeparator*>(parent)->getColor(); },
				[](IClass *parent, const Color value) {return cast<CListItemMenuSeparator*>(parent)->setColor(value); }));
		}
	}
}