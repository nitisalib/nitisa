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
		CFormColorPropertyList::CFormColorPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyColor(this, form, L"Value", false, nullptr,
				[](IClass *parent) {return cast<CFormColor*>(parent)->getValue(); },
				[](IClass *parent, const Color value) {return cast<CFormColor*>(parent)->setValue(value); }));
		}
	}
}