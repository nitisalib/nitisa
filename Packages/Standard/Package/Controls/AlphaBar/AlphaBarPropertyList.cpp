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
		CAlphaBarPropertyList::CAlphaBarPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
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

			Add(new CPropertyInteger(this, control, L"Alpha", false, nullptr,
				[](IClass *parent) {return cast<CAlphaBar*>(parent)->getAlpha(); },
				[](IClass *parent, const int value) {return cast<CAlphaBar*>(parent)->setAlpha(value); }))
				->setMin(0)->setMax(255);
			Add(new CPropertyFloat(this, control, L"PickerSize", false, nullptr,
				[](IClass *parent) {return cast<CAlphaBar*>(parent)->getPickerSize(); },
				[](IClass *parent, const float value) {return cast<CAlphaBar*>(parent)->setPickerSize(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"PickerColor", false, nullptr,
				[](IClass *parent) {return cast<CAlphaBar*>(parent)->getPickerColor(); },
				[](IClass *parent, const Color value) {return cast<CAlphaBar*>(parent)->setPickerColor(value); }));
			Add(new CPropertyColor(this, control, L"PickerBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CAlphaBar*>(parent)->getPickerBorderColor(); },
				[](IClass *parent, const Color value) {return cast<CAlphaBar*>(parent)->setPickerBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"CheckerColor1", false, nullptr,
				[](IClass *parent) {return cast<CAlphaBar*>(parent)->getCheckerColor1(); },
				[](IClass *parent, const Color value) {return cast<CAlphaBar*>(parent)->setCheckerColor1(value); }));
			Add(new CPropertyColor(this, control, L"CheckerColor2", false, nullptr,
				[](IClass *parent) {return cast<CAlphaBar*>(parent)->getCheckerColor2(); },
				[](IClass *parent, const Color value) {return cast<CAlphaBar*>(parent)->setCheckerColor2(value); }));
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CAlphaBar*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CAlphaBar*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyColor(this, control, L"GoregroundColor1", false, nullptr,
				[](IClass *parent) {return cast<CAlphaBar*>(parent)->getForegroundColor1(); },
				[](IClass *parent, const Color value) {return cast<CAlphaBar*>(parent)->setForegroundColor1(value); }));
			Add(new CPropertyColor(this, control, L"GoregroundColor2", false, nullptr,
				[](IClass *parent) {return cast<CAlphaBar*>(parent)->getForegroundColor2(); },
				[](IClass *parent, const Color value) {return cast<CAlphaBar*>(parent)->setForegroundColor2(value); }));
			Add(new CPropertyFloat(this, control, L"CheckerSize", false, nullptr,
				[](IClass *parent) {return cast<CAlphaBar*>(parent)->getCheckerSize(); },
				[](IClass *parent, const float value) {return cast<CAlphaBar*>(parent)->setCheckerSize(value); }))
				->setMin(1);
		}
	}
}