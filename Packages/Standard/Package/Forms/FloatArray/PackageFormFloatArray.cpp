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
		CPackageFormFloatArray::CPackageFormFloatArray(IPackage *package) : CPackageForm(package, L"standard")
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/FloatArray/FormFloatArray.h");
		}

		String CPackageFormFloatArray::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormFloatArray::getClassName()
		{
			return CFormFloatArray::ClassName;
		}

		String CPackageFormFloatArray::getTitle()
		{
			return L"FormFloatArray";
		}

		String CPackageFormFloatArray::getDescription()
		{
			return L"FloatArray";
		}

		String CPackageFormFloatArray::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormFloatArray::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormFloatArray::getInstance()
		{
			return CFormFloatArray::getInstance();
		}

		IForm *CPackageFormFloatArray::Create(IWindow *window, IRenderer *renderer)
		{
			return new CFormFloatArray(window, renderer);
		}

		IPropertyList *CPackageFormFloatArray::CreatePropertyList(IForm *form)
		{
			CFormFloatArray *f{ cast<CFormFloatArray*>(form) };
			if (f)
				return new CFormFloatArrayPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormFloatArray::CreateEventList(IForm *form)
		{
			CFormFloatArray *f{ cast<CFormFloatArray*>(form) };
			if (f)
				return new CFormFloatArrayEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}