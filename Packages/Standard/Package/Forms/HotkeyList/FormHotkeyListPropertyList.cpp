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
		CFormHotkeyListPropertyList::CFormHotkeyListPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyHotkeyList(this, form, L"Hotkeys", nullptr,
				[](IClass *parent) { return cast<CFormHotkeyList*>(parent)->getHotkeyCount(); },
				[](IClass *parent, const int index) { return cast<CFormHotkeyList*>(parent)->getHotkey(index); },
				[](IClass *parent, const Hotkey value) { return cast<CFormHotkeyList*>(parent)->AddHotkey(value); },
				[](IClass *parent, const int value) { return cast<CFormHotkeyList*>(parent)->DeleteHotkey(value); },
				[](IClass *parent) { return cast<CFormHotkeyList*>(parent)->DeleteHotkeys(); }));
		}
	}
}