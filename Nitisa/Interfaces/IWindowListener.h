// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/CloseAction.h"
#include "../Core/Messages.h"
#include "IWindowListenerOnMessage.h"

namespace nitisa
{
	// TODO: Implement drag&drop(OnTouch)
	// Windows example: https://msdn.microsoft.com/en-us/library/windows/desktop/ms679679(v=vs.85).aspx
	class IWindowListener : public virtual IWindowListenerOnMessage
	{
	protected:
		IWindowListener() = default;
		~IWindowListener() = default;
		IWindowListener(const IWindowListener &other) = delete;
		IWindowListener(IWindowListener &&other) = delete;
		IWindowListener &operator=(const IWindowListener &other) = delete;
		IWindowListener &operator=(IWindowListener &&other) = delete;
	public:
		virtual void OnCreate() = 0;
		virtual void OnDestroy() = 0;
		virtual void OnActivate(const MessageWindowActivate &m) = 0;
		virtual void OnDeactivate() = 0;
		virtual void OnSetFocus() = 0;
		virtual void OnKillFocus() = 0;
		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;
		virtual void OnClose(CloseAction &action) = 0;
		virtual void OnShow() = 0;
		virtual void OnHide() = 0;
		virtual void OnActivateApp() = 0;
		virtual void OnDeactivateApp() = 0;
		virtual void OnMove(const MessagePosition &m) = 0;
		virtual void OnRestore(const MessageSize &m) = 0;
		virtual void OnMinimize(const MessageSize &m) = 0;
		virtual void OnMaximize(const MessageSize &m) = 0;
		virtual void OnResizing(const MessageWindowResizing &m) = 0;
		virtual void OnMoving(const MessageRect &m) = 0;
		virtual void OnEnterSizeMove() = 0;
		virtual void OnExitSizeMove() = 0;
		virtual void OnKeyDown(const MessageKey &m) = 0;
		virtual void OnKeyUp(const MessageKey &m) = 0;
		virtual void OnChar(const MessageChar &m) = 0;
		virtual void OnDeadChar(const MessageChar &m) = 0;
		virtual void OnHScroll(const MessageWindowScroll &m) = 0;
		virtual void OnVScroll(const MessageWindowScroll &m) = 0;
		virtual void OnGestureZoom(const MessagePosition &m) = 0;
		virtual void OnGesturePan(const MessagePosition &m) = 0;
		virtual void OnGestureRotate(const MessagePosition &m) = 0;
		virtual void OnGestureTwoFingerTap(const MessagePosition &m) = 0;
		virtual void OnGesturePressAndTap(const MessagePosition &m) = 0;
		virtual void OnGestureNotify() = 0;
		virtual void OnMouseMove(const MessageMouse &m) = 0;
		virtual void OnLeftMouseButtonDown(const MessageMouse &m) = 0;
		virtual void OnLeftMouseButtonUp(const MessageMouse &m) = 0;
		virtual void OnLeftMouseButtonDoubleClick(const MessageMouse &m) = 0;
		virtual void OnRightMouseButtonDown(const MessageMouse &m) = 0;
		virtual void OnRightMouseButtonUp(const MessageMouse &m) = 0;
		virtual void OnRightMouseButtonDoubleClick(const MessageMouse &m) = 0;
		virtual void OnMiddleMouseButtonDown(const MessageMouse &m) = 0;
		virtual void OnMiddleMouseButtonUp(const MessageMouse &m) = 0;
		virtual void OnMiddleMouseButtonDoubleClick(const MessageMouse &m) = 0;
		virtual void OnMouseVerticalWheel(const MessageMouseWheel &m) = 0;
		virtual void OnMouseHorizontalWheel(const MessageMouseWheel &m) = 0;
		virtual void OnMouseHover(const MessageMouse &m) = 0;
		virtual void OnMouseLeave() = 0;
		virtual void OnLoseCapture() = 0;
		virtual void OnPaint(const MessageRect &m) = 0;
		virtual void OnQueryEndSession(bool &restricted) = 0;
		virtual void OnQueryOpen(bool &restricted) = 0;
		virtual void OnEndSession(const MessageEndSession &m) = 0;
		virtual void OnDeviceModeChange() = 0;
		virtual void OnTimeChange() = 0;
		virtual void OnInputLanguageChangeRequest(bool &restricted) = 0;
		virtual void OnInputLanguageChange() = 0;
		virtual void OnDisplayChange(const MessageSize &m) = 0;
		virtual void OnThemeChanged() = 0;
		virtual void OnClipboardUpdate() = 0;
		virtual void OnDropFiles(const MessageDropFiles &m, bool accepted) = 0;
		virtual void OnTouch(const MessageTouch &m) = 0;
		virtual void OnPasteString(const MessagePasteString &m) = 0; // Called when paste operation was requested and there is something to paste
	};
}