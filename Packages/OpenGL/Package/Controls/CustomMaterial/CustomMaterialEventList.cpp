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
		CCustomMaterialEventList::CCustomMaterialEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CMaterialControlEventList(package, control, entity)
		{
			Add(new CEvent(this, control, L"OnActivateMaterial", L"{namespace}ICustomMaterial *sender", L"sender"))
				->AddForwardDeclaration(L"class ICustomMaterial;", L"OpenGL/Controls/ICustomMaterial.h", L"opengl");
		}
	}
}