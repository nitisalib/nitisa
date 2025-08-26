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
		const String CDialogBoxReplace::ClassName{ L"DialogBoxReplace" };

	#pragma region Service
		CDialogBoxReplace::CDialogBoxReplaceService::CDialogBoxReplaceService(CDialogBoxReplace *control) :
			IDialogBoxReplaceProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxReplace::CDialogBoxReplaceService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxReplace::CDialogBoxReplace() :
			IDialogBoxReplaceProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxReplaceService(this))
		{
			OnReplace = nullptr;
			OnReplaceAll = nullptr;
			setStaticTabOrder(true);
			setUseMask(false);
			LoadTranslatableTexts();
		}

		CDialogBoxReplace::CDialogBoxReplace(IForm *parent) :CDialogBoxReplace()
		{
			setForm(parent);
		}

		CDialogBoxReplace::CDialogBoxReplace(IControl *parent) : CDialogBoxReplace()
		{
			setParent(parent);
		}

		void CDialogBoxReplace::LoadTranslatableTexts()
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
		void CDialogBoxReplace::FormReplaceProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			switch (m.Key)
			{
			case Key::Return:
			case Key::Separator:
				if (getForm()->getFocusedControl() != m_pEditText && getForm()->getFocusedControl() != m_pEditReplace &&
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

		void CDialogBoxReplace::EditText_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Return || (m.Key == Key::Separator && Application->Keyboard->isToggled(Key::NumLock)))
				m_pButtonReplace->Click();
		}

		void CDialogBoxReplace::EditText_OnChange(IControl *sender)
		{
			m_pButtonReplace->setEnabled(m_pEditText->getText().length() > 0 && m_pEditReplace->getText().length() > 0);
			m_pButtonReplaceAll->setEnabled(m_pEditText->getText().length() > 0 && m_pEditReplace->getText().length() > 0);
		}

		void CDialogBoxReplace::EditReplace_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Return || (m.Key == Key::Separator && Application->Keyboard->isToggled(Key::NumLock)))
				m_pButtonReplace->Click();
		}

		void CDialogBoxReplace::ButtonReplace_OnClick(IControl *sender)
		{
			if (OnReplace && m_pEditText->getText().length() > 0 && m_pEditReplace->getText().length() > 0)
				OnReplace(this);
		}

		void CDialogBoxReplace::ButtonReplaceAll_OnClick(IControl *sender)
		{
			if (OnReplaceAll && m_pEditText->getText().length() > 0 && m_pEditReplace->getText().length() > 0)
				OnReplaceAll(this);
		}

		void CDialogBoxReplace::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		String CDialogBoxReplace::getText()
		{
			return m_pEditText->getText();
		}

		String CDialogBoxReplace::getReplace()
		{
			return m_pEditReplace->getText();
		}

		bool CDialogBoxReplace::isMatchWholeWords()
		{
			return m_pCheckBoxWords->getChecked() == ICheckBox::CheckedState::Checked;
		}

		bool CDialogBoxReplace::isMatchCase()
		{
			return m_pCheckBoxCase->getChecked() == ICheckBox::CheckedState::Checked;
		}

		IFormReplace::SearchDirection CDialogBoxReplace::getSearchDirection()
		{
			if (m_pRadioButtonUp->isChecked())
				return SearchDirection::Up;
			if (m_pRadioButtonDown->isChecked())
				return SearchDirection::Down;
			return SearchDirection::Selection;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxReplace::setText(const String &value)
		{
			return m_pEditText->setText(value);
		}

		bool CDialogBoxReplace::setReplace(const String &value)
		{
			return m_pEditReplace->setText(value);
		}

		bool CDialogBoxReplace::setMatchWholeWords(const bool value)
		{
			return m_pCheckBoxWords->setChecked(value ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked);
		}

		bool CDialogBoxReplace::setMatchCase(const bool value)
		{
			return m_pCheckBoxCase->setChecked(value ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked);
		}

		bool CDialogBoxReplace::setSearchDirection(const SearchDirection value)
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
		void CDialogBoxReplace::ActivateFirstEnabledInput()
		{
			m_pEditText->SelectAll();
			m_pEditText->setFocus();
		}
	#pragma endregion
	}
}