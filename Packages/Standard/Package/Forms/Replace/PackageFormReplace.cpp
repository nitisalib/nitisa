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
		CPackageFormReplace::CPackageFormReplace(IPackage *package) : CPackageForm(package, L"standard")
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/Replace/FormReplace.h");
		}

		String CPackageFormReplace::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormReplace::getClassName()
		{
			return CFormReplace::ClassName;
		}

		String CPackageFormReplace::getTitle()
		{
			return L"FormReplace";
		}

		String CPackageFormReplace::getDescription()
		{
			return L"Replace";
		}

		String CPackageFormReplace::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormReplace::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormReplace::getInstance()
		{
			return CFormReplace::getInstance();
		}

		IForm *CPackageFormReplace::Create(IWindow *window, IRenderer *renderer)
		{
			return new CFormReplace(window, renderer);
		}

		IPropertyList *CPackageFormReplace::CreatePropertyList(IForm *form)
		{
			CFormReplace *f{ cast<CFormReplace*>(form) };
			if (f)
				return new CFormReplacePropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormReplace::CreateEventList(IForm *form)
		{
			CFormReplace *f{ cast<CFormReplace*>(form) };
			if (f)
				return new CFormReplaceEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}