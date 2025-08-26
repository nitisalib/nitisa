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
	namespace opengl
	{
		CTorusPropertyList::CTorusPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			C3DControlPropertyList(package, control, entity)
		{
			Add(new CPropertyFloat(this, control, L"TorusRadius1", false, nullptr,
				[](IClass *parent) {return cast<CTorus*>(parent)->getTorusRadius1(); },
				[](IClass *parent, const float value) {return cast<CTorus*>(parent)->setTorusRadius1(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"TorusRadius2", false, nullptr,
				[](IClass *parent) {return cast<CTorus*>(parent)->getTorusRadius2(); },
				[](IClass *parent, const float value) {return cast<CTorus*>(parent)->setTorusRadius2(value); }))
				->setMin(0.001f);
			Add(new CPropertyInteger(this, control, L"TorusSides1", false, nullptr,
				[](IClass *parent) {return cast<CTorus*>(parent)->getTorusSides1(); },
				[](IClass *parent, const int value) {return cast<CTorus*>(parent)->setTorusSides1(value); }))
				->setMin(3);
			Add(new CPropertyInteger(this, control, L"TorusSides2", false, nullptr,
				[](IClass *parent) {return cast<CTorus*>(parent)->getTorusSides2(); },
				[](IClass *parent, const int value) {return cast<CTorus*>(parent)->setTorusSides2(value); }))
				->setMin(3);
		}
	}
}