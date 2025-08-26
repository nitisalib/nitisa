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
	namespace standard
	{
		CPackageFormColor::CPackageFormColor(IPackage *package) : CPackageForm(package, L"standard")
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/Color/FormColor.h");
		}

		String CPackageFormColor::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormColor::getClassName()
		{
			return CFormColor::ClassName;
		}

		String CPackageFormColor::getTitle()
		{
			return L"FormColor";
		}

		String CPackageFormColor::getDescription()
		{
			return L"Color";
		}

		String CPackageFormColor::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormColor::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormColor::getInstance()
		{
			return CFormColor::getInstance();
		}

		IForm *CPackageFormColor::Create(IWindow *window, IRenderer *renderer)
		{
			return new CFormColor(window, renderer);
		}

		IPropertyList *CPackageFormColor::CreatePropertyList(IForm *form)
		{
			CFormColor *f{ cast<CFormColor*>(form) };
			if (f)
				return new CFormColorPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormColor::CreateEventList(IForm *form)
		{
			CFormColor *f{ cast<CFormColor*>(form) };
			if (f)
				return new CFormColorEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}