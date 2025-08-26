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
		const String CFormRectD::ClassName{ L"FormRectD" };

	#pragma region Service
		CFormRectD::CFormRectDService::CFormRectDService(CFormRectD *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormRectD::CFormRectDService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormRectD::CFormRectD(IWindow *window, IRenderer *renderer) :
			IFormRectDProto(window, renderer, ClassName),
			m_sValue{ 0, 0, 0, 0 },
			m_bHasMin{ false },
			m_bHasMax{ false },
			m_fMin{ 0 },
			m_fMax{ 0 }
		{
			setService(new CFormRectDService(this), true);
			LoadTranslatableTexts();
		}

		void CFormRectD::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Borders(double)"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormRectD::FormRectDProto_OnPaint(IForm *sender, const MessagePaint &m, bool &draw_children)
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

		void CFormRectD::FormRectDProto_OnKeyUp(IForm *sender, const MessageKey &m)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if (m.Key == Key::Return || m.Key == Key::Separator)
			{
				CEdit *edit{ cast<CEdit*>(getFocusedControl()) };
				if (edit)
					edit->OnKillFocus(edit);
				setModalResult(ModalResult::Ok);
			}
		}

		void CFormRectD::EditLeft_OnKillFocus(IControl *sender)
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

		void CFormRectD::EditTop_OnKillFocus(IControl *sender)
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

		void CFormRectD::EditRight_OnKillFocus(IControl *sender)
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

		void CFormRectD::EditBottom_OnKillFocus(IControl *sender)
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

		void CFormRectD::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormRectD::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		RectD CFormRectD::getValue()
		{
			return m_sValue;
		}

		bool CFormRectD::hasMin()
		{
			return m_bHasMin;
		}

		bool CFormRectD::hasMax()
		{
			return m_bHasMax;
		}

		double CFormRectD::getMin()
		{
			return m_fMin;
		}

		double CFormRectD::getMax()
		{
			return m_fMax;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormRectD::setValue(const RectD &value)
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

		bool CFormRectD::setHasMin(const bool value)
		{
			if (value != m_bHasMin)
			{
				m_bHasMin = value;
				return true;
			}
			return false;
		}

		bool CFormRectD::setHasMax(const bool value)
		{
			if (value != m_bHasMax)
			{
				m_bHasMax = value;
				return true;
			}
			return false;
		}

		bool CFormRectD::setMin(const double value)
		{
			if (ntl::IsNotEqual<double>(value, m_fMin) || !m_bHasMin)
			{
				m_fMin = value;
				m_bHasMin = true;
				return true;
			}
			return false;
		}

		bool CFormRectD::setMax(const double value)
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
		void CFormRectD::ActivateFirstEnabledInput()
		{
			m_pEditLeft->SelectAll();
			m_pEditLeft->setFocus();
		}
	#pragma endregion
	}
}