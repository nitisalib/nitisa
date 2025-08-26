// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
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
		CPackageListItemColor::CPackageListItemColor(IPackage *package) : CPackageListItem(package, L"standard")
		{
			AddHeaderFile(L"Standard/ListItems/Color/ListItemColor.h");
		}

		String CPackageListItemColor::getCategory()
		{
			return L"Standard";
		}

		String CPackageListItemColor::getClassName()
		{
			return L"ListItemColor";
		}

		String CPackageListItemColor::getTitle()
		{
			return L"Color";
		}

		String CPackageListItemColor::getDescription()
		{
			return L"Color";
		}

		String CPackageListItemColor::getReferenceUrl()
		{
			return L"";
		}

		bool CPackageListItemColor::isInstance(IListItem *listitem)
		{
			return cast<CListItemColor*>(listitem) != nullptr;
		}

		IListItem *CPackageListItemColor::Create(IPropertyList **properties)
		{
			IListItem *result{ new CListItemColor() };
			if (properties)
				*properties = new CListItemColorPropertyList(getPackage(), result, this);
			return result;
		}

		IPropertyList *CPackageListItemColor::CreatePropertyList(IListItem *listitem)
		{
			if (isInstance(listitem))
				return new CListItemColorPropertyList(getPackage(), listitem, this);
			return nullptr;
		}
	}
}