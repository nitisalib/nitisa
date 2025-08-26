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
		const String CFormPointB::ClassName{ L"FormPointB" };

	#pragma region Service
		CFormPointB::CFormPointBService::CFormPointBService(CFormPointB *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormPointB::CFormPointBService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormPointB::CFormPointB(IWindow *window, IRenderer *renderer) :
			IFormPointBProto(window, renderer, ClassName)
		{
			setService(new CFormPointBService(this), true);
			LoadTranslatableTexts();
		}

		void CFormPointB::LoadTranslatableTexts()
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
		void CFormPointB::FormPointBProto_OnKeyUp(IForm *sender, const MessageKey &m)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if (m.Key == Key::Return || m.Key == Key::Separator)
				setModalResult(ModalResult::Ok);
		}

		void CFormPointB::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormPointB::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		PointB CFormPointB::getValue()
		{
			return { m_pCheckBoxX->getChecked() == ICheckBox::CheckedState::Checked, m_pCheckBoxY->getChecked() == ICheckBox::CheckedState::Checked };
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormPointB::setValue(const PointB &value)
		{
			CLockRepaint lock{ this };
			bool result{ m_pCheckBoxX->setChecked(value.X ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked) };
			result = m_pCheckBoxY->setChecked(value.Y ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked) || result;
			return result;
		}
	#pragma endregion

	#pragma region Interface methods
		void CFormPointB::ActivateFirstEnabledInput()
		{
			m_pCheckBoxX->setFocus();
		}
	#pragma endregion
	}
}