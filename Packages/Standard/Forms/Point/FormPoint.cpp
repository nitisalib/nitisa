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
		const String CFormPoint::ClassName{ L"FormPoint" };

	#pragma region Service
		CFormPoint::CFormPointService::CFormPointService(CFormPoint *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormPoint::CFormPointService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormPoint::CFormPoint(IWindow *window, IRenderer *renderer) :
			IFormPointProto(window, renderer, ClassName),
			m_sValue{ 0, 0 },
			m_bHasMin{ false },
			m_bHasMax{ false },
			m_iMin{ 0 },
			m_iMax{ 0 }
		{
			setService(new CFormPointService(this), true);
			LoadTranslatableTexts();
		}

		void CFormPoint::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Point(integer)"));
			m_pLabelX->setCaption(Application->Translate->t(ClassName, L"X:"));
			m_pLabelY->setCaption(Application->Translate->t(ClassName, L"Y:"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormPoint::FormPointProto_OnKeyUp(IForm *sender, const MessageKey &m)
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

		void CFormPoint::EditX_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			int v;
			if (!TryStringToInt(edit->getText(), v))
				v = m_sValue.X;
			if (m_bHasMin && v < m_iMin)
				v = m_iMin;
			else if (m_bHasMax && v > m_iMax)
				v = m_iMax;
			m_sValue.X = v;
			edit->setText(ToString(v));
		}

		void CFormPoint::EditY_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			int v;
			if (!TryStringToInt(edit->getText(), v))
				v = m_sValue.Y;
			if (m_bHasMin && v < m_iMin)
				v = m_iMin;
			else if (m_bHasMax && v > m_iMax)
				v = m_iMax;
			m_sValue.Y = v;
			edit->setText(ToString(v));
		}

		void CFormPoint::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormPoint::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		Point CFormPoint::getValue()
		{
			return m_sValue;
		}

		bool CFormPoint::hasMin()
		{
			return m_bHasMin;
		}

		bool CFormPoint::hasMax()
		{
			return m_bHasMax;
		}

		int CFormPoint::getMin()
		{
			return m_iMin;
		}

		int CFormPoint::getMax()
		{
			return m_iMax;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormPoint::setValue(const Point &value)
		{
			if (value != m_sValue)
			{
				CLockRepaint lock{ this };
				m_sValue = value;
				m_pEditX->setText(ToString(m_sValue.X));
				m_pEditY->setText(ToString(m_sValue.Y));
				return true;
			}
			return false;
		}

		bool CFormPoint::setHasMin(const bool value)
		{
			if (value != m_bHasMin)
			{
				m_bHasMin = value;
				return true;
			}
			return false;
		}

		bool CFormPoint::setHasMax(const bool value)
		{
			if (value != m_bHasMax)
			{
				m_bHasMax = value;
				return true;
			}
			return false;
		}

		bool CFormPoint::setMin(const int value)
		{
			if (value != m_iMin || !m_bHasMin)
			{
				m_iMin = value;
				m_bHasMin = true;
				return true;
			}
			return false;
		}

		bool CFormPoint::setMax(const int value)
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
		void CFormPoint::ActivateFirstEnabledInput()
		{
			m_pEditX->SelectAll();
			m_pEditX->setFocus();
		}
	#pragma endregion
	}
}