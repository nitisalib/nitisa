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
		CMultiBarChartPropertyList::CMultiBarChartPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CCustomCartesianChartPropertyList(package, control, entity)
		{
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyBool(this, control, L"Vertical", false, nullptr,
				[](IClass *parent) {return cast<CMultiBarChart*>(parent)->isVertical(); },
				[](IClass *parent, const bool value) {return cast<CMultiBarChart*>(parent)->setVertical(value); }));
			Add(new CPropertyFloat(this, control, L"ContentSize", false, nullptr,
				[](IClass *parent) {return cast<CMultiBarChart*>(parent)->getContentSize(); },
				[](IClass *parent, const float value) {return cast<CMultiBarChart*>(parent)->setContentSize(value); }))
				->setMin(0.000001f)->setMax(1);
			Add(new CPropertyFloat(this, control, L"BarDistance", false, nullptr,
				[](IClass *parent) {return cast<CMultiBarChart*>(parent)->getBarDistance(); },
				[](IClass *parent, const float value) {return cast<CMultiBarChart*>(parent)->setBarDistance(value); }))
				->setMin(0)->setMax(0.999999f);

			Add(new CPropertyBoolArray(this, control, L"DrawNormalBorders", false, nullptr,
				[](IClass *parent) {return cast<CMultiBarChart*>(parent)->getDrawNormalBorders(); },
				[](IClass *parent, const BoolArray value) {return cast<CMultiBarChart*>(parent)->setDrawNormalBorders(value); }))
				->setMinCount(1);
			Add(new CPropertyBoolArray(this, control, L"DrawActiveBorders", false, nullptr,
				[](IClass *parent) {return cast<CMultiBarChart*>(parent)->getDrawActiveBorders(); },
				[](IClass *parent, const BoolArray value) {return cast<CMultiBarChart*>(parent)->setDrawActiveBorders(value); }))
				->setMinCount(1);
			Add(new CPropertyBoolArray(this, control, L"DrawNormalBackgrounds", false, nullptr,
				[](IClass *parent) {return cast<CMultiBarChart*>(parent)->getDrawNormalBackgrounds(); },
				[](IClass *parent, const BoolArray value) {return cast<CMultiBarChart*>(parent)->setDrawNormalBackgrounds(value); }))
				->setMinCount(1);
			Add(new CPropertyBoolArray(this, control, L"DrawActiveBackgrounds", false, nullptr,
				[](IClass *parent) {return cast<CMultiBarChart*>(parent)->getDrawActiveBackgrounds(); },
				[](IClass *parent, const BoolArray value) {return cast<CMultiBarChart*>(parent)->setDrawActiveBackgrounds(value); }))
				->setMinCount(1);
			Add(new CPropertyFloatArray(this, control, L"NormalBorderWidthes", false, nullptr,
				[](IClass *parent) {return cast<CMultiBarChart*>(parent)->getNormalBorderWidthes(); },
				[](IClass *parent, const FloatArray value) {return cast<CMultiBarChart*>(parent)->setNormalBorderWidthes(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyFloatArray(this, control, L"ActiveBorderWidthes", false, nullptr,
				[](IClass *parent) {return cast<CMultiBarChart*>(parent)->getActiveBorderWidthes(); },
				[](IClass *parent, const FloatArray value) {return cast<CMultiBarChart*>(parent)->setActiveBorderWidthes(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyColorArray(this, control, L"NormalBorderColors", false, nullptr,
				[](IClass *parent) {return cast<CMultiBarChart*>(parent)->getNormalBorderColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CMultiBarChart*>(parent)->setNormalBorderColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ActiveBorderColors", false, nullptr,
				[](IClass *parent) {return cast<CMultiBarChart*>(parent)->getActiveBorderColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CMultiBarChart*>(parent)->setActiveBorderColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"NormalBackgroundColors", false, nullptr,
				[](IClass *parent) {return cast<CMultiBarChart*>(parent)->getNormalBackgroundColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CMultiBarChart*>(parent)->setNormalBackgroundColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ActiveBackgroundColors", false, nullptr,
				[](IClass *parent) {return cast<CMultiBarChart*>(parent)->getActiveBackgroundColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CMultiBarChart*>(parent)->setActiveBackgroundColors(value); }))
				->setMinCount(1);
		}
	}
}