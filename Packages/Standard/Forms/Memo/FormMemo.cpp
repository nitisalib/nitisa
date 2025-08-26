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
		const String CFormMemo::ClassName{ L"FormMemo" };

	#pragma region Service
		CFormMemo::CFormMemoService::CFormMemoService(CFormMemo *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormMemo::CFormMemoService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormMemo::CFormMemo(IWindow *window, IRenderer *renderer) :
			IFormMemoProto(window, renderer, ClassName)
		{
			setService(new CFormMemoService(this), true);
			LoadTranslatableTexts();
		}

		void CFormMemo::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Memo"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormMemo::FormMemoProto_OnKeyUp(IForm *sender, const MessageKey &m)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if ((m.Key == Key::Return || m.Key == Key::Separator) && Application->Keyboard->isDown(Key::Control))
				setModalResult(ModalResult::Ok);
		}

		void CFormMemo::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormMemo::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		String CFormMemo::getValue()
		{
			return m_pMemo->getText();
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormMemo::setValue(const String &value)
		{
			return m_pMemo->setText(value);
		}
	#pragma endregion

	#pragma region Interface methods
		void CFormMemo::ActivateFirstEnabledInput()
		{
			m_pMemo->SelectAll();
			m_pMemo->setFocus();
		}
	#pragma endregion
	}
}