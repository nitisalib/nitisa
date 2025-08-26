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
		CPackageListItemMenuRadioButton::CPackageListItemMenuRadioButton(IPackage *package) : CPackageListItemMenu(package, L"standard")
		{
			AddHeaderFile(L"Standard/ListItems/MenuRadioButton/ListItemMenuRadioButton.h");
		}

		String CPackageListItemMenuRadioButton::getClassName()
		{
			return L"ListItemMenuRadioButton";
		}

		String CPackageListItemMenuRadioButton::getTitle()
		{
			return L"MenuRadioButton";
		}

		String CPackageListItemMenuRadioButton::getDescription()
		{
			return L"MenuRadioButton";
		}

		String CPackageListItemMenuRadioButton::getReferenceUrl()
		{
			return L"";
		}

		bool CPackageListItemMenuRadioButton::isInstance(IListItem *listitem)
		{
			return cast<CListItemMenuRadioButton*>(listitem) != nullptr;
		}

		IListItem *CPackageListItemMenuRadioButton::Create(IPropertyList **properties)
		{
			IListItem *result{ new CListItemMenuRadioButton() };
			if (properties)
				*properties = new CListItemMenuRadioButtonPropertyList(getPackage(), result, this);
			return result;
		}

		IPropertyList *CPackageListItemMenuRadioButton::CreatePropertyList(IListItem *listitem)
		{
			if (isInstance(listitem))
				return new CListItemMenuRadioButtonPropertyList(getPackage(), listitem, this);
			return nullptr;
		}
	}
}