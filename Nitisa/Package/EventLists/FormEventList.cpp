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
	CFormEventList::CFormEventList(IPackage *package, IForm *form, IPackageEntity *entity) :CEventList(package, form, entity)
	{
		// Events from child controls
		Add(new CEvent(this, form, L"OnChildStyleChange", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnChildFontChange", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnChildTransform", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnChildResize", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnChildShow", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnChildHide", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnChildEnable", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnChildDisable", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnChildBeforeTransform", L"IForm *sender, IControl *control, bool &allowed", L"sender, control, allowed"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnChildBeforeResize", L"IForm *sender, IControl *control, bool &allowed", L"sender, control, allowed"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnChildBeforeShow", L"IForm *sender, IControl *control, bool &allowed", L"sender, control, allowed"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnChildBeforeHide", L"IForm *sender, IControl *control, bool &allowed", L"sender, control, allowed"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnChildBeforeEnable", L"IForm *sender, IControl *control, bool &allowed", L"sender, control, allowed"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnChildBeforeDisable", L"IForm *sender, IControl *control, bool &allowed", L"sender, control, allowed"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");

		// State change events
		Add(new CEvent(this, form, L"OnResize", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnTransform", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnTransformControls", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnStyleChange", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnFontChange", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");

		// Component events
		Add(new CEvent(this, form, L"OnComponentAttach", L"IForm *sender, IComponent *component", L"sender, component"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		Add(new CEvent(this, form, L"OnComponentDetach", L"IForm *sender, IComponent *component", L"sender, component"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");

		// Control events
		Add(new CEvent(this, form, L"OnControlAttach", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnControlDetach", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnControlSetModal", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnControlKillModal", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnControlSetFocus", L"IForm *sender, IControl *control, const MessageFocus &m", L"sender, control, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnControlKillFocus", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnControlMouseHover", L"IForm *sender, IControl *control, const MessagePosition &m", L"sender, control, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnControlMouseLeave", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnControlSetCaptureKeyboard", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnControlKillCaptureKeyboard", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnControlSetCaptureMouse", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnControlKillCaptureMouse", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnControlActivate", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");
		Add(new CEvent(this, form, L"OnControlDeactivate", L"IForm *sender, IControl *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IControl;", L"Nitisa/Interfaces/IControl.h", L"");

		// Paint events
		Add(new CEvent(this, form, L"OnPaint", L"IForm *sender, const MessagePaint &m, bool &draw_children", L"sender, m, draw_children"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnPaintEnd", L"IForm *sender, const MessagePaint &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");

		// Keyboard input events
		Add(new CEvent(this, form, L"OnKeyDown", L"IForm *sender, const MessageKey &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnKeyUp", L"IForm *sender, const MessageKey &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnChar", L"IForm *sender, const MessageChar &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnDeadChar", L"IForm *sender, const MessageChar &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");

		// Mouse input events
		Add(new CEvent(this, form, L"OnMouseHover", L"IForm *sender, const MessageMouse &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnMouseLeave", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnMouseMove", L"IForm *sender, const MessageMouse &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnLeftMouseButtonDown", L"IForm *sender, const MessageMouse &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnLeftMouseButtonUp", L"IForm *sender, const MessageMouse &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnLeftMouseButtonDoubleClick", L"IForm *sender, const MessageMouse &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnRightMouseButtonDown", L"IForm *sender, const MessageMouse &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnRightMouseButtonUp", L"IForm *sender, const MessageMouse &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnRightMouseButtonDoubleClick", L"IForm *sender, const MessageMouse &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnMiddleMouseButtonDown", L"IForm *sender, const MessageMouse &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnMiddleMouseButtonUp", L"IForm *sender, const MessageMouse &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnMiddleMouseButtonDoubleClick", L"IForm *sender, const MessageMouse &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnMouseVerticalWheel", L"IForm *sender, const MessageMouseWheel &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnMouseHorizontalWheel", L"IForm *sender, const MessageMouseWheel &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");

		// Other input events
		Add(new CEvent(this, form, L"OnDropFiles", L"IForm *sender, const MessageDropFiles &m, bool &accepted", L"sender, m, accepted"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnHotkey", L"IForm *sender, const MessageHotkey &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnGestureZoom", L"IForm *sender, const MessagePosition &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnGesturePan", L"IForm *sender, const MessagePosition &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnGestureRotate", L"IForm *sender, const MessagePosition &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnGestureTwoFingerTap", L"IForm *sender, const MessagePosition &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnGesturePressAndTap", L"IForm *sender, const MessagePosition &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnGestureNotify", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnTouch", L"IForm *sender, const MessageTouch &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");

		// Application events
		Add(new CEvent(this, form, L"OnApplicationActivate", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnApplicationDeactivate", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnQueryEndSession", L"IForm *sender, bool &restricted", L"sender, restricted"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnQueryOpen", L"IForm *sender, bool &restricted", L"sender, restricted"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnEndSession", L"IForm *sender, const MessageEndSession &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnDeviceModeChange", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnTimeChange", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnInputLanguageChangeRequest", L"IForm *sender, bool &restricted", L"sender, restricted"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnInputLanguageChange", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnDisplayChange", L"IForm *sender, const MessageSize &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnThemeChange", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnClipboardUpdate", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnTranslateChange", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");

		// Window events
		Add(new CEvent(this, form, L"OnDestroy", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnActivate", L"IForm *sender, const MessageWindowActivate &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnDeactivate", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnSetFocus", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnKillFocus", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnEnable", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnDisable", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnClose", L"IForm *sender, CloseAction &action", L"sender, action"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/CloseAction.h");
		Add(new CEvent(this, form, L"OnShow", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnHide", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnMove", L"IForm *sender, const MessagePosition &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnRestore", L"IForm *sender, const MessageSize &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnMinimize", L"IForm *sender, const MessageSize &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnMaximize", L"IForm *sender, const MessageSize &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnResizing", L"IForm *sender, const MessageWindowResizing &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnMoving", L"IForm *sender, const MessageRect &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnEnterSizeMove", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnExitSizeMove", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");
		Add(new CEvent(this, form, L"OnHScroll", L"IForm *sender, const MessageWindowScroll &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnVScroll", L"IForm *sender, const MessageWindowScroll &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
		Add(new CEvent(this, form, L"OnLoseCapture", L"IForm *sender", L"sender"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"");

		// Dialog box events
		Add(new CEvent(this, form, L"OnDialogBoxActivate", L"IForm *sender, IDialogBox *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IDialogBox;", L"Nitisa/Interfaces/IDialogBox.h", L"");
		Add(new CEvent(this, form, L"OnDialogBoxDeactivate", L"IForm *sender, IDialogBox *control", L"sender, control"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddForwardDeclaration(L"class IDialogBox;", L"Nitisa/Interfaces/IDialogBox.h", L"");

		// Clipboard events
		Add(new CEvent(this, form, L"OnPasteString", L"IForm *sender, const MessagePasteString &m", L"sender, m"))
			->AddForwardDeclaration(L"class IForm;", L"Nitisa/Interfaces/IForm.h", L"")
			->AddHeaderFile(L"Nitisa/Core/Messages.h");
	}
}