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
		CStackedBarChartPropertyList::CStackedBarChartPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CCustomCartesianChartPropertyList(package, control, entity)
		{
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyBool(this, control, L"Vertical", false, nullptr,
				[](IClass *parent) {return cast<CStackedBarChart*>(parent)->isVertical(); },
				[](IClass *parent, const bool value) {return cast<CStackedBarChart*>(parent)->setVertical(value); }));
			Add(new CPropertyFloat(this, control, L"BarSize", false, nullptr,
				[](IClass *parent) {return cast<CStackedBarChart*>(parent)->getBarSize(); },
				[](IClass *parent, const float value) {return cast<CStackedBarChart*>(parent)->setBarSize(value); }))
				->setMin(0.000001f)->setMax(1);

			Add(new CPropertyColorArray(this, control, L"NormalBackgroundColors", false, nullptr,
				[](IClass *parent) {return cast<CStackedBarChart*>(parent)->getNormalBackgroundColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CStackedBarChart*>(parent)->setNormalBackgroundColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ActiveBackgroundColors", false, nullptr,
				[](IClass *parent) {return cast<CStackedBarChart*>(parent)->getActiveBackgroundColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CStackedBarChart*>(parent)->setActiveBackgroundColors(value); }))
				->setMinCount(1);
		}
	}
}