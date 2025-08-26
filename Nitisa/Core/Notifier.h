// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Math/PointF.h"
#include "FocusedBy.h"
#include "Messages.h"

namespace nitisa
{
	class IComponent;
	class IControl;
	class IDialogBox;
	class IForm;

	class CNotifier
	{
	private:
		static void FreeResources(IControl *sender);
		static void FormActivate(IControl *sender, const MessageWindowActivate &m);
		static void FormDeactivate(IControl *sender);
		static void ControlSetFocus(IControl *focused, IControl *sender, const MessageFocus &m);
		static void FormSetFocus(IControl *sender);
		static void ControlKillFocus(IControl *focused, IControl *sender);
		static void FormKillFocus(IControl *sender);
		static void FormEnable(IControl *sender);
		static void FormDisable(IControl *sender);
		static void FormShow(IControl *sender);
		static void FormHide(IControl *sender);
		static void ApplicationActivate(IControl *sender);
		static void ApplicationDeactivate(IControl *sender);
		static void FormMove(IControl *sender, const MessagePosition &m);
		static void FormRestore(IControl *sender, const MessageSize &m);
		static void FormMinimize(IControl *sender, const MessageSize &m);
		static void FormMaximize(IControl *sender, const MessageSize &m);
		static void FormEnterSizeMove(IControl *sender);
		static void FormExitSizeMove(IControl *sender);
		static void TimeChange(IControl *sender);
		static void InputLanguageChange(IControl *sender);
		static void DisplayChange(IControl *sender, const MessageSize &m);
		static void ThemeChange(IControl *sender);
		static void ClipboardUpdate(IControl *sender);
		static void ControlKillModal(IControl *sender, IControl *modal);
		static void ControlSetModal(IControl *sender, IControl *modal);
		static void ControlKillCaptureKeyboard(IControl *sender, IControl *capture);
		static void ControlSetCaptureKeyboard(IControl *sender, IControl *capture);
		static void ControlKillCaptureMouse(IControl *sender, IControl *capture);
		static void ControlSetCaptureMouse(IControl *sender, IControl *capture);
		static void ControlAttach_r(IControl *sender, IControl *control);
		static void Attach(IControl *control); // Send NotifyOnAttach to control and it's children
		static void ControlDetach_r(IControl *sender, IControl *control);
		static void Detach(IControl *control); // Send NotifyOnDetach to control and it's children
		static void TranslateChange(IControl *control);
		static void ControlActivateDialogBox(IControl *sender, IDialogBox *control);
		static void ControlDeactivateDialogBox(IControl *sender, IDialogBox *control);
	public:
		static void FreeResources(IForm *form); // Call FreeResource on all form components, controls, and form itself
		static void FormActivate(IForm *form, const MessageWindowActivate &m); // Send form activation notification to form and all its components and controls
		static void FormDeactivate(IForm *form); // Send form deactivation notification to form and all its components and controls
		static void ControlSetFocus( // Send notification to all controls, components, and form except focused one about focusing new control
			IForm *form, // Form where control is
			IControl *control, // Control getting keyboard focus
			IControl *old_focused_control, // Control which had keyboard focus before new one
			const FocusedBy focused_by); // Reason of changing focused control
		static void FormSetFocus(IForm *form); // Send notification about focusing form to form, components, and controls
		static void ControlKillFocus( // Send notification to form, components, and controls about defocusing some control. Control which lose focus don't receive the notification
			IForm *form, // Form where control is
			IControl *control); // Control losing keyboard focus
		static void FormKillFocus(IForm *form); // Send notification about defocusing form to form, components, and controls
		static void FormEnable(IForm *form); // Send notification about enabling form to form, components, and controls
		static void FormDisable(IForm *form); // Send notification about disabling form to form, components, and controls
		static void FormShow(IForm *form); // Send notification about showing form to form, components, and controls
		static void FormHide(IForm *form); // Send notification about hiding form to form, components, and controls
		static void ApplicationActivate(IForm *form); // Send notification about activating application to form, components, and controls
		static void ApplicationDeactivate(IForm *form); // Send notification about deactivating application to form, components, and controls
		static void FormMove(IForm *form, const MessagePosition &m); // Send notification about form moving to form, components, and controls
		static void ParentResize(IForm *form); // Send parent resize notification to controls placed directly on the form
		static void FormRestore(IForm *form, const MessageSize &m); // Send notification about restoring form to form, components, and controls
		static void FormMinimize(IForm *form, const MessageSize &m); // Send notification about minimizing form to form, components, and controls
		static void FormMaximize(IForm *form, const MessageSize &m); // Send notification about maximizing form to form, components, and controls
		static void FormEnterSizeMove(IForm *form); // Send notification about form entering resize and move process to form, components, and controls
		static void FormExitSizeMove(IForm *form); // Send notification about form exiting from resize and move process to form, components, and controls
		static void TimeChange(IForm *form); // Send notification about system time change to form, components, and controls
		static void InputLanguageChange(IForm *form); // Send notification about language change to form, components, and controls
		static void DisplayChange(IForm *form, const MessageSize &m); // Send notification about display change to form, components, and controls
		static void ThemeChange(IForm *form); // Send notification about theme change to form, components, and controls
		static void ClipboardUpdate(IForm *form); // Send notification about clipboard update to form, components, and controls
		static void StyleChange(IForm *form); // Send notification about style change to form, components, and controls(to those of them which use parent style)
		static void ParentStyleChange(IControl *sender); // Send notification about style change to control child controls(all in hierarchy which uses parent style)
		static void FontChange(IForm *form); // Send notification about font change to form, components, and controls(to those of them which use parent font)
		static void ParentFontChange(IControl *sender); // Send notification about font change to control child controls(all in hierarchy which uses parent font)
		static void ControlKillModal( // Send notification about control exiting modal state to form, components, and controls(excluding modal one)
			IForm *form, // Form where control is
			IControl *control); // Control losing modal state
		static void ControlSetModal( // Send notification about control receiving modal state to form, components, and controls(excluding modal one)
			IForm *form, // Form where control is
			IControl *control); // Control getting modal state
		static void ControlKillCaptureKeyboard( // Send notification about control losing keyboard capture state to form, components, and controls(excluding control which captures keyboard)
			IForm *form, // Form where control is
			IControl *control); // Control losing keyboard capture
		static void ControlSetCaptureKeyboard( // Send notification about control receiving keyboard capture state to form, components, and controls(excluding control which captures keyboard)
			IForm *form, // Form where control is
			IControl *control); // Control getting keyboard capture
		static void ControlKillCaptureMouse( // Send notification about control losing mouse capture state to form, components, and controls(excluding control which captures mouse)
			IForm *form, // Form where control is
			IControl *control); // Control losing mouse capture
		static void ControlSetCaptureMouse( // Send notification about control receiving mouse capture state to form, components, and controls(excluding control which captures mouse)
			IForm *form, // Form where control is
			IControl *control); // Control getting mouse capture
		static void TransformControls(IForm *form); // Send notification about changing child controls transformation to all the controls which are placed onto the form directly
		static void ComponentAttach(IForm *form, IComponent *component); // Send notification about attaching new component to form, components, and controls(excluding attached one)
		static void ComponentAttach(IControl *sender, IComponent *component); // Send notification about attaching new component to control and all its children
		static void ComponentDetach(IForm *form, IComponent *component); // Send notification about detaching component to form, components, and controls(excluding detached one)
		static void ComponentDetach(IControl *sender, IComponent *component); // Send notification about detaching component to control and all its children
		static void ControlAttach(IForm *form, IControl *control); // Send notification about attaching new control to form, components, and controls(excluding attached one)
		static void ControlAttach(IControl *parent, IControl *control); // Send notification about attaching new control to control and all its children(excluding attached one)
		static void ControlDetach(IForm *form, IControl *control); // Send notification about detaching control to form, components, and controls(excluding detached one)
		static void ControlDetach(IControl *parent, IControl *control); // Send notification about detaching control to control and all its childer(excluding detached one)
		static void Resize(IControl *control); // Notify specified control and its direct children about resizing specified control
		static void MouseHoverControl( // Send notification about hovering new control by mouse pointer to form and hovered control
			IForm *form, // Form where control is
			IControl *control, // Control below mouse pointer
			const PointF &position); // Mouse pointer position
		static void MouseLeaveControl( // Send notification about unhovering control by mouse pointer to form and unhovered control
			IForm *form, // Form where control is
			IControl *control); // Control was below mouse pointer
		static void Render( // Send render notification to control and all its children
			IControl *control, // Control to be rendered
			const MessagePaint &m, // Notification message data
			IControl *draw_last); // Control to be rendered last independently on its Z-index and creation order. Can be nullptr
		static void Detaching(IControl *control); // Send detaching notification to specified control and all its children(send before real detachment). Also calls FreeResources
		static void Detaching(IComponent *component); // Send detaching notification to component(sent before real detachment). Also calls FreeResource
		static void TranslateChange(IForm *form); // Send notification about translation change to form and all it's entities
		static void ControlActivate( // Send notification to form and control about activation of specified control
			IForm *form, // Form where control is
			IControl *control); // Control getting active state
		static void ControlDeactivate( // Send notification to form and control about deactivation of specified control
			IForm *form, // Form where control is
			IControl *control); // Control losing active state
		static void ControlActivateDialogBox( // Send notification to form and all controls and components about activation of specified dialog box
			IForm *form, // Form where control is
			IDialogBox *control); // Dialog box getting active state
		static void ControlDeactivateDialogBox( // Send notification to form and all controls and components about deactivation of specified dialog box
			IForm *form, // Form where control is
			IDialogBox *control); // Dialog box losing active state
		static void ControlHide(IControl *control); // Send notification to control, parent, and children when control becomes invisible
		static void ControlShow(IControl *control); // Send notification to control, parent, and children when control becomes visible
		static void ControlDisable(IControl *control); // Send notification to control, parent, and children when control becomes disabled
		static void ControlEnable(IControl *control); // Send notification to control, parent, and children when control becomes enabled
	};
}