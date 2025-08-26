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
		CCustomMaterialPropertyList::CCustomMaterialPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CMaterialControlPropertyList(package, control, entity)
		{
			Add(new CPropertyText(this, control, L"VertexShader", false, nullptr,
				[](IClass *parent) {return AnsiToString(cast<CCustomMaterial*>(parent)->getVertexShader()); },
				[](IClass *parent, const String value) {return cast<CCustomMaterial*>(parent)->setVertexShader(StringToAnsi(value)); }));
			Add(new CPropertyText(this, control, L"FragmentShader", false, nullptr,
				[](IClass *parent) {return AnsiToString(cast<CCustomMaterial*>(parent)->getFragmentShader()); },
				[](IClass *parent, const String value) {return cast<CCustomMaterial*>(parent)->setFragmentShader(StringToAnsi(value)); }));
			Add(new CPropertyBool(this, control, L"UseMatrixModel", false, nullptr,
				[](IClass *parent) {return cast<CCustomMaterial*>(parent)->isUseMatrixModel(); },
				[](IClass *parent, const bool value) {return cast<CCustomMaterial*>(parent)->setUseMatrixModel(value); }));
			Add(new CPropertyBool(this, control, L"UseMatrixCamera", false, nullptr,
				[](IClass *parent) {return cast<CCustomMaterial*>(parent)->isUseMatrixCamera(); },
				[](IClass *parent, const bool value) {return cast<CCustomMaterial*>(parent)->setUseMatrixCamera(value); }));
			Add(new CPropertyBool(this, control, L"UseHasTexture", false, nullptr,
				[](IClass *parent) {return cast<CCustomMaterial*>(parent)->isUseHasTexture(); },
				[](IClass *parent, const bool value) {return cast<CCustomMaterial*>(parent)->setUseHasTexture(value); }));
		}
	}
}