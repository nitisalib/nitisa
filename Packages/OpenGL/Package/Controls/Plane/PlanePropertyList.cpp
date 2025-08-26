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
		CPlanePropertyList::CPlanePropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			C3DControlPropertyList(package, control, entity)
		{
			Add(new CPropertyFloat(this, control, L"PlaneWidth", false, nullptr,
				[](IClass *parent) {return cast<CPlane*>(parent)->getPlaneWidth(); },
				[](IClass *parent, const float value) {return cast<CPlane*>(parent)->setPlaneWidth(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"PlaneDepth", false, nullptr,
				[](IClass *parent) {return cast<CPlane*>(parent)->getPlaneDepth(); },
				[](IClass *parent, const float value) {return cast<CPlane*>(parent)->setPlaneDepth(value); }))
				->setMin(0.001f);
			Add(new CPropertyInteger(this, control, L"WidthSegments", false, nullptr,
				[](IClass *parent) {return cast<CPlane*>(parent)->getWidthSegments(); },
				[](IClass *parent, const int value) {return cast<CPlane*>(parent)->setWidthSegments(value); }))
				->setMin(1);
			Add(new CPropertyInteger(this, control, L"DepthSegments", false, nullptr,
				[](IClass *parent) {return cast<CPlane*>(parent)->getDepthSegments(); },
				[](IClass *parent, const int value) {return cast<CPlane*>(parent)->setDepthSegments(value); }))
				->setMin(1);
		}
	}
}