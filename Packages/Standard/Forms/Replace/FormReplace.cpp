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
		const String CFormReplace::ClassName{ L"FormReplace" };
		CFormReplace *CFormReplace::m_pInstance{ nullptr };

	#pragma region Service
		CFormReplace::CFormReplaceService::CFormReplaceService(CFormReplace *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormReplace::CFormReplaceService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormReplace::CFormReplace(IWindow *window, IRenderer *renderer) :
			IFormReplaceProto(window, renderer, ClassName)
		{
			setService(new CFormReplaceService(this), true);
			OnReplace = nullptr;
			OnReplaceAll = nullptr;

			if (!m_pInstance)
				m_pInstance = this;
			LoadTranslatableTexts();
		}

		CFormReplace::~CFormReplace()
		{
			if (m_pInstance == this)
				m_pInstance = nullptr;
		}

		void CFormReplace::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Replace"));
			m_pLabel1->setCaption(Application->Translate->t(ClassName, L"Find what:"));
			m_pLabel2->setCaption(Application->Translate->t(ClassName, L"Replace with:"));
			m_pCheckBoxWords->setCaption(Application->Translate->t(ClassName, L"Match whole words"));
			m_pCheckBoxCase->setCaption(Application->Translate->t(ClassName, L"Match case"));
			m_pGroupBox1->setCaption(Application->Translate->t(ClassName, L"Direction"));
			m_pRadioButtonUp->setCaption(Application->Translate->t(ClassName, L"Up"));
			m_pRadioButtonDown->setCaption(Application->Translate->t(ClassName, L"Down"));
			m_pRadioButtonSelection->setCaption(Application->Translate->t(ClassName, L"Selection"));
			m_pButtonReplace->setCaption(Application->Translate->t(ClassName, L"Replace"));
			m_pButtonReplaceAll->setCaption(Application->Translate->t(ClassName, L"Replace All"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormReplace::FormReplaceProto_OnKeyUp(IForm *sender, const MessageKey &m)
		{
			switch (m.Key)
			{
			case Key::Return:
			case Key::Separator:
				if (getFocusedControl() != m_pEditText && getFocusedControl() != m_pEditReplace &&
					(m.Key == Key::Return || (m.Key == Key::Separator && Application->Keyboard->isToggled(Key::NumLock))))
					m_pButtonReplace->Click();
				break;
			case Key::Escape:
				m_pButtonCancel->Click();
				break;
			default:
				break;
			}
		}

		void CFormReplace::EditText_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Return || (m.Key == Key::Separator && Application->Keyboard->isToggled(Key::NumLock)))
				m_pButtonReplace->Click();
		}

		void CFormReplace::EditText_OnChange(IControl *sender)
		{
			m_pButtonReplace->setEnabled(m_pEditText->getText().length() > 0 && m_pEditReplace->getText().length() > 0);
			m_pButtonReplaceAll->setEnabled(m_pEditText->getText().length() > 0 && m_pEditReplace->getText().length() > 0);
		}

		void CFormReplace::EditReplace_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Return || (m.Key == Key::Separator && Application->Keyboard->isToggled(Key::NumLock)))
				m_pButtonReplace->Click();
		}

		void CFormReplace::ButtonReplace_OnClick(IControl *sender)
		{
			if (OnReplace && m_pEditText->getText().length() > 0 && m_pEditReplace->getText().length() > 0)
				OnReplace(this);
		}

		void CFormReplace::ButtonReplaceAll_OnClick(IControl *sender)
		{
			if (OnReplaceAll && m_pEditText->getText().length() > 0 && m_pEditReplace->getText().length() > 0)
				OnReplaceAll(this);
		}

		void CFormReplace::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		String CFormReplace::getText()
		{
			return m_pEditText->getText();
		}

		String CFormReplace::getReplace()
		{
			return m_pEditReplace->getText();
		}

		bool CFormReplace::isMatchWholeWords()
		{
			return m_pCheckBoxWords->getChecked() == ICheckBox::CheckedState::Checked;
		}

		bool CFormReplace::isMatchCase()
		{
			return m_pCheckBoxCase->getChecked() == ICheckBox::CheckedState::Checked;
		}

		IFormReplace::SearchDirection CFormReplace::getSearchDirection()
		{
			if (m_pRadioButtonUp->isChecked())
				return SearchDirection::Up;
			if (m_pRadioButtonDown->isChecked())
				return SearchDirection::Down;
			return SearchDirection::Selection;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormReplace::setText(const String &value)
		{
			return m_pEditText->setText(value);
		}

		bool CFormReplace::setReplace(const String &value)
		{
			return m_pEditReplace->setText(value);
		}

		bool CFormReplace::setMatchWholeWords(const bool value)
		{
			return m_pCheckBoxWords->setChecked(value ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked);
		}

		bool CFormReplace::setMatchCase(const bool value)
		{
			return m_pCheckBoxCase->setChecked(value ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked);
		}

		bool CFormReplace::setSearchDirection(const SearchDirection value)
		{
			switch (value)
			{
			case SearchDirection::Up:
				return m_pRadioButtonUp->setChecked(true);
			case SearchDirection::Down:
				return m_pRadioButtonDown->setChecked(true);
			case SearchDirection::Selection:
				return m_pRadioButtonSelection->setChecked(true);
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface methods
		void CFormReplace::ActivateFirstEnabledInput()
		{
			m_pEditText->SelectAll();
			m_pEditText->setFocus();
		}
	#pragma endregion

	#pragma region Getters
		CFormReplace *CFormReplace::getInstance()
		{
			return m_pInstance;
		}
	#pragma endregion
	}
}