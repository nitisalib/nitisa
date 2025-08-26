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
	namespace standard
	{
		const String CFormHotkey::ClassName{ L"FormHotkey" };

	#pragma region Service
		CFormHotkey::CFormHotkeyService::CFormHotkeyService(CFormHotkey *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormHotkey::CFormHotkeyService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormHotkey::CFormHotkey(IWindow *window, IRenderer *renderer) :
			IFormHotkeyProto(window, renderer, ClassName)
		{
			setService(new CFormHotkeyService(this), true);
			LoadTranslatableTexts();
		}

		void CFormHotkey::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(m_sClassName, L"Hotkey"));
			m_pLabelHotkey->setCaption(Application->Translate->t(m_sClassName, L"Click on field below and press key combination you want"));
			m_pCheckBoxDown->setCaption(Application->Translate->t(m_sClassName, L"Is hotkey down(up otherwise)?"));
			m_pButtonOk->setCaption(Application->Translate->t(m_sClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(m_sClassName, L"Cancel"));
			m_pButtonEmpty->setCaption(Application->Translate->t(m_sClassName, L"No hotkey"));
		}
	#pragma endregion

	#pragma region Events
		void CFormHotkey::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormHotkey::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}

		void CFormHotkey::ButtonEmpty_OnClick(IControl *sender)
		{
			m_pHotKey->setHotKey(Hotkey{ Key::Unknown, false, false, false, false });
		}
	#pragma endregion

	#pragma region Interface getters
		Hotkey CFormHotkey::getValue()
		{
			Hotkey v{ m_pHotKey->getHotKey() };
			v.Down = m_pCheckBoxDown->getChecked() == CCheckBox::CheckedState::Checked;
			return v;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormHotkey::setValue(const Hotkey &value)
		{
			bool result{ m_pHotKey->setHotKey(value) };
			result = m_pCheckBoxDown->setChecked(value.Down ? CCheckBox::CheckedState::Checked : CCheckBox::CheckedState::Unchecked) || result;
			return result;
		}
	#pragma endregion

	#pragma region Interface methods
		void CFormHotkey::ActivateFirstEnabledInput()
		{
			m_pHotKey->setFocus();
		}
	#pragma endregion
	}
}