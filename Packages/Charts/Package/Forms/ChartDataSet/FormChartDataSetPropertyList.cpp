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
		CFormChartDataSetPropertyList::CFormChartDataSetPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyChartDataSet(this, form, L"Value", nullptr,
				[](IClass *parent) {return cast<CFormChartDataSet*>(parent)->getValue(); },
				[](IClass *parent, IChartDataSet *value) {return cast<CFormChartDataSet*>(parent)->setValue(value); },
				[](IClass *parent) { }));
		}
	}
}