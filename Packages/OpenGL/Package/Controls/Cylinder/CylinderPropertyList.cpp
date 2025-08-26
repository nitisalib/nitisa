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
		CCylinderPropertyList::CCylinderPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			C3DControlPropertyList(package, control, entity)
		{
			Add(new CPropertyFloat(this, control, L"CylinderRadius", false, nullptr,
				[](IClass *parent) {return cast<CCylinder*>(parent)->getCylinderRadius(); },
				[](IClass *parent, const float value) {return cast<CCylinder*>(parent)->setCylinderRadius(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"CylinderHeight", false, nullptr,
				[](IClass *parent) {return cast<CCylinder*>(parent)->getCylinderHeight(); },
				[](IClass *parent, const float value) {return cast<CCylinder*>(parent)->setCylinderHeight(value); }))
				->setMin(0.001f);
			Add(new CPropertyInteger(this, control, L"CylinderSides", false, nullptr,
				[](IClass *parent) {return cast<CCylinder*>(parent)->getCylinderSides(); },
				[](IClass *parent, const int value) {return cast<CCylinder*>(parent)->setCylinderSides(value); }))
				->setMin(3);
			Add(new CPropertyInteger(this, control, L"CapSegments", false, nullptr,
				[](IClass *parent) {return cast<CCylinder*>(parent)->getCapSegments(); },
				[](IClass *parent, const int value) {return cast<CCylinder*>(parent)->setCapSegments(value); }))
				->setMin(1);
			Add(new CPropertyInteger(this, control, L"HeightSegments", false, nullptr,
				[](IClass *parent) {return cast<CCylinder*>(parent)->getHeightSegments(); },
				[](IClass *parent, const int value) {return cast<CCylinder*>(parent)->setHeightSegments(value); }))
				->setMin(1);
		}
	}
}