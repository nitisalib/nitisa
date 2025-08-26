// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
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
		CCustomRadialChartPropertyList::CCustomRadialChartPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");

			Add(new CPropertyChartDataSet(this, control, L"DataSet", nullptr,
				[](IClass *parent) {return cast<CCustomRadialChart*>(parent)->getDataSet(); },
				[](IClass *parent, IChartDataSet *value) {return cast<CCustomRadialChart*>(parent)->setDataSet(value, true); },
				[](IClass *parent) {cast<CCustomRadialChart*>(parent)->Update(); }));

			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CCustomRadialChart*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CCustomRadialChart*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CCustomRadialChart*>(parent)->getBackgroundGradient(); }));
		}
	}
}