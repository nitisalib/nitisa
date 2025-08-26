// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IComponentService.h"
#include "Messages.h"
#include "Strings.h"

namespace nitisa
{
	class IComponent;
	class IControl;
	class IDialogBox;
	class IForm;
	
	class CComponentSpliceService :public virtual IComponentService
	{
	private:
		IComponent *m_pComponent;
		IComponentService *m_pService;
	public:
		void setName(const String &value) override;
		void setForm(IForm *value) override;

		void Release() override;
		void SendChangeNotification() override;

		// State change notifications
		void NotifyOnAttach() override;
		void NotifyOnDetaching() override;
		void NotifyOnDetach() override;
		void NotifyOnFreeResources() override;

		// Component notifications
		void NotifyOnComponentAttach(IComponent *component) override;
		void NotifyOnComponentDetach(IComponent *component) override;
		void NotifyOnComponentChange(IComponent *component) override;

		// Control notifications
		void NotifyOnControlAttach(IControl *control) override;
		void NotifyOnControlDetach(IControl *control) override;
		void NotifyOnControlChange(IControl *control) override;
		void NotifyOnControlSetFocus(IControl *control, const MessageFocus &m) override;
		void NotifyOnControlKillFocus(IControl *control) override;
		void NotifyOnControlSetCaptureKeyboard(IControl *control) override;
		void NotifyOnControlKillCaptureKeyboard(IControl *control) override;
		void NotifyOnControlSetCaptureMouse(IControl *control) override;
		void NotifyOnControlKillCaptureMouse(IControl *control) override;
		void NotifyOnControlSetModal(IControl *control) override;
		void NotifyOnControlKillModal(IControl *control) override;

		// Other input notifications
		void NotifyOnHotkey(const MessageHotkey &m) override;

		// Application notifications
		void NotifyOnApplicationActivate() override;
		void NotifyOnApplicationDeactivate() override;
		void NotifyOnTimeChange() override;
		void NotifyOnInputLanguageChange() override;
		void NotifyOnDisplayChange(const MessageSize &m) override;
		void NotifyOnThemeChange() override;
		void NotifyOnClipboardUpdate() override;
		void NotifyOnTranslateChange() override;

		// Form/window notifications
		void NotifyOnFormActivate(const MessageWindowActivate &m) override;
		void NotifyOnFormDeactivate() override;
		void NotifyOnFormSetFocus() override;
		void NotifyOnFormKillFocus() override;
		void NotifyOnFormEnable() override;
		void NotifyOnFormDisable() override;
		void NotifyOnFormShow() override;
		void NotifyOnFormHide() override;
		void NotifyOnFormMove(const MessagePosition &m) override;
		void NotifyOnFormRestore(const MessageSize &m) override;
		void NotifyOnFormMinimize(const MessageSize &m) override;
		void NotifyOnFormMaximize(const MessageSize &m) override;
		void NotifyOnFormEnterSizeMove() override;
		void NotifyOnFormExitSizeMove() override;

		// Dialog box notifications
		void NotifyOnDialogBoxActivate(IDialogBox *control) override;
		void NotifyOnDialogBoxDeactivate(IDialogBox *control) override;

		CComponentSpliceService(IComponent *component); // Specify component which service should be spliced(replaced) by this one. Component is assumed to be valid, empty value should not be used. Also component should return valid service via QueryService() method. Empty service is unacceptable
		virtual ~CComponentSpliceService(); // Restore component original service and destroy itself. If component's service was spliced several times, restore only own splicing changes. It allows to work properly with multiple splicing
	};
}