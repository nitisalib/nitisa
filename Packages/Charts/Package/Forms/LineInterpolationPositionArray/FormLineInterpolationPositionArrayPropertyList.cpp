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
	namespace charts
	{
		CFormLineInterpolationPositionArrayPropertyList::CFormLineInterpolationPositionArrayPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyLineInterpolationPositionArray(this, form, L"Value", false, nullptr,
				[](IClass *parent) {return cast<CFormLineInterpolationPositionArray*>(parent)->getValue(); },
				[](IClass *parent, const std::vector<LineInterpolationPosition> value) {return cast<CFormLineInterpolationPositionArray*>(parent)->setValue(value); }));
			Add(new CPropertyInteger(this, form, L"MinCount", false, nullptr,
				[](IClass *parent) {return cast<CFormLineInterpolationPositionArray*>(parent)->getMinCount(); },
				[](IClass *parent, const int value) {return cast<CFormLineInterpolationPositionArray*>(parent)->setMinCount(value); }))
				->setMin(0);
		}
	}
}