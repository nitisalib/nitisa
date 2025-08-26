// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	CComponentService::CComponentService(CComponent *component) :m_pComponent{ component }
	{

	}

	void CComponentService::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Setters
	void CComponentService::setName(const String &value)
	{
		m_pComponent->m_sName = value;
	}

	void CComponentService::setForm(IForm *value)
	{
		m_pComponent->m_pForm = value;
	}
#pragma endregion

#pragma region Helpers
	void CComponentService::SendChangeNotification()
	{
		if (m_pComponent->m_pForm)
		{
			for (int i = 0; i < m_pComponent->m_pForm->getComponentCount(); i++)
				if (m_pComponent->m_pForm->getComponent(i) != m_pComponent)
				{
					m_pComponent->m_pForm->getComponent(i)->QueryService()->NotifyOnComponentChange(m_pComponent);
					if (m_pComponent->m_pForm->getComponent(i)->OnComponentChange)
						m_pComponent->m_pForm->getComponent(i)->OnComponentChange(m_pComponent->m_pForm->getComponent(i), m_pComponent);
				}
			for (int i = 0; i < m_pComponent->m_pForm->getControlCount(); i++)
				SendChangeNotification(m_pComponent->m_pForm->getControl(i));
		}
	}

	void CComponentService::SendChangeNotification(IControl *control)
	{
		control->QueryService()->NotifyOnComponentChange(m_pComponent);
		if (control->OnComponentChange)
			control->OnComponentChange(control, m_pComponent);
		for (int i = 0; i < control->getControlCount(); i++)
			SendChangeNotification(control->getControl(i));
	}
#pragma endregion

#pragma region State change notifications
	void CComponentService::NotifyOnAttach()
	{

	}

	void CComponentService::NotifyOnDetaching()
	{

	}

	void CComponentService::NotifyOnDetach()
	{

	}

	void CComponentService::NotifyOnFreeResources()
	{

	}
#pragma endregion

#pragma region Component notifications
	void CComponentService::NotifyOnComponentAttach(IComponent *component)
	{

	}

	void CComponentService::NotifyOnComponentDetach(IComponent *component)
	{

	}

	void CComponentService::NotifyOnComponentChange(IComponent *component)
	{

	}
#pragma endregion

#pragma region Control notifications
	void CComponentService::NotifyOnControlAttach(IControl *control)
	{

	}

	void CComponentService::NotifyOnControlDetach(IControl *control)
	{

	}

	void CComponentService::NotifyOnControlChange(IControl *control)
	{

	}

	void CComponentService::NotifyOnControlSetFocus(IControl *control, const MessageFocus &m)
	{

	}

	void CComponentService::NotifyOnControlKillFocus(IControl *control)
	{

	}

	void CComponentService::NotifyOnControlSetCaptureKeyboard(IControl *control)
	{

	}

	void CComponentService::NotifyOnControlKillCaptureKeyboard(IControl *control)
	{

	}

	void CComponentService::NotifyOnControlSetCaptureMouse(IControl *control)
	{

	}

	void CComponentService::NotifyOnControlKillCaptureMouse(IControl *control)
	{

	}

	void CComponentService::NotifyOnControlSetModal(IControl *control)
	{

	}

	void CComponentService::NotifyOnControlKillModal(IControl *control)
	{

	}
#pragma endregion

#pragma region Other input notifications
	void CComponentService::NotifyOnHotkey(const MessageHotkey &m)
	{

	}
#pragma endregion

#pragma region Application notifications
	void CComponentService::NotifyOnApplicationActivate()
	{

	}

	void CComponentService::NotifyOnApplicationDeactivate()
	{

	}

	void CComponentService::NotifyOnTimeChange()
	{

	}

	void CComponentService::NotifyOnInputLanguageChange()
	{

	}

	void CComponentService::NotifyOnDisplayChange(const MessageSize &m)
	{

	}

	void CComponentService::NotifyOnThemeChange()
	{

	}

	void CComponentService::NotifyOnClipboardUpdate()
	{

	}

	void CComponentService::NotifyOnTranslateChange()
	{

	}
#pragma endregion

#pragma region Form/window notifications
	void CComponentService::NotifyOnFormActivate(const MessageWindowActivate &m)
	{

	}

	void CComponentService::NotifyOnFormDeactivate()
	{

	}

	void CComponentService::NotifyOnFormSetFocus()
	{

	}

	void CComponentService::NotifyOnFormKillFocus()
	{

	}

	void CComponentService::NotifyOnFormEnable()
	{

	}

	void CComponentService::NotifyOnFormDisable()
	{

	}

	void CComponentService::NotifyOnFormShow()
	{

	}

	void CComponentService::NotifyOnFormHide()
	{

	}

	void CComponentService::NotifyOnFormMove(const MessagePosition &m)
	{

	}

	void CComponentService::NotifyOnFormRestore(const MessageSize &m)
	{

	}

	void CComponentService::NotifyOnFormMinimize(const MessageSize &m)
	{

	}

	void CComponentService::NotifyOnFormMaximize(const MessageSize &m)
	{

	}

	void CComponentService::NotifyOnFormEnterSizeMove()
	{

	}

	void CComponentService::NotifyOnFormExitSizeMove()
	{

	}
#pragma endregion

#pragma region Dialog box notifications
	void CComponentService::NotifyOnDialogBoxActivate(IDialogBox *control)
	{

	}

	void CComponentService::NotifyOnDialogBoxDeactivate(IDialogBox *control)
	{

	}
#pragma endregion
}