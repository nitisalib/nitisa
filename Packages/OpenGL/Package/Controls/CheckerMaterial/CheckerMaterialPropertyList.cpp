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
		CCheckerMaterialPropertyList::CCheckerMaterialPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CMaterialControlPropertyList(package, control, entity)
		{
			Add(new CPropertyColor(this, control, L"Color1", false, nullptr,
				[](IClass *parent) {return cast<CCheckerMaterial*>(parent)->getColor1(); },
				[](IClass *parent, const Color value) {return cast<CCheckerMaterial*>(parent)->setColor1(value); }));
			Add(new CPropertyColor(this, control, L"Color2", false, nullptr,
				[](IClass *parent) {return cast<CCheckerMaterial*>(parent)->getColor2(); },
				[](IClass *parent, const Color value) {return cast<CCheckerMaterial*>(parent)->setColor2(value); }));
			Add(new CPropertyPointF(this, control, L"Scale", false, nullptr,
				[](IClass *parent) {return cast<CCheckerMaterial*>(parent)->getScale(); },
				[](IClass *parent, const PointF value) {return cast<CCheckerMaterial*>(parent)->setScale(value); }));
		}
	}
}