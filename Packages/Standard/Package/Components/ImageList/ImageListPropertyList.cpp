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
		CImageListPropertyList::CImageListPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyImageList(this, component, L"Images", nullptr,
				[](IClass *parent) {return cast<CImageList*>(parent)->getImageCount(); },
				[](IClass *parent, const int index) { return cast<CImageList*>(parent)->getImage(index); },
				[](IClass *parent, Image *data) {return cast<CImageList*>(parent)->AddImage(data); },
				[](IClass *parent, const int index) {return cast<CImageList*>(parent)->DeleteImage(index); },
				[](IClass *parent) {return cast<CImageList*>(parent)->DeleteImages(); },
				[](IClass *parent) {cast<CImageList*>(parent)->Update(); }));
		}
	}
}