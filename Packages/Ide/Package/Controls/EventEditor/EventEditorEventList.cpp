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
	namespace ide
	{
		CEventEditorEventList::CEventEditorEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CControlEventList(package, control, entity)
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
			Delete(L"OnEnable");
			Delete(L"OnDisable");
			Delete(L"OnTransformControls");
			Delete(L"OnSetModal");
			Delete(L"OnKillModal");
			Delete(L"OnSetCaptureKeyboard");
			Delete(L"OnKillCaptureKeyboard");
			Delete(L"OnActivate");
			Delete(L"OnDeactivate");

			Add(new CEvent(this, control, L"OnEventChange", L"{namespace}IEventEditor *sender, IEvent *event, IEventList *event_list, IClass *parent", L"sender, event, event_list, parent"))
				->AddForwardDeclaration(L"class IEventEditor;", L"Ide/Controls/IEventEditor.h", L"ide")
				->AddForwardDeclaration(L"class IEvent;", L"Nitisa/Package/Interfaces/IEvent.h", L"")
				->AddForwardDeclaration(L"class IEventList;", L"Nitisa/Package/Interfaces/IEventList.h", L"")
				->AddForwardDeclaration(L"class IClass;", L"Nitisa/Interfaces/IClass.h", L"");
		}
	}
}