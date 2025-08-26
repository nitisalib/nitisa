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
		CRadarChartPropertyList::CRadarChartPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
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

			Add(new CPropertyChartDataSet(this, control, L"DataSet", nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getDataSet(); },
				[](IClass *parent, IChartDataSet *value) {return cast<CRadarChart*>(parent)->setDataSet(value, true); },
				[](IClass *parent) {cast<CRadarChart*>(parent)->Update(); }));
			Add(new CPropertyBool(this, control, L"AutoRange", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->isAutoRange(); },
				[](IClass *parent, const bool value) {return cast<CRadarChart*>(parent)->setAutoRange(value); }));
			Add(new CPropertyFloat(this, control, L"Range", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getRange(); },
				[](IClass *parent, const float value) {return cast<CRadarChart*>(parent)->setRange(value); }));
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CRadarChart*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyBool(this, control, L"DrawGrid", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->isDrawGrid(); },
				[](IClass *parent, const bool value) {return cast<CRadarChart*>(parent)->setDrawGrid(value); }));
			Add(new CPropertyBool(this, control, L"AutoGridStep", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->isAutoGridStep(); },
				[](IClass *parent, const bool value) {return cast<CRadarChart*>(parent)->setAutoGridStep(value); }));
			Add(new CPropertyFloat(this, control, L"GridStep", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getGridStep(); },
				[](IClass *parent, const float value) {return cast<CRadarChart*>(parent)->setGridStep(value); }))
				->setMin(2 * ntl::Tolerance<float>);
			Add(new CPropertyFloat(this, control, L"DefaultGridStep", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getDefaultGridStep(); },
				[](IClass *parent, const float value) {return cast<CRadarChart*>(parent)->setDefaultGridStep(value); }))
				->setMin(2 * ntl::Tolerance<float>);
			Add(new CPropertyColor(this, control, L"GridColor", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getGridColor(); },
				[](IClass *parent, const Color value) {return cast<CRadarChart*>(parent)->setGridColor(value); }));
			Add(new CPropertyBool(this, control, L"DrawLabels", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->isDrawLabels(); },
				[](IClass *parent, const bool value) {return cast<CRadarChart*>(parent)->setDrawLabels(value); }));
			Add(new CPropertyColor(this, control, L"LabelsColor", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getLabelsColor(); },
				[](IClass *parent, const Color value) {return cast<CRadarChart*>(parent)->setLabelsColor(value); }));
			Add(new CPropertyInteger(this, control, L"LabelSigns", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getLabelSigns(); },
				[](IClass *parent, const int value) {return cast<CRadarChart*>(parent)->setLabelSigns(value); }))
				->setMin(0)->setMax(9);
			Add(new CPropertyFloat(this, control, L"Quality", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getQuality(); },
				[](IClass *parent, const float value) {return cast<CRadarChart*>(parent)->setQuality(value); }))
				->setMin(0)->setMax(1);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CRadarChart*>(parent)->setPadding(value); }))
				->setMin(0)->setAllowInvalid(false);
			Add(new CPropertyFloat(this, control, L"PointSize", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getPointSize(); },
				[](IClass *parent, const float value) {return cast<CRadarChart*>(parent)->setPointSize(value); }))
				->setMin(1);
			Add(new CPropertyBool(this, control, L"DrawLegend", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->isDrawLegend(); },
				[](IClass *parent, const bool value) {return cast<CRadarChart*>(parent)->setDrawLegend(value); }));
			Add(new CPropertyColor(this, control, L"LegendColor", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getLegendColor(); },
				[](IClass *parent, const Color value) {return cast<CRadarChart*>(parent)->setLegendColor(value); }));
			
			Add(new CPropertyColorArray(this, control, L"BackgroundColors", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getBackgroundColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CRadarChart*>(parent)->setBackgroundColors(value); }))
				->setMinCount(1);
			Add(new CPropertyFloatArray(this, control, L"LineWidthes", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getLineWidthes(); },
				[](IClass *parent, const FloatArray value) {return cast<CRadarChart*>(parent)->setLineWidthes(value); }))
				->setMinCount(1)->setMin(1);
			Add(new CPropertyColorArray(this, control, L"LineColors", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getLineColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CRadarChart*>(parent)->setLineColors(value); }))
				->setMinCount(1);
			Add(new CPropertyFloatArray(this, control, L"NormalPointSizes", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getNormalPointSizes(); },
				[](IClass *parent, const FloatArray value) {return cast<CRadarChart*>(parent)->setNormalPointSizes(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyFloatArray(this, control, L"ActivePointSizes", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getActivePointSizes(); },
				[](IClass *parent, const FloatArray value) {return cast<CRadarChart*>(parent)->setActivePointSizes(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyFloatArray(this, control, L"NormalPointHoles", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getNormalPointHoles(); },
				[](IClass *parent, const FloatArray value) {return cast<CRadarChart*>(parent)->setNormalPointHoles(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyFloatArray(this, control, L"ActivePointHoles", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getActivePointHoles(); },
				[](IClass *parent, const FloatArray value) {return cast<CRadarChart*>(parent)->setActivePointHoles(value); }))
				->setMinCount(1)->setMin(0);
			Add(new CPropertyColorArray(this, control, L"NormalPointColors", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getNormalPointColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CRadarChart*>(parent)->setNormalPointColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ActivePointColors", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getActivePointColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CRadarChart*>(parent)->setActivePointColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"NormalHoleColors", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getNormalHoleColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CRadarChart*>(parent)->setNormalHoleColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ActiveHoleColors", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getActiveHoleColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CRadarChart*>(parent)->setActiveHoleColors(value); }))
				->setMinCount(1);
			Add(new CPropertyBoolArray(this, control, L"DrawPoints", false, nullptr,
				[](IClass *parent) {return cast<CRadarChart*>(parent)->getDrawPoints(); },
				[](IClass *parent, const BoolArray value) {return cast<CRadarChart*>(parent)->setDrawPoints(value); }))
				->setMinCount(1);
		}
	}
}