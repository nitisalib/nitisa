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
		CBoxPropertyList::CBoxPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			C3DControlPropertyList(package, control, entity)
		{
			Add(new CPropertyFloat(this, control, L"BoxWidth", false, nullptr,
				[](IClass *parent) {return cast<CBox*>(parent)->getBoxWidth(); },
				[](IClass *parent, const float value) {return cast<CBox*>(parent)->setBoxWidth(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"BoxHeight", false, nullptr,
				[](IClass *parent) {return cast<CBox*>(parent)->getBoxHeight(); },
				[](IClass *parent, const float value) {return cast<CBox*>(parent)->setBoxHeight(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"BoxDepth", false, nullptr,
				[](IClass *parent) {return cast<CBox*>(parent)->getBoxDepth(); },
				[](IClass *parent, const float value) {return cast<CBox*>(parent)->setBoxDepth(value); }))
				->setMin(0.001f);
			Add(new CPropertyInteger(this, control, L"WidthSegments", false, nullptr,
				[](IClass *parent) {return cast<CBox*>(parent)->getWidthSegments(); },
				[](IClass *parent, const int value) {return cast<CBox*>(parent)->setWidthSegments(value); }))
				->setMin(1);
			Add(new CPropertyInteger(this, control, L"HeightSegments", false, nullptr,
				[](IClass *parent) {return cast<CBox*>(parent)->getHeightSegments(); },
				[](IClass *parent, const int value) {return cast<CBox*>(parent)->setHeightSegments(value); }))
				->setMin(1);
			Add(new CPropertyInteger(this, control, L"DepthSegments", false, nullptr,
				[](IClass *parent) {return cast<CBox*>(parent)->getDepthSegments(); },
				[](IClass *parent, const int value) {return cast<CBox*>(parent)->setDepthSegments(value); }))
				->setMin(1);
		}
	}
}