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
	namespace standard
	{
		CFormImageListPropertyList::CFormImageListPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyImageList(this, form, L"Images", nullptr,
				[](IClass *parent) { return cast<CFormImageList*>(parent)->getImageCount(); },
				[](IClass *parent, const int index) { return cast<CFormImageList*>(parent)->getImage(index); },
				[](IClass *parent, Image *value) { return cast<CFormImageList*>(parent)->AddImage(value); },
				[](IClass *parent, const int value) { return cast<CFormImageList*>(parent)->DeleteImage(value); },
				[](IClass *parent) { return cast<CFormImageList*>(parent)->DeleteImages(); },
				[](IClass *parent) { }));
		}
	}
}