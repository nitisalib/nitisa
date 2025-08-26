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
		CSemiDoughnutChartPropertyList::CSemiDoughnutChartPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CCustomRadialChartPropertyList(package, control, entity)
		{
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CSemiDoughnutChart*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) {return cast<CSemiDoughnutChart*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"Quality", false, nullptr,
				[](IClass *parent) {return cast<CSemiDoughnutChart*>(parent)->getQuality(); },
				[](IClass *parent, const float value) {return cast<CSemiDoughnutChart*>(parent)->setQuality(value); }))
				->setMin(0)->setMax(1);
			Add(new CPropertyFloat(this, control, L"Cutout", false, nullptr,
				[](IClass *parent) {return cast<CSemiDoughnutChart*>(parent)->getCutout(); },
				[](IClass *parent, const float value) {return cast<CSemiDoughnutChart*>(parent)->setCutout(value); }))
				->setMin(0)->setMax(1);
			Add(new CPropertyBool(this, control, L"RestartColors", false, nullptr,
				[](IClass *parent) {return cast<CSemiDoughnutChart*>(parent)->isRestartColors(); },
				[](IClass *parent, const bool value) {return cast<CSemiDoughnutChart*>(parent)->setRestartColors(value); }));

			Add(new CPropertyColorArray(this, control, L"NormalColors", false, nullptr,
				[](IClass *parent) {return cast<CSemiDoughnutChart*>(parent)->getNormalColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CSemiDoughnutChart*>(parent)->setNormalColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ActiveColors", false, nullptr,
				[](IClass *parent) {return cast<CSemiDoughnutChart*>(parent)->getActiveColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CSemiDoughnutChart*>(parent)->setActiveColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"NormalBorderColors", false, nullptr,
				[](IClass *parent) {return cast<CSemiDoughnutChart*>(parent)->getNormalBorderColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CSemiDoughnutChart*>(parent)->setNormalBorderColors(value); }))
				->setMinCount(1);
			Add(new CPropertyColorArray(this, control, L"ActiveBorderColors", false, nullptr,
				[](IClass *parent) {return cast<CSemiDoughnutChart*>(parent)->getActiveBorderColors(); },
				[](IClass *parent, const ColorArray value) {return cast<CSemiDoughnutChart*>(parent)->setActiveBorderColors(value); }))
				->setMinCount(1);
		}
	}
}