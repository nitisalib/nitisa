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
		CPolarAreaChartPropertyList::CPolarAreaChartPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
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
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->getDataSet(); },
				[](IClass *parent, IChartDataSet *value) {return cast<CPolarAreaChart*>(parent)->setDataSet(value, true); },
				[](IClass *parent) {cast<CPolarAreaChart*>(parent)->Update(); }));
			Add(new CPropertyBool(this, control, L"AutoRange", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->isAutoRange(); },
				[](IClass *parent, const bool value) {return cast<CPolarAreaChart*>(parent)->setAutoRange(value); }));
			Add(new CPropertyFloat(this, control, L"Range", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->getRange(); },
				[](IClass *parent, const float value) {return cast<CPolarAreaChart*>(parent)->setRange(value); }));
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CPolarAreaChart*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyBool(this, control, L"DrawGrid", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->isDrawGrid(); },
				[](IClass *parent, const bool value) {return cast<CPolarAreaChart*>(parent)->setDrawGrid(value); }));
			Add(new CPropertyBool(this, control, L"AutoGridStep", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->isAutoGridStep(); },
				[](IClass *parent, const bool value) {return cast<CPolarAreaChart*>(parent)->setAutoGridStep(value); }));
			Add(new CPropertyFloat(this, control, L"GridStep", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->getGridStep(); },
				[](IClass *parent, const float value) {return cast<CPolarAreaChart*>(parent)->setGridStep(value); }))
				->setMin(2 * ntl::Tolerance<float>);
			Add(new CPropertyFloat(this, control, L"DefaultGridStep", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->getDefaultGridStep(); },
				[](IClass *parent, const float value) {return cast<CPolarAreaChart*>(parent)->setDefaultGridStep(value); }))
				->setMin(2 * ntl::Tolerance<float>);
			Add(new CPropertyColor(this, control, L"GridColor", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->getGridColor(); },
				[](IClass *parent, const Color value) {return cast<CPolarAreaChart*>(parent)->setGridColor(value); }));
			Add(new CPropertyBool(this, control, L"DrawLabels", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->isDrawLabels(); },
				[](IClass *parent, const bool value) {return cast<CPolarAreaChart*>(parent)->setDrawLabels(value); }));
			Add(new CPropertyColor(this, control, L"LabelsColor", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->getLabelsColor(); },
				[](IClass *parent, const Color value) {return cast<CPolarAreaChart*>(parent)->setLabelsColor(value); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) {return cast<CPolarAreaChart*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"Quality", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->getQuality(); },
				[](IClass *parent, const float value) {return cast<CPolarAreaChart*>(parent)->setQuality(value); }))
				->setMin(0)->setMax(1);
			Add(new CPropertyInteger(this, control, L"LabelSigns", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->getLabelSigns(); },
				[](IClass *parent, const int value) {return cast<CPolarAreaChart*>(parent)->setLabelSigns(value); }))
				->setMin(0)->setMax(9);

			Add(new CPropertyColorArray(this, control, L"NormalColors", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->getNormalColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CPolarAreaChart*>(parent)->setNormalColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ActiveColors", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->getActiveColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CPolarAreaChart*>(parent)->setActiveColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"NormalBorderColors", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->getNormalBorderColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CPolarAreaChart*>(parent)->setNormalBorderColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ActiveBorderColors", false, nullptr,
				[](IClass *parent) {return cast<CPolarAreaChart*>(parent)->getActiveBorderColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CPolarAreaChart*>(parent)->setActiveBorderColors(value); }))
				->setMinCount(1);
		}
	}
}