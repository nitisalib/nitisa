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
		CFormMaskPropertyList::CFormMaskPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyMask(this, form, L"Value", false, nullptr,
				[](IClass *parent) {return cast<CFormMask*>(parent)->getValue(); },
				[](IClass *parent, const unsigned int value) {return cast<CFormMask*>(parent)->setValue(value); }));
		}
	}
}