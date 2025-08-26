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
		CLineChartPropertyList::CLineChartPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CCustomCartesianChartPropertyList(package, control, entity)
		{
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyBoolArray(this, control, L"ChartDrawPoints", false, nullptr,
				[](IClass *parent) {return cast<CLineChart*>(parent)->getChartDrawPoints(); },
				[](IClass *parent, const BoolArray value) {return cast<CLineChart*>(parent)->setChartDrawPoints(value); }))
				->setMinCount(1);
			Add(new CPropertyBoolArray(this, control, L"ChartDrawLines", false, nullptr,
				[](IClass *parent) {return cast<CLineChart*>(parent)->getChartDrawLines(); },
				[](IClass *parent, const BoolArray value) {return cast<CLineChart*>(parent)->setChartDrawLines(value); }))
				->setMinCount(1);
			Add(new CPropertyBoolArray(this, control, L"ChartDrawBackgrounds", false, nullptr,
				[](IClass *parent) {return cast<CLineChart*>(parent)->getChartDrawBackgrounds(); },
				[](IClass *parent, const BoolArray value) {return cast<CLineChart*>(parent)->setChartDrawBackgrounds(value); }))
				->setMinCount(1);
			Add(new CPropertyFloatArray(this, control, L"ChartNormalPointSizes", false, nullptr,
				[](IClass *parent) {return cast<CLineChart*>(parent)->getChartNormalPointSizes(); },
				[](IClass *parent, const FloatArray value) {return cast<CLineChart*>(parent)->setChartNormalPointSizes(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyFloatArray(this, control, L"ChartActivePointSizes", false, nullptr,
				[](IClass *parent) {return cast<CLineChart*>(parent)->getChartActivePointSizes(); },
				[](IClass *parent, const FloatArray value) {return cast<CLineChart*>(parent)->setChartActivePointSizes(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyFloatArray(this, control, L"ChartNormalPointHoles", false, nullptr,
				[](IClass *parent) {return cast<CLineChart*>(parent)->getChartNormalPointHoles(); },
				[](IClass *parent, const FloatArray value) {return cast<CLineChart*>(parent)->setChartNormalPointHoles(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyFloatArray(this, control, L"ChartActivePointHoles", false, nullptr,
				[](IClass *parent) {return cast<CLineChart*>(parent)->getChartActivePointHoles(); },
				[](IClass *parent, const FloatArray value) {return cast<CLineChart*>(parent)->setChartActivePointHoles(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyColorArray(this, control, L"ChartNormalPointColors", false, nullptr,
				[](IClass *parent) {return cast<CLineChart*>(parent)->getChartNormalPointColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CLineChart*>(parent)->setChartNormalPointColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ChartActivePointColors", false, nullptr,
				[](IClass *parent) {return cast<CLineChart*>(parent)->getChartActivePointColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CLineChart*>(parent)->setChartActivePointColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ChartNormalPointHoleColors", false, nullptr,
				[](IClass *parent) {return cast<CLineChart*>(parent)->getChartNormalPointHoleColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CLineChart*>(parent)->setChartNormalPointHoleColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ChartActivePointHoleColors", false, nullptr,
				[](IClass *parent) {return cast<CLineChart*>(parent)->getChartActivePointHoleColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CLineChart*>(parent)->setChartActivePointHoleColors(value); }))
				->setMinCount(1);
			Add(new CPropertyFloatArray(this, control, L"ChartLineWidthes", false, nullptr,
				[](IClass *parent) {return cast<CLineChart*>(parent)->getChartLineWidthes(); },
				[](IClass *parent, const FloatArray value) {return cast<CLineChart*>(parent)->setChartLineWidthes(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyColorArray(this, control, L"ChartLineColors", false, nullptr,
				[](IClass *parent) {return cast<CLineChart*>(parent)->getChartLineColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CLineChart*>(parent)->setChartLineColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ChartBackgroundColors", false, nullptr,
				[](IClass *parent) {return cast<CLineChart*>(parent)->getChartBackgroundColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CLineChart*>(parent)->setChartBackgroundColors(value); }))
				->setMinCount(1);
			Add(new CPropertyBoolArray(this, control, L"ChartVerticals", false, nullptr,
				[](IClass *parent) {return cast<CLineChart*>(parent)->getChartVerticals(); },
				[](IClass *parent, const BoolArray value) {return cast<CLineChart*>(parent)->setChartVerticals(value); }))
				->setMinCount(1);
		}
	}
}