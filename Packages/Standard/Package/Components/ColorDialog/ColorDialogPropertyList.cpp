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
	namespace standard
	{
		CColorDialogPropertyList::CColorDialogPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyColor(this, component, L"Color", false, nullptr,
				[](IClass *parent) {return cast<CColorDialog*>(parent)->getColor(); },
				[](IClass *parent, const Color value) {return cast<CColorDialog*>(parent)->setColor(value); }));
			Add(new CPropertyBool(this, component, L"UseDialogBox", false, nullptr,
				[](IClass *parent) {return cast<CColorDialog*>(parent)->isUseDialogBox(); },
				[](IClass *parent, const bool value) {return cast<CColorDialog*>(parent)->setUseDialogBox(value); }));
		}
	}
}