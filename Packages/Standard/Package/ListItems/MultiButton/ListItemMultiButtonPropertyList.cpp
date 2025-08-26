// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
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
		CListItemMultiButtonPropertyList::CListItemMultiButtonPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity) :
			CListItemPropertyList(package, listitem, entity)
		{
			Add(new CPropertyInteger(this, listitem, L"ImageIndexNormal", false, nullptr,
				[](IClass *parent) {return cast<CListItemMultiButton*>(parent)->getImageIndexNormal(); },
				[](IClass *parent, const int value) {return cast<CListItemMultiButton*>(parent)->setImageIndexNormal(value); }));
			Add(new CPropertyInteger(this, listitem, L"ImageIndexHovered", false, nullptr,
				[](IClass *parent) {return cast<CListItemMultiButton*>(parent)->getImageIndexHovered(); },
				[](IClass *parent, const int value) {return cast<CListItemMultiButton*>(parent)->setImageIndexHovered(value); }));
			Add(new CPropertyInteger(this, listitem, L"ImageIndexFocused", false, nullptr,
				[](IClass *parent) {return cast<CListItemMultiButton*>(parent)->getImageIndexFocused(); },
				[](IClass *parent, const int value) {return cast<CListItemMultiButton*>(parent)->setImageIndexFocused(value); }));
			Add(new CPropertyInteger(this, listitem, L"ImageIndexFocusedHovered", false, nullptr,
				[](IClass *parent) {return cast<CListItemMultiButton*>(parent)->getImageIndexFocusedHovered(); },
				[](IClass *parent, const int value) {return cast<CListItemMultiButton*>(parent)->setImageIndexFocusedHovered(value); }));
			Add(new CPropertyInteger(this, listitem, L"ImageIndexDown", false, nullptr,
				[](IClass *parent) {return cast<CListItemMultiButton*>(parent)->getImageIndexDown(); },
				[](IClass *parent, const int value) {return cast<CListItemMultiButton*>(parent)->setImageIndexDown(value); }));
			Add(new CPropertyInteger(this, listitem, L"ImageIndexDownHovered", false, nullptr,
				[](IClass *parent) {return cast<CListItemMultiButton*>(parent)->getImageIndexDownHovered(); },
				[](IClass *parent, const int value) {return cast<CListItemMultiButton*>(parent)->setImageIndexDownHovered(value); }));
			Add(new CPropertyInteger(this, listitem, L"ImageIndexDownFocused", false, nullptr,
				[](IClass *parent) {return cast<CListItemMultiButton*>(parent)->getImageIndexDownFocused(); },
				[](IClass *parent, const int value) {return cast<CListItemMultiButton*>(parent)->setImageIndexDownFocused(value); }));
			Add(new CPropertyInteger(this, listitem, L"ImageIndexDownFocusedHovered", false, nullptr,
				[](IClass *parent) {return cast<CListItemMultiButton*>(parent)->getImageIndexDownFocusedHovered(); },
				[](IClass *parent, const int value) {return cast<CListItemMultiButton*>(parent)->setImageIndexDownFocusedHovered(value); }));
			Add(new CPropertyInteger(this, listitem, L"ImageIndexActive", false, nullptr,
				[](IClass *parent) {return cast<CListItemMultiButton*>(parent)->getImageIndexActive(); },
				[](IClass *parent, const int value) {return cast<CListItemMultiButton*>(parent)->setImageIndexActive(value); }));
			Add(new CPropertyInteger(this, listitem, L"ImageIndexActiveHovered", false, nullptr,
				[](IClass *parent) {return cast<CListItemMultiButton*>(parent)->getImageIndexActiveHovered(); },
				[](IClass *parent, const int value) {return cast<CListItemMultiButton*>(parent)->setImageIndexActiveHovered(value); }));
			Add(new CPropertyInteger(this, listitem, L"ImageIndexInactive", false, nullptr,
				[](IClass *parent) {return cast<CListItemMultiButton*>(parent)->getImageIndexInactive(); },
				[](IClass *parent, const int value) {return cast<CListItemMultiButton*>(parent)->setImageIndexInactive(value); }));
			Add(new CPropertyInteger(this, listitem, L"ImageIndexInactiveHovered", false, nullptr,
				[](IClass *parent) {return cast<CListItemMultiButton*>(parent)->getImageIndexInactiveHovered(); },
				[](IClass *parent, const int value) {return cast<CListItemMultiButton*>(parent)->setImageIndexInactiveHovered(value); }));
			Add(new CPropertyInteger(this, listitem, L"ImageIndexDisabled", false, nullptr,
				[](IClass *parent) {return cast<CListItemMultiButton*>(parent)->getImageIndexDisabled(); },
				[](IClass *parent, const int value) {return cast<CListItemMultiButton*>(parent)->setImageIndexDisabled(value); }));
		}
	}
}