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
	namespace opengl
	{
		CDiskPropertyList::CDiskPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			C3DControlPropertyList(package, control, entity)
		{
			Add(new CPropertyFloat(this, control, L"DiskOuterRadius", false, nullptr,
				[](IClass *parent) {return cast<CDisk*>(parent)->getDiskOuterRadius(); },
				[](IClass *parent, const float value) {return cast<CDisk*>(parent)->setDiskOuterRadius(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"DiskInnerRadius", false, nullptr,
				[](IClass *parent) {return cast<CDisk*>(parent)->getDiskInnerRadius(); },
				[](IClass *parent, const float value) {return cast<CDisk*>(parent)->setDiskInnerRadius(value); }))
				->setMin(0.001f);
			Add(new CPropertyInteger(this, control, L"DiskSides", false, nullptr,
				[](IClass *parent) {return cast<CDisk*>(parent)->getDiskSides(); },
				[](IClass *parent, const int value) {return cast<CDisk*>(parent)->setDiskSides(value); }))
				->setMin(3);
			Add(new CPropertyInteger(this, control, L"CapSegments", false, nullptr,
				[](IClass *parent) {return cast<CDisk*>(parent)->getCapSegments(); },
				[](IClass *parent, const int value) {return cast<CDisk*>(parent)->setCapSegments(value); }))
				->setMin(1);
		}
	}
}