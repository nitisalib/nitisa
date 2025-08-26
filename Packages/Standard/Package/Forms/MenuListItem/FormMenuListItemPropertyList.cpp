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
		CFormMenuListItemPropertyList::CFormMenuListItemPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyInteger(this, form, L"ItemTypeIndex", false, nullptr,
				[](IClass *parent) {return cast<CFormMenuListItem*>(parent)->getItemTypeIndex(); },
				[](IClass *parent, const int value) {return cast<CFormMenuListItem*>(parent)->setItemTypeIndex(value); }))
				->setMin(0)->setMax(3);
			Add(new CPropertyString(this, form, L"ItemCaption", false, nullptr,
				[](IClass *parent) {return cast<CFormMenuListItem*>(parent)->getItemCaption(); },
				[](IClass *parent, const String value) {return cast<CFormMenuListItem*>(parent)->setItemCaption(value); }));
		}
	}
}