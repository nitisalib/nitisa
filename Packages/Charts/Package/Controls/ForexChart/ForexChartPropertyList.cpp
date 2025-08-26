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
		CForexChartPropertyList::CForexChartPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyPointD(this, control, L"XRange", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getXRange(); },
				[](IClass *parent, const PointD value) {return cast<CForexChart*>(parent)->setXRange(value); }));
			Add(new CPropertyPointD(this, control, L"YRange", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getYRange(); },
				[](IClass *parent, const PointD value) {return cast<CForexChart*>(parent)->setYRange(value); }));
			Add(new CPropertyPointB(this, control, L"AutoRange", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getAutoRange(); },
				[](IClass *parent, const PointB value) {return cast<CForexChart*>(parent)->setAutoRange(value); }));
			Add(new CPropertyForexChartData(this, control, L"Data", nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getData(); },
				[](IClass *parent, IForexChart::IForexChartData *value) {return cast<CForexChart*>(parent)->setData(value, true); },
				[](IClass *parent) {cast<CForexChart*>(parent)->Update(); }));

			Add(new CPropertyPointB(this, control, L"ShowAxes", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getShowAxes(); },
				[](IClass *parent, const PointB value) {return cast<CForexChart*>(parent)->setShowAxes(value); }));
			Add(new CPropertyPointB(this, control, L"ShowGrid", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getShowGrid(); },
				[](IClass *parent, const PointB value) {return cast<CForexChart*>(parent)->setShowGrid(value); }));
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CForexChart*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyColor(this, control, L"XAxisColor", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getXAxisColor(); },
				[](IClass *parent, const Color value) {return cast<CForexChart*>(parent)->setXAxisColor(value); }));
			Add(new CPropertyColor(this, control, L"YAxisColor", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getYAxisColor(); },
				[](IClass *parent, const Color value) {return cast<CForexChart*>(parent)->setYAxisColor(value); }));
			Add(new CPropertyColor(this, control, L"XGridColor", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getXGridColor(); },
				[](IClass *parent, const Color value) {return cast<CForexChart*>(parent)->setXGridColor(value); }));
			Add(new CPropertyColor(this, control, L"YGridColor", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getYGridColor(); },
				[](IClass *parent, const Color value) {return cast<CForexChart*>(parent)->setYGridColor(value); }));
			Add(new CPropertyPointD(this, control, L"GridStep", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getGridStep(); },
				[](IClass *parent, const PointD value) {return cast<CForexChart*>(parent)->setGridStep(value); }))
				->setMin(2 * ntl::Tolerance<float>);
			Add(new CPropertyPointF(this, control, L"LabelPadding", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getLabelPadding(); },
				[](IClass *parent, const PointF value) {return cast<CForexChart*>(parent)->setLabelPadding(value); }))
				->setMin(0);
			Add(new CPropertyPointB(this, control, L"ShowLabels", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getShowLabels(); },
				[](IClass *parent, const PointB value) {return cast<CForexChart*>(parent)->setShowLabels(value); }));
			Add(new CPropertyBool(this, control, L"XLabelsAtTop", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->isXLabelsAtTop(); },
				[](IClass *parent, const bool value) {return cast<CForexChart*>(parent)->setXLabelsAtTop(value); }));
			Add(new CPropertyBool(this, control, L"YLabelsAtRight", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->isYLabelsAtRight(); },
				[](IClass *parent, const bool value) {return cast<CForexChart*>(parent)->setYLabelsAtRight(value); }));
			Add(new CPropertyPoint(this, control, L"LabelSigns", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getLabelSigns(); },
				[](IClass *parent, const Point value) {return cast<CForexChart*>(parent)->setLabelSigns(value); }))
				->setMin(0)->setMax(9);
			Add(new CPropertyColor(this, control, L"XLabelsColor", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getXLabelsColor(); },
				[](IClass *parent, const Color value) {return cast<CForexChart*>(parent)->setXLabelsColor(value); }));
			Add(new CPropertyColor(this, control, L"YLabelsColor", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getYLabelsColor(); },
				[](IClass *parent, const Color value) {return cast<CForexChart*>(parent)->setYLabelsColor(value); }));
			Add(new CPropertyPointB(this, control, L"AutoGrid", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getAutoGrid(); },
				[](IClass *parent, const PointB value) {return cast<CForexChart*>(parent)->setAutoGrid(value); }));
			Add(new CPropertyPointD(this, control, L"DefaultGridStep", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getDefaultGridStep(); },
				[](IClass *parent, const PointD value) {return cast<CForexChart*>(parent)->setDefaultGridStep(value); }))
				->setMin(2 * ntl::Tolerance<float>);
			Add(new CPropertyFloat(this, control, L"BarWidth", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getBarWidth(); },
				[](IClass *parent, const float value) {return cast<CForexChart*>(parent)->setBarWidth(value); }))
				->setMin(1);
			Add(new CPropertyColor(this, control, L"NormalPositiveBarBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getNormalPositiveBarBorderColor(); },
				[](IClass *parent, const Color value) {return cast<CForexChart*>(parent)->setNormalPositiveBarBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"ActivePositiveBarBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getActivePositiveBarBorderColor(); },
				[](IClass *parent, const Color value) {return cast<CForexChart*>(parent)->setActivePositiveBarBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"NormalNegativeBarBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getNormalNegativeBarBorderColor(); },
				[](IClass *parent, const Color value) {return cast<CForexChart*>(parent)->setNormalNegativeBarBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"ActiveNegativeBarBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getActiveNegativeBarBorderColor(); },
				[](IClass *parent, const Color value) {return cast<CForexChart*>(parent)->setActiveNegativeBarBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"NormalPositiveBarBackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getNormalPositiveBarBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CForexChart*>(parent)->setNormalPositiveBarBackgroundColor(value); }));
			Add(new CPropertyColor(this, control, L"ActivePositiveBarBackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getActivePositiveBarBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CForexChart*>(parent)->setActivePositiveBarBackgroundColor(value); }));
			Add(new CPropertyColor(this, control, L"NormalNegativeBarBackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getNormalNegativeBarBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CForexChart*>(parent)->setNormalNegativeBarBackgroundColor(value); }));
			Add(new CPropertyColor(this, control, L"ActiveNegativeBarBackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->getActiveNegativeBarBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CForexChart*>(parent)->setActiveNegativeBarBackgroundColor(value); }));
			Add(new CPropertyBool(this, control, L"CandleStick", false, nullptr,
				[](IClass *parent) {return cast<CForexChart*>(parent)->isCandleStick(); },
				[](IClass *parent, const bool value) {return cast<CForexChart*>(parent)->setCandlestick(value); }));
		}
	}
}