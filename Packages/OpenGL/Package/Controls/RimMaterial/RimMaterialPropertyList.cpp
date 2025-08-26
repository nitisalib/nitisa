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
		CRimMaterialPropertyList::CRimMaterialPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CMaterialControlPropertyList(package, control, entity)
		{
			Add(new CPropertyColor(this, control, L"AmbientColor", false, nullptr,
				[](IClass *parent) {return cast<CRimMaterial*>(parent)->getAmbientColor(); },
				[](IClass *parent, const Color value) {return cast<CRimMaterial*>(parent)->setAmbientColor(value); }));
			Add(new CPropertyColor(this, control, L"DiffuseColor", false, nullptr,
				[](IClass *parent) {return cast<CRimMaterial*>(parent)->getDiffuseColor(); },
				[](IClass *parent, const Color value) {return cast<CRimMaterial*>(parent)->setDiffuseColor(value); }));
			Add(new CPropertyColor(this, control, L"SpecularColor", false, nullptr,
				[](IClass *parent) {return cast<CRimMaterial*>(parent)->getSpecularColor(); },
				[](IClass *parent, const Color value) {return cast<CRimMaterial*>(parent)->setSpecularColor(value); }));
			Add(new CPropertyColor(this, control, L"RimColor", false, nullptr,
				[](IClass *parent) {return cast<CRimMaterial*>(parent)->getRimColor(); },
				[](IClass *parent, const Color value) {return cast<CRimMaterial*>(parent)->setRimColor(value); }));
			Add(new CPropertyColor(this, control, L"LightDiffuseColor", false, nullptr,
				[](IClass *parent) {return cast<CRimMaterial*>(parent)->getLightDiffuseColor(); },
				[](IClass *parent, const Color value) {return cast<CRimMaterial*>(parent)->setLightDiffuseColor(value); }));
			Add(new CPropertyColor(this, control, L"LightSpecularColor", false, nullptr,
				[](IClass *parent) {return cast<CRimMaterial*>(parent)->getLightSpecularColor(); },
				[](IClass *parent, const Color value) {return cast<CRimMaterial*>(parent)->setLightSpecularColor(value); }));
			Add(new CPropertyFloat(this, control, L"LightX", false, nullptr,
				[](IClass *parent) {return cast<CRimMaterial*>(parent)->getLightX(); },
				[](IClass *parent, const float value) {return cast<CRimMaterial*>(parent)->setLightX(value); }));
			Add(new CPropertyFloat(this, control, L"LightY", false, nullptr,
				[](IClass *parent) {return cast<CRimMaterial*>(parent)->getLightY(); },
				[](IClass *parent, const float value) {return cast<CRimMaterial*>(parent)->setLightY(value); }));
			Add(new CPropertyFloat(this, control, L"LightZ", false, nullptr,
				[](IClass *parent) {return cast<CRimMaterial*>(parent)->getLightZ(); },
				[](IClass *parent, const float value) {return cast<CRimMaterial*>(parent)->setLightZ(value); }));
			Add(new CPropertyFloat(this, control, L"Shininess", false, nullptr,
				[](IClass *parent) {return cast<CRimMaterial*>(parent)->getShininess(); },
				[](IClass *parent, const float value) {return cast<CRimMaterial*>(parent)->setShininess(value); }));
			Add(new CPropertyFloat(this, control, L"RimPower", false, nullptr,
				[](IClass *parent) {return cast<CRimMaterial*>(parent)->getRimPower(); },
				[](IClass *parent, const float value) {return cast<CRimMaterial*>(parent)->setRimPower(value); }));
		}
	}
}