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
		CFormColorArrayPropertyList::CFormColorArrayPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyColorArray(this, form, L"Value", false, nullptr,
				[](IClass *parent) {return cast<CFormColorArray*>(parent)->getValue(); },
				[](IClass *parent, const ColorArray value) {return cast<CFormColorArray*>(parent)->setValue(value); }));
			Add(new CPropertyInteger(this, form, L"MinCount", false, nullptr,
				[](IClass *parent) {return cast<CFormColorArray*>(parent)->getMinCount(); },
				[](IClass *parent, const int value) {return cast<CFormColorArray*>(parent)->setMinCount(value); }))
				->setMin(0);
		}
	}
}