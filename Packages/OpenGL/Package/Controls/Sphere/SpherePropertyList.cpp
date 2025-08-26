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
		CSpherePropertyList::CSpherePropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			C3DControlPropertyList(package, control, entity)
		{
			Add(new CPropertyFloat(this, control, L"SphereRadius", false, nullptr,
				[](IClass *parent) {return cast<CSphere*>(parent)->getSphereRadius(); },
				[](IClass *parent, const float value) {return cast<CSphere*>(parent)->setSphereRadius(value); }))
				->setMin(0.001f);
			Add(new CPropertyInteger(this, control, L"SphereSides", false, nullptr,
				[](IClass *parent) {return cast<CSphere*>(parent)->getSphereSides(); },
				[](IClass *parent, const int value) {return cast<CSphere*>(parent)->setSphereSides(value); }))
				->setMin(3);
			Add(new CPropertyInteger(this, control, L"SphereYSides", false, nullptr,
				[](IClass *parent) {return cast<CSphere*>(parent)->getSphereYSides(); },
				[](IClass *parent, const int value) {return cast<CSphere*>(parent)->setSphereYSides(value); }))
				->setMin(3);
		}
	}
}