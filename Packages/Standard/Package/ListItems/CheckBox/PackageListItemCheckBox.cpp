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
		CPackageListItemCheckBox::CPackageListItemCheckBox(IPackage *package) : CPackageListItem(package, L"standard")
		{
			AddHeaderFile(L"Standard/ListItems/CheckBox/ListItemCheckBox.h");
		}

		String CPackageListItemCheckBox::getCategory()
		{
			return L"Standard";
		}

		String CPackageListItemCheckBox::getClassName()
		{
			return L"ListItemCheckBox";
		}

		String CPackageListItemCheckBox::getTitle()
		{
			return L"CheckBox";
		}

		String CPackageListItemCheckBox::getDescription()
		{
			return L"CheckBox";
		}

		String CPackageListItemCheckBox::getReferenceUrl()
		{
			return L"";
		}

		bool CPackageListItemCheckBox::isInstance(IListItem *listitem)
		{
			return cast<CListItemCheckBox*>(listitem) != nullptr;
		}

		IListItem *CPackageListItemCheckBox::Create(IPropertyList **properties)
		{
			IListItem *result{ new CListItemCheckBox() };
			if (properties)
				*properties = new CListItemCheckBoxPropertyList(getPackage(), result, this);
			return result;
		}

		IPropertyList *CPackageListItemCheckBox::CreatePropertyList(IListItem *listitem)
		{
			if (isInstance(listitem))
				return new CListItemCheckBoxPropertyList(getPackage(), listitem, this);
			return nullptr;
		}
	}
}