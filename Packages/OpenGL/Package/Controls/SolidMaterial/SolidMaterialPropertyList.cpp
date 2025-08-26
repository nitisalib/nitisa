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
		CSolidMaterialPropertyList::CSolidMaterialPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CMaterialControlPropertyList(package, control, entity)
		{
			Add(new CPropertyColor(this, control, L"Color", false, nullptr,
				[](IClass *parent) {return cast<CSolidMaterial*>(parent)->getColor(); },
				[](IClass *parent, const Color value) {return cast<CSolidMaterial*>(parent)->setColor(value); }));
		}
	}
}