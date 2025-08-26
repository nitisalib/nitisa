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
		CToggleEventList::CToggleEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CControlEventList(package, control, entity)
		{
			// Other input events
			Delete(L"OnHotkey");

			// Events from parent control
			Delete(L"OnParentFontChange");

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
			Delete(L"OnChildBeforeTransform");
			Delete(L"OnChildBeforeResize");
			Delete(L"OnChildBeforeShow");
			Delete(L"OnChildBeforeHide");
			Delete(L"OnChildBeforeEnable");
			Delete(L"OnChildBeforeDisable");

			// State change events
			Delete(L"OnTransformControls");
			Delete(L"OnFontChange");
			Delete(L"OnSetModal");
			Delete(L"OnKillModal");
			Delete(L"OnSetFocus");
			Delete(L"OnKillFocus");
			Delete(L"OnSetCaptureKeyboard");
			Delete(L"OnKillCaptureKeyboard");
			Delete(L"OnSetCaptureMouse");
			Delete(L"OnKillCaptureMouse");
			Delete(L"OnActivate");
			Delete(L"OnDeactivate");

			// Keyboard input events
			Delete(L"OnKeyDown");
			Delete(L"OnKeyUp");
			Delete(L"OnChar");
			Delete(L"OnDeadChar");

			// Clipboard events
			Delete(L"OnPasteString");

			Add(new CEvent(this, control, L"OnToggle", L"IControl *sender", L"sender"))
				->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		}
	}
}