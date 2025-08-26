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
		CScrollListEventList::CScrollListEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CControlEventList(package, control, entity)
		{
			// Other input events
			Delete(L"OnHotkey");

			// Events from child controls
			Delete(L"OnChildTransform");
			Delete(L"OnChildBeforeTransform");

			// State change events
			Delete(L"OnTransformControls");
			Delete(L"OnSetModal");
			Delete(L"OnKillModal");
			Delete(L"OnSetFocus");
			Delete(L"OnKillFocus");
			Delete(L"OnSetCaptureKeyboard");
			Delete(L"OnKillCaptureKeyboard");
			Delete(L"OnActivate");
			Delete(L"OnDeactivate");

			// Keyboard input events
			Delete(L"OnKeyDown");
			Delete(L"OnKeyUp");
			Delete(L"OnChar");
			Delete(L"OnDeadChar");

			// Clipboard events
			Delete(L"OnPasteString");
		}
	}
}