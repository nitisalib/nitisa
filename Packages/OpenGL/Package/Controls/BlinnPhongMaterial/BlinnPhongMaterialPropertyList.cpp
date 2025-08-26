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
		CBlinnPhongMaterialPropertyList::CBlinnPhongMaterialPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CMaterialControlPropertyList(package, control, entity)
		{
			Add(new CPropertyColor(this, control, L"AmbientColor", false, nullptr,
				[](IClass *parent) {return cast<CBlinnPhongMaterial*>(parent)->getAmbientColor(); },
				[](IClass *parent, const Color value) {return cast<CBlinnPhongMaterial*>(parent)->setAmbientColor(value); }));
			Add(new CPropertyColor(this, control, L"DiffuseColor", false, nullptr,
				[](IClass *parent) {return cast<CBlinnPhongMaterial*>(parent)->getDiffuseColor(); },
				[](IClass *parent, const Color value) {return cast<CBlinnPhongMaterial*>(parent)->setDiffuseColor(value); }));
			Add(new CPropertyColor(this, control, L"SpecularColor", false, nullptr,
				[](IClass *parent) {return cast<CBlinnPhongMaterial*>(parent)->getSpecularColor(); },
				[](IClass *parent, const Color value) {return cast<CBlinnPhongMaterial*>(parent)->setSpecularColor(value); }));
			Add(new CPropertyColor(this, control, L"LightDiffuseColor", false, nullptr,
				[](IClass *parent) {return cast<CBlinnPhongMaterial*>(parent)->getLightDiffuseColor(); },
				[](IClass *parent, const Color value) {return cast<CBlinnPhongMaterial*>(parent)->setLightDiffuseColor(value); }));
			Add(new CPropertyColor(this, control, L"LightSpecularColor", false, nullptr,
				[](IClass *parent) {return cast<CBlinnPhongMaterial*>(parent)->getLightSpecularColor(); },
				[](IClass *parent, const Color value) {return cast<CBlinnPhongMaterial*>(parent)->setLightSpecularColor(value); }));
			Add(new CPropertyFloat(this, control, L"LightX", false, nullptr,
				[](IClass *parent) {return cast<CBlinnPhongMaterial*>(parent)->getLightX(); },
				[](IClass *parent, const float value) {return cast<CBlinnPhongMaterial*>(parent)->setLightX(value); }));
			Add(new CPropertyFloat(this, control, L"LightY", false, nullptr,
				[](IClass *parent) {return cast<CBlinnPhongMaterial*>(parent)->getLightY(); },
				[](IClass *parent, const float value) {return cast<CBlinnPhongMaterial*>(parent)->setLightY(value); }));
			Add(new CPropertyFloat(this, control, L"LightZ", false, nullptr,
				[](IClass *parent) {return cast<CBlinnPhongMaterial*>(parent)->getLightZ(); },
				[](IClass *parent, const float value) {return cast<CBlinnPhongMaterial*>(parent)->setLightZ(value); }));
			Add(new CPropertyFloat(this, control, L"Shininess", false, nullptr,
				[](IClass *parent) {return cast<CBlinnPhongMaterial*>(parent)->getShininess(); },
				[](IClass *parent, const float value) {return cast<CBlinnPhongMaterial*>(parent)->setShininess(value); }));
		}
	}
}