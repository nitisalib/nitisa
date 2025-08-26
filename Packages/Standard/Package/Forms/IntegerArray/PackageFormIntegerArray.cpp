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
		CPackageFormIntegerArray::CPackageFormIntegerArray(IPackage *package) : CPackageForm(package, L"standard")
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/IntegerArray/FormIntegerArray.h");
		}

		String CPackageFormIntegerArray::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormIntegerArray::getClassName()
		{
			return CFormIntegerArray::ClassName;
		}

		String CPackageFormIntegerArray::getTitle()
		{
			return L"FormIntegerArray";
		}

		String CPackageFormIntegerArray::getDescription()
		{
			return L"IntegerArray";
		}

		String CPackageFormIntegerArray::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormIntegerArray::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormIntegerArray::getInstance()
		{
			return CFormIntegerArray::getInstance();
		}

		IForm *CPackageFormIntegerArray::Create(IWindow *window, IRenderer *renderer)
		{
			return new CFormIntegerArray(window, renderer);
		}

		IPropertyList *CPackageFormIntegerArray::CreatePropertyList(IForm *form)
		{
			CFormIntegerArray *f{ cast<CFormIntegerArray*>(form) };
			if (f)
				return new CFormIntegerArrayPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormIntegerArray::CreateEventList(IForm *form)
		{
			CFormIntegerArray *f{ cast<CFormIntegerArray*>(form) };
			if (f)
				return new CFormIntegerArrayEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}