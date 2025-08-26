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
		CPackageListItemIcon::CPackageListItemIcon(IPackage *package) : CPackageListItem(package, L"standard")
		{
			AddHeaderFile(L"Standard/ListItems/Icon/ListItemIcon.h");
		}

		String CPackageListItemIcon::getCategory()
		{
			return L"Standard";
		}

		String CPackageListItemIcon::getClassName()
		{
			return L"ListItemIcon";
		}

		String CPackageListItemIcon::getTitle()
		{
			return L"Icon";
		}

		String CPackageListItemIcon::getDescription()
		{
			return L"Icon";
		}

		String CPackageListItemIcon::getReferenceUrl()
		{
			return L"";
		}

		bool CPackageListItemIcon::isInstance(IListItem *listitem)
		{
			return cast<CListItemIcon*>(listitem) != nullptr;
		}

		IListItem *CPackageListItemIcon::Create(IPropertyList **properties)
		{
			IListItem *result{ new CListItemIcon() };
			if (properties)
				*properties = new CListItemIconPropertyList(getPackage(), result, this);
			return result;
		}

		IPropertyList *CPackageListItemIcon::CreatePropertyList(IListItem *listitem)
		{
			if (isInstance(listitem))
				return new CListItemIconPropertyList(getPackage(), listitem, this);
			return nullptr;
		}
	}
}