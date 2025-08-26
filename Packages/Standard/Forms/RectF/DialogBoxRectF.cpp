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
		const String CDialogBoxRectF::ClassName{ L"DialogBoxRectF" };

	#pragma region Service
		CDialogBoxRectF::CDialogBoxRectFService::CDialogBoxRectFService(CDialogBoxRectF *control) :
			IDialogBoxRectFProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxRectF::CDialogBoxRectFService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
			IDialogBoxRectFProtoService::NotifyOnFreeResources();
		}

		void CDialogBoxRectF::CDialogBoxRectFService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxRectF::CDialogBoxRectF() :
			IDialogBoxRectFProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxRectFService(this)),
			m_sValue{ 0, 0, 0, 0 },
			m_bHasMin{ false },
			m_bHasMax{ false },
			m_fMin{ 0 },
			m_fMax{ 0 },
			m_pCanvas{ nullptr }
		{
			setStaticTabOrder(true);
			setUseMask(false);
			LoadTranslatableTexts();
		}

		CDialogBoxRectF::CDialogBoxRectF(IForm *parent) :CDialogBoxRectF()
		{
			setForm(parent);
		}

		CDialogBoxRectF::CDialogBoxRectF(IControl *parent) : CDialogBoxRectF()
		{
			setParent(parent);
		}

		void CDialogBoxRectF::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Borders(float)"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CDialogBoxRectF::FormRectFProto_OnPaint(IControl *sender, const MessagePaint &m, bool &draw_children)
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

		void CDialogBoxRectF::FormRectFProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if (m.Key == Key::Return || m.Key == Key::Separator)
			{
				CEdit *edit{ cast<CEdit*>(getForm()->getFocusedControl()) };
				if (edit)
					edit->OnKillFocus(edit);
				setModalResult(ModalResult::Ok);
			}
		}

		void CDialogBoxRectF::EditLeft_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			float v;
			if (!TryStringToFloat(edit->getText(), v))
				v = m_sValue.Left;
			if (m_bHasMin && ntl::IsLess<float>(v, m_fMin))
				v = m_fMin;
			else if (m_bHasMax && ntl::IsGreater<float>(v, m_fMax))
				v = m_fMax;
			m_sValue.Left = v;
			edit->setText(ToStringCompact(v));
		}

		void CDialogBoxRectF::EditTop_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			float v;
			if (!TryStringToFloat(edit->getText(), v))
				v = m_sValue.Top;
			if (m_bHasMin && ntl::IsLess<float>(v, m_fMin))
				v = m_fMin;
			else if (m_bHasMax && ntl::IsGreater<float>(v, m_fMax))
				v = m_fMax;
			m_sValue.Top = v;
			edit->setText(ToStringCompact(v));
		}

		void CDialogBoxRectF::EditRight_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			float v;
			if (!TryStringToFloat(edit->getText(), v))
				v = m_sValue.Right;
			if (m_bHasMin && ntl::IsLess<float>(v, m_fMin))
				v = m_fMin;
			else if (m_bHasMax && ntl::IsGreater<float>(v, m_fMax))
				v = m_fMax;
			m_sValue.Right = v;
			edit->setText(ToStringCompact(v));
		}

		void CDialogBoxRectF::EditBottom_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			float v;
			if (!TryStringToFloat(edit->getText(), v))
				v = m_sValue.Bottom;
			if (m_bHasMin && ntl::IsLess<float>(v, m_fMin))
				v = m_fMin;
			else if (m_bHasMax && ntl::IsGreater<float>(v, m_fMax))
				v = m_fMax;
			m_sValue.Bottom = v;
			edit->setText(ToStringCompact(v));
		}

		void CDialogBoxRectF::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxRectF::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		RectF CDialogBoxRectF::getValue()
		{
			return m_sValue;
		}

		bool CDialogBoxRectF::hasMin()
		{
			return m_bHasMin;
		}

		bool CDialogBoxRectF::hasMax()
		{
			return m_bHasMax;
		}

		float CDialogBoxRectF::getMin()
		{
			return m_fMin;
		}

		float CDialogBoxRectF::getMax()
		{
			return m_fMax;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxRectF::setValue(const RectF &value)
		{
			if (IsNotEqual(value, m_sValue))
			{
				CLockRepaint lock{ this };
				m_sValue = value;
				m_pEditLeft->setText(ToStringCompact(m_sValue.Left));
				m_pEditTop->setText(ToStringCompact(m_sValue.Top));
				m_pEditRight->setText(ToStringCompact(m_sValue.Right));
				m_pEditBottom->setText(ToStringCompact(m_sValue.Bottom));
				return true;
			}
			return false;
		}

		bool CDialogBoxRectF::setHasMin(const bool value)
		{
			if (value != m_bHasMin)
			{
				m_bHasMin = value;
				return true;
			}
			return false;
		}

		bool CDialogBoxRectF::setHasMax(const bool value)
		{
			if (value != m_bHasMax)
			{
				m_bHasMax = value;
				return true;
			}
			return false;
		}

		bool CDialogBoxRectF::setMin(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMin) || !m_bHasMin)
			{
				m_fMin = value;
				m_bHasMin = true;
				return true;
			}
			return false;
		}

		bool CDialogBoxRectF::setMax(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMax) || !m_bHasMax)
			{
				m_fMax = value;
				m_bHasMax = true;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface methods
		void CDialogBoxRectF::ActivateFirstEnabledInput()
		{
			m_pEditLeft->SelectAll();
			m_pEditLeft->setFocus();
		}
	#pragma endregion
	}
}