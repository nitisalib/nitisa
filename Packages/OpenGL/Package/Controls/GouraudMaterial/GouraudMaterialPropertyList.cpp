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
		CGouraudMaterialPropertyList::CGouraudMaterialPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CMaterialControlPropertyList(package, control, entity)
		{
			Add(new CPropertyColor(this, control, L"AmbientColor", false, nullptr,
				[](IClass *parent) {return cast<CGouraudMaterial*>(parent)->getAmbientColor(); },
				[](IClass *parent, const Color value) {return cast<CGouraudMaterial*>(parent)->setAmbientColor(value); }));
			Add(new CPropertyColor(this, control, L"DiffuseColor", false, nullptr,
				[](IClass *parent) {return cast<CGouraudMaterial*>(parent)->getDiffuseColor(); },
				[](IClass *parent, const Color value) {return cast<CGouraudMaterial*>(parent)->setDiffuseColor(value); }));
			Add(new CPropertyColor(this, control, L"SpecularColor", false, nullptr,
				[](IClass *parent) {return cast<CGouraudMaterial*>(parent)->getSpecularColor(); },
				[](IClass *parent, const Color value) {return cast<CGouraudMaterial*>(parent)->setSpecularColor(value); }));
			Add(new CPropertyColor(this, control, L"LightDiffuseColor", false, nullptr,
				[](IClass *parent) {return cast<CGouraudMaterial*>(parent)->getLightDiffuseColor(); },
				[](IClass *parent, const Color value) {return cast<CGouraudMaterial*>(parent)->setLightDiffuseColor(value); }));
			Add(new CPropertyColor(this, control, L"LightSpecularColor", false, nullptr,
				[](IClass *parent) {return cast<CGouraudMaterial*>(parent)->getLightSpecularColor(); },
				[](IClass *parent, const Color value) {return cast<CGouraudMaterial*>(parent)->setLightSpecularColor(value); }));
			Add(new CPropertyFloat(this, control, L"LightX", false, nullptr,
				[](IClass *parent) {return cast<CGouraudMaterial*>(parent)->getLightX(); },
				[](IClass *parent, const float value) {return cast<CGouraudMaterial*>(parent)->setLightX(value); }));
			Add(new CPropertyFloat(this, control, L"LightY", false, nullptr,
				[](IClass *parent) {return cast<CGouraudMaterial*>(parent)->getLightY(); },
				[](IClass *parent, const float value) {return cast<CGouraudMaterial*>(parent)->setLightY(value); }));
			Add(new CPropertyFloat(this, control, L"LightZ", false, nullptr,
				[](IClass *parent) {return cast<CGouraudMaterial*>(parent)->getLightZ(); },
				[](IClass *parent, const float value) {return cast<CGouraudMaterial*>(parent)->setLightZ(value); }));
			Add(new CPropertyFloat(this, control, L"Shininess", false, nullptr,
				[](IClass *parent) {return cast<CGouraudMaterial*>(parent)->getShininess(); },
				[](IClass *parent, const float value) {return cast<CGouraudMaterial*>(parent)->setShininess(value); }));
		}
	}
}