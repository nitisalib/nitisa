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
		CPackageFormForexChartData::CPackageFormForexChartData(IPackage *package) : CPackageForm(package, L"charts")
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Charts/Forms/ForexChartData/FormForexChartData.h");
		}

		String CPackageFormForexChartData::getCategory()
		{
			return L"Charts";
		}

		String CPackageFormForexChartData::getClassName()
		{
			return CFormForexChartData::ClassName;
		}

		String CPackageFormForexChartData::getTitle()
		{
			return L"FormForexChartData";
		}

		String CPackageFormForexChartData::getDescription()
		{
			return L"ForexChartData";
		}

		String CPackageFormForexChartData::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormForexChartData::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormForexChartData::getInstance()
		{
			return CFormForexChartData::getInstance();
		}

		IForm *CPackageFormForexChartData::Create(IWindow *window, IRenderer *renderer)
		{
			return new CFormForexChartData(window, renderer);
		}

		IPropertyList *CPackageFormForexChartData::CreatePropertyList(IForm *form)
		{
			CFormForexChartData *f{ cast<CFormForexChartData*>(form) };
			if (f)
				return new CFormForexChartDataPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormForexChartData::CreateEventList(IForm *form)
		{
			CFormForexChartData *f{ cast<CFormForexChartData*>(form) };
			if (f)
				return new CFormForexChartDataEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}