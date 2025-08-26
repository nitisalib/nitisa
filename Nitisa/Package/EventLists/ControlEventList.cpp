// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	CControlEventList::CControlEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CComponentEventList(package, control, entity)
	{
		// Events from parent control
		Add(new CEvent(this, control, L"OnParentStyleChange", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnParentFontChange", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnParentResize", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnParentTransform", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnParentTransformControls", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");

		// Events from child controls
		Add(new CEvent(this, control, L"OnChildStyleChange", L"IControl *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnChildFontChange", L"IControl *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnChildTransform", L"IControl *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnChildResize", L"IControl *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnChildShow", L"IControl *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnChildHide", L"IControl *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnChildAttach", L"IControl *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnChildDetach", L"IControl *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnChildEnable", L"IControl *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnChildDisable", L"IControl *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnChildBeforeTransform", L"IControl *sender, IControl *control, bool &allowed", L"sender, control, allowed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnChildBeforeResize", L"IControl *sender, IControl *control, bool &allowed", L"sender, control, allowed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnChildBeforeShow", L"IControl *sender, IControl *control, bool &allowed", L"sender, control, allowed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnChildBeforeHide", L"IControl *sender, IControl *control, bool &allowed", L"sender, control, allowed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnChildBeforeEnable", L"IControl *sender, IControl *control, bool &allowed", L"sender, control, allowed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnChildBeforeDisable", L"IControl *sender, IControl *control, bool &allowed", L"sender, control, allowed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");

		// State change events
		Add(new CEvent(this, control, L"OnShow", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnHide", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnEnable", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnDisable", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnResize", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnTransform", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnTransformControls", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnStyleChange", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnFontChange", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnSetModal", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnKillModal", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnSetFocus", L"IControl *sender, const MessageFocus &m", L"sender, m"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnKillFocus", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnSetCaptureKeyboard", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnKillCaptureKeyboard", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnSetCaptureMouse", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnKillCaptureMouse", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnActivate", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnDeactivate", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");

		// Paint events
		Add(new CEvent(this, control, L"OnPaint", L"IControl *sender, const MessagePaint &m, bool &draw_children", L"sender, m, draw_children"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnPaintEnd", L"IControl *sender, const MessagePaint &m", L"sender, m"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");

		// Keyboard input events
		Add(new CEvent(this, control, L"OnKeyDown", L"IControl *sender, const MessageKey &m, bool &processed", L"sender, m, processed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnKeyUp", L"IControl *sender, const MessageKey &m, bool &processed", L"sender, m, processed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnChar", L"IControl *sender, const MessageChar &m, bool &processed", L"sender, m, processed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnDeadChar", L"IControl *sender, const MessageChar &m, bool &processed", L"sender, m, processed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");

		// Mouse input events
		Add(new CEvent(this, control, L"OnMouseHover", L"IControl *sender, const MessagePosition &m", L"sender, m"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnMouseLeave", L"IControl *sender", L"sender"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, control, L"OnMouseMove", L"IControl *sender, const MessageMouse &m, bool &processed", L"sender, m, processed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnLeftMouseButtonDown", L"IControl *sender, const MessageMouse &m, bool &processed", L"sender, m, processed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnLeftMouseButtonUp", L"IControl *sender, const MessageMouse &m, bool &processed", L"sender, m, processed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnLeftMouseButtonDoubleClick", L"IControl *sender, const MessageMouse &m, bool &processed", L"sender, m, processed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnRightMouseButtonDown", L"IControl *sender, const MessageMouse &m, bool &processed", L"sender, m, processed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnRightMouseButtonUp", L"IControl *sender, const MessageMouse &m, bool &processed", L"sender, m, processed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnRightMouseButtonDoubleClick", L"IControl *sender, const MessageMouse &m, bool &processed", L"sender, m, processed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnMiddleMouseButtonDown", L"IControl *sender, const MessageMouse &m, bool &processed", L"sender, m, processed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnMiddleMouseButtonUp", L"IControl *sender, const MessageMouse &m, bool &processed", L"sender, m, processed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnMiddleMouseButtonDoubleClick", L"IControl *sender, const MessageMouse &m, bool &processed", L"sender, m, processed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnMouseVerticalWheel", L"IControl *sender, const MessageMouseWheel &m, bool &processed", L"sender, m, processed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, control, L"OnMouseHorizontalWheel", L"IControl *sender, const MessageMouseWheel &m, bool &processed", L"sender, m, processed"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");

		// Other input events
		Add(new CEvent(this, control, L"OnDropFiles", L"IControl *sender, const MessageDropFiles &m, bool &processed, bool &accepted", L"sender, m, processed, accepted"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");

		// Clipboard events
		Add(new CEvent(this, control, L"OnPasteString", L"IControl *sender, const MessagePasteString &m", L"sender, m"))
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
	}
}