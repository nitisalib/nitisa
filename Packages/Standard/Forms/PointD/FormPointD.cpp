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
		const String CFormPointD::ClassName{ L"FormPointD" };

	#pragma region Service
		CFormPointD::CFormPointDService::CFormPointDService(CFormPointD *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormPointD::CFormPointDService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormPointD::CFormPointD(IWindow *window, IRenderer *renderer) :
			IFormPointDProto(window, renderer, ClassName),
			m_sValue{ 0, 0 },
			m_bHasMin{ false },
			m_bHasMax{ false },
			m_fMin{ 0 },
			m_fMax{ 0 }
		{
			setService(new CFormPointDService(this), true);
			LoadTranslatableTexts();
		}

		void CFormPointD::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Point(double)"));
			m_pLabelX->setCaption(Application->Translate->t(ClassName, L"X:"));
			m_pLabelY->setCaption(Application->Translate->t(ClassName, L"Y:"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormPointD::FormPointDProto_OnKeyUp(IForm *sender, const MessageKey &m)
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

		void CFormPointD::EditX_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			double v;
			if (!TryStringToDouble(edit->getText(), v))
				v = m_sValue.X;
			if (m_bHasMin && ntl::IsLess<double>(v, m_fMin))
				v = m_fMin;
			else if (m_bHasMax && ntl::IsGreater<double>(v, m_fMax))
				v = m_fMax;
			m_sValue.X = v;
			edit->setText(ToStringCompact(v));
		}

		void CFormPointD::EditY_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			double v;
			if (!TryStringToDouble(edit->getText(), v))
				v = m_sValue.Y;
			if (m_bHasMin && ntl::IsLess<double>(v, m_fMin))
				v = m_fMin;
			else if (m_bHasMax && ntl::IsGreater<double>(v, m_fMax))
				v = m_fMax;
			m_sValue.Y = v;
			edit->setText(ToStringCompact(v));
		}

		void CFormPointD::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormPointD::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		PointD CFormPointD::getValue()
		{
			return m_sValue;
		}

		bool CFormPointD::hasMin()
		{
			return m_bHasMin;
		}

		bool CFormPointD::hasMax()
		{
			return m_bHasMax;
		}

		double CFormPointD::getMin()
		{
			return m_fMin;
		}

		double CFormPointD::getMax()
		{
			return m_fMax;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormPointD::setValue(const PointD &value)
		{
			if (IsNotEqual(value, m_sValue))
			{
				CLockRepaint lock{ this };
				m_sValue = value;
				m_pEditX->setText(ToStringCompact(m_sValue.X));
				m_pEditY->setText(ToStringCompact(m_sValue.Y));
				return true;
			}
			return false;
		}

		bool CFormPointD::setHasMin(const bool value)
		{
			if (value != m_bHasMin)
			{
				m_bHasMin = value;
				return true;
			}
			return false;
		}

		bool CFormPointD::setHasMax(const bool value)
		{
			if (value != m_bHasMax)
			{
				m_bHasMax = value;
				return true;
			}
			return false;
		}

		bool CFormPointD::setMin(const double value)
		{
			if (ntl::IsNotEqual<double>(value, m_fMin) || !m_bHasMin)
			{
				m_fMin = value;
				m_bHasMin = true;
				return true;
			}
			return false;
		}

		bool CFormPointD::setMax(const double value)
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
		void CFormPointD::ActivateFirstEnabledInput()
		{
			m_pEditX->SelectAll();
			m_pEditX->setFocus();
		}
	#pragma endregion
	}
}