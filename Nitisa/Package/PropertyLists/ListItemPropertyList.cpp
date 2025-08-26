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
	CListItemPropertyList::CListItemPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity) :CPropertyList(package, listitem, entity)
	{
		Add(new CPropertyString(this, listitem, L"Name", false, nullptr,
			[](IClass *parent) { return cast<CListItem*>(parent)->Name; },
			[](IClass *parent, const String value) {return cast<CListItem*>(parent)->setName(value); }));
		Add(new CPropertyBool(this, listitem, L"Visible", false, nullptr,
			[](IClass *parent) { return cast<CListItem*>(parent)->isVisible(); },
			[](IClass *parent, const bool value) {return cast<CListItem*>(parent)->setVisible(value); }));
		Add(new CPropertyBool(this, listitem, L"Enabled", false, nullptr,
			[](IClass *parent) { return cast<CListItem*>(parent)->isEnabled(); },
			[](IClass *parent, const bool value) {return cast<CListItem*>(parent)->setEnabled(value); }));
		Add(new CPropertyBool(this, listitem, L"Selected", false, nullptr,
			[](IClass *parent) { return cast<CListItem*>(parent)->isSelected(); },
			[](IClass *parent, const bool value) {return cast<CListItem*>(parent)->setSelected(value); }));
		Add(new CPropertyBool(this, listitem, L"Active", false, nullptr,
			[](IClass *parent) { return cast<CListItem*>(parent)->isActive(); },
			[](IClass *parent, const bool value) {return cast<CListItem*>(parent)->setActive(value); }));
	}
}