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
		const String CFormRect::ClassName{ L"FormRect" };

	#pragma region Service
		CFormRect::CFormRectService::CFormRectService(CFormRect *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormRect::CFormRectService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormRect::CFormRect(IWindow *window, IRenderer *renderer) :
			IFormRectProto(window, renderer, ClassName),
			m_sValue{ 0, 0, 0, 0 },
			m_bHasMin{ false },
			m_bHasMax{ false },
			m_iMin{ 0 },
			m_iMax{ 0 }
		{
			setService(new CFormRectService(this), true);
			LoadTranslatableTexts();
		}

		void CFormRect::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Borders(integer)"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormRect::FormRectProto_OnPaint(IForm *sender, const MessagePaint &m, bool &draw_children)
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

		void CFormRect::FormRectProto_OnKeyDown(IForm *sender, const MessageKey &m)
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

		void CFormRect::EditLeft_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			int v;
			if (!TryStringToInt(edit->getText(), v))
				v = m_sValue.Left;
			if (m_bHasMin && v < m_iMin)
				v = m_iMin;
			else if (m_bHasMax && v > m_iMax)
				v = m_iMax;
			m_sValue.Left = v;
			edit->setText(ToString(v));
		}

		void CFormRect::EditTop_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			int v;
			if (!TryStringToInt(edit->getText(), v))
				v = m_sValue.Top;
			if (m_bHasMin && v < m_iMin)
				v = m_iMin;
			else if (m_bHasMax && v > m_iMax)
				v = m_iMax;
			m_sValue.Top = v;
			edit->setText(ToString(v));
		}

		void CFormRect::EditRight_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			int v;
			if (!TryStringToInt(edit->getText(), v))
				v = m_sValue.Right;
			if (m_bHasMin && v < m_iMin)
				v = m_iMin;
			else if (m_bHasMax && v > m_iMax)
				v = m_iMax;
			m_sValue.Right = v;
			edit->setText(ToString(v));
		}

		void CFormRect::EditBottom_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			int v;
			if (!TryStringToInt(edit->getText(), v))
				v = m_sValue.Bottom;
			if (m_bHasMin && v < m_iMin)
				v = m_iMin;
			else if (m_bHasMax && v > m_iMax)
				v = m_iMax;
			m_sValue.Bottom = v;
			edit->setText(ToString(v));
		}

		void CFormRect::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormRect::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		Rect CFormRect::getValue()
		{
			return m_sValue;
		}

		bool CFormRect::hasMin()
		{
			return m_bHasMin;
		}

		bool CFormRect::hasMax()
		{
			return m_bHasMax;
		}

		int CFormRect::getMin()
		{
			return m_iMin;
		}

		int CFormRect::getMax()
		{
			return m_iMax;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormRect::setValue(const Rect &value)
		{
			if (value != m_sValue)
			{
				CLockRepaint lock{ this };
				m_sValue = value;
				m_pEditLeft->setText(ToString(m_sValue.Left));
				m_pEditTop->setText(ToString(m_sValue.Top));
				m_pEditRight->setText(ToString(m_sValue.Right));
				m_pEditBottom->setText(ToString(m_sValue.Bottom));
				return true;
			}
			return false;
		}

		bool CFormRect::setHasMin(const bool value)
		{
			if (value != m_bHasMin)
			{
				m_bHasMin = value;
				return true;
			}
			return false;
		}

		bool CFormRect::setHasMax(const bool value)
		{
			if (value != m_bHasMax)
			{
				m_bHasMax = value;
				return true;
			}
			return false;
		}

		bool CFormRect::setMin(const int value)
		{
			if (value != m_iMin || !m_bHasMin)
			{
				m_iMin = value;
				m_bHasMin = true;
				return true;
			}
			return false;
		}

		bool CFormRect::setMax(const int value)
		{
			if (value != m_iMax || !m_bHasMax)
			{
				m_iMax = value;
				m_bHasMax = true;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface methods
		void CFormRect::ActivateFirstEnabledInput()
		{
			m_pEditLeft->SelectAll();
			m_pEditLeft->setFocus();
		}
	#pragma endregion
	}
}