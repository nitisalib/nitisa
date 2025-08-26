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
		CFormMatrixPropertyList::CFormMatrixPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyMatrix(this, form, L"Value", false, nullptr,
				[](IClass *parent) {return cast<CFormMatrix*>(parent)->getValue(); },
				[](IClass *parent, const Mat4f value) {return cast<CFormMatrix*>(parent)->setValue(value); }));
		}
	}
}