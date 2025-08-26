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
		CFormViewEventList::CFormViewEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CControlEventList(package, control, entity)
		{
			// Other input events
			Delete(L"OnHotkey");

			// State change events
			Delete(L"OnEnable");
			Delete(L"OnDisable");
			Delete(L"OnSetModal");
			Delete(L"OnKillModal");
			Delete(L"OnSetCaptureKeyboard");
			Delete(L"OnKillCaptureKeyboard");
			Delete(L"OnActivate");
			Delete(L"OnDeactivate");

			// Keyboard input events
			Delete(L"OnKeyDown");
			Delete(L"OnKeyUp");
			Delete(L"OnChar");
			Delete(L"OnDeadChar");

			// Other input events
			Delete(L"OnDropFiles");

			// Clipboard events
			Delete(L"OnPasteString");
		}
	}
}