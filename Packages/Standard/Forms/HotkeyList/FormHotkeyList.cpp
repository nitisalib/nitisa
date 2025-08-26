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
		const String CFormHotkeyList::ClassName{ L"FormHotkeyList" };
		
	#pragma region Service
		CFormHotkeyList::CFormHotkeyListService::CFormHotkeyListService(CFormHotkeyList *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormHotkeyList::CFormHotkeyListService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormHotkeyList::CFormHotkeyList(IWindow *window, IRenderer *renderer) :
			IFormHotkeyListProto(window, renderer, ClassName)
		{
			setService(new CFormHotkeyListService(this), true);
			LoadTranslatableTexts();
		}

		void CFormHotkeyList::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Hotkey List"));
			m_pLabelList->setCaption(Application->Translate->t(ClassName, L"Hotkeys"));
			m_pLabelHotkey->setCaption(Application->Translate->t(ClassName, L"Click on field below and press key combination you want"));
			m_pCheckBoxDown->setCaption(Application->Translate->t(ClassName, L"Is hotkey down(up otherwise)?"));
			m_pButtonAdd->setCaption(Application->Translate->t(ClassName, L"Add"));
			m_pButtonDelete->setCaption(Application->Translate->t(ClassName, L"Delete"));
			m_pButtonClear->setCaption(Application->Translate->t(ClassName, L"Clear"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormHotkeyList::ButtonAdd_OnClick(IControl *sender)
		{
			Hotkey v{ m_pHotKey->getHotKey() };
			if (v.Key == Key::Unknown)
			{
				Application->Dialogs->Warning(Application->Translate->t(ClassName, L"Empty hotkey can't be added"));
				return;
			}
			v.Down = m_pCheckBoxDown->getChecked() == CCheckBox::CheckedState::Checked;
			for (auto pos : m_aHotkeys)
				if (pos == v)
				{
					Application->Dialogs->Warning(Application->Translate->t(ClassName, L"The same hotkey is already exists in list"));
					return;
				}
			m_aHotkeys.push_back(v);
			m_pListBoxList->Add(Application->Translate->t(ClassName, v.Down ? L"[Down]" : L"[Up]") + CTranslate::Hotkey(v));
		}

		void CFormHotkeyList::ButtonDelete_OnClick(IControl *sender)
		{
			int i{ 0 };
			while (i < m_pListBoxList->getItemCount())
				if (m_pListBoxList->getItem(i)->isSelected())
				{
					m_aHotkeys.erase(m_aHotkeys.begin() + i);
					m_pListBoxList->DeleteItem(i);
				}
				else
					i++;
		}

		void CFormHotkeyList::ButtonClear_OnClick(IControl *sender)
		{
			m_aHotkeys.clear();
			m_pListBoxList->Clear();
		}

		void CFormHotkeyList::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormHotkeyList::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		int CFormHotkeyList::getHotkeyCount()
		{
			return (int)m_aHotkeys.size();
		}

		Hotkey CFormHotkeyList::getHotkey(const int index)
		{
			if (index >= 0 && index < (int)m_aHotkeys.size())
				return m_aHotkeys[index];
			return Hotkey{ Key::Unknown, false, false, false, false };
		}
	#pragma endregion

	#pragma region Interface methods
		void CFormHotkeyList::ActivateFirstEnabledInput()
		{
			m_pHotKey->setFocus();
		}
	#pragma endregion

	#pragma region Hotkeys
		bool CFormHotkeyList::AddHotkey(const Hotkey &value)
		{
			if (value.Key != Key::Unknown)
			{
				for (auto pos : m_aHotkeys)
					if (pos == value)
						return false;
				m_aHotkeys.push_back(value);
				m_pListBoxList->Add(Application->Translate->t(ClassName, value.Down ? L"[Down]" : L"[Up]") + CTranslate::Hotkey(value));
				return true;
			}
			return false;
		}

		bool CFormHotkeyList::DeleteHotkey(const int index)
		{
			if (index >= 0 && index < (int)m_aHotkeys.size())
			{
				m_aHotkeys.erase(m_aHotkeys.begin() + index);
				m_pListBoxList->Delete(index);
				return true;
			}
			return false;
		}

		bool CFormHotkeyList::DeleteHotkeys()
		{
			if (m_aHotkeys.size() > 0)
			{
				m_aHotkeys.clear();
				m_pListBoxList->Clear();
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}