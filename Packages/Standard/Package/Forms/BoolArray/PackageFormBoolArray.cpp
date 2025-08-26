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
		CPackageFormBoolArray::CPackageFormBoolArray(IPackage *package) : CPackageForm(package, L"standard")
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/BoolArray/FormBoolArray.h");
		}

		String CPackageFormBoolArray::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormBoolArray::getClassName()
		{
			return CFormBoolArray::ClassName;
		}

		String CPackageFormBoolArray::getTitle()
		{
			return L"FormBoolArray";
		}

		String CPackageFormBoolArray::getDescription()
		{
			return L"BoolArray";
		}

		String CPackageFormBoolArray::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormBoolArray::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormBoolArray::getInstance()
		{
			return CFormBoolArray::getInstance();
		}

		IForm *CPackageFormBoolArray::Create(IWindow *window, IRenderer *renderer)
		{
			return new CFormBoolArray(window, renderer);
		}

		IPropertyList *CPackageFormBoolArray::CreatePropertyList(IForm *form)
		{
			CFormBoolArray *f{ cast<CFormBoolArray*>(form) };
			if (f)
				return new CFormBoolArrayPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormBoolArray::CreateEventList(IForm *form)
		{
			CFormBoolArray *f{ cast<CFormBoolArray*>(form) };
			if (f)
				return new CFormBoolArrayEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}