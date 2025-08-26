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
		CTubePropertyList::CTubePropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			C3DControlPropertyList(package, control, entity)
		{
			Add(new CPropertyFloat(this, control, L"TubeOuterRadius", false, nullptr,
				[](IClass *parent) {return cast<CTube*>(parent)->getTubeOuterRadius(); },
				[](IClass *parent, const float value) {return cast<CTube*>(parent)->setTubeOuterRadius(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"TubeInnerRadius", false, nullptr,
				[](IClass *parent) {return cast<CTube*>(parent)->getTubeInnerRadius(); },
				[](IClass *parent, const float value) {return cast<CTube*>(parent)->setTubeInnerRadius(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"TubeHeight", false, nullptr,
				[](IClass *parent) {return cast<CTube*>(parent)->getTubeHeight(); },
				[](IClass *parent, const float value) {return cast<CTube*>(parent)->setTubeHeight(value); }))
				->setMin(0.001f);
			Add(new CPropertyInteger(this, control, L"TubeSides", false, nullptr,
				[](IClass *parent) {return cast<CTube*>(parent)->getTubeSides(); },
				[](IClass *parent, const int value) {return cast<CTube*>(parent)->setTubeSides(value); }))
				->setMin(3);
			Add(new CPropertyInteger(this, control, L"CapSegments", false, nullptr,
				[](IClass *parent) {return cast<CTube*>(parent)->getCapSegments(); },
				[](IClass *parent, const int value) {return cast<CTube*>(parent)->setCapSegments(value); }))
				->setMin(1);
			Add(new CPropertyInteger(this, control, L"HeightSegments", false, nullptr,
				[](IClass *parent) {return cast<CTube*>(parent)->getHeightSegments(); },
				[](IClass *parent, const int value) {return cast<CTube*>(parent)->setHeightSegments(value); }))
				->setMin(1);
		}
	}
}