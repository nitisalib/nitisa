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
		CPackageListItemMenuLabel::CPackageListItemMenuLabel(IPackage *package) : CPackageListItemMenu(package, L"standard")
		{
			AddHeaderFile(L"Standard/ListItems/MenuLabel/ListItemMenuLabel.h");
		}

		String CPackageListItemMenuLabel::getClassName()
		{
			return L"ListItemMenuLabel";
		}

		String CPackageListItemMenuLabel::getTitle()
		{
			return L"MenuLabel";
		}

		String CPackageListItemMenuLabel::getDescription()
		{
			return L"MenuLabel";
		}

		String CPackageListItemMenuLabel::getReferenceUrl()
		{
			return L"";
		}

		bool CPackageListItemMenuLabel::isInstance(IListItem *listitem)
		{
			return cast<CListItemMenuLabel*>(listitem) != nullptr;
		}

		IListItem *CPackageListItemMenuLabel::Create(IPropertyList **properties)
		{
			IListItem *result{ new CListItemMenuLabel() };
			if (properties)
				*properties = new CListItemMenuLabelPropertyList(getPackage(), result, this);
			return result;
		}

		IPropertyList *CPackageListItemMenuLabel::CreatePropertyList(IListItem *listitem)
		{
			if (isInstance(listitem))
				return new CListItemMenuLabelPropertyList(getPackage(), listitem, this);
			return nullptr;
		}
	}
}