// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Messages.h"
#include "../Core/Variant.h"
#include "IClass.h"
#include "IReleasable.h"

namespace nitisa
{
	class IComponent;
	class IComponentService;
	class IControl;
	class IDialogBox;
	class IForm;

	class IComponent : public virtual IClass, public virtual IReleasable
	{
	protected:
		IComponent() = default;
		~IComponent() = default;
		IComponent(const IComponent &other) = delete;
		IComponent(IComponent &&other) = delete;
		IComponent &operator=(const IComponent &other) = delete;
		IComponent &operator=(IComponent &&other) = delete;
	public:
		Variant Tag; // User data

		// State change events
		void(*OnAttach)(IComponent *sender); // Event called when component is just attached to a form
		void(*OnDetaching)(IComponent *sender); // Event called when component is about to be detached from a form
		void(*OnDetach)(IComponent *sender); // Event called when component has just been detached from a form

		// Component events
		void(*OnComponentAttach)(IComponent *sender, IComponent *component); // Event called when another component has just been attached to a form
		void(*OnComponentDetach)(IComponent *sender, IComponent *component); // Event called when another component has just been detached from a form
		void(*OnComponentChange)(IComponent *sender, IComponent *component); // Event called when another component has been changed and sent notification about it

		// Control events
		void(*OnControlAttach)(IComponent *sender, IControl *control); // Event called when control has just been attached to a form
		void(*OnControlDetach)(IComponent *sender, IControl *control); // Event called when control has just been detached form a form
		void(*OnControlChange)(IComponent *sender, IControl *control); // Event called when control has been changed and sent notification about it
		void(*OnControlSetFocus)(IComponent *sender, IControl *control, const MessageFocus &m); // Event called when control has received keyboard focus
		void(*OnControlKillFocus)(IComponent *sender, IControl *control); // Event called when control has lost keyboard focus
		void(*OnControlSetCaptureMouse)(IComponent *sender, IControl *control); // Event called when control has captured mouse input
		void(*OnControlKillCaptureMouse)(IComponent *sender, IControl *control); // Event called when control has lost capture of mouse input
		void(*OnControlSetCaptureKeyboard)(IComponent *sender, IControl *control); // Event called when control has captured keyboard input
		void(*OnControlKillCaptureKeyboard)(IComponent *sender, IControl *control); // Event called when control has lost capture of keyboard input
		void(*OnControlSetModal)(IComponent *sender, IControl *control); // Event called when control becomes modal
		void(*OnControlKillModal)(IComponent *sender, IControl *control); // Event called when modal control becomes non-modal

		// Other input events
		void(*OnHotkey)(IComponent *sender, const MessageHotkey &m); // Event called when registered hotkey received

		// Application events
		void(*OnApplicationActivate)(IComponent *sender); // Event called when application become active
		void(*OnApplicationDeactivate)(IComponent *sender); // Event called when application become inactive
		void(*OnTimeChange)(IComponent *sender); // Event called when system time changed
		void(*OnInputLanguageChange)(IComponent *sender); // Event called when input language changed
		void(*OnDisplayChange)(IComponent *sender, const MessageSize &m); // Event called when display settings changed
		void(*OnThemeChange)(IComponent *sender); // Event called when system theme changed
		void(*OnClipboardUpdate)(IComponent *sender); // Event called when clipboard data has been updated
		void(*OnTranslateChange)(IComponent *sender); // Event called when application gets information about changes in translation matrix

		// Form events
		void(*OnFormActivate)(IComponent *sender, const MessageWindowActivate &m); // Event called when form becomes active
		void(*OnFormDeactivate)(IComponent *sender); // Event called when form becomes inactive
		void(*OnFormSetFocus)(IComponent *sender); // Event called when form receives keyboard focus
		void(*OnFormKillFocus)(IComponent *sender); // Event called when form loses keyboard focus
		void(*OnFormEnable)(IComponent *sender); // Event called when form becomes enabled
		void(*OnFormDisable)(IComponent *sender); // Event called when form becomes disabled
		void(*OnFormShow)(IComponent *sender); // Event called when form becomes visible
		void(*OnFormHide)(IComponent *sender); // Event called when form becomes invisible
		void(*OnFormMove)(IComponent *sender, const MessagePosition &m); // Event called when form is moving
		void(*OnFormRestore)(IComponent *sender, const MessageSize &m); // Event called when form has been restored
		void(*OnFormMinimize)(IComponent *sender, const MessageSize &m); // Event called when form has been minimized
		void(*OnFormMaximize)(IComponent *sender, const MessageSize &m); // Event called when form has been maximized
		void(*OnFormEnterSizeMove)(IComponent *sender); // Event called when form enters in resize and move process
		void(*OnFormExitSizeMove)(IComponent *sender); // Event called when form exists from resize and move process

		// Dialog box events
		void(*OnDialogBoxActivate)(IComponent *sender, IDialogBox *control); // Event called when specified dialog box becomes active
		void(*OnDialogBoxDeactivate)(IComponent *sender, IDialogBox *control); // Event called when specified dialog box loses active state

		virtual IForm *getForm() = 0; // Return form to which the component belongs

		virtual bool setForm(IForm *value) = 0; // Set new form for the component. Nullptr to remove from current form and don't add to other one
		virtual void setService(IComponentService *value, const bool release_prev) = 0; // Set new service. Use only compatible services and avoid setting empty value

		virtual IComponentService *QueryService() = 0; // Return service
	};
}