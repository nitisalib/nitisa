// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/FocusedBy.h"
#include "../Core/Messages.h"
#include "../Math/PointF.h"
#include "IComponentService.h"

namespace nitisa
{
	class IControl;

	// Usually notifications do not require any action, but if you change any property in it, don't forget to do all corresponding actions like control aligning, modal/active/focused/hovered/capture
	// control update, send notifications and so on. Also don't send notifications recursively in methods of this interface because they can be already called recursively by parent. Send recursive
	// notification in place where it was required(like control or form implementation)
	class IControlService :public virtual IComponentService
	{
	protected:
		IControlService() = default;
		~IControlService() = default;
		IControlService(const IControlService &other) = delete;
		IControlService(IControlService &&other) = delete;
		IControlService &operator=(const IControlService &other) = delete;
		IControlService &operator=(IControlService &&other) = delete;
	public:
		// Getters
		virtual PointF getSizeRequested() = 0; // Return requested size(the size was passed to setSize() without alignment & constraints applied). Real size returned by control's getSize could be different due to constraints and alignment

		// Setters
		virtual void setParent(IControl *value) = 0; // Should only set specified parent pointer, no other changes should be done, operation should be always successful
		virtual void setTabOrder(const int value) = 0; // Should only set specified tab order, no other changes should be done, operation should be always successful
		virtual void setSize(const PointF &value) = 0; // Should only set specified size, no other changes should be done, operation should be always successful

		// Helpers
		virtual void AdjustSize() = 0; // Should adjust size by constraints, align child controls and send notifications if size was changed
		virtual bool MoveControl(IControl *control, const int before) = 0; // Change control order in list. Index should be in range 0..ControlCount, control should be child and it's index should not be equal to index. Should return true only if control was moved
		virtual void AlignControls() = 0; // Recalculate child controls sizes and positions depending on their alignment
		virtual void InsertControl(IControl *control, const int before) = 0; // Should add control to list before specified index or to the end without any checks and other operations

		// Notifications from parent control
		virtual void NotifyOnParentStyleChange() = 0; // Called when parent control/form style was changed due to style set or change use parent style settings(the font may be changed as well but there will not be any notification about it). No repaint is required
		virtual void NotifyOnParentFontChange() = 0; // Called when parent control/form font was changed due to set font or change font properties. No repaint is required
		virtual void NotifyOnParentResize() = 0; // Called when parent control/form was resized
		virtual void NotifyOnParentTransform() = 0; // Called when parent control/form was transformed or new transform was assigned
		virtual void NotifyOnParentTransformControls() = 0; // Called when parent control/form child controls transformation was changed or new child controls transformation was assigned

		// Notifications from child controls
		virtual void NotifyOnChildStyleChange(IControl *control) = 0; // If size depends on child size, it is the best place where to handle child control size changes due to style change
		virtual void NotifyOnChildFontChange(IControl *control) = 0; // If size depends on child size, it is the best place where to handle child control size changes due to font change
		virtual void NotifyOnChildTransform(IControl *control) = 0; // If size depends on child position, it is the best place where to handle child control position changes due to transformation change
		virtual void NotifyOnChildResize(IControl *control) = 0; // If size depends on child size, it is the best place where to handle child control size changes due to resize or alignment change
		virtual void NotifyOnChildShow(IControl *control) = 0; // If size depends on child visibility, it is the best place where to handle child control visibility changes due to show
		virtual void NotifyOnChildHide(IControl *control) = 0; // If size depends on child visibility, it is the best place where to handle child control visibility changes due to hide
		virtual void NotifyOnChildAttach(IControl *control) = 0; // If size depends on child visibility, it is the best place where to handle child control visibility changes due to attach. e.getTarget() is attached control
		virtual void NotifyOnChildDetach(IControl *control) = 0; // If size depends on child visibility, it is the best place where to handle child control visibility changes due to detach. e.getTarget() is detached control
		virtual void NotifyOnChildEnable(IControl *control) = 0; // Called when child control become enabled
		virtual void NotifyOnChildDisable(IControl *control) = 0; // Called when child control become disabled
		virtual void NotifyOnChildBeforeTransform(IControl *control, bool &allowed) = 0; // Called before applying transformation to control. Set allowed to false to forbid the change
		virtual void NotifyOnChildBeforeResize(IControl *control, bool &allowed) = 0; // Called before resizing control. Set allowed to false to forbid the change
		virtual void NotifyOnChildBeforeShow(IControl *control, bool &allowed) = 0; // Called before showing control. Set allowed to false to forbid the change
		virtual void NotifyOnChildBeforeHide(IControl *control, bool &allowed) = 0; // Called before hiding control. Set allowed to false to forbid the change
		virtual void NotifyOnChildBeforeEnable(IControl *control, bool &allowed) = 0; // Called before enabling control. Set allowed to false to forbid the change
		virtual void NotifyOnChildBeforeDisable(IControl *control, bool &allowed) = 0; // Called before disabling control. Set allowed to false to forbid the change

		// State change notifications
		virtual void NotifyOnShow() = 0; // Called when control becomes visible due to visibility flag change(a parent controls may still be invisible)
		virtual void NotifyOnHide() = 0; // Called when control becomes invisible due to visibility flag change
		virtual void NotifyOnEnable() = 0; // Called when control becomes enabled due to accessibility flag change
		virtual void NotifyOnDisable() = 0; // Called when control becomes disabled due to accessibility flag change
		virtual void NotifyOnResize() = 0; // Called when control size was changed
		virtual void NotifyOnTransform() = 0; // Called when control transformation was changed due to transformation or set new transformation object
		virtual void NotifyOnTransformControls() = 0; // Called when child controls transformation was changed due to change of child controls transformation or set new one
		virtual void NotifyOnStyleChange() = 0; // Called when style was changed due to set new style or change use parent style setting. If size was changed, apply constraints here. No repaint is required
		virtual void NotifyOnFontChange() = 0; // Called when font was changed due to change properties or set new font. If size was changed, apply constraints here. No repaint is required
		virtual void NotifyOnSetModal() = 0; // Called when control becomes modal
		virtual void NotifyOnKillModal() = 0; // Called when controls lose modal state
		virtual void NotifyOnSetFocus(const MessageFocus &m) = 0; // Called when control becomes focused
		virtual void NotifyOnKillFocus() = 0; // Called when focused control lose focus
		virtual void NotifyOnSetCaptureKeyboard() = 0; // Called when control gets keyboard capture
		virtual void NotifyOnKillCaptureKeyboard() = 0; // Called when control loses keyboard capture
		virtual void NotifyOnSetCaptureMouse() = 0; // Called when control gets mouse capture
		virtual void NotifyOnKillCaptureMouse() = 0; // Called when control loses mouse capture
		virtual void NotifyOnActivate() = 0; // Called when control become active
		virtual void NotifyOnDeactivate() = 0; // Called when control lose active state

		// Paint notifications. If m.last_pass is true only unclipped parts should be rendered. If m.last_pass is false, any parent control may apply clipping, so only part that may be clipped should be rendered. Also if control is capture mouse and should be over other controls independently on z-index, it may draw itself if m.last_pass is true
		virtual void NotifyOnPaint(const MessagePaint &m, bool &draw_children) = 0; // Called when control should be drawn. 
		virtual void NotifyOnPaintEnd(const MessagePaint &m) = 0; // Called after drawing of control and children

		// Keyboard input notifications
		virtual void NotifyOnKeyDown(const MessageKey &m, bool &processed) = 0; // Called when control is focused or capture keyboard and key is down
		virtual void NotifyOnKeyUp(const MessageKey &m, bool &processed) = 0; // Called when control is focused or capture keyboard and key is up
		virtual void NotifyOnChar(const MessageChar &m, bool &processed) = 0; // Called when control is focused or capture keyboard and char translated
		virtual void NotifyOnDeadChar(const MessageChar &m, bool &processed) = 0; // Called when control is focused or capture keyboard and dead char translated

		// Mouse input notifications
		virtual void NotifyOnMouseHover(const MessagePosition &m) = 0; // Called when mouse pointer appears over control. m.Position is in form coordinate space
		virtual void NotifyOnMouseLeave() = 0; // Called when mouse pointer leaves control area
		virtual void NotifyOnMouseMove(const MessageMouse &m, bool &processed) = 0; // Called when control is under mouse pointer or capture mouse and mouse moves. m.Position is in form coordinate space
		virtual void NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed) = 0; // Called when control is under mouse pointer or capture mouse and left mouse button down
		virtual void NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed) = 0; // Called when control is under mouse pointer or capture mouse and left mouse button up
		virtual void NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed) = 0; // Called when control is under mouse pointer or capture mouse and left mouse button double clicked
		virtual void NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed) = 0; // Called when control is under mouse pointer or capture mouse and right mouse button down
		virtual void NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed) = 0; // Called when control is under mouse pointer or capture mouse and right mouse button up
		virtual void NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed) = 0; // Called when control is under mouse pointer or capture mouse and right mouse mutton double clicked
		virtual void NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed) = 0; // Called when control is under mouse pointer or capture mouse and middle mouse button down
		virtual void NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed) = 0; // Called when control is under mouse pointer or capture mouse and middle mouse button up
		virtual void NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed) = 0; // Called when control is under mouse pointer or capture mouse and middle mouse button double clicked
		virtual void NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed) = 0; // Called when control is under mouse pointer or capture mouse and mouse vertical scroll appear
		virtual void NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed) = 0; // Called when control is under mouse pointer or capture mouse and mouse horizontal scroll appear

		// Other input notifications
		virtual void NotifyOnDropFiles(const MessageDropFiles &m, bool &processed, bool &accepted) = 0; // Called when control is under mouse pointer or capture mouse and drop files appear

		// Clipboard notifications
		virtual void NotifyOnPasteString(const MessagePasteString &m) = 0; // Called when a string is available after paste request

		// Interceptors. Catch child control events. Return true if handled, otherwise default action will be taken. Only nearest parent will intercept event. Don't use interceptors in hierarchy
		// Also capture and modal controls does not involved in interceptions. No parent control can intercept event of child control which have capture or modal state
		virtual bool InterceptSetCursor(IControl *control) = 0; // Intercept change cursor
		virtual bool InterceptMouseHover(IControl *control) = 0; // Intercept mouse hovering
		virtual bool InterceptShowHint(IControl *control, String &hint) = 0; // Intercept show hint. To change hint only, change hint argument and return false
		virtual bool InterceptTabOrder() = 0; // Intercept tab order. Return true if no child controls can be focused by Tab or by FocusNextControl/FocusPrevControl
		virtual bool InterceptHotkeys(IControl *control, const MessageHotkey &m) = 0;
		virtual bool InterceptKeyDown(IControl *control, const MessageKey &m) = 0;
		virtual bool InterceptKeyUp(IControl *control, const MessageKey &m) = 0;
		virtual bool InterceptChar(IControl *control, const MessageChar &m) = 0;
		virtual bool InterceptDeadChar(IControl *control, const MessageChar &m) = 0;
		virtual bool InterceptMouseMove(IControl *control, const MessageMouse &m) = 0;
		virtual bool InterceptLeftMouseButtonDown(IControl *control, const MessageMouse &m) = 0;
		virtual bool InterceptLeftMouseButtonUp(IControl *control, const MessageMouse &m) = 0;
		virtual bool InterceptLeftMouseButtonDoubleClick(IControl *control, const MessageMouse &m) = 0;
		virtual bool InterceptMiddleMouseButtonDown(IControl *control, const MessageMouse &m) = 0;
		virtual bool InterceptMiddleMouseButtonUp(IControl *control, const MessageMouse &m) = 0;
		virtual bool InterceptMiddleMouseButtonDoubleClick(IControl *control, const MessageMouse &m) = 0;
		virtual bool InterceptRightMouseButtonDown(IControl *control, const MessageMouse &m) = 0;
		virtual bool InterceptRightMouseButtonUp(IControl *control, const MessageMouse &m) = 0;
		virtual bool InterceptRightMouseButtonDoubleClick(IControl *control, const MessageMouse &m) = 0;
		virtual bool InterceptMouseVerticalWheel(IControl *control, const MessageMouseWheel &m) = 0;
		virtual bool InterceptMouseHorizontalWheel(IControl *control, const MessageMouseWheel &m) = 0;
		virtual bool InterceptDropFiles(IControl *control, const MessageDropFiles &m) = 0;
		virtual bool InterceptFocus(IControl *control, const FocusedBy focused_by) = 0; // Works for focus by mouse. To prevent focus by tab use InterceptTabOrder(). If control intercept focus, it will be focused regardless of isAcceptFocus() returns
	};
}