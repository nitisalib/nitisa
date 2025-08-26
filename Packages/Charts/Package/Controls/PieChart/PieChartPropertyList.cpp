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
	namespace charts
	{
		CPieChartPropertyList::CPieChartPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CCustomRadialChartPropertyList(package, control, entity)
		{
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CPieChart*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) {return cast<CPieChart*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"Quality", false, nullptr,
				[](IClass *parent) {return cast<CPieChart*>(parent)->getQuality(); },
				[](IClass *parent, const float value) {return cast<CPieChart*>(parent)->setQuality(value); }))
				->setMin(0)->setMax(1);
			Add(new CPropertyBool(this, control, L"RestartColors", false, nullptr,
				[](IClass *parent) {return cast<CPieChart*>(parent)->isRestartColors(); },
				[](IClass *parent, const bool value) {return cast<CPieChart*>(parent)->setRestartColors(value); }));

			Add(new CPropertyColorArray(this, control, L"NormalColors", false, nullptr,
				[](IClass *parent) {return cast<CPieChart*>(parent)->getNormalColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CPieChart*>(parent)->setNormalColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ActiveColors", false, nullptr,
				[](IClass *parent) {return cast<CPieChart*>(parent)->getActiveColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CPieChart*>(parent)->setActiveColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"NormalBorderColors", false, nullptr,
				[](IClass *parent) {return cast<CPieChart*>(parent)->getNormalBorderColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CPieChart*>(parent)->setNormalBorderColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ActiveBorderColors", false, nullptr,
				[](IClass *parent) {return cast<CPieChart*>(parent)->getActiveBorderColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CPieChart*>(parent)->setActiveBorderColors(value); }))
				->setMinCount(1);
		}
	}
}