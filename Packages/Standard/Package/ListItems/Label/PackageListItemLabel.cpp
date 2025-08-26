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
		CPackageListItemLabel::CPackageListItemLabel(IPackage *package) : CPackageListItem(package, L"standard")
		{
			AddHeaderFile(L"Standard/ListItems/Label/ListItemLabel.h");
		}

		String CPackageListItemLabel::getCategory()
		{
			return L"Standard";
		}

		String CPackageListItemLabel::getClassName()
		{
			return L"ListItemLabel";
		}

		String CPackageListItemLabel::getTitle()
		{
			return L"Label";
		}

		String CPackageListItemLabel::getDescription()
		{
			return L"Label";
		}

		String CPackageListItemLabel::getReferenceUrl()
		{
			return L"";
		}

		bool CPackageListItemLabel::isInstance(IListItem *listitem)
		{
			return cast<CListItemLabel*>(listitem) != nullptr;
		}

		IListItem *CPackageListItemLabel::Create(IPropertyList **properties)
		{
			IListItem *result{ new CListItemLabel() };
			if (properties)
				*properties = new CListItemLabelPropertyList(getPackage(), result, this);
			return result;
		}

		IPropertyList *CPackageListItemLabel::CreatePropertyList(IListItem *listitem)
		{
			if (isInstance(listitem))
				return new CListItemLabelPropertyList(getPackage(), listitem, this);
			return nullptr;
		}
	}
}