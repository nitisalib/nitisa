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
		CSysFontDialogPropertyList::CSysFontDialogPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyFont(this, component, L"Font", false, nullptr,
				[](IClass *parent) {return cast<CSysFontDialog*>(parent)->getFont(); },
				[](IClass *parent, IFont *value) {return cast<CSysFontDialog*>(parent)->setFont(value); }));
		}
	}
}