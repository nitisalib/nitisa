// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Messages.h"
#include "../Core/Strings.h"

namespace nitisa
{
	class IComponent;
	class IDialogBox;
	class IForm;

	class IComponentService
	{
	protected:
		IComponentService() = default;
		~IComponentService() = default;
		IComponentService(const IComponentService &other) = delete;
		IComponentService(IComponentService &&other) = delete;
		IComponentService &operator=(const IComponentService &other) = delete;
		IComponentService &operator=(IComponentService &&other) = delete;
	public:
		virtual void setName(const String &value) = 0; // Should only set component name and do nothing more
		virtual void setForm(IForm *value) = 0; // Should only set form and do nothing more

		virtual void Release() = 0; // Destroy service
		virtual void SendChangeNotification() = 0; // Send notification to form, other components and controls about this component change

		// State change notifications
		virtual void NotifyOnAttach() = 0; // Called after component was attached to form
		virtual void NotifyOnDetaching() = 0; // Called before detaching from parent. Called for all child controls
		virtual void NotifyOnDetach() = 0; // Called after component was detached from form
		virtual void NotifyOnFreeResources() = 0; // Should free any resources related to form(timers, textures, platform fonts,...)

		// Component notifications
		virtual void NotifyOnComponentAttach(IComponent *component) = 0; // Called when some component was attached to form
		virtual void NotifyOnComponentDetach(IComponent *component) = 0; // Called when some component was detached from form
		virtual void NotifyOnComponentChange(IComponent *component) = 0; // Called when some component was changed

		// Control notifications
		virtual void NotifyOnControlAttach(IControl *control) = 0; // Called when some control was attached to form
		virtual void NotifyOnControlDetach(IControl *control) = 0; // Called when some control was detached from form
		virtual void NotifyOnControlChange(IControl *control) = 0; // Called when some component was changed
		virtual void NotifyOnControlSetFocus(IControl *control, const MessageFocus &m) = 0; // Called when another control has received keyboard focus
		virtual void NotifyOnControlKillFocus(IControl *control) = 0; // Called when another control has lost keyboard focus
		virtual void NotifyOnControlSetCaptureKeyboard(IControl *control) = 0; // Called when another control has captured keyboard input
		virtual void NotifyOnControlKillCaptureKeyboard(IControl *control) = 0;// Called when another control has lost capture of keyboard input
		virtual void NotifyOnControlSetCaptureMouse(IControl *control) = 0; // Called when another control has captured mouse input
		virtual void NotifyOnControlKillCaptureMouse(IControl *control) = 0; // Called when another control has lost capture of mouse input
		virtual void NotifyOnControlSetModal(IControl *control) = 0; // Called when another control has became modal
		virtual void NotifyOnControlKillModal(IControl *control) = 0; // Called when another control has lost modal state

		// Other input notifications
		virtual void NotifyOnHotkey(const MessageHotkey &m) = 0; // Called when registered hotkey pressed/released

		// Application notifications
		virtual void NotifyOnApplicationActivate() = 0; // Called when application has became active
		virtual void NotifyOnApplicationDeactivate() = 0; // Called when application has became inactive
		virtual void NotifyOnTimeChange() = 0; // Called when system time has been changed
		virtual void NotifyOnInputLanguageChange() = 0; // Called when input language has been changed
		virtual void NotifyOnDisplayChange(const MessageSize &m) = 0; // Called when display settings has been changed
		virtual void NotifyOnThemeChange() = 0; // Called when theme has been changed
		virtual void NotifyOnClipboardUpdate() = 0; // Called when clipboard data has been changed
		virtual void NotifyOnTranslateChange() = 0; // Called when application gets information about changes in translation matrix(either by current language change in ITranslate or via custom call of IApplicationService::SendTranslateChange method)

		// Form/window notifications
		virtual void NotifyOnFormActivate(const MessageWindowActivate &m) = 0; // Called when form has became active
		virtual void NotifyOnFormDeactivate() = 0; // Called when form has became inactive
		virtual void NotifyOnFormSetFocus() = 0; // Called when form has received keyboard input
		virtual void NotifyOnFormKillFocus() = 0; // Called when form has lost keyboard input
		virtual void NotifyOnFormEnable() = 0; // Called when form has became enabled
		virtual void NotifyOnFormDisable() = 0; // Called when form has became disabled
		virtual void NotifyOnFormShow() = 0; // Called when form has became visible
		virtual void NotifyOnFormHide() = 0; // Called when form has became invisible
		virtual void NotifyOnFormMove(const MessagePosition &m) = 0; // Called when form is being moved
		virtual void NotifyOnFormRestore(const MessageSize &m) = 0;  // Called when form has been restored
		virtual void NotifyOnFormMinimize(const MessageSize &m) = 0; // Called when form has been minimized
		virtual void NotifyOnFormMaximize(const MessageSize &m) = 0; // Called when form has been maximizing
		virtual void NotifyOnFormEnterSizeMove() = 0; // Called when form has entered in resizing and moving state
		virtual void NotifyOnFormExitSizeMove() = 0; // Called when form has exited resizing and moving state

		// Dialog box notifications
		virtual void NotifyOnDialogBoxActivate(IDialogBox *control) = 0; // Called when specified dialog box becomes active
		virtual void NotifyOnDialogBoxDeactivate(IDialogBox *control) = 0; // Called when specified dialog box loses active state
	};
}