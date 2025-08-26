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
	CComponentEventList::CComponentEventList(IPackage *package, IComponent *component, IPackageEntity *entity) :CEventList(package, component, entity)
	{
		// State change events
		Add(new CEvent(this, component, L"OnAttach", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnDetaching", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnDetach", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");

		// Component events
		Add(new CEvent(this, component, L"OnComponentAttach", L"IComponent *sender, IComponent *component", L"sender, component"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnComponentDetach", L"IComponent *sender, IComponent *component", L"sender, component"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnComponentChange", L"IComponent *sender, IComponent *component", L"sender, component"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");

		// Control events
		Add(new CEvent(this, component, L"OnControlAttach", L"IComponent *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, component, L"OnControlDetach", L"IComponent *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, component, L"OnControlChange", L"IComponent *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, component, L"OnControlSetFocus", L"IComponent *sender, IControl *control, const MessageFocus &m", L"sender, control, m"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, component, L"OnControlKillFocus", L"IComponent *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, component, L"OnControlSetCaptureMouse", L"IComponent *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, component, L"OnControlKillCaptureMouse", L"IComponent *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, component, L"OnControlSetCaptureKeyboard", L"IComponent *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, component, L"OnControlKillCaptureKeyboard", L"IComponent *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, component, L"OnControlSetModal", L"IComponent *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, component, L"OnControlKillModal", L"IComponent *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");

		// Other input events
		Add(new CEvent(this, component, L"OnHotkey", L"IComponent *sender, const MessageHotkey &m", L"sender, m"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");

		// Application events
		Add(new CEvent(this, component, L"OnApplicationActivate", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnApplicationDeactivate", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnTimeChange", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnInputLanguageChange", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnDisplayChange", L"IComponent *sender, const MessageSize &m", L"sender, m"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, component, L"OnThemeChange", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnClipboardUpdate", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnTranslateChange", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");

		//Form events
		Add(new CEvent(this, component, L"OnFormActivate", L"IComponent *sender, const MessageWindowActivate &m", L"sender, m"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, component, L"OnFormDeactivate", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnFormSetFocus", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnFormKillFocus", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnFormEnable", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnFormDisable", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnFormShow", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnFormHide", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnFormMove", L"IComponent *sender, const MessagePosition &m", L"sender, m"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, component, L"OnFormRestore", L"IComponent *sender, const MessageSize &m", L"sender, m"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, component, L"OnFormMinimize", L"IComponent *sender, const MessageSize &m", L"sender, m"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, component, L"OnFormMaximize", L"IComponent *sender, const MessageSize &m", L"sender, m"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, component, L"OnFormEnterSizeMove", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, component, L"OnFormExitSizeMove", L"IComponent *sender", L"sender"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");

		// Dialog box events
		Add(new CEvent(this, component, L"OnDialogBoxActivate", L"IComponent *sender, IDialogBox *control", L"sender, control"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddForwardDeclaration(L"class IDialogBox;", L"Nitisa/Interfaces/IDialogBox.h", L"");
		Add(new CEvent(this, component, L"OnDialogBoxDeactivate", L"IComponent *sender, IDialogBox *control", L"sender, control"))
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"")
			->AddForwardDeclaration(L"class IDialogBox;", L"Nitisa/Interfaces/IDialogBox.h", L"");
	}
}