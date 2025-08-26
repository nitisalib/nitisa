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
		CPyramidPropertyList::CPyramidPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			C3DControlPropertyList(package, control, entity)
		{
			Add(new CPropertyFloat(this, control, L"PyramidWidth", false, nullptr,
				[](IClass *parent) {return cast<CPyramid*>(parent)->getPyramidWidth(); },
				[](IClass *parent, const float value) {return cast<CPyramid*>(parent)->setPyramidWidth(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"PyramidDepth", false, nullptr,
				[](IClass *parent) {return cast<CPyramid*>(parent)->getPyramidDepth(); },
				[](IClass *parent, const float value) {return cast<CPyramid*>(parent)->setPyramidDepth(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"PyramidHeight", false, nullptr,
				[](IClass *parent) {return cast<CPyramid*>(parent)->getPyramidHeight(); },
				[](IClass *parent, const float value) {return cast<CPyramid*>(parent)->setPyramidHeight(value); }))
				->setMin(0.001f);
			Add(new CPropertyInteger(this, control, L"HeightSegments", false, nullptr,
				[](IClass *parent) {return cast<CPyramid*>(parent)->getHeightSegments(); },
				[](IClass *parent, const int value) {return cast<CPyramid*>(parent)->setHeightSegments(value); }))
				->setMin(1);
		}
	}
}