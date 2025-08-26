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
		CPackageListItemSelectLabel::CPackageListItemSelectLabel(IPackage *package) : CPackageListItem(package, L"standard")
		{
			AddHeaderFile(L"Standard/ListItems/SelectLabel/ListItemSelectLabel.h");
		}

		String CPackageListItemSelectLabel::getCategory()
		{
			return L"Standard";
		}

		String CPackageListItemSelectLabel::getClassName()
		{
			return L"ListItemSelectLabel";
		}

		String CPackageListItemSelectLabel::getTitle()
		{
			return L"Label";
		}

		String CPackageListItemSelectLabel::getDescription()
		{
			return L"Label";
		}

		String CPackageListItemSelectLabel::getReferenceUrl()
		{
			return L"";
		}

		bool CPackageListItemSelectLabel::isInstance(IListItem *listitem)
		{
			return cast<CListItemSelectLabel*>(listitem) != nullptr;
		}

		IListItem *CPackageListItemSelectLabel::Create(IPropertyList **properties)
		{
			IListItem *result{ new CListItemSelectLabel() };
			if (properties)
				*properties = new CListItemSelectLabelPropertyList(getPackage(), result, this);
			return result;
		}

		IPropertyList *CPackageListItemSelectLabel::CreatePropertyList(IListItem *listitem)
		{
			if (isInstance(listitem))
				return new CListItemSelectLabelPropertyList(getPackage(), listitem, this);
			return nullptr;
		}
	}
}