// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
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
		CListItemMenuPropertyList::CListItemMenuPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity) :
			CListItemPropertyList(package, listitem, entity)
		{
			Add(new CPropertyHotkeyList(this, listitem, L"Hotkeys", nullptr,
				[](IClass *parent) {return cast<CListItemMenu*>(parent)->getHotkeyCount(); },
				[](IClass *parent, const int index) {return cast<CListItemMenu*>(parent)->getHotkey(index); },
				[](IClass *parent, const Hotkey value) {return cast<CListItemMenu*>(parent)->AddHotkey(value.Key, value.Ctrl, value.Alt, value.Shift, value.Down); },
				[](IClass *parent, const int index) {return cast<CListItemMenu*>(parent)->DeleteHotkey(index); },
				[](IClass *parent) {return cast<CListItemMenu*>(parent)->DeleteHotkeys(); }));
			Add(new CPropertyBool(this, listitem, L"RightAligned", false, nullptr,
				[](IClass *parent) {
					IListItem *item{ cast<IListItem*>(parent) };
					if (item && item->QueryService()->getOwner())
					{
						CMainMenu *menu{ cast<CMainMenu*>(item->QueryService()->getOwner()->getControl()) };
						if (menu)
							return menu->isItemRightAligned(item);
					}
					return false;
				},
				[](IClass *parent, const bool value) {
					IListItem *item{ cast<IListItem*>(parent) };
					if (item && item->QueryService()->getOwner())
					{
						CMainMenu *menu{ cast<CMainMenu*>(item->QueryService()->getOwner()->getControl()) };
						if (menu)
							return menu->setItemRightAligned(item, value);
					}
					return false;
				}));
		}
	}
}