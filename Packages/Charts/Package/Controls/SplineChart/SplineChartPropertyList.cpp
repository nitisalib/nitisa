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
		CSplineChartPropertyList::CSplineChartPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CCustomCartesianChartPropertyList(package, control, entity)
		{
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyBoolArray(this, control, L"ChartDrawPoints", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartDrawPoints(); },
				[](IClass *parent, const BoolArray value) {return cast<CSplineChart*>(parent)->setChartDrawPoints(value); }))
				->setMinCount(1);
			Add(new CPropertyBoolArray(this, control, L"ChartDrawLines", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartDrawLines(); },
				[](IClass *parent, const BoolArray value) {return cast<CSplineChart*>(parent)->setChartDrawLines(value); }))
				->setMinCount(1);
			Add(new CPropertyBoolArray(this, control, L"ChartDrawBackgrounds", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartDrawBackgrounds(); },
				[](IClass *parent, const BoolArray value) {return cast<CSplineChart*>(parent)->setChartDrawBackgrounds(value); }))
				->setMinCount(1);
			Add(new CPropertyFloatArray(this, control, L"ChartNormalPointSizes", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartNormalPointSizes(); },
				[](IClass *parent, const FloatArray value) {return cast<CSplineChart*>(parent)->setChartNormalPointSizes(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyFloatArray(this, control, L"ChartActivePointSizes", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartActivePointSizes(); },
				[](IClass *parent, const FloatArray value) {return cast<CSplineChart*>(parent)->setChartActivePointSizes(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyFloatArray(this, control, L"ChartNormalPointHoles", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartNormalPointHoles(); },
				[](IClass *parent, const FloatArray value) {return cast<CSplineChart*>(parent)->setChartNormalPointHoles(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyFloatArray(this, control, L"ChartActivePointHoles", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartActivePointHoles(); },
				[](IClass *parent, const FloatArray value) {return cast<CSplineChart*>(parent)->setChartActivePointHoles(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyColorArray(this, control, L"ChartNormalPointColors", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartNormalPointColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CSplineChart*>(parent)->setChartNormalPointColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ChartActivePointColors", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartActivePointColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CSplineChart*>(parent)->setChartActivePointColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ChartNormalPointHoleColors", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartNormalPointHoleColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CSplineChart*>(parent)->setChartNormalPointHoleColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ChartActivePointHoleColors", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartActivePointHoleColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CSplineChart*>(parent)->setChartActivePointHoleColors(value); }))
				->setMinCount(1);
			Add(new CPropertyFloatArray(this, control, L"ChartLineWidthes", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartLineWidthes(); },
				[](IClass *parent, const FloatArray value) {return cast<CSplineChart*>(parent)->setChartLineWidthes(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyColorArray(this, control, L"ChartLineColors", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartLineColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CSplineChart*>(parent)->setChartLineColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ChartBackgroundColors", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartBackgroundColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CSplineChart*>(parent)->setChartBackgroundColors(value); }))
				->setMinCount(1);
			Add(new CPropertyBoolArray(this, control, L"ChartVerticals", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartVerticals(); },
				[](IClass *parent, const BoolArray value) {return cast<CSplineChart*>(parent)->setChartVerticals(value); }))
				->setMinCount(1);
			Add(new CPropertyFloatArray(this, control, L"ChartTensions", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartTensions(); },
				[](IClass *parent, const FloatArray value) {return cast<CSplineChart*>(parent)->setChartTensions(value); }))
				->setMinCount(1)->setMin(0.001f);
			Add(new CPropertyIntegerArray(this, control, L"ChartCurveRecursionLimits", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartCurveRecursionLimits(); },
				[](IClass *parent, const IntegerArray value) {return cast<CSplineChart*>(parent)->setChartCurveRecursionLimits(value); }))
				->setMinCount(1)->setMin(1)->setMax(64);
			Add(new CPropertyFloatArray(this, control, L"ChartDistanceTolerances", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartDistanceTolerances(); },
				[](IClass *parent, const FloatArray value) {return cast<CSplineChart*>(parent)->setChartDistanceTolerances(value); }))
				->setMinCount(1)->setMin(0.0001f);
			Add(new CPropertyFloatArray(this, control, L"ChartAngleTolerances", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartAngleTolerances(); },
				[](IClass *parent, const FloatArray value) {return cast<CSplineChart*>(parent)->setChartAngleTolerances(value); }))
				->setMinCount(1)->setMin(0.0001f);
			Add(new CPropertyFloatArray(this, control, L"ChartCuspLimits", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartCuspLimits(); },
				[](IClass *parent, const FloatArray value) {return cast<CSplineChart*>(parent)->setChartCuspLimits(value); }))
				->setMinCount(1)->setMin(0.0001f);
			Add(new CPropertyFloatArray(this, control, L"ChartCurveAngleTolerances", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartCurveAngleTolerances(); },
				[](IClass *parent, const FloatArray value) {return cast<CSplineChart*>(parent)->setChartCurveAngleTolerances(value); }))
				->setMinCount(1)->setMin(0.0001f);
			Add(new CPropertyFloatArray(this, control, L"ChartCurveCollinearityTolerances", false, nullptr,
				[](IClass *parent) {return cast<CSplineChart*>(parent)->getChartCurveCollinearityTolerances(); },
				[](IClass *parent, const FloatArray value) {return cast<CSplineChart*>(parent)->setChartCurveCollinearityTolerances(value); }))
				->setMinCount(1)->setMin(0.0001f);
		}
	}
}