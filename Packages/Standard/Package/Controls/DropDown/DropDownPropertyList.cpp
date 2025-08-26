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
		CDropDownPropertyList::CDropDownPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CCustomDropDownPropertyList(package, control, entity)
		{
			Delete(L"ActiveIndex");
			Add(new CPropertyInteger(this, control, L"ActiveIndex", false, nullptr,
				[](IClass *parent) {return cast<CDropDown*>(parent)->getActiveIndex(); },
				[](IClass *parent, const int value) {return cast<CDropDown*>(parent)->setActiveIndex(value); }));
		}
	}
}