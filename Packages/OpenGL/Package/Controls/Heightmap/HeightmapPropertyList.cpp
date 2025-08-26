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
		CHeightmapPropertyList::CHeightmapPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			C3DControlPropertyList(package, control, entity)
		{
			Add(new CPropertyFloat(this, control, L"CellWidth", false, nullptr,
				[](IClass *parent) {return cast<CHeightmap*>(parent)->getCellWidth(); },
				[](IClass *parent, const float value) {return cast<CHeightmap*>(parent)->setCellWidth(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"CellHeight", false, nullptr,
				[](IClass *parent) {return cast<CHeightmap*>(parent)->getCellHeight(); },
				[](IClass *parent, const float value) {return cast<CHeightmap*>(parent)->setCellHeight(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"CellDepth", false, nullptr,
				[](IClass *parent) {return cast<CHeightmap*>(parent)->getCellDepth(); },
				[](IClass *parent, const float value) {return cast<CHeightmap*>(parent)->setCellDepth(value); }))
				->setMin(0.001f);
			Add(new CPropertyString(this, control, L"Filename", true, nullptr,
				[](IClass *parent) {return cast<CHeightmap*>(parent)->getFilename(); },
				[](IClass *parent, const String value) {return cast<CHeightmap*>(parent)->setFilename(value); }));
		}
	}
}