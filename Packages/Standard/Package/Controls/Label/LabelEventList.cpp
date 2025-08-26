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
		CLabelEventList::CLabelEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CControlEventList(package, control, entity)
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
			Delete(L"OnSetFocus");
			Delete(L"OnKillFocus");
			Delete(L"OnSetCaptureKeyboard");
			Delete(L"OnKillCaptureKeyboard");
			Delete(L"OnSetCaptureMouse");
			Delete(L"OnKillCaptureMouse");
			Delete(L"OnActivate");
			Delete(L"OnDeactivate");

			// Mouse input events
			Delete(L"OnMouseHover");
			Delete(L"OnMouseLeave");
			Delete(L"OnMouseMove");
			Delete(L"OnLeftMouseButtonDown");
			Delete(L"OnLeftMouseButtonUp");
			Delete(L"OnLeftMouseButtonDoubleClick");
			Delete(L"OnRightMouseButtonDown");
			Delete(L"OnRightMouseButtonUp");
			Delete(L"OnRightMouseButtonDoubleClick");
			Delete(L"OnMiddleMouseButtonDown");
			Delete(L"OnMiddleMouseButtonUp");
			Delete(L"OnMiddleMouseButtonDoubleClick");
			Delete(L"OnMouseVerticalWheel");
			Delete(L"OnMouseHorizontalWheel");

			// Other input events
			Delete(L"OnDropFiles");

			// Clipboard events
			Delete(L"OnPasteString");
		}
	}
}