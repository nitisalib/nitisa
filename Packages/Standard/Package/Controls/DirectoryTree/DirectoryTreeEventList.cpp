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
		CDirectoryTreeEventList::CDirectoryTreeEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CControlEventList(package, control, entity)
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

			// Clipboard events
			Delete(L"OnPasteString");

			Add(new CEvent(this, control, L"OnSelectDirectory", L"IControl *sender, const String &path", L"sender, path"))
				->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
				->AddHeaderFile(L"Nitisa/Core/Strings.h");
			Add(new CEvent(this, control, L"OnDeselectItem", L"IControl *sender, const String &path", L"sender, path"))
				->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
				->AddHeaderFile(L"Nitisa/Core/Strings.h");
			Add(new CEvent(this, control, L"OnActivateDirectory", L"IControl *sender, const String &path", L"sender, path"))
				->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
				->AddHeaderFile(L"Nitisa/Core/Strings.h");
			Add(new CEvent(this, control, L"OnDeactivateItem", L"IControl *sender, const String &path", L"sender, path"))
				->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
				->AddHeaderFile(L"Nitisa/Core/Strings.h");
		}
	}
}