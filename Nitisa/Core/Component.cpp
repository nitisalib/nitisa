// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	CComponent::CComponent(const String &class_name) :
		CClass(class_name),
		CReleasable(),
		m_pForm{ nullptr },
		m_pService{ nullptr }
	{
		// State change events
		OnAttach = nullptr;
		OnDetaching = nullptr;
		OnDetach = nullptr;

		// Component events
		OnComponentAttach = nullptr;
		OnComponentDetach = nullptr;
		OnComponentChange = nullptr;

		// Control events
		OnControlAttach = nullptr;
		OnControlDetach = nullptr;
		OnControlChange = nullptr;
		OnControlSetFocus = nullptr;
		OnControlKillFocus = nullptr;
		OnControlSetCaptureMouse = nullptr;
		OnControlKillCaptureMouse = nullptr;
		OnControlSetCaptureKeyboard = nullptr;
		OnControlKillCaptureKeyboard = nullptr;
		OnControlSetModal = nullptr;
		OnControlKillModal = nullptr;

		// Other input events
		OnHotkey = nullptr;

		// Application events
		OnApplicationActivate = nullptr;
		OnApplicationDeactivate = nullptr;
		OnTimeChange = nullptr;
		OnInputLanguageChange = nullptr;
		OnDisplayChange = nullptr;
		OnThemeChange = nullptr;
		OnClipboardUpdate = nullptr;
		OnTranslateChange = nullptr;

		// Form events
		OnFormActivate = nullptr;
		OnFormDeactivate = nullptr;
		OnFormSetFocus = nullptr;
		OnFormKillFocus = nullptr;
		OnFormEnable = nullptr;
		OnFormDisable = nullptr;
		OnFormShow = nullptr;
		OnFormHide = nullptr;
		OnFormMove = nullptr;
		OnFormRestore = nullptr;
		OnFormMinimize = nullptr;
		OnFormMaximize = nullptr;
		OnFormEnterSizeMove = nullptr;
		OnFormExitSizeMove = nullptr;

		// Dialog box events
		OnDialogBoxActivate = nullptr;
		OnDialogBoxDeactivate = nullptr;
	}

	CComponent::~CComponent()
	{
		if (m_pService)
			m_pService->Release();
	}

	void CComponent::BeforeRelease()
	{
		if (m_pForm)
			m_pForm->DetachComponent(this);
	}
#pragma endregion

#pragma region Getters
	IForm *CComponent::getForm()
	{
		return m_pForm;
	}
#pragma endregion

#pragma region Setters
	bool CComponent::setName(const String &value)
	{
		if (value != m_sName)
		{
			m_sName = value;
			if (getForm())
				QueryService()->setName(getForm()->QueryService()->GenerateComponentName(this));
			return true;
		}
		return false;
	}

	bool CComponent::setForm(IForm *value)
	{
		if (value == m_pForm)
			return false;
		if (m_pForm)
			m_pForm->DetachComponent(this);
		if (value)
			return value->AttachComponent(this);
		return true;
	}

	void CComponent::setService(IComponentService *value, const bool release_prev)
	{
		if (m_pService && m_pService != value && release_prev)
			m_pService->Release();
		m_pService = value;
	}
#pragma endregion

#pragma region Helpers
	IComponentService *CComponent::QueryService()
	{
		if (!m_pService)
			m_pService = new CComponentService(this);
		return m_pService;
	}
#pragma endregion
}