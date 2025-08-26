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
		CViewEventList::CViewEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CControlEventList(package, control, entity)
		{
			// Other input events
			Delete(L"OnHotkey");

			// Events from parent control
			Delete(L"OnParentFontChange");

			// State change events
			Delete(L"OnEnable");
			Delete(L"OnDisable");
			Delete(L"OnFontChange");
			Delete(L"OnSetModal");
			Delete(L"OnKillModal");
			Delete(L"OnSetCaptureKeyboard");
			Delete(L"OnKillCaptureKeyboard");
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

			Add(new CEvent(this, control, L"OnRender", L"{namespace}IView *sender", L"sender"))
				->AddForwardDeclaration(L"class IView;", L"OpenGL/Controls/IView.h", L"opengl");
		}
	}
}