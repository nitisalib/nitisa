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
	namespace opengl
	{
		C3DControlEventList::C3DControlEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CControlEventList(package, control, entity)
		{
			// Other input events
			Delete(L"OnHotkey");

			// Application events
			Delete(L"OnApplicationActivate");
			Delete(L"OnApplicationDeactivate");
			Delete(L"OnTimeChange");
			Delete(L"OnInputLanguageChange");
			Delete(L"OnDisplayChange");
			Delete(L"OnThemeChange");
			Delete(L"OnClipboardUpdate");
			Delete(L"OnTranslateChange");

			//Form events
			Delete(L"OnFormActivate");
			Delete(L"OnFormDeactivate");
			Delete(L"OnFormSetFocus");
			Delete(L"OnFormKillFocus");
			Delete(L"OnFormEnable");
			Delete(L"OnFormDisable");
			Delete(L"OnFormShow");
			Delete(L"OnFormHide");
			Delete(L"OnFormMove");
			Delete(L"OnFormRestore");
			Delete(L"OnFormMinimize");
			Delete(L"OnFormMaximize");
			Delete(L"OnFormEnterSizeMove");
			Delete(L"OnFormExitSizeMove");

			// Events from parent control
			Delete(L"OnParentStyleChange");
			Delete(L"OnParentFontChange");
			Delete(L"OnParentResize");
			Delete(L"OnParentTransform");
			Delete(L"OnParentTransformControls");

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
			Delete(L"OnShow");
			Delete(L"OnHide");
			Delete(L"OnEnable");
			Delete(L"OnDisable");
			Delete(L"OnResize");
			Delete(L"OnTransform");
			Delete(L"OnTransformControls");
			Delete(L"OnStyleChange");
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

			// Paint events
			Delete(L"OnPaint");
			Delete(L"OnPaintEnd");

			// Keyboard input events
			Delete(L"OnKeyDown");
			Delete(L"OnKeyUp");
			Delete(L"OnChar");
			Delete(L"OnDeadChar");

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