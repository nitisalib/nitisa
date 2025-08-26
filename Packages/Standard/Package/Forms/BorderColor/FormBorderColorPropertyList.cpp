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
		CFormBorderColorPropertyList::CFormBorderColorPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyBorderColor(this, form, L"Value", false, nullptr,
				[](IClass *parent) {return cast<CFormBorderColor*>(parent)->getValue(); },
				[](IClass *parent, const BorderColor value) {return cast<CFormBorderColor*>(parent)->setValue(value); }));
		}
	}
}