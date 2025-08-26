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
	void CNotifier::FreeResources(IForm *form) 
	{
		for (int i = 0; i < form->getComponentCount(); i++)
			form->getComponent(i)->QueryService()->NotifyOnFreeResources();
		for (int i = 0; i < form->getControlCount(); i++)
			FreeResources(form->getControl(i));
		form->QueryService()->NotifyOnFreeResources();
	}

	void CNotifier::FreeResources(IControl *sender)
	{
		if (sender->hasFont())
			sender->getControlFont()->NotifyOnFreeResources();
		sender->QueryService()->NotifyOnFreeResources();
		for (int i = 0; i < sender->getControlCount(); i++)
			FreeResources(sender->getControl(i));
	}

	void CNotifier::FormActivate(IForm *form, const MessageWindowActivate &m)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnFormActivate(m);
			if (form->getComponent(i)->OnFormActivate)
				form->getComponent(i)->OnFormActivate(form->getComponent(i), m);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			FormActivate(form->getControl(i), m);
		form->QueryService()->NotifyOnActivate(m);
		if (form->OnActivate)
			form->OnActivate(form, m);
	}

	void CNotifier::FormActivate(IControl *sender, const MessageWindowActivate &m)
	{
		sender->QueryService()->NotifyOnFormActivate(m);
		if (sender->OnFormActivate)
			sender->OnFormActivate(sender, m);
		for (int i = 0; i < sender->getControlCount(); i++)
			FormActivate(sender->getControl(i), m);
	}

	void CNotifier::FormDeactivate(IForm *form)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnFormDeactivate();
			if (form->getComponent(i)->OnFormDeactivate)
				form->getComponent(i)->OnFormDeactivate(form->getComponent(i));
		}
		for (int i = 0; i < form->getControlCount(); i++)
			FormDeactivate(form->getControl(i));
		form->QueryService()->NotifyOnDeactivate();
		if (form->OnDeactivate)
			form->OnDeactivate(form);
	}

	void CNotifier::FormDeactivate(IControl *sender)
	{
		sender->QueryService()->NotifyOnFormDeactivate();
		if (sender->OnFormDeactivate)
			sender->OnFormDeactivate(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			FormDeactivate(sender->getControl(i));
	}

	void CNotifier::ControlSetFocus(IForm *form, IControl *control, IControl *old_focused_control, const FocusedBy focused_by)
	{
		MessageFocus m{ old_focused_control, focused_by };
		form->QueryService()->NotifyOnControlSetFocus(control, m);
		if (form->OnControlSetFocus)
			form->OnControlSetFocus(form, control, m);
		control->QueryService()->NotifyOnSetFocus(m);
		if (control->OnSetFocus)
			control->OnSetFocus(control, m);
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnControlSetFocus(control, m);
			if (form->getComponent(i)->OnControlSetFocus)
				form->getComponent(i)->OnControlSetFocus(form->getComponent(i), control, m);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			ControlSetFocus(control, form->getControl(i), m);
	}

	void CNotifier::ControlSetFocus(IControl *focused, IControl *sender, const MessageFocus &m)
	{
		if (sender != focused)
		{
			sender->QueryService()->NotifyOnControlSetFocus(focused, m);
			if (sender->OnControlSetFocus)
				sender->OnControlSetFocus(sender, focused, m);
		}
		for (int i = 0; i < sender->getControlCount(); i++)
			ControlSetFocus(focused, sender->getControl(i), m);
	}

	void CNotifier::FormSetFocus(IForm *form)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnFormSetFocus();
			if (form->getComponent(i)->OnFormSetFocus)
				form->getComponent(i)->OnFormSetFocus(form->getComponent(i));
		}
		for (int i = 0; i < form->getControlCount(); i++)
			FormSetFocus(form->getControl(i));
		form->QueryService()->NotifyOnSetFocus();
		if (form->OnSetFocus)
			form->OnSetFocus(form);
	}

	void CNotifier::FormSetFocus(IControl *sender)
	{
		sender->QueryService()->NotifyOnFormSetFocus();
		if (sender->OnFormSetFocus)
			sender->OnFormSetFocus(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			FormSetFocus(sender->getControl(i));
	}

	void CNotifier::ControlKillFocus(IForm *form, IControl *control)
	{
		form->QueryService()->NotifyOnControlKillFocus(control);
		if (form->OnControlKillFocus)
			form->OnControlKillFocus(form, control);
		control->QueryService()->NotifyOnKillFocus();
		if (control->OnKillFocus)
			control->OnKillFocus(control);
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnControlKillFocus(control);
			if (form->getComponent(i)->OnControlKillFocus)
				form->getComponent(i)->OnControlKillFocus(form->getComponent(i), control);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			ControlKillFocus(control, form->getControl(i));
	}

	void CNotifier::ControlKillFocus(IControl *focused, IControl *sender)
	{
		if (sender != focused)
		{
			sender->QueryService()->NotifyOnControlKillFocus(focused);
			if (sender->OnControlKillFocus)
				sender->OnControlKillFocus(sender, focused);
		}
		for (int i = 0; i < sender->getControlCount(); i++)
			ControlKillFocus(focused, sender->getControl(i));
	}

	void CNotifier::FormKillFocus(IForm *form)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnFormKillFocus();
			if (form->getComponent(i)->OnFormKillFocus)
				form->getComponent(i)->OnFormKillFocus(form->getComponent(i));
		}
		for (int i = 0; i < form->getControlCount(); i++)
			FormKillFocus(form->getControl(i));
		form->QueryService()->NotifyOnKillFocus();
		if (form->OnKillFocus)
			form->OnKillFocus(form);
	}

	void CNotifier::FormKillFocus(IControl *sender)
	{
		sender->QueryService()->NotifyOnFormKillFocus();
		if (sender->OnFormKillFocus)
			sender->OnFormKillFocus(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			FormKillFocus(sender->getControl(i));
	}

	void CNotifier::FormEnable(IForm *form)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnFormEnable();
			if (form->getComponent(i)->OnFormEnable)
				form->getComponent(i)->OnFormEnable(form->getComponent(i));
		}
		for (int i = 0; i < form->getControlCount(); i++)
			FormEnable(form->getControl(i));
		form->QueryService()->NotifyOnEnable();
		if (form->OnEnable)
			form->OnEnable(form);
	}

	void CNotifier::FormEnable(IControl *sender)
	{
		sender->QueryService()->NotifyOnFormEnable();
		if (sender->OnFormEnable)
			sender->OnFormEnable(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			FormEnable(sender->getControl(i));
	}

	void CNotifier::FormDisable(IForm *form)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnFormDisable();
			if (form->getComponent(i)->OnFormDisable)
				form->getComponent(i)->OnFormDisable(form->getComponent(i));
		}
		for (int i = 0; i < form->getControlCount(); i++)
			FormDisable(form->getControl(i));
		form->QueryService()->NotifyOnDisable();
		if (form->OnDisable)
			form->OnDisable(form);
	}

	void CNotifier::FormDisable(IControl *sender)
	{
		sender->QueryService()->NotifyOnFormDisable();
		if (sender->OnFormDisable)
			sender->OnFormDisable(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			FormDisable(sender->getControl(i));
	}

	void CNotifier::FormShow(IForm *form)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnFormShow();
			if (form->getComponent(i)->OnFormShow)
				form->getComponent(i)->OnFormShow(form->getComponent(i));
		}
		for (int i = 0; i < form->getControlCount(); i++)
			FormShow(form->getControl(i));
		form->QueryService()->NotifyOnShow();
		if (form->OnShow)
			form->OnShow(form);
	}

	void CNotifier::FormShow(IControl *sender)
	{
		sender->QueryService()->NotifyOnFormShow();
		if (sender->OnFormShow)
			sender->OnFormShow(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			FormShow(sender->getControl(i));
	}

	void CNotifier::FormHide(IForm *form)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnFormHide();
			if (form->getComponent(i)->OnFormHide)
				form->getComponent(i)->OnFormHide(form->getComponent(i));
		}
		for (int i = 0; i < form->getControlCount(); i++)
			FormHide(form->getControl(i));
		form->QueryService()->NotifyOnHide();
		if (form->OnHide)
			form->OnHide(form);
	}

	void CNotifier::FormHide(IControl *sender)
	{
		sender->QueryService()->NotifyOnFormHide();
		if (sender->OnFormHide)
			sender->OnFormHide(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			FormHide(sender->getControl(i));
	}

	void CNotifier::ApplicationActivate(IForm *form)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnApplicationActivate();
			if (form->getComponent(i)->OnApplicationActivate)
				form->getComponent(i)->OnApplicationActivate(form->getComponent(i));
		}
		for (int i = 0; i < form->getControlCount(); i++)
			ApplicationActivate(form->getControl(i));
		form->QueryService()->NotifyOnApplicationActivate();
		if (form->OnApplicationActivate)
			form->OnApplicationActivate(form);
	}

	void CNotifier::ApplicationActivate(IControl *sender)
	{
		sender->QueryService()->NotifyOnApplicationActivate();
		if (sender->OnApplicationActivate)
			sender->OnApplicationActivate(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			ApplicationActivate(sender->getControl(i));
	}

	void CNotifier::ApplicationDeactivate(IForm *form)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnApplicationDeactivate();
			if (form->getComponent(i)->OnApplicationDeactivate)
				form->getComponent(i)->OnApplicationDeactivate(form->getComponent(i));
		}
		for (int i = 0; i < form->getControlCount(); i++)
			ApplicationDeactivate(form->getControl(i));
		form->QueryService()->NotifyOnApplicationDeactivate();
		if (form->OnApplicationDeactivate)
			form->OnApplicationDeactivate(form);
	}

	void CNotifier::ApplicationDeactivate(IControl *sender)
	{
		sender->QueryService()->NotifyOnApplicationDeactivate();
		if (sender->OnApplicationDeactivate)
			sender->OnApplicationDeactivate(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			ApplicationDeactivate(sender->getControl(i));
	}

	void CNotifier::FormMove(IForm *form, const MessagePosition &m)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnFormMove(m);
			if (form->getComponent(i)->OnFormMove)
				form->getComponent(i)->OnFormMove(form->getComponent(i), m);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			FormMove(form->getControl(i), m);
		form->QueryService()->NotifyOnMove(m);
		if (form->OnMove)
			form->OnMove(form, m);
	}

	void CNotifier::FormMove(IControl *sender, const MessagePosition &m)
	{
		sender->QueryService()->NotifyOnFormMove(m);
		if (sender->OnFormMove)
			sender->OnFormMove(sender, m);
		for (int i = 0; i < sender->getControlCount(); i++)
			FormMove(sender->getControl(i), m);
	}

	void CNotifier::ParentResize(IForm *form)
	{
		form->QueryService()->NotifyOnResize();
		if (form->OnResize)
			form->OnResize(form);
		for (int i = 0; i < form->getControlCount(); i++)
		{
			form->getControl(i)->QueryService()->NotifyOnParentResize();
			if (form->getControl(i)->OnParentResize)
				form->getControl(i)->OnParentResize(form->getControl(i));
		}
	}

	void CNotifier::FormRestore(IForm *form, const MessageSize &m)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnFormRestore(m);
			if (form->getComponent(i)->OnFormRestore)
				form->getComponent(i)->OnFormRestore(form->getComponent(i), m);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			FormRestore(form->getControl(i), m);
		form->QueryService()->NotifyOnRestore(m);
		if (form->OnRestore)
			form->OnRestore(form, m);
	}

	void CNotifier::FormRestore(IControl *sender, const MessageSize &m)
	{
		sender->QueryService()->NotifyOnFormRestore(m);
		if (sender->OnFormRestore)
			sender->OnFormRestore(sender, m);
		for (int i = 0; i < sender->getControlCount(); i++)
			FormRestore(sender->getControl(i), m);
	}

	void CNotifier::FormMinimize(IForm *form, const MessageSize &m)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnFormMinimize(m);
			if (form->getComponent(i)->OnFormMinimize)
				form->getComponent(i)->OnFormMinimize(form->getComponent(i), m);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			FormMinimize(form->getControl(i), m);
		form->QueryService()->NotifyOnMinimize(m);
		if (form->OnMinimize)
			form->OnMinimize(form, m);
	}

	void CNotifier::FormMinimize(IControl *sender, const MessageSize &m)
	{
		sender->QueryService()->NotifyOnFormMinimize(m);
		if (sender->OnFormMinimize)
			sender->OnFormMinimize(sender, m);
		for (int i = 0; i < sender->getControlCount(); i++)
			FormMinimize(sender->getControl(i), m);
	}

	void CNotifier::FormMaximize(IForm *form, const MessageSize &m)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnFormMaximize(m);
			if (form->getComponent(i)->OnFormMaximize)
				form->getComponent(i)->OnFormMaximize(form->getComponent(i), m);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			FormMaximize(form->getControl(i), m);
		form->QueryService()->NotifyOnMaximize(m);
		if (form->OnMaximize)
			form->OnMaximize(form, m);
	}

	void CNotifier::FormMaximize(IControl *sender, const MessageSize &m)
	{
		sender->QueryService()->NotifyOnFormMaximize(m);
		if (sender->OnFormMaximize)
			sender->OnFormMaximize(sender, m);
		for (int i = 0; i < sender->getControlCount(); i++)
			FormMaximize(sender->getControl(i), m);
	}

	void CNotifier::FormEnterSizeMove(IForm *form)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnFormEnterSizeMove();
			if (form->getComponent(i)->OnFormEnterSizeMove)
				form->getComponent(i)->OnFormEnterSizeMove(form->getComponent(i));
		}
		for (int i = 0; i < form->getControlCount(); i++)
			FormEnterSizeMove(form->getControl(i));
		form->QueryService()->NotifyOnEnterSizeMove();
		if (form->OnEnterSizeMove)
			form->OnEnterSizeMove(form);
	}

	void CNotifier::FormEnterSizeMove(IControl *sender)
	{
		sender->QueryService()->NotifyOnFormEnterSizeMove();
		if (sender->OnFormEnterSizeMove)
			sender->OnFormEnterSizeMove(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			FormEnterSizeMove(sender->getControl(i));
	}

	void CNotifier::FormExitSizeMove(IForm *form)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnFormExitSizeMove();
			if (form->getComponent(i)->OnFormExitSizeMove)
				form->getComponent(i)->OnFormExitSizeMove(form->getComponent(i));
		}
		for (int i = 0; i < form->getControlCount(); i++)
			FormExitSizeMove(form->getControl(i));
		form->QueryService()->NotifyOnExitSizeMove();
		if (form->OnExitSizeMove)
			form->OnExitSizeMove(form);
	}

	void CNotifier::FormExitSizeMove(IControl *sender)
	{
		sender->QueryService()->NotifyOnFormExitSizeMove();
		if (sender->OnFormExitSizeMove)
			sender->OnFormExitSizeMove(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			FormExitSizeMove(sender->getControl(i));
	}

	void CNotifier::TimeChange(IForm *form)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnTimeChange();
			if (form->getComponent(i)->OnTimeChange)
				form->getComponent(i)->OnTimeChange(form->getComponent(i));
		}
		for (int i = 0; i < form->getControlCount(); i++)
			TimeChange(form->getControl(i));
		form->QueryService()->NotifyOnTimeChange();
		if (form->OnTimeChange)
			form->OnTimeChange(form);
	}

	void CNotifier::TimeChange(IControl *sender)
	{
		sender->QueryService()->NotifyOnTimeChange();
		if (sender->OnTimeChange)
			sender->OnTimeChange(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			TimeChange(sender->getControl(i));
	}

	void CNotifier::InputLanguageChange(IForm *form)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnInputLanguageChange();
			if (form->getComponent(i)->OnInputLanguageChange)
				form->getComponent(i)->OnInputLanguageChange(form->getComponent(i));
		}
		for (int i = 0; i < form->getControlCount(); i++)
			InputLanguageChange(form->getControl(i));
		form->QueryService()->NotifyOnInputLanguageChange();
		if (form->OnInputLanguageChange)
			form->OnInputLanguageChange(form);
	}

	void CNotifier::InputLanguageChange(IControl *sender)
	{
		sender->QueryService()->NotifyOnInputLanguageChange();
		if (sender->OnInputLanguageChange)
			sender->OnInputLanguageChange(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			InputLanguageChange(sender->getControl(i));
	}

	void CNotifier::DisplayChange(IForm *form, const MessageSize &m)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnDisplayChange(m);
			if (form->getComponent(i)->OnDisplayChange)
				form->getComponent(i)->OnDisplayChange(form->getComponent(i), m);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			DisplayChange(form->getControl(i), m);
		form->QueryService()->NotifyOnDisplayChange(m);
		if (form->OnDisplayChange)
			form->OnDisplayChange(form, m);
	}

	void CNotifier::DisplayChange(IControl *sender, const MessageSize &m)
	{
		sender->QueryService()->NotifyOnDisplayChange(m);
		if (sender->OnDisplayChange)
			sender->OnDisplayChange(sender, m);
		for (int i = 0; i < sender->getControlCount(); i++)
			DisplayChange(sender->getControl(i), m);
	}

	void CNotifier::ThemeChange(IForm *form)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnThemeChange();
			if (form->getComponent(i)->OnThemeChange)
				form->getComponent(i)->OnThemeChange(form->getComponent(i));
		}
		for (int i = 0; i < form->getControlCount(); i++)
			ThemeChange(form->getControl(i));
		form->QueryService()->NotifyOnThemeChange();
		if (form->OnThemeChange)
			form->OnThemeChange(form);
	}

	void CNotifier::ThemeChange(IControl *sender)
	{
		sender->QueryService()->NotifyOnThemeChange();
		if (sender->OnThemeChange)
			sender->OnThemeChange(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			ThemeChange(sender->getControl(i));
	}

	void CNotifier::ClipboardUpdate(IForm *form)
	{
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnClipboardUpdate();
			if (form->getComponent(i)->OnClipboardUpdate)
				form->getComponent(i)->OnClipboardUpdate(form->getComponent(i));
		}
		for (int i = 0; i < form->getControlCount(); i++)
			ClipboardUpdate(form->getControl(i));
		form->QueryService()->NotifyOnClipboardUpdate();
		if (form->OnClipboardUpdate)
			form->OnClipboardUpdate(form);
	}

	void CNotifier::ClipboardUpdate(IControl *sender)
	{
		sender->QueryService()->NotifyOnClipboardUpdate();
		if (sender->OnClipboardUpdate)
			sender->OnClipboardUpdate(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			ClipboardUpdate(sender->getControl(i));
	}

	void CNotifier::StyleChange(IForm *form)
	{
		form->QueryService()->NotifyOnStyleChange();
		if (form->OnStyleChange)
			form->OnStyleChange(form);
		for (int i = 0; i < form->getControlCount(); i++)
			if (form->getControl(i)->isUseParentStyle())
				ParentStyleChange(form->getControl(i));
	}

	void CNotifier::ParentStyleChange(IControl *sender)
	{
		sender->QueryService()->NotifyOnParentStyleChange();
		if (sender->OnParentStyleChange)
			sender->OnParentStyleChange(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			if (sender->getControl(i)->isUseParentStyle())
				ParentStyleChange(sender->getControl(i));
	}

	void CNotifier::FontChange(IForm *form)
	{
		form->QueryService()->NotifyOnFontChange();
		if (form->OnFontChange)
			form->OnFontChange(form);
		for (int i = 0; i < form->getControlCount(); i++)
			if (form->getControl(i)->isUseParentFont())
				ParentFontChange(form->getControl(i));
	}

	void CNotifier::ParentFontChange(IControl *sender)
	{
		sender->QueryService()->NotifyOnParentFontChange();
		if (sender->OnParentFontChange)
			sender->OnParentFontChange(sender);
		for (int i = 0; i < sender->getControlCount(); i++)
			if (sender->getControl(i)->isUseParentFont())
				ParentFontChange(sender->getControl(i));
	}

	void CNotifier::ControlKillModal(IForm *form, IControl *control)
	{
		form->QueryService()->NotifyOnControlKillModal(control);
		if (form->OnControlKillModal)
			form->OnControlKillModal(form, control);
		control->QueryService()->NotifyOnKillModal();
		if (control->OnKillModal)
			control->OnKillModal(control);
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnControlKillModal(control);
			if (form->getComponent(i)->OnControlKillModal)
				form->getComponent(i)->OnControlKillModal(form->getComponent(i), control);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			ControlKillModal(form->getControl(i), control);
	}

	void CNotifier::ControlKillModal(IControl *sender, IControl *modal)
	{
		if (sender != modal)
		{
			sender->QueryService()->NotifyOnControlKillModal(modal);
			if (sender->OnControlKillModal)
				sender->OnControlKillModal(sender, modal);
		}
		for (int i = 0; i < sender->getControlCount(); i++)
			ControlKillModal(sender->getControl(i), modal);
	}

	void CNotifier::ControlSetModal(IForm *form, IControl *control)
	{
		form->QueryService()->NotifyOnControlSetModal(control);
		if (form->OnControlSetModal)
			form->OnControlSetModal(form, control);
		control->QueryService()->NotifyOnSetModal();
		if (control->OnSetModal)
			control->OnSetModal(control);
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnControlSetModal(control);
			if (form->getComponent(i)->OnControlSetModal)
				form->getComponent(i)->OnControlSetModal(form->getComponent(i), control);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			ControlSetModal(form->getControl(i), control);
	}

	void CNotifier::ControlSetModal(IControl *sender, IControl *modal)
	{
		if (sender != modal)
		{
			sender->QueryService()->NotifyOnControlSetModal(modal);
			if (sender->OnControlSetModal)
				sender->OnControlSetModal(sender, modal);
		}
		for (int i = 0; i < sender->getControlCount(); i++)
			ControlSetModal(sender->getControl(i), modal);
	}

	void CNotifier::ControlKillCaptureKeyboard(IForm *form, IControl *control)
	{
		form->QueryService()->NotifyOnControlKillCaptureKeyboard(control);
		if (form->OnControlKillCaptureKeyboard)
			form->OnControlKillCaptureKeyboard(form, control);
		control->QueryService()->NotifyOnKillCaptureKeyboard();
		if (control->OnKillCaptureKeyboard)
			control->OnKillCaptureKeyboard(control);
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnControlKillCaptureKeyboard(control);
			if (form->getComponent(i)->OnControlKillCaptureKeyboard)
				form->getComponent(i)->OnControlKillCaptureKeyboard(form->getComponent(i), control);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			ControlKillCaptureKeyboard(form->getControl(i), control);
	}

	void CNotifier::ControlKillCaptureKeyboard(IControl *sender, IControl *capture)
	{
		if (sender != capture)
		{
			sender->QueryService()->NotifyOnControlKillCaptureKeyboard(capture);
			if (sender->OnControlKillCaptureKeyboard)
				sender->OnControlKillCaptureKeyboard(sender, capture);
		}
		for (int i = 0; i < sender->getControlCount(); i++)
			ControlKillCaptureKeyboard(sender->getControl(i), capture);
	}

	void CNotifier::ControlSetCaptureKeyboard(IForm *form, IControl *control)
	{
		form->QueryService()->NotifyOnControlSetCaptureKeyboard(control);
		if (form->OnControlSetCaptureKeyboard)
			form->OnControlSetCaptureKeyboard(form, control);
		control->QueryService()->NotifyOnSetCaptureKeyboard();
		if (control->OnSetCaptureKeyboard)
			control->OnSetCaptureKeyboard(control);
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnControlSetCaptureKeyboard(control);
			if (form->getComponent(i)->OnControlSetCaptureKeyboard)
				form->getComponent(i)->OnControlSetCaptureKeyboard(form->getComponent(i), control);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			ControlSetCaptureKeyboard(form->getControl(i), control);
	}

	void CNotifier::ControlSetCaptureKeyboard(IControl *sender, IControl *capture)
	{
		if (sender != capture)
		{
			sender->QueryService()->NotifyOnControlSetCaptureKeyboard(capture);
			if (sender->OnControlSetCaptureKeyboard)
				sender->OnControlSetCaptureKeyboard(sender, capture);
		}
		for (int i = 0; i < sender->getControlCount(); i++)
			ControlSetCaptureKeyboard(sender->getControl(i), capture);
	}

	void CNotifier::ControlKillCaptureMouse(IForm *form, IControl *control)
	{
		form->QueryService()->NotifyOnControlKillCaptureMouse(control);
		if (form->OnControlKillCaptureMouse)
			form->OnControlKillCaptureMouse(form, control);
		control->QueryService()->NotifyOnKillCaptureMouse();
		if (control->OnKillCaptureMouse)
			control->OnKillCaptureMouse(control);
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnControlKillCaptureMouse(control);
			if (form->getComponent(i)->OnControlKillCaptureMouse)
				form->getComponent(i)->OnControlKillCaptureMouse(form->getComponent(i), control);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			ControlKillCaptureMouse(form->getControl(i), control);
	}

	void CNotifier::ControlKillCaptureMouse(IControl *sender, IControl *capture)
	{
		if (sender != capture)
		{
			sender->QueryService()->NotifyOnControlKillCaptureMouse(capture);
			if (sender->OnControlKillCaptureMouse)
				sender->OnControlKillCaptureMouse(sender, capture);
		}
		for (int i = 0; i < sender->getControlCount(); i++)
			ControlKillCaptureMouse(sender->getControl(i), capture);
	}

	void CNotifier::ControlSetCaptureMouse(IForm *form, IControl *control)
	{
		form->QueryService()->NotifyOnControlSetCaptureMouse(control);
		if (form->OnControlSetCaptureMouse)
			form->OnControlSetCaptureMouse(form, control);
		form->getCaptureMouseControl()->QueryService()->NotifyOnSetCaptureMouse();
		if (control->OnSetCaptureMouse)
			control->OnSetCaptureMouse(control);
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnControlSetCaptureMouse(control);
			if (form->getComponent(i)->OnControlSetCaptureMouse)
				form->getComponent(i)->OnControlSetCaptureMouse(form->getComponent(i), control);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			ControlSetCaptureMouse(form->getControl(i), control);
	}

	void CNotifier::ControlSetCaptureMouse(IControl *sender, IControl *capture)
	{
		if (sender != capture)
		{
			sender->QueryService()->NotifyOnControlSetCaptureMouse(capture);
			if (sender->OnControlSetCaptureMouse)
				sender->OnControlSetCaptureMouse(sender, capture);
		}
		for (int i = 0; i < sender->getControlCount(); i++)
			ControlSetCaptureMouse(sender->getControl(i), capture);
	}

	void CNotifier::TransformControls(IForm *form)
	{
		form->QueryService()->NotifyOnTransformControls();
		if (form->OnTransformControls)
			form->OnTransformControls(form);
		for (int i = 0; i < form->getControlCount(); i++)
		{
			form->getControl(i)->QueryService()->NotifyOnParentTransformControls();
			if (form->getControl(i)->OnParentTransformControls)
				form->getControl(i)->OnParentTransformControls(form->getControl(i));
		}
	}

	void CNotifier::ComponentAttach(IForm *form, IComponent *component)
	{
		form->QueryService()->NotifyOnComponentAttach(component);
		if (form->OnComponentAttach)
			form->OnComponentAttach(form, component);
		component->QueryService()->NotifyOnAttach();
		if (component->OnAttach)
			component->OnAttach(component);
		for (int i = 0; i < form->getComponentCount(); i++)
			if (form->getComponent(i) != component)
			{
				form->getComponent(i)->QueryService()->NotifyOnComponentAttach(component);
				if (form->getComponent(i)->OnComponentAttach)
					form->getComponent(i)->OnComponentAttach(form->getComponent(i), component);
			}
		for (int i = 0; i < form->getControlCount(); i++)
			ComponentAttach(form->getControl(i), component);
	}

	void CNotifier::ComponentAttach(IControl *sender, IComponent *component)
	{
		sender->QueryService()->NotifyOnComponentAttach(component);
		if (sender->OnComponentAttach)
			sender->OnComponentAttach(sender, component);
		for (int i = 0; i < sender->getControlCount(); i++)
			ComponentAttach(sender->getControl(i), component);
	}

	void CNotifier::ComponentDetach(IForm *form, IComponent *component)
	{
		form->QueryService()->NotifyOnComponentDetach(component);
		if (form->OnComponentDetach)
			form->OnComponentDetach(form, component);
		component->QueryService()->NotifyOnDetach();
		if (component->OnDetach)
			component->OnDetach(component);
		for (int i = 0; i < form->getComponentCount(); i++)
			if (form->getComponent(i) != component)
			{
				form->getComponent(i)->QueryService()->NotifyOnComponentDetach(component);
				if (form->getComponent(i)->OnComponentDetach)
					form->getComponent(i)->OnComponentDetach(form->getComponent(i), component);
			}
		for (int i = 0; i < form->getControlCount(); i++)
			ComponentDetach(form->getControl(i), component);
	}

	void CNotifier::ComponentDetach(IControl *sender, IComponent *component)
	{
		sender->QueryService()->NotifyOnComponentDetach(component);
		if (sender->OnComponentDetach)
			sender->OnComponentDetach(sender, component);
		for (int i = 0; i < sender->getControlCount(); i++)
			ComponentDetach(sender->getControl(i), component);
	}

	void CNotifier::ControlAttach(IForm *form, IControl *control)
	{
		form->QueryService()->NotifyOnControlAttach(control);
		if (form->OnControlAttach)
			form->OnControlAttach(form, control);
		Attach(control);
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnControlAttach(control);
			if (form->getComponent(i)->OnControlAttach)
				form->getComponent(i)->OnControlAttach(form->getComponent(i), control);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			ControlAttach_r(form->getControl(i), control);
	}

	void CNotifier::ControlAttach(IControl *parent, IControl *control)
	{
		parent->QueryService()->NotifyOnChildAttach(control);
		if (parent->OnChildAttach)
			parent->OnChildAttach(parent, control);
		Attach(control);
		if (parent->getForm())
			ControlAttach(parent->getForm(), control);
		else
		{
			IControl *p{ parent };
			while (p->getParent())
				p = p->getParent();
			for (int i = 0; i < p->getControlCount(); i++)
				ControlAttach_r(p->getControl(i), control);
		}
	}

	void CNotifier::ControlAttach_r(IControl *sender, IControl *control)
	{
		if (sender != control)
		{
			sender->QueryService()->NotifyOnControlAttach(control);
			if (sender->OnControlAttach)
				sender->OnControlAttach(sender, control);
		}
		for (int i = 0; i < sender->getControlCount(); i++)
			ControlAttach_r(sender->getControl(i), control);
	}

	void CNotifier::Attach(IControl *control)
	{
		control->QueryService()->NotifyOnAttach();
		if (control->OnAttach)
			control->OnAttach(control);
		for (int i = 0; i < control->getControlCount(); i++)
			Attach(control->getControl(i));
	}

	void CNotifier::ControlDetach(IForm *form, IControl *control)
	{
		form->QueryService()->NotifyOnControlDetach(control);
		if (form->OnControlDetach)
			form->OnControlDetach(form, control);
		Detach(control);
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnControlDetach(control);
			if (form->getComponent(i)->OnControlDetach)
				form->getComponent(i)->OnControlDetach(form->getComponent(i), control);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			ControlDetach_r(form->getControl(i), control);
	}

	void CNotifier::ControlDetach(IControl *parent, IControl *control)
	{
		parent->QueryService()->NotifyOnChildDetach(control);
		if (parent->OnChildDetach)
			parent->OnChildDetach(parent, control);
		Detach(control);
		if (parent->getForm())
			ControlDetach(parent->getForm(), control);
		else
		{
			IControl *p{ parent };
			while (p->getParent())
				p = p->getParent();
			for (int i = 0; i < p->getControlCount(); i++)
				ControlDetach_r(p->getControl(i), control);
		}
	}

	void CNotifier::ControlDetach_r(IControl *sender, IControl *control)
	{
		if (sender != control)
		{
			sender->QueryService()->NotifyOnControlDetach(control);
			if (sender->OnControlDetach)
				sender->OnControlDetach(sender, control);
		}
		for (int i = 0; i < sender->getControlCount(); i++)
			ControlDetach_r(sender->getControl(i), control);
	}

	void CNotifier::Detach(IControl *control)
	{
		control->QueryService()->NotifyOnDetach();
		if (control->OnDetach)
			control->OnDetach(control);
		for (int i = 0; i < control->getControlCount(); i++)
			Detach(control->getControl(i));
	}

	void CNotifier::Resize(IControl *control)
	{
		control->QueryService()->NotifyOnResize();
		if (control->OnResize)
			control->OnResize(control);
		for (int i = 0; i < control->getControlCount(); i++)
		{
			control->getControl(i)->QueryService()->NotifyOnParentResize();
			if (control->getControl(i)->OnParentResize)
				control->getControl(i)->OnParentResize(control->getControl(i));
		}
	}

	void CNotifier::MouseHoverControl(IForm *form, IControl *control, const PointF &position)
	{
		MessagePosition m{ position };
		form->QueryService()->NotifyOnControlMouseHover(control, m);
		if (form->OnControlMouseHover)
			form->OnControlMouseHover(form, control, m);
		control->QueryService()->NotifyOnMouseHover(m);
		if (control->OnMouseHover)
			control->OnMouseHover(control, m);
	}

	void CNotifier::MouseLeaveControl(IForm *form, IControl *control)
	{
		form->QueryService()->NotifyOnControlMouseLeave(control);
		if (form->OnControlMouseLeave)
			form->OnControlMouseLeave(form, control);
		control->QueryService()->NotifyOnMouseLeave();
		if (control->OnMouseLeave)
			control->OnMouseLeave(control);
	}

	void CNotifier::Render(IControl *control, const MessagePaint &m, IControl *draw_last)
	{
		bool draw_children{ true };
		if (draw_last == control) // If current control is the one to be drawn the last, draw as usually
			draw_last = nullptr;
		control->QueryService()->NotifyOnPaint(m, draw_children);
		if (control->OnPaint)
			control->OnPaint(control, m, draw_children);
		if (draw_children)
		{
			// Find child control to be drawn last
			IControl *draw_last_parent{ draw_last };
			if (draw_last_parent)
			{
				while (draw_last_parent->getParent() != control)
					draw_last_parent = draw_last_parent->getParent();
			}
			// Build ordered control list
			std::vector<IControl*> controls;
			for (int i = 0; i < control->getControlCount(); i++)
				if (control->getControl(i)->isVisible(false) && control->getControl(i) != draw_last_parent)
					controls.push_back(control->getControl(i));
			std::sort(controls.begin(), controls.end(), [](IControl *a, IControl *b) {return a->getZIndex() < b->getZIndex(); });
			// Draw children
			for (auto pos : controls)
				Render(pos, m, nullptr);
			// Draw last
			if (draw_last_parent)
				Render(draw_last_parent, m, draw_last);
		}
		control->QueryService()->NotifyOnPaintEnd(m);
		if (control->OnPaintEnd)
			control->OnPaintEnd(control, m);
	}

	void CNotifier::Detaching(IControl *control)
	{
		if (!control->isUseParentFont() && control->getControlFont())
			control->getControlFont()->NotifyOnFreeResources();
		control->QueryService()->NotifyOnFreeResources();
		control->QueryService()->NotifyOnDetaching();
		if (control->OnDetaching)
			control->OnDetaching(control);
		for (int i = 0; i < control->getControlCount(); i++)
			Detaching(control->getControl(i));
	}

	void CNotifier::Detaching(IComponent *component)
	{
		component->QueryService()->NotifyOnFreeResources();
		component->QueryService()->NotifyOnDetaching();
		if (component->OnDetaching)
			component->OnDetaching(component);
	}

	void CNotifier::TranslateChange(IControl *control)
	{
		control->QueryService()->NotifyOnTranslateChange();
		if (control->OnTranslateChange)
			control->OnTranslateChange(control);
		for (int i = 0; i < control->getControlCount(); i++)
			TranslateChange(control->getControl(i));
	}

	void CNotifier::TranslateChange(IForm *form)
	{
		form->QueryService()->NotifyOnTranslateChange();
		if (form->OnTranslateChange)
			form->OnTranslateChange(form);
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnTranslateChange();
			if (form->getComponent(i)->OnTranslateChange)
				form->getComponent(i)->OnTranslateChange(form->getComponent(i));
		}
		for (int i = 0; i < form->getControlCount(); i++)
			TranslateChange(form->getControl(i));
	}

	void CNotifier::ControlActivate(IForm *form, IControl *control)
	{
		form->QueryService()->NotifyOnControlActivate(control);
		if (form->OnControlActivate)
			form->OnControlActivate(form, control);
		control->QueryService()->NotifyOnActivate();
		if (control->OnActivate)
			control->OnActivate(control);
	}

	void CNotifier::ControlDeactivate(IForm *form, IControl *control)
	{
		form->QueryService()->NotifyOnControlDeactivate(control);
		if (form->OnControlDeactivate)
			form->OnControlDeactivate(form, control);
		control->QueryService()->NotifyOnDeactivate();
		if (control->OnDeactivate)
			control->OnDeactivate(control);
	}

	void CNotifier::ControlActivateDialogBox(IForm *form, IDialogBox *control)
	{
		form->QueryService()->NotifyOnDialogBoxActivate(control);
		if (form->OnDialogBoxActivate)
			form->OnDialogBoxActivate(form, control);
		IDialogBoxService *service{ cast<IDialogBoxService*>(control->QueryService()) };
		if (service)
			service->NotifyOnSetActive();
		if (control->OnSetActive)
			control->OnSetActive(control);
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnDialogBoxActivate(control);
			if (form->getComponent(i)->OnDialogBoxActivate)
				form->getComponent(i)->OnDialogBoxActivate(form->getComponent(i), control);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			ControlActivateDialogBox(form->getControl(i), control);
	}

	void CNotifier::ControlActivateDialogBox(IControl *sender, IDialogBox *control)
	{
		if (sender != control)
		{
			sender->QueryService()->NotifyOnDialogBoxActivate(control);
			if (sender->OnDialogBoxActivate)
				sender->OnDialogBoxActivate(sender, control);
		}
		for (int i = 0; i < sender->getControlCount(); i++)
			ControlActivateDialogBox(sender->getControl(i), control);
	}

	void CNotifier::ControlDeactivateDialogBox(IForm *form, IDialogBox *control)
	{
		form->QueryService()->NotifyOnDialogBoxDeactivate(control);
		if (form->OnDialogBoxDeactivate)
			form->OnDialogBoxDeactivate(form, control);
		IDialogBoxService *service{ cast<IDialogBoxService*>(control->QueryService()) };
		if (service)
			service->NotifyOnKillActive();
		if (control->OnKillActive)
			control->OnKillActive(control);
		for (int i = 0; i < form->getComponentCount(); i++)
		{
			form->getComponent(i)->QueryService()->NotifyOnDialogBoxDeactivate(control);
			if (form->getComponent(i)->OnDialogBoxDeactivate)
				form->getComponent(i)->OnDialogBoxDeactivate(form->getComponent(i), control);
		}
		for (int i = 0; i < form->getControlCount(); i++)
			ControlDeactivateDialogBox(form->getControl(i), control);
	}

	void CNotifier::ControlDeactivateDialogBox(IControl *sender, IDialogBox *control)
	{
		if (sender != control)
		{
			sender->QueryService()->NotifyOnDialogBoxDeactivate(control);
			if (sender->OnDialogBoxDeactivate)
				sender->OnDialogBoxDeactivate(sender, control);
		}
		for (int i = 0; i < sender->getControlCount(); i++)
			ControlDeactivateDialogBox(sender->getControl(i), control);
	}

	void CNotifier::ControlHide(IControl *control)
	{
		IControl *parent;
		IForm *form;
		control->QueryService()->NotifyOnHide();
		if (control->OnHide)
			control->OnHide(control);
		if ((parent = control->getParent()))
		{
			parent->QueryService()->NotifyOnChildHide(control);
			if (parent->OnChildHide)
				parent->OnChildHide(parent, control);
		}
		else if ((form = control->getForm()))
		{
			form->QueryService()->NotifyOnChildHide(control);
			if (form->OnChildHide)
				form->OnChildHide(form, control);
		}
	}

	void CNotifier::ControlShow(IControl *control)
	{
		IControl *parent;
		IForm *form;
		control->QueryService()->NotifyOnShow();
		if (control->OnShow)
			control->OnShow(control);
		if ((parent = control->getParent()))
		{
			parent->QueryService()->NotifyOnChildShow(control);
			if (parent->OnChildShow)
				parent->OnChildShow(parent, control);
		}
		else if ((form = control->getForm()))
		{
			form->QueryService()->NotifyOnChildShow(control);
			if (form->OnChildShow)
				form->OnChildShow(form, control);
		}
	}

	void CNotifier::ControlDisable(IControl *control)
	{
		IControl *parent;
		IForm *form;
		control->QueryService()->NotifyOnDisable();
		if (control->OnDisable)
			control->OnDisable(control);
		if ((parent = control->getParent()))
		{
			parent->QueryService()->NotifyOnChildDisable(control);
			if (parent->OnChildDisable)
				parent->OnChildDisable(parent, control);
		}
		else if ((form = control->getForm()))
		{
			form->QueryService()->NotifyOnChildDisable(control);
			if (form->OnChildDisable)
				form->OnChildDisable(form, control);
		}
	}

	void CNotifier::ControlEnable(IControl *control)
	{
		IControl *parent;
		IForm *form;
		control->QueryService()->NotifyOnEnable();
		if (control->OnEnable)
			control->OnEnable(control);
		if ((parent = control->getParent()))
		{
			parent->QueryService()->NotifyOnChildEnable(control);
			if (parent->OnChildEnable)
				parent->OnChildEnable(parent, control);
		}
		else if ((form = control->getForm()))
		{
			form->QueryService()->NotifyOnChildEnable(control);
			if (form->OnChildEnable)
				form->OnChildEnable(form, control);
		}
	}
}