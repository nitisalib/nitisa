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
		const String CDialogBoxFind::ClassName{ L"DialogBoxFind" };

	#pragma region Service
		CDialogBoxFind::CDialogBoxFindService::CDialogBoxFindService(CDialogBoxFind *control) :
			IDialogBoxFindProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxFind::CDialogBoxFindService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxFind::CDialogBoxFind() :
			IDialogBoxFindProto(ClassName, true, true, false, false, DesignDPI)
		{
			OnSearch = nullptr;
			setStaticTabOrder(true);
			setUseMask(false);
			LoadTranslatableTexts();
		}

		CDialogBoxFind::CDialogBoxFind(IForm *parent) :CDialogBoxFind()
		{
			setForm(parent);
		}

		CDialogBoxFind::CDialogBoxFind(IControl *parent) : CDialogBoxFind()
		{
			setParent(parent);
		}

		void CDialogBoxFind::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Find"));
			m_pLabel1->setCaption(Application->Translate->t(ClassName, L"Find what:"));
			m_pCheckBoxWords->setCaption(Application->Translate->t(ClassName, L"Match whole words"));
			m_pCheckBoxCase->setCaption(Application->Translate->t(ClassName, L"Match case"));
			m_pGroupBox1->setCaption(Application->Translate->t(ClassName, L"Direction"));
			m_pRadioButtonUp->setCaption(Application->Translate->t(ClassName, L"Up"));
			m_pRadioButtonDown->setCaption(Application->Translate->t(ClassName, L"Down"));
			m_pButtonSearch->setCaption(Application->Translate->t(ClassName, L"Find Next"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CDialogBoxFind::FormFindProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			switch (m.Key)
			{
			case Key::Return:
			case Key::Separator:
				if (getForm()->getFocusedControl() != m_pEditText && (m.Key == Key::Return || (m.Key == Key::Separator && Application->Keyboard->isToggled(Key::NumLock))))
					m_pButtonSearch->Click();
				break;
			case Key::Escape:
				m_pButtonCancel->Click();
				break;
			default:
				break;
			}
		}

		void CDialogBoxFind::EditText_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Return || (m.Key == Key::Separator && Application->Keyboard->isToggled(Key::NumLock)))
				m_pButtonSearch->Click();
		}

		void CDialogBoxFind::EditText_OnChange(IControl *sender)
		{
			m_pButtonSearch->setEnabled(m_pEditText->getText().length() > 0);
		}

		void CDialogBoxFind::ButtonSearch_OnClick(IControl *sender)
		{
			if (OnSearch && m_pEditText->getText().length() > 0)
				OnSearch(this);
		}

		void CDialogBoxFind::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		String CDialogBoxFind::getText()
		{
			return m_pEditText->getText();
		}

		bool CDialogBoxFind::isMatchWholeWords()
		{
			return m_pCheckBoxWords->getChecked() == ICheckBox::CheckedState::Checked;
		}

		bool CDialogBoxFind::isMatchCase()
		{
			return m_pCheckBoxCase->getChecked() == ICheckBox::CheckedState::Checked;
		}

		IFormFind::SearchDirection CDialogBoxFind::getSearchDirection()
		{
			if (m_pRadioButtonUp->isChecked())
				return SearchDirection::Up;
			return SearchDirection::Down;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxFind::setText(const String &value)
		{
			return m_pEditText->setText(value);
		}

		bool CDialogBoxFind::setMatchWholeWords(const bool value)
		{
			return m_pCheckBoxWords->setChecked(value ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked);
		}

		bool CDialogBoxFind::setMatchCase(const bool value)
		{
			return m_pCheckBoxCase->setChecked(value ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked);
		}

		bool CDialogBoxFind::setSearchDirection(const SearchDirection value)
		{
			return value == SearchDirection::Up ? m_pRadioButtonUp->setChecked(true) : m_pRadioButtonDown->setChecked(true);
		}
	#pragma endregion

	#pragma region Interface methods
		void CDialogBoxFind::ActivateFirstEnabledInput()
		{
			m_pEditText->SelectAll();
			m_pEditText->setFocus();
		}
	#pragma endregion
	}
}