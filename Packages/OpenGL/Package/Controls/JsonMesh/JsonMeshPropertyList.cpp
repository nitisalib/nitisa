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
		CJsonMeshPropertyList::CJsonMeshPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			C3DControlPropertyList(package, control, entity)
		{
			Add(new CPropertyString(this, control, L"Filename", true, nullptr,
				[](IClass *parent) {return cast<CJsonMesh*>(parent)->getFilename(); },
				[](IClass *parent, const String value) {return cast<CJsonMesh*>(parent)->setFilename(value); }));
		}
	}
}