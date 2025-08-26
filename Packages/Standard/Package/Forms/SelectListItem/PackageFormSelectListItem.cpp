// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		CPackageFormSelectListItem::CPackageFormSelectListItem(IPackage *package) : CPackageForm(package, L"standard")
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/SelectListItem/FormSelectListItem.h");
		}

		String CPackageFormSelectListItem::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormSelectListItem::getClassName()
		{
			return CFormSelectListItem::ClassName;
		}

		String CPackageFormSelectListItem::getTitle()
		{
			return L"FormSelectListItem";
		}

		String CPackageFormSelectListItem::getDescription()
		{
			return L"SelectListItem";
		}

		String CPackageFormSelectListItem::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormSelectListItem::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormSelectListItem::getInstance()
		{
			return CFormSelectListItem::getInstance();
		}

		IForm *CPackageFormSelectListItem::Create(IWindow *window, IRenderer *renderer)
		{
			return new CFormSelectListItem(window, renderer);
		}

		IPropertyList *CPackageFormSelectListItem::CreatePropertyList(IForm *form)
		{
			CFormSelectListItem *f{ cast<CFormSelectListItem*>(form) };
			if (f)
				return new CFormSelectListItemPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormSelectListItem::CreateEventList(IForm *form)
		{
			CFormSelectListItem *f{ cast<CFormSelectListItem*>(form) };
			if (f)
				return new CFormSelectListItemEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}