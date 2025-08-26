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
		CPackageFormImage::CPackageFormImage(IPackage *package) : CPackageForm(package, L"standard")
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/Image/FormImage.h");
		}

		String CPackageFormImage::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormImage::getClassName()
		{
			return CFormImage::ClassName;
		}

		String CPackageFormImage::getTitle()
		{
			return L"FormImage";
		}

		String CPackageFormImage::getDescription()
		{
			return L"Image";
		}

		String CPackageFormImage::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormImage::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormImage::getInstance()
		{
			return CFormImage::getInstance();
		}

		IForm *CPackageFormImage::Create(IWindow *window, IRenderer *renderer)
		{
			return new CFormImage(window, renderer);
		}

		IPropertyList *CPackageFormImage::CreatePropertyList(IForm *form)
		{
			CFormImage *f{ cast<CFormImage*>(form) };
			if (f)
				return new CFormImagePropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormImage::CreateEventList(IForm *form)
		{
			CFormImage *f{ cast<CFormImage*>(form) };
			if (f)
				return new CFormImageEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}