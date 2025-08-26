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
	namespace ide
	{
		CFormEditorEventList::CFormEditorEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CControlEventList(package, control, entity)
		{
			// Other input events
			Delete(L"OnHotkey");

			// Events from parent control
			Delete(L"OnParentFontChange");

			// State change events
			Delete(L"OnFontChange");
			Delete(L"OnSetModal");
			Delete(L"OnKillModal");
			Delete(L"OnSetFocus");
			Delete(L"OnKillFocus");
			Delete(L"OnSetCaptureKeyboard");
			Delete(L"OnKillCaptureKeyboard");
			Delete(L"OnActivate");
			Delete(L"OnDeactivate");

			// Other input events
			Delete(L"OnDropFiles");

			Add(new CEvent(this, control, L"OnSelectControl", L"{namespace}IFormEditor *sender, IControl *control", L"sender, control"))
				->AddForwardDeclaration(L"class IFormEditor;", L"Ide/Controls/IFormEditor.h", L"ide")
				->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
			Add(new CEvent(this, control, L"OnDeselectControl", L"{namespace}IFormEditor *sender, IControl *control", L"sender, control"))
				->AddForwardDeclaration(L"class IFormEditor;", L"Ide/Controls/IFormEditor.h", L"ide")
				->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
			Add(new CEvent(this, control, L"OnSelectComponent", L"{namespace}IFormEditor *sender, IComponent *component", L"sender, component"))
				->AddForwardDeclaration(L"class IFormEditor;", L"Ide/Controls/IFormEditor.h", L"ide")
				->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
			Add(new CEvent(this, control, L"OnDeselectComponent", L"{namespace}IFormEditor *sender, IComponent *component", L"sender, component"))
				->AddForwardDeclaration(L"class IFormEditor;", L"Ide/Controls/IFormEditor.h", L"ide")
				->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
			Add(new CEvent(this, control, L"OnCheckComponentAllowed", L"{namespace}IFormEditor *sender, IComponent *component, bool &allowed", L"sender, component, allowed"))
				->AddForwardDeclaration(L"class IFormEditor;", L"Ide/Controls/IFormEditor.h", L"ide")
				->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
			Add(new CEvent(this, control, L"OnComponentTransform", L"{namespace}IFormEditor *sender, IComponent *component", L"sender, component"))
				->AddForwardDeclaration(L"class IFormEditor;", L"Ide/Controls/IFormEditor.h", L"ide")
				->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
			Add(new CEvent(this, control, L"OnControlTransform", L"{namespace}IFormEditor *sender, IComponent *component", L"sender, component"))
				->AddForwardDeclaration(L"class IFormEditor;", L"Ide/Controls/IFormEditor.h", L"ide")
				->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
			Add(new CEvent(this, control, L"OnControlResize", L"{namespace}IFormEditor *sender, IComponent *component", L"sender, component"))
				->AddForwardDeclaration(L"class IFormEditor;", L"Ide/Controls/IFormEditor.h", L"ide")
				->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
			Add(new CEvent(this, control, L"OnMouseDown", L"{namespace}IFormEditor *sender, const MessageMouse &m, bool &processed", L"sender, m, processed"))
				->AddForwardDeclaration(L"class IFormEditor;", L"Ide/Controls/IFormEditor.h", L"ide")
				->AddHeaderFile(L"Nitisa/Core/Messages.h");
		}
	}
}