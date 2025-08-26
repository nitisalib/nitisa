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
		CCustomCartesianChartPropertyList::CCustomCartesianChartPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");

			Add(new CPropertyPointF(this, control, L"XRange", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getXRange(); },
				[](IClass *parent, const PointF value) {return cast<CCustomCartesianChart*>(parent)->setXRange(value); }));
			Add(new CPropertyPointF(this, control, L"YRange", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getYRange(); },
				[](IClass *parent, const PointF value) {return cast<CCustomCartesianChart*>(parent)->setYRange(value); }));
			Add(new CPropertyPointB(this, control, L"AutoRange", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getAutoRange(); },
				[](IClass *parent, const PointB value) {return cast<CCustomCartesianChart*>(parent)->setAutoRange(value); }));
			Add(new CPropertyChartDataSet(this, control, L"DataSet", nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getDataSet(); },
				[](IClass *parent, IChartDataSet *value) {return cast<CCustomCartesianChart*>(parent)->setDataSet(value, true); },
				[](IClass *parent) {cast<CCustomCartesianChart*>(parent)->Update(); }));

			Add(new CPropertyPointB(this, control, L"ShowAxes", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getShowAxes(); },
				[](IClass *parent, const PointB value) {return cast<CCustomCartesianChart*>(parent)->setShowAxes(value); }));
			Add(new CPropertyPointB(this, control, L"ShowGrid", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getShowGrid(); },
				[](IClass *parent, const PointB value) {return cast<CCustomCartesianChart*>(parent)->setShowGrid(value); }));
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CCustomCartesianChart*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyColor(this, control, L"XAxisColor", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getXAxisColor(); },
				[](IClass *parent, const Color value) {return cast<CCustomCartesianChart*>(parent)->setXAxisColor(value); }));
			Add(new CPropertyColor(this, control, L"YAxisColor", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getYAxisColor(); },
				[](IClass *parent, const Color value) {return cast<CCustomCartesianChart*>(parent)->setYAxisColor(value); }));
			Add(new CPropertyColor(this, control, L"XGridColor", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getXGridColor(); },
				[](IClass *parent, const Color value) {return cast<CCustomCartesianChart*>(parent)->setXGridColor(value); }));
			Add(new CPropertyColor(this, control, L"YGridColor", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getYGridColor(); },
				[](IClass *parent, const Color value) {return cast<CCustomCartesianChart*>(parent)->setYGridColor(value); }));
			Add(new CPropertyPointF(this, control, L"GridStep", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getGridStep(); },
				[](IClass *parent, const PointF value) {return cast<CCustomCartesianChart*>(parent)->setGridStep(value); }))
				->setMin(2 * ntl::Tolerance<float>);
			Add(new CPropertyPointF(this, control, L"LabelPadding", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getLabelPadding(); },
				[](IClass *parent, const PointF value) {return cast<CCustomCartesianChart*>(parent)->setLabelPadding(value); }))
				->setMin(0);
			Add(new CPropertyPointB(this, control, L"ShowLabels", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getShowLabels(); },
				[](IClass *parent, const PointB value) {return cast<CCustomCartesianChart*>(parent)->setShowLabels(value); }));
			Add(new CPropertyBool(this, control, L"XLabelsAtTop", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->isXLabelsAtTop(); },
				[](IClass *parent, const bool value) {return cast<CCustomCartesianChart*>(parent)->setXLabelsAtTop(value); }));
			Add(new CPropertyBool(this, control, L"YLabelsAtRight", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->isYLabelsAtRight(); },
				[](IClass *parent, const bool value) {return cast<CCustomCartesianChart*>(parent)->setYLabelsAtRight(value); }));
			Add(new CPropertyPoint(this, control, L"LabelSigns", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getLabelSigns(); },
				[](IClass *parent, const Point value) {return cast<CCustomCartesianChart*>(parent)->setLabelSigns(value); }))
				->setMin(0)->setMax(9);
			Add(new CPropertyFloat(this, control, L"PointSize", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getPointSize(); },
				[](IClass *parent, const float value) {return cast<CCustomCartesianChart*>(parent)->setPointSize(value); }))
				->setMin(1);
			Add(new CPropertyPointB(this, control, L"AutoGrid", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getAutoGrid(); },
				[](IClass *parent, const PointB value) {return cast<CCustomCartesianChart*>(parent)->setAutoGrid(value); }));
			Add(new CPropertyPointF(this, control, L"DefaultGridStep", false, nullptr,
				[](IClass *parent) {return cast<CCustomCartesianChart*>(parent)->getDefaultGridStep(); },
				[](IClass *parent, const PointF value) {return cast<CCustomCartesianChart*>(parent)->setDefaultGridStep(value); }))
				->setMin(2 * ntl::Tolerance<float>);
		}
	}
}