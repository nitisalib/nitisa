// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/CloseAction.h"
#include "../Core/Key.h"
#include "../Core/Messages.h"
#include "../Core/Strings.h"

namespace nitisa
{
	class IComponent;
	class IControl;
	class IDialogBox;
	class IRenderer;
	class IWindow;
	class IWindowListenerOnMessage;

	class IFormService
	{
	protected:
		IFormService() = default;
		~IFormService() = default;
		IFormService(const IFormService &other) = delete;
		IFormService(IFormService &&other) = delete;
		IFormService &operator=(const IFormService &other) = delete;
		IFormService &operator=(IFormService &&other) = delete;
	public:
		virtual IWindow *getWindow() = 0; // Return form window. Do not change events and avoid of using this window methods at all. They are for internal usage by form

		virtual void setWindow(IWindow *value) = 0; // Set form window. For purposes when derived form wants handle window and/or renderer itself
		virtual void setRenderer(IRenderer *value) = 0; // Set renderer. Could be set only once

		virtual void Release() = 0; // Destroy instance
		virtual void UpdateTabOrders(const int old_tab_order, const int new_tab_order) = 0; // Update tab orders of controls when changing any control tab order from old_tab_order to new_tab_order
		virtual String GenerateComponentName(IComponent *component) = 0; // Generate unique name for the component
		virtual String GenerateControlName(IControl *control) = 0; // Generate unique name for the control
		virtual bool MoveControl(IControl *control, const int before) = 0; // Change control position in list. Index should be in range 0..ControlCount, control should be child and it's index should not be equal to index
		virtual bool RegisterHotkey(IComponent *component, const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down) = 0; // Register component's hotkey combination
		virtual bool UnregisterHotkey(IComponent *component, const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down) = 0; // Unregister component's hotkey combination
		virtual bool UnregisterHotkeys(IComponent *component) = 0; // Unregister specified component all registered hotkey combinations
		virtual bool RegisterHotkey(IControl *control, const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down) = 0; // Register control's hotkey combination
		virtual bool UnregisterHotkey(IControl *control, const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down) = 0; // Unregister control's hotkey combination
		virtual bool UnregisterHotkeys(IControl *control) = 0; // Unregister specified control all registered hotkey combinations
		virtual void AlignControls() = 0; // Recalculate controls positions and size. For those controls which have alignment different from Align::None
		virtual int GenerateTabOrder(IControl *control) = 0; // Return first available tab order if specified in control is not available
		virtual bool RegisterMessageListener(IComponent *component, IWindowListenerOnMessage *listener) = 0; // Register custom message listener for specified component
		virtual bool UnregisterMessageListener(IComponent *component, IWindowListenerOnMessage *listener) = 0; // Unregister custom message listener
		virtual bool UnregisterMessageListeners(IComponent *component) = 0; // Unregister all custom message listeners for specified component
		virtual void ProcessControlDisable(IControl *control) = 0; // Cleanup form state related to disabling a control belonging to form. Should be called by control when it is on a form and becomes disabled
		virtual void ProcessControlHide(IControl *control) = 0; // Cleanup form state related to hiding a control belonging to form. Should be called by control when it is on a form and becomes invisible
		virtual void ProcessControlDetach(IControl *control) = 0; // Cleanup form state related to detaching a control belonging to form. Should be called by control when it was on a form and becomes detached from it

		// Notifications from child controls
		virtual void NotifyOnChildStyleChange(IControl *control) = 0; // Called when child control style has been changed
		virtual void NotifyOnChildFontChange(IControl *control) = 0; // Called when child control font has been changed
		virtual void NotifyOnChildTransform(IControl *control) = 0; // Called when child control has been transformed
		virtual void NotifyOnChildResize(IControl *control) = 0; // Called when child control has been resized
		virtual void NotifyOnChildShow(IControl *control) = 0; // Called when child control has been shown
		virtual void NotifyOnChildHide(IControl *control) = 0; // Called when child control has been hidden
		virtual void NotifyOnChildEnable(IControl *control) = 0; // Called when child control has been enabled
		virtual void NotifyOnChildDisable(IControl *control) = 0; // Called when child control has been disabled
		virtual void NotifyOnChildBeforeTransform(IControl *control, bool &allowed) = 0; // Called before applying transformation to control. Set allowed to false to forbid the change
		virtual void NotifyOnChildBeforeResize(IControl *control, bool &allowed) = 0; // Called before resizing control. Set allowed to false to forbid the change
		virtual void NotifyOnChildBeforeShow(IControl *control, bool &allowed) = 0; // Called before showing control. Set allowed to false to forbid the change
		virtual void NotifyOnChildBeforeHide(IControl *control, bool &allowed) = 0; // Called before hiding control. Set allowed to false to forbid the change
		virtual void NotifyOnChildBeforeEnable(IControl *control, bool &allowed) = 0; // Called before enabling control. Set allowed to false to forbid the change
		virtual void NotifyOnChildBeforeDisable(IControl *control, bool &allowed) = 0; // Called before disabling control. Set allowed to false to forbid the change

		// State change notifications
		virtual void NotifyOnResize() = 0; // Called when form size was changed
		virtual void NotifyOnTransform() = 0; // Called when transformation was changed due to transformation
		virtual void NotifyOnTransformControls() = 0; // Called when child controls transformation was changed due to change of child controls transformation or set new one
		virtual void NotifyOnStyleChange() = 0; // Called when style was changed due to set new style
		virtual void NotifyOnFontChange() = 0; // Called when font was changed due to change properties
		virtual void NotifyOnFreeResources() = 0; // Free resources(timers, textures, platform fonts)

		// Component notifications
		virtual void NotifyOnComponentAttach(IComponent *component) = 0; // Called when some component was attached to form
		virtual void NotifyOnComponentDetach(IComponent *component) = 0; // Called when some component was detached from form

		// Control notifications
		virtual void NotifyOnControlAttach(IControl *control) = 0; // Called when some control was attached to form even if it was attached as a child of another control
		virtual void NotifyOnControlDetach(IControl *control) = 0; // Called when some control was detached from form even if it was a child of another control
		virtual void NotifyOnControlSetModal(IControl *control) = 0; // Called when control becomes modal
		virtual void NotifyOnControlKillModal(IControl *control) = 0; // Called when controls lose modal state
		virtual void NotifyOnControlSetFocus(IControl *control, const MessageFocus &m) = 0; // Called when control becomes focused
		virtual void NotifyOnControlKillFocus(IControl *control) = 0; // Called when focused control lose focus
		virtual void NotifyOnControlMouseHover(IControl *control, const MessagePosition &m) = 0; // Called when mouse pointer appears over control
		virtual void NotifyOnControlMouseLeave(IControl *control) = 0; // Called when mouse pointer leaves control area
		virtual void NotifyOnControlSetCaptureKeyboard(IControl *control) = 0; // Called when control gets keyboard capture
		virtual void NotifyOnControlKillCaptureKeyboard(IControl *control) = 0; // Called when control loses keyboard capture
		virtual void NotifyOnControlSetCaptureMouse(IControl *control) = 0; // Called when control gets mouse capture
		virtual void NotifyOnControlKillCaptureMouse(IControl *control) = 0; // Called when control loses mouse capture
		virtual void NotifyOnControlActivate(IControl *control) = 0; // Called when control becomes active
		virtual void NotifyOnControlDeactivate(IControl *control) = 0; // Called when control has lost active state

		// Paint notifications
		virtual void NotifyOnPaint(const MessagePaint &m, bool &draw_children) = 0; // Called when form should be drawn. By default render background
		virtual void NotifyOnPaintEnd(const MessagePaint &m) = 0; // Called after drawing the form and all its child controls

		// Keyboard input notifications
		virtual void NotifyOnKeyDown(const MessageKey &m) = 0; // Called when control is focused or capture keyboard and key is down
		virtual void NotifyOnKeyUp(const MessageKey &m) = 0; // Called when control is focused or capture keyboard and key is up
		virtual void NotifyOnChar(const MessageChar &m) = 0; // Called when control is focused or capture keyboard and char translated
		virtual void NotifyOnDeadChar(const MessageChar &m) = 0; // Called when control is focused or capture keyboard and dead char translated

		// Mouse input notifications
		virtual void NotifyOnMouseHover(const MessageMouse &m) = 0; // Called when mouse pointer appears over the form
		virtual void NotifyOnMouseLeave() = 0; // Called when mouse pointer leaves the form
		virtual void NotifyOnMouseMove(const MessageMouse &m) = 0; // Called when control is under mouse pointer or capture mouse and mouse moves
		virtual void NotifyOnLeftMouseButtonDown(const MessageMouse &m) = 0; // Called when control is under mouse pointer or capture mouse and left mouse button down
		virtual void NotifyOnLeftMouseButtonUp(const MessageMouse &m) = 0; // Called when control is under mouse pointer or capture mouse and left mouse button up
		virtual void NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m) = 0; // Called when control is under mouse pointer or capture mouse and left mouse button double clicked
		virtual void NotifyOnRightMouseButtonDown(const MessageMouse &m) = 0; // Called when control is under mouse pointer or capture mouse and right mouse button down
		virtual void NotifyOnRightMouseButtonUp(const MessageMouse &m) = 0; // Called when control is under mouse pointer or capture mouse and right mouse button up
		virtual void NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m) = 0; // Called when control is under mouse pointer or capture mouse and right mouse mutton double clicked
		virtual void NotifyOnMiddleMouseButtonDown(const MessageMouse &m) = 0; // Called when control is under mouse pointer or capture mouse and middle mouse button down
		virtual void NotifyOnMiddleMouseButtonUp(const MessageMouse &m) = 0; // Called when control is under mouse pointer or capture mouse and middle mouse button up
		virtual void NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m) = 0; // Called when control is under mouse pointer or capture mouse and middle mouse button double clicked
		virtual void NotifyOnMouseVerticalWheel(const MessageMouseWheel &m) = 0; // Called when control is under mouse pointer or capture mouse and mouse vertical scroll appear
		virtual void NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m) = 0; // Called when control is under mouse pointer or capture mouse and mouse horizontal scroll appear

		// Other input notifications
		virtual void NotifyOnDropFiles(const MessageDropFiles &m, bool &accepted) = 0; // Called when control is under mouse pointer or capture mouse and drop files appear
		virtual void NotifyOnHotkey(const MessageHotkey &m) = 0; // Called when registered hotkey pressed/released
		virtual void NotifyOnGestureZoom(const MessagePosition &m) = 0; // Called on gesture zoom
		virtual void NotifyOnGesturePan(const MessagePosition &m) = 0; // Called on gesture pan
		virtual void NotifyOnGestureRotate(const MessagePosition &m) = 0; // Called on gesture rotate
		virtual void NotifyOnGestureTwoFingerTap(const MessagePosition &m) = 0; // Called on gesture two finger tap
		virtual void NotifyOnGesturePressAndTap(const MessagePosition &m) = 0; // Called on gesture press and tap
		virtual void NotifyOnGestureNotify() = 0; // Called on gesture notify
		virtual void NotifyOnTouch(const MessageTouch &m) = 0; // Called on touch

		// Application notifications
		virtual void NotifyOnApplicationActivate() = 0; // Called when application becomes active
		virtual void NotifyOnApplicationDeactivate() = 0; // Called when application becomes inactive
		virtual void NotifyOnQueryEndSession(bool &restricted) = 0; // Called when system tries to end user session. Could be aborter by setting restricted to true
		virtual void NotifyOnQueryOpen(bool &restricted) = 0; // Called when system tries to open the form from query. Could be aborted by setting restricted to true
		virtual void NotifyOnEndSession(const MessageEndSession &m) = 0; // Called when system ends user session
		virtual void NotifyOnDeviceModeChange() = 0; // Called when device mode has been changed
		virtual void NotifyOnTimeChange() = 0; // Called when system time has been changed
		virtual void NotifyOnInputLanguageChangeRequest(bool &restricted) = 0; // Called when user tries to change input language. Could be aborted by setting restricted to true
		virtual void NotifyOnInputLanguageChange() = 0; // Called when input language has been changed
		virtual void NotifyOnDisplayChange(const MessageSize &m) = 0; // Called when display mode has been changed
		virtual void NotifyOnThemeChange() = 0; // Called when system theme has been changed
		virtual void NotifyOnClipboardUpdate() = 0; // Called when clipboard data has been changed
		virtual void NotifyOnTranslateChange() = 0; // Called when application gets information about changes in translation matrix(either by current language change in ITranslate or via custom call of IApplicationService::SendTranslateChange method)

		// Window notifications
		virtual void NotifyOnCreate() = 0; // Called after form create
		virtual void NotifyOnDestroy() = 0; // Called before form destroy
		virtual void NotifyOnActivate(const MessageWindowActivate &m) = 0; // Called when form has been activated
		virtual void NotifyOnDeactivate() = 0; // Called when form has been deactivated
		virtual void NotifyOnSetFocus() = 0; // Called when form has received keyboard focus
		virtual void NotifyOnKillFocus() = 0; // Called when form has lost keyboard focus
		virtual void NotifyOnEnable() = 0; // Called when form becomes enabled
		virtual void NotifyOnDisable() = 0; // Called when form becomes disabled
		virtual void NotifyOnClose(CloseAction &action) = 0; // Called when form is about to be closed. Action could be changed to change default behavior(which is close and destroy the form usually)
		virtual void NotifyOnShow() = 0; // Called when form has been shown
		virtual void NotifyOnHide() = 0; // Called when form has been hidden
		virtual void NotifyOnMove(const MessagePosition &m) = 0; // Called when form has been moved
		virtual void NotifyOnRestore(const MessageSize &m) = 0; // Called when form has been restored
		virtual void NotifyOnMinimize(const MessageSize &m) = 0; // Called when form has been minimized
		virtual void NotifyOnMaximize(const MessageSize &m) = 0; // Called when form has been maximized
		virtual void NotifyOnResizing(const MessageWindowResizing &m) = 0; // Called when form has been resized
		virtual void NotifyOnMoving(const MessageRect &m) = 0; // Called when form has been moved
		virtual void NotifyOnEnterSizeMove() = 0; // Called when form has entered resizing and moving state
		virtual void NotifyOnExitSizeMove() = 0; // Called when form has existed resizing and moving state
		virtual void NotifyOnHScroll(const MessageWindowScroll &m) = 0; // Called when horizontal scroll has happened
		virtual void NotifyOnVScroll(const MessageWindowScroll &m) = 0; // Called when vertical scroll has happened
		virtual void NotifyOnLoseCapture() = 0; // Called when form has lose capture mouse input

		// Dialog box notifications
		virtual void NotifyOnDialogBoxActivate(IDialogBox *control) = 0; // Called when dialog box becomes active
		virtual void NotifyOnDialogBoxDeactivate(IDialogBox *control) = 0; // Called when dialog box loses active state

		// Clipboard notifications
		virtual void NotifyOnPasteString(const MessagePasteString &m) = 0; // Called when a string is available after paste request
	};
}