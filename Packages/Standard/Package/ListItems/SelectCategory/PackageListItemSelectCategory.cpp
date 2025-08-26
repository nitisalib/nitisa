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
		CPackageListItemSelectCategory::CPackageListItemSelectCategory(IPackage *package) : CPackageListItem(package, L"standard")
		{
			AddHeaderFile(L"Standard/ListItems/SelectCategory/ListItemSelectCategory.h");
		}

		String CPackageListItemSelectCategory::getCategory()
		{
			return L"Standard";
		}

		String CPackageListItemSelectCategory::getClassName()
		{
			return L"ListItemSelectCategory";
		}

		String CPackageListItemSelectCategory::getTitle()
		{
			return L"Category";
		}

		String CPackageListItemSelectCategory::getDescription()
		{
			return L"Category";
		}

		String CPackageListItemSelectCategory::getReferenceUrl()
		{
			return L"";
		}

		bool CPackageListItemSelectCategory::isInstance(IListItem *listitem)
		{
			return cast<CListItemSelectCategory*>(listitem) != nullptr;
		}

		IListItem *CPackageListItemSelectCategory::Create(IPropertyList **properties)
		{
			IListItem *result{ new CListItemSelectCategory() };
			if (properties)
				*properties = new CListItemSelectCategoryPropertyList(getPackage(), result, this);
			return result;
		}

		IPropertyList *CPackageListItemSelectCategory::CreatePropertyList(IListItem *listitem)
		{
			if (isInstance(listitem))
				return new CListItemSelectCategoryPropertyList(getPackage(), listitem, this);
			return nullptr;
		}
	}
}