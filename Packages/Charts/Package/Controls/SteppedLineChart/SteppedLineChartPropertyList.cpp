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
		CSteppedLineChartPropertyList::CSteppedLineChartPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CCustomCartesianChartPropertyList(package, control, entity)
		{
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyBoolArray(this, control, L"ChartDrawPoints", false, nullptr,
				[](IClass *parent) {return cast<CSteppedLineChart*>(parent)->getChartDrawPoints(); },
				[](IClass *parent, const BoolArray value) {return cast<CSteppedLineChart*>(parent)->setChartDrawPoints(value); }))
				->setMinCount(1);
			Add(new CPropertyBoolArray(this, control, L"ChartDrawLines", false, nullptr,
				[](IClass *parent) {return cast<CSteppedLineChart*>(parent)->getChartDrawLines(); },
				[](IClass *parent, const BoolArray value) {return cast<CSteppedLineChart*>(parent)->setChartDrawLines(value); }))
				->setMinCount(1);
			Add(new CPropertyBoolArray(this, control, L"ChartDrawBackgrounds", false, nullptr,
				[](IClass *parent) {return cast<CSteppedLineChart*>(parent)->getChartDrawBackgrounds(); },
				[](IClass *parent, const BoolArray value) {return cast<CSteppedLineChart*>(parent)->setChartDrawBackgrounds(value); }))
				->setMinCount(1);
			Add(new CPropertyFloatArray(this, control, L"ChartNormalPointSizes", false, nullptr,
				[](IClass *parent) {return cast<CSteppedLineChart*>(parent)->getChartNormalPointSizes(); },
				[](IClass *parent, const FloatArray value) {return cast<CSteppedLineChart*>(parent)->setChartNormalPointSizes(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyFloatArray(this, control, L"ChartActivePointSizes", false, nullptr,
				[](IClass *parent) {return cast<CSteppedLineChart*>(parent)->getChartActivePointSizes(); },
				[](IClass *parent, const FloatArray value) {return cast<CSteppedLineChart*>(parent)->setChartActivePointSizes(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyFloatArray(this, control, L"ChartNormalPointHoles", false, nullptr,
				[](IClass *parent) {return cast<CSteppedLineChart*>(parent)->getChartNormalPointHoles(); },
				[](IClass *parent, const FloatArray value) {return cast<CSteppedLineChart*>(parent)->setChartNormalPointHoles(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyFloatArray(this, control, L"ChartActivePointHoles", false, nullptr,
				[](IClass *parent) {return cast<CSteppedLineChart*>(parent)->getChartActivePointHoles(); },
				[](IClass *parent, const FloatArray value) {return cast<CSteppedLineChart*>(parent)->setChartActivePointHoles(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyColorArray(this, control, L"ChartNormalPointColors", false, nullptr,
				[](IClass *parent) {return cast<CSteppedLineChart*>(parent)->getChartNormalPointColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CSteppedLineChart*>(parent)->setChartNormalPointColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ChartActivePointColors", false, nullptr,
				[](IClass *parent) {return cast<CSteppedLineChart*>(parent)->getChartActivePointColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CSteppedLineChart*>(parent)->setChartActivePointColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ChartNormalPointHoleColors", false, nullptr,
				[](IClass *parent) {return cast<CSteppedLineChart*>(parent)->getChartNormalPointHoleColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CSteppedLineChart*>(parent)->setChartNormalPointHoleColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ChartActivePointHoleColors", false, nullptr,
				[](IClass *parent) {return cast<CSteppedLineChart*>(parent)->getChartActivePointHoleColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CSteppedLineChart*>(parent)->setChartActivePointHoleColors(value); }))
				->setMinCount(1);
			Add(new CPropertyFloatArray(this, control, L"ChartLineWidthes", false, nullptr,
				[](IClass *parent) {return cast<CSteppedLineChart*>(parent)->getChartLineWidthes(); },
				[](IClass *parent, const FloatArray value) {return cast<CSteppedLineChart*>(parent)->setChartLineWidthes(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyColorArray(this, control, L"ChartLineColors", false, nullptr,
				[](IClass *parent) {return cast<CSteppedLineChart*>(parent)->getChartLineColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CSteppedLineChart*>(parent)->setChartLineColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ChartBackgroundColors", false, nullptr,
				[](IClass *parent) {return cast<CSteppedLineChart*>(parent)->getChartBackgroundColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CSteppedLineChart*>(parent)->setChartBackgroundColors(value); }))
				->setMinCount(1);
			Add(new CPropertyBoolArray(this, control, L"ChartVerticals", false, nullptr,
				[](IClass *parent) {return cast<CSteppedLineChart*>(parent)->getChartVerticals(); },
				[](IClass *parent, const BoolArray value) {return cast<CSteppedLineChart*>(parent)->setChartVerticals(value); }))
				->setMinCount(1);
			Add(new CPropertyLineInterpolationPositionArray(this, control, L"ChartInterpolationPositions", false, nullptr,
				[](IClass *parent) {return cast<CSteppedLineChart*>(parent)->getChartInterpolationPositions(); },
				[](IClass *parent, const std::vector<LineInterpolationPosition> value) {return cast<CSteppedLineChart*>(parent)->setChartInterpolationPositions(value); }))
				->setMinCount(1);
		}
	}
}