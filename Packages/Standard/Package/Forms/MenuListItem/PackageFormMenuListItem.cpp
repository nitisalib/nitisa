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
		CPackageFormMenuListItem::CPackageFormMenuListItem(IPackage *package) : CPackageForm(package, L"standard")
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/MenuListItem/FormMenuListItem.h");
		}

		String CPackageFormMenuListItem::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormMenuListItem::getClassName()
		{
			return CFormMenuListItem::ClassName;
		}

		String CPackageFormMenuListItem::getTitle()
		{
			return L"FormMenuListItem";
		}

		String CPackageFormMenuListItem::getDescription()
		{
			return L"MenuListItem";
		}

		String CPackageFormMenuListItem::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormMenuListItem::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormMenuListItem::getInstance()
		{
			return CFormMenuListItem::getInstance();
		}

		IForm *CPackageFormMenuListItem::Create(IWindow *window, IRenderer *renderer)
		{
			return new CFormMenuListItem(window, renderer);
		}

		IPropertyList *CPackageFormMenuListItem::CreatePropertyList(IForm *form)
		{
			CFormMenuListItem *f{ cast<CFormMenuListItem*>(form) };
			if (f)
				return new CFormMenuListItemPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormMenuListItem::CreateEventList(IForm *form)
		{
			CFormMenuListItem *f{ cast<CFormMenuListItem*>(form) };
			if (f)
				return new CFormMenuListItemEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}