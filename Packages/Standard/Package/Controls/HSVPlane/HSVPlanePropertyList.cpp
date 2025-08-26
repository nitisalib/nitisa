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
	namespace standard
	{
		CHSVPlanePropertyList::CHSVPlanePropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Font");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Font.Monospace");
			Delete(L"Font.Distance");
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyInteger(this, control, L"Hue", false, nullptr,
				[](IClass *parent) {return cast<CHSVPlane*>(parent)->getHue(); },
				[](IClass *parent, const int value) {return cast<CHSVPlane*>(parent)->setHue(value); }))
				->setMin(0)->setMax(360);
			Add(new CPropertyFloat(this, control, L"Saturation", false, nullptr,
				[](IClass *parent) {return cast<CHSVPlane*>(parent)->getSaturation(); },
				[](IClass *parent, const float value) {return cast<CHSVPlane*>(parent)->setSaturation(value); }))
				->setMin(0)->setMax(1);
			Add(new CPropertyFloat(this, control, L"Value", false, nullptr,
				[](IClass *parent) {return cast<CHSVPlane*>(parent)->getValue(); },
				[](IClass *parent, const float value) {return cast<CHSVPlane*>(parent)->setValue(value); }))
				->setMin(0)->setMax(1);
			Add(new CPropertyFloat(this, control, L"PickerRadius", false, nullptr,
				[](IClass *parent) {return cast<CHSVPlane*>(parent)->getPickerRadius(); },
				[](IClass *parent, const float value) {return cast<CHSVPlane*>(parent)->setPickerRadius(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"PickerBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CHSVPlane*>(parent)->getPickerBorderWidth(); },
				[](IClass *parent, const float value) {return cast<CHSVPlane*>(parent)->setPickerBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"PickerBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CHSVPlane*>(parent)->getPickerBorderRadius(); },
				[](IClass *parent, const float value) {return cast<CHSVPlane*>(parent)->setPickerBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"PickerBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CHSVPlane*>(parent)->getPickerBorderColor(); },
				[](IClass *parent, const Color value) {return cast<CHSVPlane*>(parent)->setPickerBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"PickerBorderColorInv", false, nullptr,
				[](IClass *parent) {return cast<CHSVPlane*>(parent)->getPickerBorderColorInv(); },
				[](IClass *parent, const Color value) {return cast<CHSVPlane*>(parent)->setPickerBorderColorInv(value); }));
			Add(new CPropertyColor(this, control, L"PickerBackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CHSVPlane*>(parent)->getPickerBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CHSVPlane*>(parent)->setPickerBackgroundColor(value); }));
			Add(new CPropertyColor(this, control, L"PickerBackgroundColorInv", false, nullptr,
				[](IClass *parent) {return cast<CHSVPlane*>(parent)->getPickerBackgroundColorInv(); },
				[](IClass *parent, const Color value) {return cast<CHSVPlane*>(parent)->setPickerBackgroundColorInv(value); }));
		}
	}
}