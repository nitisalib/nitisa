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
		const String CFormMask::ClassName{ L"FormMask" };

	#pragma region Service
		CFormMask::CFormMaskService::CFormMaskService(CFormMask *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormMask::CFormMaskService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormMask::CFormMask(IWindow *window, IRenderer *renderer) :
			IFormMaskProto(window, renderer, ClassName),
			m_aBits{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 
				nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr }
		{
			setService(new CFormMaskService(this), true);
			CLockRepaint lock{ this };
			InitControls();
			InitEvents();
			LoadTranslatableTexts();
		}

		void CFormMask::InitControls()
		{
			int x{ 8 };
			for (int i = 0; i < 32; i++)
			{
				m_aBits[i] = new CCheckBox(this);
				m_aBits[i]->getTransform()->Translate((float)x, 8, 0);
				m_aBits[i]->setSize(PointF{ 14, 14 });
				x += 14;
			}
		}

		void CFormMask::InitEvents()
		{
			for (int i = 0; i < 32; i++)
				m_aBits[i]->OnChange = CheckBox_OnChange;
		}

		void CFormMask::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Mask"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormMask::FormMaskProto_OnPaint(IForm *sender, const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass)
			{
				IRenderer *renderer{ getRenderer() };
				CStoreBitmask s_bitmask{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ m_iValue, 0b11111111111111111111111111111111, false, false })
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(8, 26, 0) * ntl::Mat4Scale<float>(14, 14, 1))
					->DrawRectangle(RectF{ 0, 0, 32, 1 }, Color{ 0, 0, 0, 255 });
			}
		}

		void CFormMask::FormMaskProto_OnKeyUp(IForm *sender, const MessageKey &m)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if ((m.Key == Key::Return || m.Key == Key::Separator) && Application->Keyboard->isDown(Key::Control))
				setModalResult(ModalResult::Ok);
		}

		void CFormMask::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormMask::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}

		void CFormMask::CheckBox_OnChange(IControl *sender)
		{
			CFormMask *form{ cast<CFormMask*>(sender->getForm()) };
			form->ControlsToValue();
			form->Repaint();
		}
	#pragma endregion
		
	#pragma region Helpers
		void CFormMask::ValueToControls()
		{
			unsigned int cmp;
			for (int i = 0; i < 32; i++)
			{
				cmp = 1 << i;
				m_aBits[i]->setChecked((m_iValue & cmp) ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked);
			}
		}

		void CFormMask::ControlsToValue()
		{
			m_iValue = 0;
			for (int i = 0; i < 32; i++)
				if (m_aBits[i]->getChecked() == ICheckBox::CheckedState::Checked)
					m_iValue |= 1 << i;
		}
	#pragma endregion

	#pragma region Interface getters
		unsigned int CFormMask::getValue()
		{
			return m_iValue;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormMask::setValue(const unsigned int value)
		{
			if (value != m_iValue)
			{
				m_iValue = value;
				ValueToControls();
				Repaint();
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}