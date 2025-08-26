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
		CPackageFormColorArray::CPackageFormColorArray(IPackage *package) : CPackageForm(package, L"standard")
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/ColorArray/FormColorArray.h");
		}

		String CPackageFormColorArray::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormColorArray::getClassName()
		{
			return CFormColorArray::ClassName;
		}

		String CPackageFormColorArray::getTitle()
		{
			return L"FormColorArray";
		}

		String CPackageFormColorArray::getDescription()
		{
			return L"ColorArray";
		}

		String CPackageFormColorArray::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormColorArray::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormColorArray::getInstance()
		{
			return CFormColorArray::getInstance();
		}

		IForm *CPackageFormColorArray::Create(IWindow *window, IRenderer *renderer)
		{
			return new CFormColorArray(window, renderer);
		}

		IPropertyList *CPackageFormColorArray::CreatePropertyList(IForm *form)
		{
			CFormColorArray *f{ cast<CFormColorArray*>(form) };
			if (f)
				return new CFormColorArrayPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormColorArray::CreateEventList(IForm *form)
		{
			CFormColorArray *f{ cast<CFormColorArray*>(form) };
			if (f)
				return new CFormColorArrayEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}