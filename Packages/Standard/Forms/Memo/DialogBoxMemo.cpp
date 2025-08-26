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
		const String CDialogBoxMemo::ClassName{ L"DialogBoxMemo" };

	#pragma region Service
		CDialogBoxMemo::CDialogBoxMemoService::CDialogBoxMemoService(CDialogBoxMemo *control) :
			IDialogBoxMemoProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxMemo::CDialogBoxMemoService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxMemo::CDialogBoxMemo() :
			IDialogBoxMemoProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxMemoService(this))
		{
			setStaticTabOrder(true);
			setUseMask(false);
			LoadTranslatableTexts();
		}

		CDialogBoxMemo::CDialogBoxMemo(IForm *parent) :CDialogBoxMemo()
		{
			setForm(parent);
		}

		CDialogBoxMemo::CDialogBoxMemo(IControl *parent) : CDialogBoxMemo()
		{
			setParent(parent);
		}

		void CDialogBoxMemo::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Memo"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CDialogBoxMemo::FormMemoProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if ((m.Key == Key::Return || m.Key == Key::Separator) && Application->Keyboard->isDown(Key::Control))
				setModalResult(ModalResult::Ok);
		}

		void CDialogBoxMemo::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxMemo::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		String CDialogBoxMemo::getValue()
		{
			return m_pMemo->getText();
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxMemo::setValue(const String &value)
		{
			return m_pMemo->setText(value);
		}
	#pragma endregion

	#pragma region Interface methods
		void CDialogBoxMemo::ActivateFirstEnabledInput()
		{
			m_pMemo->SelectAll();
			m_pMemo->setFocus();
		}
	#pragma endregion
	}
}