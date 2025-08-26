// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	CComponentPropertyList::CComponentPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :CPropertyList(package, component, entity)
	{
		Add(new CPropertyIdentifier(this, component, L"Name", false, nullptr,
			[](IClass *parent) {return cast<IComponent*>(parent)->Name; },
			[](IClass *parent, const String value) {return cast<IComponent*>(parent)->setName(value); }));
	}
}