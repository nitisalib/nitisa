// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
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
		CListItemStatusPanelPropertyList::CListItemStatusPanelPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity) :
			CListItemPropertyList(package, listitem, entity)
		{
			Add(new CPropertyFloat(this, listitem, L"Width", false, nullptr,
				[](IClass *parent) {return cast<CListItemStatusPanel*>(parent)->getWidth(); },
				[](IClass *parent, const float value) {return cast<CListItemStatusPanel*>(parent)->setWidth(value); }));
		}
	}
}