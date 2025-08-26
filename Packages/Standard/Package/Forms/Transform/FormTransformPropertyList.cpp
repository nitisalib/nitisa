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
		CFormTransformPropertyList::CFormTransformPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyTransform(this, form, L"Value", false, nullptr,
				[](IClass *parent) {return cast<CFormTransform*>(parent)->getValue(); },
				[](IClass *parent, const Transform value) {return cast<CFormTransform*>(parent)->setValue(value); }));
		}
	}
}