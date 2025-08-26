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
		const String CDialogBoxRectB::ClassName{ L"DialogBoxRectB" };

	#pragma region Service
		CDialogBoxRectB::CDialogBoxRectBService::CDialogBoxRectBService(CDialogBoxRectB *control) :
			IDialogBoxRectBProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxRectB::CDialogBoxRectBService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
			IDialogBoxRectBProtoService::NotifyOnFreeResources();
		}

		void CDialogBoxRectB::CDialogBoxRectBService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxRectB::CDialogBoxRectB() :
			IDialogBoxRectBProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxRectBService(this)),
			m_pCanvas{ nullptr }
		{
			setStaticTabOrder(true);
			setUseMask(false);
			LoadTranslatableTexts();
		}

		CDialogBoxRectB::CDialogBoxRectB(IForm *parent) :CDialogBoxRectB()
		{
			setForm(parent);
		}

		CDialogBoxRectB::CDialogBoxRectB(IControl *parent) : CDialogBoxRectB()
		{
			setParent(parent);
		}

		void CDialogBoxRectB::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Enable borders"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CDialogBoxRectB::FormRectBProto_OnPaint(IControl *sender, const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass)
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				if (!m_pCanvas)
				{
					if ((m_pCanvas = renderer->CreateTexture(258, 88, 1, TextureFormat::RGBA, true)))
					{
						CStoreTarget s_target{ renderer };
						renderer
							->ActivateTarget(m_pCanvas)
							->Clear(Color{ 0, 0, 0, 0 })
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
				if (m_pCanvas)
				{
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivatePrimitiveMatrix(getTransformControls()->getMatrix() * getTransformMatrix())
						->DrawImage(m_pCanvas, 1);
				}
			}
		}

		void CDialogBoxRectB::FormRectBProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if (m.Key == Key::Return || m.Key == Key::Separator)
				setModalResult(ModalResult::Ok);
		}

		void CDialogBoxRectB::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxRectB::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		RectB CDialogBoxRectB::getValue()
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
		bool CDialogBoxRectB::setValue(const RectB &value)
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
		void CDialogBoxRectB::ActivateFirstEnabledInput()
		{
			m_pCheckBoxLeft->setFocus();
		}
	#pragma endregion
	}
}