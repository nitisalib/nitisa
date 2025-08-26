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
	CComponentSpliceService::CComponentSpliceService(IComponent *component) :
		m_pComponent{ component }
	{
		m_pService = m_pComponent->QueryService();
		m_pComponent->setService(this, false);
	}

	CComponentSpliceService::~CComponentSpliceService()
	{
		if (m_pComponent->QueryService() == this)
			m_pComponent->setService(m_pService, false);
		else
		{
			CComponentSpliceService *s{ cast<CComponentSpliceService*>(m_pComponent->QueryService()) };
			while (s)
			{
				if (s->m_pService == this)
				{
					s->m_pService = m_pService;
					break;
				}
				s = cast<CComponentSpliceService*>(s->m_pService);
			}
		}
	}

	void CComponentSpliceService::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Setters
	void CComponentSpliceService::setName(const String &value)
	{
		m_pService->setName(value);
	}

	void CComponentSpliceService::setForm(IForm *value)
	{
		m_pService->setForm(value);
	}
#pragma endregion

#pragma region Helpers
	void CComponentSpliceService::SendChangeNotification()
	{
		m_pService->SendChangeNotification();
	}
#pragma endregion

#pragma region State change notifications
	void CComponentSpliceService::NotifyOnAttach()
	{
		m_pService->NotifyOnAttach();
	}

	void CComponentSpliceService::NotifyOnDetaching()
	{
		m_pService->NotifyOnDetaching();
	}

	void CComponentSpliceService::NotifyOnDetach()
	{
		m_pService->NotifyOnDetach();
	}

	void CComponentSpliceService::NotifyOnFreeResources()
	{
		m_pService->NotifyOnFreeResources();
	}
#pragma endregion

#pragma region Component notifications
	void CComponentSpliceService::NotifyOnComponentAttach(IComponent *component)
	{
		m_pService->NotifyOnComponentAttach(component);
	}

	void CComponentSpliceService::NotifyOnComponentDetach(IComponent *component)
	{
		m_pService->NotifyOnComponentDetach(component);
	}

	void CComponentSpliceService::NotifyOnComponentChange(IComponent *component)
	{
		m_pService->NotifyOnComponentChange(component);
	}
#pragma endregion

#pragma region Control notifications
	void CComponentSpliceService::NotifyOnControlAttach(IControl *control)
	{
		m_pService->NotifyOnControlAttach(control);
	}

	void CComponentSpliceService::NotifyOnControlDetach(IControl *control)
	{
		m_pService->NotifyOnControlDetach(control);
	}

	void CComponentSpliceService::NotifyOnControlChange(IControl *control)
	{
		m_pService->NotifyOnControlChange(control);
	}

	void CComponentSpliceService::NotifyOnControlSetFocus(IControl *control, const MessageFocus &m)
	{
		m_pService->NotifyOnControlSetFocus(control, m);
	}

	void CComponentSpliceService::NotifyOnControlKillFocus(IControl *control)
	{
		m_pService->NotifyOnControlKillFocus(control);
	}

	void CComponentSpliceService::NotifyOnControlSetCaptureKeyboard(IControl *control)
	{
		m_pService->NotifyOnControlSetCaptureKeyboard(control);
	}

	void CComponentSpliceService::NotifyOnControlKillCaptureKeyboard(IControl *control)
	{
		m_pService->NotifyOnControlKillCaptureKeyboard(control);
	}

	void CComponentSpliceService::NotifyOnControlSetCaptureMouse(IControl *control)
	{
		m_pService->NotifyOnControlSetCaptureMouse(control);
	}

	void CComponentSpliceService::NotifyOnControlKillCaptureMouse(IControl *control)
	{
		m_pService->NotifyOnControlKillCaptureMouse(control);
	}

	void CComponentSpliceService::NotifyOnControlSetModal(IControl *control)
	{
		m_pService->NotifyOnControlSetModal(control);
	}

	void CComponentSpliceService::NotifyOnControlKillModal(IControl *control)
	{
		m_pService->NotifyOnControlKillModal(control);
	}
#pragma endregion

#pragma region Other input notifications
	void CComponentSpliceService::NotifyOnHotkey(const MessageHotkey &m)
	{
		m_pService->NotifyOnHotkey(m);
	}
#pragma endregion

#pragma region Application notifications
	void CComponentSpliceService::NotifyOnApplicationActivate()
	{
		m_pService->NotifyOnApplicationActivate();
	}

	void CComponentSpliceService::NotifyOnApplicationDeactivate()
	{
		m_pService->NotifyOnApplicationDeactivate();
	}

	void CComponentSpliceService::NotifyOnTimeChange()
	{
		m_pService->NotifyOnTimeChange();
	}

	void CComponentSpliceService::NotifyOnInputLanguageChange()
	{
		m_pService->NotifyOnInputLanguageChange();
	}

	void CComponentSpliceService::NotifyOnDisplayChange(const MessageSize &m)
	{
		m_pService->NotifyOnDisplayChange(m);
	}

	void CComponentSpliceService::NotifyOnThemeChange()
	{
		m_pService->NotifyOnThemeChange();
	}

	void CComponentSpliceService::NotifyOnClipboardUpdate()
	{
		m_pService->NotifyOnClipboardUpdate();
	}

	void CComponentSpliceService::NotifyOnTranslateChange()
	{
		m_pService->NotifyOnTranslateChange();
	}
#pragma endregion

#pragma region Form/window notifications
	void CComponentSpliceService::NotifyOnFormActivate(const MessageWindowActivate &m)
	{
		m_pService->NotifyOnFormActivate(m);
	}

	void CComponentSpliceService::NotifyOnFormDeactivate()
	{
		m_pService->NotifyOnFormDeactivate();
	}

	void CComponentSpliceService::NotifyOnFormSetFocus()
	{
		m_pService->NotifyOnFormSetFocus();
	}

	void CComponentSpliceService::NotifyOnFormKillFocus()
	{
		m_pService->NotifyOnFormKillFocus();
	}

	void CComponentSpliceService::NotifyOnFormEnable()
	{
		m_pService->NotifyOnFormEnable();
	}

	void CComponentSpliceService::NotifyOnFormDisable()
	{
		m_pService->NotifyOnFormDisable();
	}

	void CComponentSpliceService::NotifyOnFormShow()
	{
		m_pService->NotifyOnFormShow();
	}

	void CComponentSpliceService::NotifyOnFormHide()
	{
		m_pService->NotifyOnFormHide();
	}

	void CComponentSpliceService::NotifyOnFormMove(const MessagePosition &m)
	{
		m_pService->NotifyOnFormMove(m);
	}

	void CComponentSpliceService::NotifyOnFormRestore(const MessageSize &m)
	{
		m_pService->NotifyOnFormRestore(m);
	}

	void CComponentSpliceService::NotifyOnFormMinimize(const MessageSize &m)
	{
		m_pService->NotifyOnFormMinimize(m);
	}

	void CComponentSpliceService::NotifyOnFormMaximize(const MessageSize &m)
	{
		m_pService->NotifyOnFormMaximize(m);
	}

	void CComponentSpliceService::NotifyOnFormEnterSizeMove()
	{
		m_pService->NotifyOnFormEnterSizeMove();
	}

	void CComponentSpliceService::NotifyOnFormExitSizeMove()
	{
		m_pService->NotifyOnFormExitSizeMove();
	}
#pragma endregion

#pragma region Dialog box notifications
	void CComponentSpliceService::NotifyOnDialogBoxActivate(IDialogBox *control)
	{

	}

	void CComponentSpliceService::NotifyOnDialogBoxDeactivate(IDialogBox *control)
	{

	}
#pragma endregion
}