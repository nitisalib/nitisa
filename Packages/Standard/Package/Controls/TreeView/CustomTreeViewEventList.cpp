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
		CCustomTreeViewEventList::CCustomTreeViewEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CControlEventList(package, control, entity)
		{
			// Other input events
			Delete(L"OnHotkey");

			// Events from child controls
			Delete(L"OnChildStyleChange");
			Delete(L"OnChildFontChange");
			Delete(L"OnChildTransform");
			Delete(L"OnChildResize");
			Delete(L"OnChildShow");
			Delete(L"OnChildHide");
			Delete(L"OnChildAttach");
			Delete(L"OnChildDetach");
			Delete(L"OnChildEnable");
			Delete(L"OnChildDisable");

			// State change events
			Delete(L"OnTransformControls");
			Delete(L"OnSetModal");
			Delete(L"OnKillModal");
			Delete(L"OnSetCaptureKeyboard");
			Delete(L"OnKillCaptureKeyboard");
			Delete(L"OnActivate");
			Delete(L"OnDeactivate");

			Add(new CEvent(this, control, L"OnSelectItem", L"IControl *sender, IListItem *item", L"sender, item"))
				->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"");
			Add(new CEvent(this, control, L"OnDeselectItem", L"IControl *sender, IListItem *item", L"sender, item"))
				->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"");
			Add(new CEvent(this, control, L"OnActivateItem", L"IControl *sender, IListItem *item", L"sender, item"))
				->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"");
			Add(new CEvent(this, control, L"OnDeactivateItem", L"IControl *sender, IListItem *item", L"sender, item"))
				->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"");
			Add(new CEvent(this, control, L"OnMovingSelection", L"IControl *sender, IListItem *dest", L"sender, dest"))
				->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"");
			Add(new CEvent(this, control, L"OnMoveSelection", L"IControl *sender, IListItem *dest", L"sender, dest"))
				->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"");
		}
	}
}