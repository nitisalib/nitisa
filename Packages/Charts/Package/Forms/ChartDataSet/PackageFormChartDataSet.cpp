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
		CPackageFormChartDataSet::CPackageFormChartDataSet(IPackage *package) : CPackageForm(package, L"charts")
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Charts/Forms/ChartDataSet/FormChartDataSet.h");
		}

		String CPackageFormChartDataSet::getCategory()
		{
			return L"Charts";
		}

		String CPackageFormChartDataSet::getClassName()
		{
			return CFormChartDataSet::ClassName;
		}

		String CPackageFormChartDataSet::getTitle()
		{
			return L"FormChartDataSet";
		}

		String CPackageFormChartDataSet::getDescription()
		{
			return L"ChartDataSet";
		}

		String CPackageFormChartDataSet::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormChartDataSet::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormChartDataSet::getInstance()
		{
			return CFormChartDataSet::getInstance();
		}

		IForm *CPackageFormChartDataSet::Create(IWindow *window, IRenderer *renderer)
		{
			return new CFormChartDataSet(window, renderer);
		}

		IPropertyList *CPackageFormChartDataSet::CreatePropertyList(IForm *form)
		{
			CFormChartDataSet *f{ cast<CFormChartDataSet*>(form) };
			if (f)
				return new CFormChartDataSetPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormChartDataSet::CreateEventList(IForm *form)
		{
			CFormChartDataSet *f{ cast<CFormChartDataSet*>(form) };
			if (f)
				return new CFormChartDataSetEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}