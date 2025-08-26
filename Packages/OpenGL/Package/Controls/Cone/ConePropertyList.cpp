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
		CConePropertyList::CConePropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			C3DControlPropertyList(package, control, entity)
		{
			Add(new CPropertyFloat(this, control, L"ConeRadius1", false, nullptr,
				[](IClass *parent) {return cast<CCone*>(parent)->getConeRadius1(); },
				[](IClass *parent, const float value) {return cast<CCone*>(parent)->setConeRadius1(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"ConeRadius2", false, nullptr,
				[](IClass *parent) {return cast<CCone*>(parent)->getConeRadius2(); },
				[](IClass *parent, const float value) {return cast<CCone*>(parent)->setConeRadius2(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"ConeHeight", false, nullptr,
				[](IClass *parent) {return cast<CCone*>(parent)->getConeHeight(); },
				[](IClass *parent, const float value) {return cast<CCone*>(parent)->setConeHeight(value); }))
				->setMin(0.001f);
			Add(new CPropertyInteger(this, control, L"ConeSides", false, nullptr,
				[](IClass *parent) {return cast<CCone*>(parent)->getConeSides(); },
				[](IClass *parent, const int value) {return cast<CCone*>(parent)->setConeSides(value); }))
				->setMin(3);
			Add(new CPropertyInteger(this, control, L"CapSegments", false, nullptr,
				[](IClass *parent) {return cast<CCone*>(parent)->getCapSegments(); },
				[](IClass *parent, const int value) {return cast<CCone*>(parent)->setCapSegments(value); }))
				->setMin(1);
			Add(new CPropertyInteger(this, control, L"HeightSegments", false, nullptr,
				[](IClass *parent) {return cast<CCone*>(parent)->getHeightSegments(); },
				[](IClass *parent, const int value) {return cast<CCone*>(parent)->setHeightSegments(value); }))
				->setMin(1);
		}
	}
}