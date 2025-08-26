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
		const String CDialogBoxMask::ClassName{ L"DialogBoxMask" };

	#pragma region Service
		CDialogBoxMask::CDialogBoxMaskService::CDialogBoxMaskService(CDialogBoxMask *control) :
			IDialogBoxMaskProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxMask::CDialogBoxMaskService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxMask::CDialogBoxMask() :
			IDialogBoxMaskProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxMaskService(this)),
			m_aBits{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
				nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr }
		{
			setStaticTabOrder(true);
			setUseMask(false);
			InitControls();
			InitEvents();
			LoadTranslatableTexts();
		}

		CDialogBoxMask::CDialogBoxMask(IForm *parent) :CDialogBoxMask()
		{
			setForm(parent);
		}

		CDialogBoxMask::CDialogBoxMask(IControl *parent) : CDialogBoxMask()
		{
			setParent(parent);
		}

		void CDialogBoxMask::InitControls()
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

		void CDialogBoxMask::InitEvents()
		{
			for (int i = 0; i < 32; i++)
				m_aBits[i]->OnChange = CheckBox_OnChange;
		}

		void CDialogBoxMask::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Mask"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CDialogBoxMask::FormMaskProto_OnPaint(IControl *sender, const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass)
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreBitmask s_bitmask{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBitmask(Bitmask{ m_iValue, 0b11111111111111111111111111111111, false, false })
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(8, 26, 0) * getTransformMatrix() * getTransformControls()->getMatrix() * ntl::Mat4Scale<float>(14, 14, 1))
					->DrawRectangle(RectF{ 0, 0, 32, 1 }, Color{ 0, 0, 0, 255 });
			}
		}

		void CDialogBoxMask::FormMaskProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if ((m.Key == Key::Return || m.Key == Key::Separator) && Application->Keyboard->isDown(Key::Control))
				setModalResult(ModalResult::Ok);
		}

		void CDialogBoxMask::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxMask::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}

		void CDialogBoxMask::CheckBox_OnChange(IControl *sender)
		{
			CDialogBoxMask *dlg{ parent<CDialogBoxMask*, false>(sender) };
			dlg->ControlsToValue();
			dlg->Repaint(false);
		}
	#pragma endregion

	#pragma region Helpers
		void CDialogBoxMask::ValueToControls()
		{
			unsigned int cmp;
			for (int i = 0; i < 32; i++)
			{
				cmp = 1 << i;
				m_aBits[i]->setChecked((m_iValue & cmp) ? ICheckBox::CheckedState::Checked : ICheckBox::CheckedState::Unchecked);
			}
		}

		void CDialogBoxMask::ControlsToValue()
		{
			m_iValue = 0;
			for (int i = 0; i < 32; i++)
				if (m_aBits[i]->getChecked() == ICheckBox::CheckedState::Checked)
					m_iValue |= 1 << i;
		}
	#pragma endregion

	#pragma region Interface getters
		unsigned int CDialogBoxMask::getValue()
		{
			return m_iValue;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxMask::setValue(const unsigned int value)
		{
			if (value != m_iValue)
			{
				m_iValue = value;
				ValueToControls();
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}