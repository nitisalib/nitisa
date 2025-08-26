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
		CFormIntegerArrayPropertyList::CFormIntegerArrayPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyIntegerArray(this, form, L"Value", false, nullptr,
				[](IClass *parent) {return cast<CFormIntegerArray*>(parent)->getValue(); },
				[](IClass *parent, const IntegerArray value) {return cast<CFormIntegerArray*>(parent)->setValue(value); }));
			Add(new CPropertyInteger(this, form, L"MinCount", false, nullptr,
				[](IClass *parent) {return cast<CFormIntegerArray*>(parent)->getMinCount(); },
				[](IClass *parent, const int value) {return cast<CFormIntegerArray*>(parent)->setMinCount(value); }))
				->setMin(0);
			Add(new CPropertyBool(this, form, L"HasMin", false, nullptr,
				[](IClass *parent) {return cast<CFormIntegerArray*>(parent)->hasMin(); },
				[](IClass *parent, const bool value) {return cast<CFormIntegerArray*>(parent)->setHasMin(value); }));
			Add(new CPropertyBool(this, form, L"HasMax", false, nullptr,
				[](IClass *parent) {return cast<CFormIntegerArray*>(parent)->hasMax(); },
				[](IClass *parent, const bool value) {return cast<CFormIntegerArray*>(parent)->setHasMax(value); }));
			Add(new CPropertyInteger(this, form, L"Min", false, nullptr,
				[](IClass *parent) {return cast<CFormIntegerArray*>(parent)->getMin(); },
				[](IClass *parent, const int value) {return cast<CFormIntegerArray*>(parent)->setMin(value); }));
			Add(new CPropertyInteger(this, form, L"Max", false, nullptr,
				[](IClass *parent) {return cast<CFormIntegerArray*>(parent)->getMax(); },
				[](IClass *parent, const int value) {return cast<CFormIntegerArray*>(parent)->setMax(value); }));
		}
	}
}