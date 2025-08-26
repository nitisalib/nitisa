// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
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
		const String CFormRectB::ClassName{ L"FormRectB" };

	#pragma region Service
		CFormRectB::CFormRectBService::CFormRectBService(CFormRectB *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormRectB::CFormRectBService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormRectB::CFormRectB(IWindow *window, IRenderer *renderer) :
			IFormRectBProto(window, renderer, ClassName)
		{
			setService(new CFormRectBService(this), true);
			LoadTranslatableTexts();
		}

		void CFormRectB::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Enable borders"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormRectB::FormRectBProto_OnPaint(IForm *sender, const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass)
			{
				IRenderer *renderer{ sender->getRenderer() };
				renderer
					->DrawBlock(
						RectF{ 8, 8, 258, 88 },
						RectF{ 50, 20, 50, 20 },
						RectF{ 0, 0, 0, 0 },
						BlockColors{ Color{ 200, 200, 200, 255 }, Color{ 160, 160, 160, 255 }, Color{ 200, 200, 200, 255 }, Color{ 160, 160, 160, 255 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } })
					->DrawBlock(
						RectF{ 8, 8, 258, 88 },
						RectF{ 1, 1, 1, 1 },
						RectF{ 0, 0, 0, 0 },
						BlockColors{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } })
					->DrawBlock(
						RectF{ 58, 28, 208, 68 },
						RectF{ 1, 1, 1, 1 },
						RectF{ 0, 0, 0, 0 },
						BlockColors{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } });
			}
		}

		void CFormRectB::FormRectBProto_OnKeyUp(IForm *sender, const MessageKey &m)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if (m.Key == Key::Return || m.Key == Key::Separator)
				setModalResult(ModalResult::Ok);
		}

		void CFormRectB::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormRectB::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		RectB CFormRectB::getValue()
		{
			return {
				m_pCheckBoxLeft->getChecked() == ICheckBox::CheckedState::Checked,
				m_pCheckBoxTop->getChecked() == ICheckBox::CheckedState::Checked,
				m_pCheckBoxRight->getChecked() == ICheckBox::CheckedState::Checked,
				m_pCheckBoxBottom->getChecked() == ICheckBox::CheckedState::Checked
			};
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormRectB::setValue(const RectB &value)
		{
			CLockRepaint lock{ this };
			bool result{ m_pCheckBoxLeft->setChecked(value.Left ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked) };
			result = m_pCheckBoxTop->setChecked(value.Top ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked) || result;
			result = m_pCheckBoxRight->setChecked(value.Right ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked) || result;
			result = m_pCheckBoxBottom->setChecked(value.Bottom ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked) || result;
			return result;
		}
	#pragma endregion

	#pragma region Interface methods
		void CFormRectB::ActivateFirstEnabledInput()
		{
			m_pCheckBoxLeft->setFocus();
		}
	#pragma endregion
	}
}