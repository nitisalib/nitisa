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
		CPackageListItemMenuCheckBox::CPackageListItemMenuCheckBox(IPackage *package) : CPackageListItemMenu(package, L"standard")
		{
			AddHeaderFile(L"Standard/ListItems/MenuCheckBox/ListItemMenuCheckBox.h");
		}

		String CPackageListItemMenuCheckBox::getClassName()
		{
			return L"ListItemMenuCheckBox";
		}

		String CPackageListItemMenuCheckBox::getTitle()
		{
			return L"MenuCheckBox";
		}

		String CPackageListItemMenuCheckBox::getDescription()
		{
			return L"MenuCheckBox";
		}

		String CPackageListItemMenuCheckBox::getReferenceUrl()
		{
			return L"";
		}

		bool CPackageListItemMenuCheckBox::isInstance(IListItem *listitem)
		{
			return cast<CListItemMenuCheckBox*>(listitem) != nullptr;
		}

		IListItem *CPackageListItemMenuCheckBox::Create(IPropertyList **properties)
		{
			IListItem *result{ new CListItemMenuCheckBox() };
			if (properties)
				*properties = new CListItemMenuCheckBoxPropertyList(getPackage(), result, this);
			return result;
		}

		IPropertyList *CPackageListItemMenuCheckBox::CreatePropertyList(IListItem *listitem)
		{
			if (isInstance(listitem))
				return new CListItemMenuCheckBoxPropertyList(getPackage(), listitem, this);
			return nullptr;
		}
	}
}