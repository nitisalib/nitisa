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
		const String CFormFind::ClassName{ L"FormFind" };
		CFormFind *CFormFind::m_pInstance{ nullptr };

	#pragma region Service
		CFormFind::CFormFindService::CFormFindService(CFormFind *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormFind::CFormFindService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormFind::CFormFind(IWindow *window, IRenderer *renderer) :
			IFormFindProto(window, renderer, ClassName)
		{
			setService(new CFormFindService(this), true);
			OnSearch = nullptr;

			if (!m_pInstance)
				m_pInstance = this;
			LoadTranslatableTexts();
		}

		CFormFind::~CFormFind()
		{
			if (m_pInstance == this)
				m_pInstance = nullptr;
		}

		void CFormFind::LoadTranslatableTexts()
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
		void CFormFind::FormFindProto_OnKeyUp(IForm *sender, const MessageKey &m)
		{
			switch (m.Key)
			{
			case Key::Return:
			case Key::Separator:
				if (getFocusedControl() != m_pEditText && (m.Key == Key::Return || (m.Key == Key::Separator && Application->Keyboard->isToggled(Key::NumLock))))
					m_pButtonSearch->Click();
				break;
			case Key::Escape:
				m_pButtonCancel->Click();
				break;
			default:
				break;
			}
		}

		void CFormFind::EditText_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Return || (m.Key == Key::Separator && Application->Keyboard->isToggled(Key::NumLock)))
				m_pButtonSearch->Click();
		}

		void CFormFind::EditText_OnChange(IControl *sender)
		{
			m_pButtonSearch->setEnabled(m_pEditText->getText().length() > 0);
		}

		void CFormFind::ButtonSearch_OnClick(IControl *sender)
		{
			if (OnSearch && m_pEditText->getText().length() > 0)
				OnSearch(this);
		}

		void CFormFind::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		String CFormFind::getText()
		{
			return m_pEditText->getText();
		}

		bool CFormFind::isMatchWholeWords()
		{
			return m_pCheckBoxWords->getChecked() == ICheckBox::CheckedState::Checked;
		}

		bool CFormFind::isMatchCase()
		{
			return m_pCheckBoxCase->getChecked() == ICheckBox::CheckedState::Checked;
		}

		IFormFind::SearchDirection CFormFind::getSearchDirection()
		{
			if (m_pRadioButtonUp->isChecked())
				return SearchDirection::Up;
			return SearchDirection::Down;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormFind::setText(const String &value)
		{
			return m_pEditText->setText(value);
		}

		bool CFormFind::setMatchWholeWords(const bool value)
		{
			return m_pCheckBoxWords->setChecked(value ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked);
		}

		bool CFormFind::setMatchCase(const bool value)
		{
			return m_pCheckBoxCase->setChecked(value ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked);
		}

		bool CFormFind::setSearchDirection(const SearchDirection value)
		{
			return value == SearchDirection::Up ? m_pRadioButtonUp->setChecked(true) : m_pRadioButtonDown->setChecked(true);
		}
	#pragma endregion

	#pragma region Interface methods
		void CFormFind::ActivateFirstEnabledInput()
		{
			m_pEditText->SelectAll();
			m_pEditText->setFocus();
		}
	#pragma endregion

	#pragma region Getters
		CFormFind *CFormFind::getInstance()
		{
			return m_pInstance;
		}
	#pragma endregion
	}
}