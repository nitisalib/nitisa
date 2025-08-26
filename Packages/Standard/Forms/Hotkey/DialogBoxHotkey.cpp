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
		const String CDialogBoxHotkey::ClassName{ L"DialogBoxHotkey" };

	#pragma region Service
		CDialogBoxHotkey::CDialogBoxHotkeyService::CDialogBoxHotkeyService(CDialogBoxHotkey *control) :
			IDialogBoxHotkeyProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxHotkey::CDialogBoxHotkeyService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxHotkey::CDialogBoxHotkey() :
			IDialogBoxHotkeyProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxHotkeyService(this))
		{
			setStaticTabOrder(true);
			setUseMask(false);
			LoadTranslatableTexts();
		}

		CDialogBoxHotkey::CDialogBoxHotkey(IForm *parent) :CDialogBoxHotkey()
		{
			setForm(parent);
		}

		CDialogBoxHotkey::CDialogBoxHotkey(IControl *parent) : CDialogBoxHotkey()
		{
			setParent(parent);
		}

		void CDialogBoxHotkey::LoadTranslatableTexts()
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
		void CDialogBoxHotkey::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxHotkey::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}

		void CDialogBoxHotkey::ButtonEmpty_OnClick(IControl *sender)
		{
			m_pHotKey->setHotKey(Hotkey{ Key::Unknown, false, false, false, false });
		}
	#pragma endregion

	#pragma region Interface getters
		Hotkey CDialogBoxHotkey::getValue()
		{
			Hotkey v{ m_pHotKey->getHotKey() };
			v.Down = m_pCheckBoxDown->getChecked() == CCheckBox::CheckedState::Checked;
			return v;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxHotkey::setValue(const Hotkey &value)
		{
			bool result{ m_pHotKey->setHotKey(value) };
			result = m_pCheckBoxDown->setChecked(value.Down ? CCheckBox::CheckedState::Checked : CCheckBox::CheckedState::Unchecked) || result;
			return result;
		}
	#pragma endregion

	#pragma region Interface methods
		void CDialogBoxHotkey::ActivateFirstEnabledInput()
		{
			m_pHotKey->setFocus();
		}
	#pragma endregion
	}
}