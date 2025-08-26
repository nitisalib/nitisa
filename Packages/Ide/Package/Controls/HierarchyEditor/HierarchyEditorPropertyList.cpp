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
	namespace ide
	{
		CHierarchyEditorPropertyList::CHierarchyEditorPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			standard::CCustomTreeViewPropertyList(package, control, entity)
		{
			Add(new standard::CPropertyComponentImageList(this, control, L"ImageList", nullptr,
				[](IClass *parent) {return cast<CHierarchyEditor*>(parent)->getImageList(); },
				[](IClass *parent, standard::IImageList *value) { return cast<CHierarchyEditor*>(parent)->setImageList(value); }));
		}
	}
}