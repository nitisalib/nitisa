// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		CFormSelectListItemPropertyList::CFormSelectListItemPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyInteger(this, form, L"ItemTypeIndex", false, nullptr,
				[](IClass *parent) {return cast<CFormSelectListItem*>(parent)->getItemTypeIndex(); },
				[](IClass *parent, const int value) {return cast<CFormSelectListItem*>(parent)->setItemTypeIndex(value); }))
				->setMin(0)->setMax(3);
			Add(new CPropertyString(this, form, L"ItemCaption", false, nullptr,
				[](IClass *parent) {return cast<CFormSelectListItem*>(parent)->getItemCaption(); },
				[](IClass *parent, const String value) {return cast<CFormSelectListItem*>(parent)->setItemCaption(value); }));
		}
	}
}