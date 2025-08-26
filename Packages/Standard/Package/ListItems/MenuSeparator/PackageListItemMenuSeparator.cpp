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
		CPackageListItemMenuSeparator::CPackageListItemMenuSeparator(IPackage *package) : CPackageListItemMenu(package, L"standard")
		{
			AddHeaderFile(L"Standard/ListItems/MenuSeparator/ListItemMenuSeparator.h");
		}

		String CPackageListItemMenuSeparator::getClassName()
		{
			return L"ListItemMenuSeparator";
		}

		String CPackageListItemMenuSeparator::getTitle()
		{
			return L"MenuSeparator";
		}

		String CPackageListItemMenuSeparator::getDescription()
		{
			return L"MenuSeparator";
		}

		String CPackageListItemMenuSeparator::getReferenceUrl()
		{
			return L"";
		}

		bool CPackageListItemMenuSeparator::isInstance(IListItem *listitem)
		{
			return cast<CListItemMenuSeparator*>(listitem) != nullptr;
		}

		IListItem *CPackageListItemMenuSeparator::Create(IPropertyList **properties)
		{
			IListItem *result{ new CListItemMenuSeparator() };
			if (properties)
				*properties = new CListItemMenuSeparatorPropertyList(getPackage(), result, this);
			return result;
		}

		IPropertyList *CPackageListItemMenuSeparator::CreatePropertyList(IListItem *listitem)
		{
			if (isInstance(listitem))
				return new CListItemMenuSeparatorPropertyList(getPackage(), listitem, this);
			return nullptr;
		}
	}
}