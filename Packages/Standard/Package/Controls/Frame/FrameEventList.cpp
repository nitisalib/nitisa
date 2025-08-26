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
		CFrameEventList::CFrameEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CControlEventList(package, control, entity)
		{
			// Other input events
			Delete(L"OnHotkey");

			// State change events
			Delete(L"OnSetModal");
			Delete(L"OnKillModal");
			Delete(L"OnSetCaptureKeyboard");
			Delete(L"OnKillCaptureKeyboard");
			Delete(L"OnActivate");
			Delete(L"OnDeactivate");

			// Clipboard events
			Delete(L"OnPasteString");

			Add(new CEvent(this, control, L"OnMinimize", L"{namespace}IFrame *sender", L"sender"))
				->AddForwardDeclaration(L"class IFrame;", L"Standard/Controls/IFrame.h", L"standard");
			Add(new CEvent(this, control, L"OnMaximize", L"{namespace}IFrame *sender", L"sender"))
				->AddForwardDeclaration(L"class IFrame;", L"Standard/Controls/IFrame.h", L"standard");
			Add(new CEvent(this, control, L"OnRestore", L"{namespace}IFrame *sender", L"sender"))
				->AddForwardDeclaration(L"class IFrame;", L"Standard/Controls/IFrame.h", L"standard");
			Add(new CEvent(this, control, L"OnClose", L"{namespace}IFrame *sender, CloseAction &action", L"sender, action"))
				->AddForwardDeclaration(L"class IFrame;", L"Standard/Controls/IFrame.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/CloseAction.h");
		}
	}
}