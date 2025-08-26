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
		const String CFormPointL::ClassName{ L"FormPointL" };

	#pragma region Service
		CFormPointL::CFormPointLService::CFormPointLService(CFormPointL *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormPointL::CFormPointLService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormPointL::CFormPointL(IWindow *window, IRenderer *renderer) :
			IFormPointLProto(window, renderer, ClassName),
			m_sValue{ 0, 0 },
			m_bHasMin{ false },
			m_bHasMax{ false },
			m_iMin{ 0 },
			m_iMax{ 0 }
		{
			setService(new CFormPointLService(this), true);
			LoadTranslatableTexts();
		}

		void CFormPointL::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Point(64-bit integer)"));
			m_pLabelX->setCaption(Application->Translate->t(ClassName, L"X:"));
			m_pLabelY->setCaption(Application->Translate->t(ClassName, L"Y:"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormPointL::FormPointLProto_OnKeyUp(IForm *sender, const MessageKey &m)
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

		void CFormPointL::EditX_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			long long v;
			if (!TryStringToInt64(edit->getText(), v))
				v = m_sValue.X;
			if (m_bHasMin && v < m_iMin)
				v = m_iMin;
			else if (m_bHasMax && v > m_iMax)
				v = m_iMax;
			m_sValue.X = v;
			edit->setText(ToString(v));
		}

		void CFormPointL::EditY_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			long long v;
			if (!TryStringToInt64(edit->getText(), v))
				v = m_sValue.Y;
			if (m_bHasMin && v < m_iMin)
				v = m_iMin;
			else if (m_bHasMax && v > m_iMax)
				v = m_iMax;
			m_sValue.Y = v;
			edit->setText(ToString(v));
		}

		void CFormPointL::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormPointL::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		PointL CFormPointL::getValue()
		{
			return m_sValue;
		}

		bool CFormPointL::hasMin()
		{
			return m_bHasMin;
		}

		bool CFormPointL::hasMax()
		{
			return m_bHasMax;
		}

		long long CFormPointL::getMin()
		{
			return m_iMin;
		}

		long long CFormPointL::getMax()
		{
			return m_iMax;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormPointL::setValue(const PointL &value)
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

		bool CFormPointL::setHasMin(const bool value)
		{
			if (value != m_bHasMin)
			{
				m_bHasMin = value;
				return true;
			}
			return false;
		}

		bool CFormPointL::setHasMax(const bool value)
		{
			if (value != m_bHasMax)
			{
				m_bHasMax = value;
				return true;
			}
			return false;
		}

		bool CFormPointL::setMin(const long long value)
		{
			if (value != m_iMin || !m_bHasMin)
			{
				m_iMin = value;
				m_bHasMin = true;
				return true;
			}
			return false;
		}

		bool CFormPointL::setMax(const long long value)
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
		void CFormPointL::ActivateFirstEnabledInput()
		{
			m_pEditX->SelectAll();
			m_pEditX->setFocus();
		}
	#pragma endregion
	}
}