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
		CSysColorDialogPropertyList::CSysColorDialogPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyBool(this, component, L"AnyColor", false, nullptr,
				[](IClass *parent) {return cast<CSysColorDialog*>(parent)->isAnyColor(); },
				[](IClass *parent, const bool value) {return cast<CSysColorDialog*>(parent)->setAnyColor(value); }));
			Add(new CPropertyBool(this, component, L"FullOpen", false, nullptr,
				[](IClass *parent) {return cast<CSysColorDialog*>(parent)->isFullOpen(); },
				[](IClass *parent, const bool value) {return cast<CSysColorDialog*>(parent)->setFullOpen(value); }));
			Add(new CPropertyBool(this, component, L"PreventFullOpen", false, nullptr,
				[](IClass *parent) {return cast<CSysColorDialog*>(parent)->isPreventFullOpen(); },
				[](IClass *parent, const bool value) {return cast<CSysColorDialog*>(parent)->setPreventFullOpen(value); }));
			Add(new CPropertyBool(this, component, L"OnlySolidColors", false, nullptr,
				[](IClass *parent) {return cast<CSysColorDialog*>(parent)->isOnlySolidColors(); },
				[](IClass *parent, const bool value) {return cast<CSysColorDialog*>(parent)->setOnlySolidColors(value); }));
			Add(new CPropertyColor(this, component, L"Color", false, nullptr,
				[](IClass *parent) {return cast<CSysColorDialog*>(parent)->getColor(); },
				[](IClass *parent, const Color value) {return cast<CSysColorDialog*>(parent)->setColor(value); }));
		}
	}
}