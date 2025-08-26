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
		CCirclePropertyList::CCirclePropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			C3DControlPropertyList(package, control, entity)
		{
			Add(new CPropertyFloat(this, control, L"CircleRadius", false, nullptr,
				[](IClass *parent) {return cast<CCircle*>(parent)->getCircleRadius(); },
				[](IClass *parent, const float value) {return cast<CCircle*>(parent)->setCircleRadius(value); }))
				->setMin(0.001f);
			Add(new CPropertyInteger(this, control, L"CircleSides", false, nullptr,
				[](IClass *parent) {return cast<CCircle*>(parent)->getCircleSides(); },
				[](IClass *parent, const int value) {return cast<CCircle*>(parent)->setCircleSides(value); }))
				->setMin(3);
			Add(new CPropertyInteger(this, control, L"CapSegments", false, nullptr,
				[](IClass *parent) {return cast<CCircle*>(parent)->getCapSegments(); },
				[](IClass *parent, const int value) {return cast<CCircle*>(parent)->setCapSegments(value); }))
				->setMin(1);
		}
	}
}