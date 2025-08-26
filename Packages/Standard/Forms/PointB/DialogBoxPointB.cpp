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
		const String CDialogBoxPointB::ClassName{ L"DialogBoxPointB" };

	#pragma region Service
		CDialogBoxPointB::CDialogBoxPointBService::CDialogBoxPointBService(CDialogBoxPointB *control) :
			IDialogBoxPointBProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxPointB::CDialogBoxPointBService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxPointB::CDialogBoxPointB() :
			IDialogBoxPointBProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxPointBService(this))
		{
			setStaticTabOrder(true);
			setUseMask(false);
			LoadTranslatableTexts();
		}

		CDialogBoxPointB::CDialogBoxPointB(IForm *parent) :CDialogBoxPointB()
		{
			setForm(parent);
		}

		CDialogBoxPointB::CDialogBoxPointB(IControl *parent) : CDialogBoxPointB()
		{
			setParent(parent);
		}

		void CDialogBoxPointB::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Point(bool)"));
			m_pCheckBoxX->setCaption(Application->Translate->t(ClassName, L"X"));
			m_pCheckBoxY->setCaption(Application->Translate->t(ClassName, L"Y"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CDialogBoxPointB::FormPointBProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if (m.Key == Key::Return || m.Key == Key::Separator)
				setModalResult(ModalResult::Ok);
		}

		void CDialogBoxPointB::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxPointB::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		PointB CDialogBoxPointB::getValue()
		{
			return { m_pCheckBoxX->getChecked() == ICheckBox::CheckedState::Checked, m_pCheckBoxY->getChecked() == ICheckBox::CheckedState::Checked };
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxPointB::setValue(const PointB &value)
		{
			CLockRepaint lock{ this };
			bool result{ m_pCheckBoxX->setChecked(value.X ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked) };
			result = m_pCheckBoxY->setChecked(value.Y ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked) || result;
			return result;
		}
	#pragma endregion

	#pragma region Interface methods
		void CDialogBoxPointB::ActivateFirstEnabledInput()
		{
			m_pCheckBoxX->setFocus();
		}
	#pragma endregion
	}
}