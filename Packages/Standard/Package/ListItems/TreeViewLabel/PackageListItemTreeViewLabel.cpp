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
		CPackageListItemTreeViewLabel::CPackageListItemTreeViewLabel(IPackage *package) : CPackageListItem(package, L"standard")
		{
			AddHeaderFile(L"Standard/ListItems/TreeViewLabel/ListItemTreeViewLabel.h");
		}

		String CPackageListItemTreeViewLabel::getCategory()
		{
			return L"Standard";
		}

		String CPackageListItemTreeViewLabel::getClassName()
		{
			return L"ListItemTreeViewLabel";
		}

		String CPackageListItemTreeViewLabel::getTitle()
		{
			return L"TreeViewLabel";
		}

		String CPackageListItemTreeViewLabel::getDescription()
		{
			return L"TreeViewLabel";
		}

		String CPackageListItemTreeViewLabel::getReferenceUrl()
		{
			return L"";
		}

		bool CPackageListItemTreeViewLabel::isInstance(IListItem *listitem)
		{
			return cast<CListItemTreeViewLabel*>(listitem) != nullptr;
		}

		IListItem *CPackageListItemTreeViewLabel::Create(IPropertyList **properties)
		{
			IListItem *result{ new CListItemTreeViewLabel() };
			if (properties)
				*properties = new CListItemTreeViewLabelPropertyList(getPackage(), result, this);
			return result;
		}

		IPropertyList *CPackageListItemTreeViewLabel::CreatePropertyList(IListItem *listitem)
		{
			if (isInstance(listitem))
				return new CListItemTreeViewLabelPropertyList(getPackage(), listitem, this);
			return nullptr;
		}
	}
}