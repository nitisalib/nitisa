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
		CListBoxPropertyList::CListBoxPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CCustomListBoxPropertyList(package, control, entity)
		{
			Delete(L"ActiveIndex");

			Add(new CPropertyInteger(this, control, L"ActiveIndex", false, nullptr,
				[](IClass *parent) {return cast<CListBox*>(parent)->getActiveIndex(); },
				[](IClass *parent, const int value) {return cast<CListBox*>(parent)->setActiveIndex(value); }));
		}
	}
}