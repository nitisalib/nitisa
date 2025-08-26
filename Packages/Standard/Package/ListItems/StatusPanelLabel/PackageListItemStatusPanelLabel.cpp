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
		CPackageListItemStatusPanelLabel::CPackageListItemStatusPanelLabel(IPackage *package) : CPackageListItemStatusPanel(package, L"standard")
		{
			AddHeaderFile(L"Standard/ListItems/StatusPanelLabel/ListItemStatusPanelLabel.h");
		}

		String CPackageListItemStatusPanelLabel::getClassName()
		{
			return L"ListItemStatusPanelLabel";
		}

		String CPackageListItemStatusPanelLabel::getTitle()
		{
			return L"StatusPanelLabel";
		}

		String CPackageListItemStatusPanelLabel::getDescription()
		{
			return L"StatusPanelLabel";
		}

		String CPackageListItemStatusPanelLabel::getReferenceUrl()
		{
			return L"";
		}

		bool CPackageListItemStatusPanelLabel::isInstance(IListItem *listitem)
		{
			return cast<CListItemStatusPanelLabel*>(listitem) != nullptr;
		}

		IListItem *CPackageListItemStatusPanelLabel::Create(IPropertyList **properties)
		{
			IListItem *result{ new CListItemStatusPanelLabel() };
			if (properties)
				*properties = new CListItemStatusPanelLabelPropertyList(getPackage(), result, this);
			return result;
		}

		IPropertyList *CPackageListItemStatusPanelLabel::CreatePropertyList(IListItem *listitem)
		{
			if (isInstance(listitem))
				return new CListItemStatusPanelLabelPropertyList(getPackage(), listitem, this);
			return nullptr;
		}
	}
}