// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
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
		CHSVBarPropertyList::CHSVBarPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
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
				[](IClass *parent) {return cast<CHSVBar*>(parent)->getHue(); },
				[](IClass *parent, const int value) {return cast<CHSVBar*>(parent)->setHue(value); }))
				->setMin(0)->setMax(360);
			Add(new CPropertyFloat(this, control, L"PickerSize", false, nullptr,
				[](IClass *parent) {return cast<CHSVBar*>(parent)->getPickerSize(); },
				[](IClass *parent, const float value) {return cast<CHSVBar*>(parent)->setPickerSize(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"PickerColor", false, nullptr,
				[](IClass *parent) {return cast<CHSVBar*>(parent)->getPickerColor(); },
				[](IClass *parent, const Color value) {return cast<CHSVBar*>(parent)->setPickerColor(value); }));
			Add(new CPropertyColor(this, control, L"PickerBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CHSVBar*>(parent)->getPickerBorderColor(); },
				[](IClass *parent, const Color value) {return cast<CHSVBar*>(parent)->setPickerBorderColor(value); }));
			Add(new CPropertyControlHSVPlane(this, control, L"HSVPlane", nullptr,
				[](IClass *parent) {return cast<CHSVBar*>(parent)->getHSVPlane(); },
				[](IClass *parent, IHSVPlane *value) {return cast<CHSVBar*>(parent)->setHSVPlane(value); }));
		}
	}
}