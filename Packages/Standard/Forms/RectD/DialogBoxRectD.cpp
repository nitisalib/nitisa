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
		const String CDialogBoxRectD::ClassName{ L"DialogBoxRectD" };

	#pragma region Service
		CDialogBoxRectD::CDialogBoxRectDService::CDialogBoxRectDService(CDialogBoxRectD *control) :
			IDialogBoxRectDProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxRectD::CDialogBoxRectDService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
			IDialogBoxRectDProtoService::NotifyOnFreeResources();
		}

		void CDialogBoxRectD::CDialogBoxRectDService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxRectD::CDialogBoxRectD() :
			IDialogBoxRectDProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxRectDService(this)),
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

		CDialogBoxRectD::CDialogBoxRectD(IForm *parent) :CDialogBoxRectD()
		{
			setForm(parent);
		}

		CDialogBoxRectD::CDialogBoxRectD(IControl *parent) : CDialogBoxRectD()
		{
			setParent(parent);
		}

		void CDialogBoxRectD::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Borders(double)"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CDialogBoxRectD::FormRectDProto_OnPaint(IControl *sender, const MessagePaint &m, bool &draw_children)
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

		void CDialogBoxRectD::FormRectDProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
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

		void CDialogBoxRectD::EditLeft_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			double v;
			if (!TryStringToDouble(edit->getText(), v))
				v = m_sValue.Left;
			if (m_bHasMin && ntl::IsLess<double>(v, m_fMin))
				v = m_fMin;
			else if (m_bHasMax && ntl::IsGreater<double>(v, m_fMax))
				v = m_fMax;
			m_sValue.Left = v;
			edit->setText(ToStringCompact(v));
		}

		void CDialogBoxRectD::EditTop_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			double v;
			if (!TryStringToDouble(edit->getText(), v))
				v = m_sValue.Top;
			if (m_bHasMin && ntl::IsLess<double>(v, m_fMin))
				v = m_fMin;
			else if (m_bHasMax && ntl::IsGreater<double>(v, m_fMax))
				v = m_fMax;
			m_sValue.Top = v;
			edit->setText(ToStringCompact(v));
		}

		void CDialogBoxRectD::EditRight_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			double v;
			if (!TryStringToDouble(edit->getText(), v))
				v = m_sValue.Right;
			if (m_bHasMin && ntl::IsLess<double>(v, m_fMin))
				v = m_fMin;
			else if (m_bHasMax && ntl::IsGreater<double>(v, m_fMax))
				v = m_fMax;
			m_sValue.Right = v;
			edit->setText(ToStringCompact(v));
		}

		void CDialogBoxRectD::EditBottom_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			double v;
			if (!TryStringToDouble(edit->getText(), v))
				v = m_sValue.Bottom;
			if (m_bHasMin && ntl::IsLess<double>(v, m_fMin))
				v = m_fMin;
			else if (m_bHasMax && ntl::IsGreater<double>(v, m_fMax))
				v = m_fMax;
			m_sValue.Bottom = v;
			edit->setText(ToStringCompact(v));
		}

		void CDialogBoxRectD::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxRectD::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		RectD CDialogBoxRectD::getValue()
		{
			return m_sValue;
		}

		bool CDialogBoxRectD::hasMin()
		{
			return m_bHasMin;
		}

		bool CDialogBoxRectD::hasMax()
		{
			return m_bHasMax;
		}

		double CDialogBoxRectD::getMin()
		{
			return m_fMin;
		}

		double CDialogBoxRectD::getMax()
		{
			return m_fMax;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxRectD::setValue(const RectD &value)
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

		bool CDialogBoxRectD::setHasMin(const bool value)
		{
			if (value != m_bHasMin)
			{
				m_bHasMin = value;
				return true;
			}
			return false;
		}

		bool CDialogBoxRectD::setHasMax(const bool value)
		{
			if (value != m_bHasMax)
			{
				m_bHasMax = value;
				return true;
			}
			return false;
		}

		bool CDialogBoxRectD::setMin(const double value)
		{
			if (ntl::IsNotEqual<double>(value, m_fMin) || !m_bHasMin)
			{
				m_fMin = value;
				m_bHasMin = true;
				return true;
			}
			return false;
		}

		bool CDialogBoxRectD::setMax(const double value)
		{
			if (ntl::IsNotEqual<double>(value, m_fMax) || !m_bHasMax)
			{
				m_fMax = value;
				m_bHasMax = true;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface methods
		void CDialogBoxRectD::ActivateFirstEnabledInput()
		{
			m_pEditLeft->SelectAll();
			m_pEditLeft->setFocus();
		}
	#pragma endregion
	}
}