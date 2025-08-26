// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IFormService.h"
#include "../Math/IntegerArray.h"
#include "CloseAction.h"
#include "Key.h"
#include "Messages.h"
#include "Strings.h"

namespace nitisa
{
	class IComponent;
	class IControl;
	class IDialogBox;
	class IWindow;
	class IWindowListenerOnMessage;

	class CForm;

	class CFormService :public virtual IFormService
	{
	private:
		void EnumControls(StringArray &names, IControl *control, IControl *exclude);
		void EnumTabOrders(IntegerArray &orders, IControl *control, IControl *exclude);
	protected:
		CForm *m_pForm;

		IControl *FindControlByTabOrder(const int tab_order);
		IControl *FindControlByTabOrder(IControl *parent, const int tab_order);
	public:
		IWindow *getWindow() override;

		void setWindow(IWindow *value) override;
		void setRenderer(IRenderer *value) override;

		void Release() override;
		void UpdateTabOrders(const int old_tab_order, const int new_tab_order) override;
		String GenerateComponentName(IComponent *component) override;
		String GenerateControlName(IControl *control) override;
		bool MoveControl(IControl *control, const int before) override;
		bool RegisterHotkey(IComponent *component, const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down) override;
		bool UnregisterHotkey(IComponent *component, const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down) override;
		bool UnregisterHotkeys(IComponent *component) override;
		bool RegisterHotkey(IControl *control, const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down) override;
		bool UnregisterHotkey(IControl *control, const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down) override;
		bool UnregisterHotkeys(IControl *control) override;
		void AlignControls() override;
		int GenerateTabOrder(IControl *control) override;
		bool RegisterMessageListener(IComponent *component, IWindowListenerOnMessage *listener) override;
		bool UnregisterMessageListener(IComponent *component, IWindowListenerOnMessage *listener) override;
		bool UnregisterMessageListeners(IComponent *component) override;
		void ProcessControlDisable(IControl *control) override;
		void ProcessControlHide(IControl *control) override;
		void ProcessControlDetach(IControl *control) override;

		// Notifications from child controls
		void NotifyOnChildStyleChange(IControl *control) override;
		void NotifyOnChildFontChange(IControl *control) override;
		void NotifyOnChildTransform(IControl *control) override;
		void NotifyOnChildResize(IControl *control) override;
		void NotifyOnChildShow(IControl *control) override;
		void NotifyOnChildHide(IControl *control) override;
		void NotifyOnChildEnable(IControl *control) override;
		void NotifyOnChildDisable(IControl *control) override;
		void NotifyOnChildBeforeTransform(IControl *control, bool &allowed) override;
		void NotifyOnChildBeforeResize(IControl *control, bool &allowed) override;
		void NotifyOnChildBeforeShow(IControl *control, bool &allowed) override;
		void NotifyOnChildBeforeHide(IControl *control, bool &allowed) override;
		void NotifyOnChildBeforeEnable(IControl *control, bool &allowed) override;
		void NotifyOnChildBeforeDisable(IControl *control, bool &allowed) override;

		// State change notifications
		void NotifyOnResize() override;
		void NotifyOnTransform() override;
		void NotifyOnTransformControls() override;
		void NotifyOnStyleChange() override;
		void NotifyOnFontChange() override;
		void NotifyOnFreeResources() override;

		// Component notifications
		void NotifyOnComponentAttach(IComponent *component) override;
		void NotifyOnComponentDetach(IComponent *component) override;

		// Control notifications
		void NotifyOnControlAttach(IControl *control) override;
		void NotifyOnControlDetach(IControl *control) override;
		void NotifyOnControlSetModal(IControl *control) override;
		void NotifyOnControlKillModal(IControl *control) override;
		void NotifyOnControlSetFocus(IControl *control, const MessageFocus &m) override;
		void NotifyOnControlKillFocus(IControl *control) override;
		void NotifyOnControlMouseHover(IControl *control, const MessagePosition &m) override;
		void NotifyOnControlMouseLeave(IControl *control) override;
		void NotifyOnControlSetCaptureKeyboard(IControl *control) override;
		void NotifyOnControlKillCaptureKeyboard(IControl *control) override;
		void NotifyOnControlSetCaptureMouse(IControl *control) override;
		void NotifyOnControlKillCaptureMouse(IControl *control) override;
		void NotifyOnControlActivate(IControl *control) override;
		void NotifyOnControlDeactivate(IControl *control) override;

		// Paint notifications
		void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;
		void NotifyOnPaintEnd(const MessagePaint &m) override;

		// Keyboard input notifications
		void NotifyOnKeyDown(const MessageKey &m) override;
		void NotifyOnKeyUp(const MessageKey &m) override;
		void NotifyOnChar(const MessageChar &m) override;
		void NotifyOnDeadChar(const MessageChar &m) override;

		// Mouse input notifications
		void NotifyOnMouseHover(const MessageMouse &m) override;
		void NotifyOnMouseLeave() override;
		void NotifyOnMouseMove(const MessageMouse &m) override;
		void NotifyOnLeftMouseButtonDown(const MessageMouse &m) override;
		void NotifyOnLeftMouseButtonUp(const MessageMouse &m) override;
		void NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m) override;
		void NotifyOnRightMouseButtonDown(const MessageMouse &m) override;
		void NotifyOnRightMouseButtonUp(const MessageMouse &m) override;
		void NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m) override;
		void NotifyOnMiddleMouseButtonDown(const MessageMouse &m) override;
		void NotifyOnMiddleMouseButtonUp(const MessageMouse &m) override;
		void NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m) override;
		void NotifyOnMouseVerticalWheel(const MessageMouseWheel &m) override;
		void NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m) override;

		// Other input notifications
		void NotifyOnDropFiles(const MessageDropFiles &m, bool &accepted) override;
		void NotifyOnHotkey(const MessageHotkey &m) override;
		void NotifyOnGestureZoom(const MessagePosition &m) override;
		void NotifyOnGesturePan(const MessagePosition &m) override;
		void NotifyOnGestureRotate(const MessagePosition &m) override;
		void NotifyOnGestureTwoFingerTap(const MessagePosition &m) override;
		void NotifyOnGesturePressAndTap(const MessagePosition &m) override;
		void NotifyOnGestureNotify() override;
		void NotifyOnTouch(const MessageTouch &m) override;

		// Application notifications
		void NotifyOnApplicationActivate() override;
		void NotifyOnApplicationDeactivate() override;
		void NotifyOnQueryEndSession(bool &restricted) override;
		void NotifyOnQueryOpen(bool &restricted) override;
		void NotifyOnEndSession(const MessageEndSession &m) override;
		void NotifyOnDeviceModeChange() override;
		void NotifyOnTimeChange() override;
		void NotifyOnInputLanguageChangeRequest(bool &restricted) override;
		void NotifyOnInputLanguageChange() override;
		void NotifyOnDisplayChange(const MessageSize &m) override;
		void NotifyOnThemeChange() override;
		void NotifyOnClipboardUpdate() override;
		void NotifyOnTranslateChange() override;

		// Window notifications
		void NotifyOnCreate() override;
		void NotifyOnDestroy() override;
		void NotifyOnActivate(const MessageWindowActivate &m) override;
		void NotifyOnDeactivate() override;
		void NotifyOnSetFocus() override;
		void NotifyOnKillFocus() override;
		void NotifyOnEnable() override;
		void NotifyOnDisable() override;
		void NotifyOnClose(CloseAction &action) override;
		void NotifyOnShow() override;
		void NotifyOnHide() override;
		void NotifyOnMove(const MessagePosition &m) override;
		void NotifyOnRestore(const MessageSize &m) override;
		void NotifyOnMinimize(const MessageSize &m) override;
		void NotifyOnMaximize(const MessageSize &m) override;
		void NotifyOnResizing(const MessageWindowResizing &m) override;
		void NotifyOnMoving(const MessageRect &m) override;
		void NotifyOnEnterSizeMove() override;
		void NotifyOnExitSizeMove() override;
		void NotifyOnHScroll(const MessageWindowScroll &m) override;
		void NotifyOnVScroll(const MessageWindowScroll &m) override;
		void NotifyOnLoseCapture() override;

		// Dialog box notifications
		void NotifyOnDialogBoxActivate(IDialogBox *control) override;
		void NotifyOnDialogBoxDeactivate(IDialogBox *control) override;

		// Clipboard notifications
		void NotifyOnPasteString(const MessagePasteString &m) override;

		CFormService(CForm *form);
		virtual ~CFormService() = default;
	};
}