// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
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
		CPackageListItemMultiButton::CPackageListItemMultiButton(IPackage *package) : CPackageListItem(package, L"standard")
		{
			AddHeaderFile(L"Standard/ListItems/MultiButton/ListItemMultiButton.h");
		}

		String CPackageListItemMultiButton::getCategory()
		{
			return L"Standard";
		}

		String CPackageListItemMultiButton::getClassName()
		{
			return L"ListItemMultiButton";
		}

		String CPackageListItemMultiButton::getTitle()
		{
			return L"MultiButton";
		}

		String CPackageListItemMultiButton::getDescription()
		{
			return L"MultiButton";
		}

		String CPackageListItemMultiButton::getReferenceUrl()
		{
			return L"";
		}

		bool CPackageListItemMultiButton::isInstance(IListItem *listitem)
		{
			return cast<CListItemMultiButton*>(listitem) != nullptr;
		}

		IListItem *CPackageListItemMultiButton::Create(IPropertyList **properties)
		{
			IListItem *result{ new CListItemMultiButton() };
			if (properties)
				*properties = new CListItemMultiButtonPropertyList(getPackage(), result, this);
			return result;
		}

		IPropertyList *CPackageListItemMultiButton::CreatePropertyList(IListItem *listitem)
		{
			if (isInstance(listitem))
				return new CListItemMultiButtonPropertyList(getPackage(), listitem, this);
			return nullptr;
		}
	}
}