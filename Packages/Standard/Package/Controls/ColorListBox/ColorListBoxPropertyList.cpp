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
		CColorListBoxPropertyList::CColorListBoxPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CCustomListBoxPropertyList(package, control, entity)
		{
			Delete(L"ActiveIndex");
			Add(new CPropertyBool(this, control, L"HasStandardColors", false,
				[](IClass *parent) {return cast<CColorListBox*>(parent)->isCustomItems(); },
				[](IClass *parent) {return cast<CColorListBox*>(parent)->hasStandardColors(); },
				[](IClass *parent, const bool value) {return cast<CColorListBox*>(parent)->setStandardColors(value); }))
				->setAffectItems(true);
			Add(new CPropertyBool(this, control, L"HasExtendedColors", false,
				[](IClass *parent) {return cast<CColorListBox*>(parent)->isCustomItems(); },
				[](IClass *parent) {return cast<CColorListBox*>(parent)->hasExtendedColors(); },
				[](IClass *parent, const bool value) {return cast<CColorListBox*>(parent)->setExtendedColors(value); }))
				->setAffectItems(true);
			Add(new CPropertyBool(this, control, L"HasNoneColor", false,
				[](IClass *parent) {return cast<CColorListBox*>(parent)->isCustomItems(); },
				[](IClass *parent) {return cast<CColorListBox*>(parent)->hasNoneColor(); },
				[](IClass *parent, const bool value) {return cast<CColorListBox*>(parent)->setNoneColor(value); }))
				->setAffectItems(true);
			Add(new CPropertyInteger(this, control, L"ActiveIndex", false, nullptr,
				[](IClass *parent) {return cast<CColorListBox*>(parent)->getActiveIndex(); },
				[](IClass *parent, const int value) {return cast<CColorListBox*>(parent)->setActiveIndex(value); }));
		}
	}
}