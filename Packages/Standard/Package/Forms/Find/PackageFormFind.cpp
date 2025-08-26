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
		CPackageFormFind::CPackageFormFind(IPackage *package) : CPackageForm(package, L"standard")
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/Find/FormFind.h");
		}

		String CPackageFormFind::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormFind::getClassName()
		{
			return CFormFind::ClassName;
		}

		String CPackageFormFind::getTitle()
		{
			return L"FormFind";
		}

		String CPackageFormFind::getDescription()
		{
			return L"Find";
		}

		String CPackageFormFind::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormFind::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormFind::getInstance()
		{
			return CFormFind::getInstance();
		}

		IForm *CPackageFormFind::Create(IWindow *window, IRenderer *renderer)
		{
			return new CFormFind(window, renderer);
		}

		IPropertyList *CPackageFormFind::CreatePropertyList(IForm *form)
		{
			CFormFind *f{ cast<CFormFind*>(form) };
			if (f)
				return new CFormFindPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormFind::CreateEventList(IForm *form)
		{
			CFormFind *f{ cast<CFormFind*>(form) };
			if (f)
				return new CFormFindEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}