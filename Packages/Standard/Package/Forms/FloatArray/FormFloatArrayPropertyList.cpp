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
		CFormFloatArrayPropertyList::CFormFloatArrayPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyFloatArray(this, form, L"Value", false, nullptr,
				[](IClass *parent) {return cast<CFormFloatArray*>(parent)->getValue(); },
				[](IClass *parent, const FloatArray value) {return cast<CFormFloatArray*>(parent)->setValue(value); }));
			Add(new CPropertyInteger(this, form, L"MinCount", false, nullptr,
				[](IClass *parent) {return cast<CFormFloatArray*>(parent)->getMinCount(); },
				[](IClass *parent, const int value) {return cast<CFormFloatArray*>(parent)->setMinCount(value); }))
				->setMin(0);
			Add(new CPropertyBool(this, form, L"HasMin", false, nullptr,
				[](IClass *parent) {return cast<CFormFloatArray*>(parent)->hasMin(); },
				[](IClass *parent, const bool value) {return cast<CFormFloatArray*>(parent)->setHasMin(value); }));
			Add(new CPropertyBool(this, form, L"HasMax", false, nullptr,
				[](IClass *parent) {return cast<CFormFloatArray*>(parent)->hasMax(); },
				[](IClass *parent, const bool value) {return cast<CFormFloatArray*>(parent)->setHasMax(value); }));
			Add(new CPropertyFloat(this, form, L"Min", false, nullptr,
				[](IClass *parent) {return cast<CFormFloatArray*>(parent)->getMin(); },
				[](IClass *parent, const float value) {return cast<CFormFloatArray*>(parent)->setMin(value); }));
			Add(new CPropertyFloat(this, form, L"Max", false, nullptr,
				[](IClass *parent) {return cast<CFormFloatArray*>(parent)->getMax(); },
				[](IClass *parent, const float value) {return cast<CFormFloatArray*>(parent)->setMax(value); }));
		}
	}
}