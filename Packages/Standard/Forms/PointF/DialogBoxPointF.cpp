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
		const String CDialogBoxPointF::ClassName{ L"DialogBoxPointF" };

	#pragma region Service
		CDialogBoxPointF::CDialogBoxPointFService::CDialogBoxPointFService(CDialogBoxPointF *control) :
			IDialogBoxPointFProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxPointF::CDialogBoxPointFService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxPointF::CDialogBoxPointF() :
			IDialogBoxPointFProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxPointFService(this)),
			m_sValue{ 0, 0 },
			m_bHasMin{ false },
			m_bHasMax{ false },
			m_fMin{ 0 },
			m_fMax{ 0 }
		{
			setStaticTabOrder(true);
			setUseMask(false);
			LoadTranslatableTexts();
		}

		CDialogBoxPointF::CDialogBoxPointF(IForm *parent) :CDialogBoxPointF()
		{
			setForm(parent);
		}

		CDialogBoxPointF::CDialogBoxPointF(IControl *parent) : CDialogBoxPointF()
		{
			setParent(parent);
		}

		void CDialogBoxPointF::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Point(float)"));
			m_pLabelX->setCaption(Application->Translate->t(ClassName, L"X:"));
			m_pLabelY->setCaption(Application->Translate->t(ClassName, L"Y:"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CDialogBoxPointF::FormPointFProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
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

		void CDialogBoxPointF::EditX_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			float v;
			if (!TryStringToFloat(edit->getText(), v))
				v = m_sValue.X;
			if (m_bHasMin && ntl::IsLess<float>(v, m_fMin))
				v = m_fMin;
			else if (m_bHasMax && ntl::IsGreater<float>(v, m_fMax))
				v = m_fMax;
			m_sValue.X = v;
			edit->setText(ToStringCompact(v));
		}

		void CDialogBoxPointF::EditY_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			float v;
			if (!TryStringToFloat(edit->getText(), v))
				v = m_sValue.Y;
			if (m_bHasMin && ntl::IsLess<float>(v, m_fMin))
				v = m_fMin;
			else if (m_bHasMax && ntl::IsGreater<float>(v, m_fMax))
				v = m_fMax;
			m_sValue.Y = v;
			edit->setText(ToStringCompact(v));
		}

		void CDialogBoxPointF::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxPointF::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		PointF CDialogBoxPointF::getValue()
		{
			return m_sValue;
		}

		bool CDialogBoxPointF::hasMin()
		{
			return m_bHasMin;
		}

		bool CDialogBoxPointF::hasMax()
		{
			return m_bHasMax;
		}

		float CDialogBoxPointF::getMin()
		{
			return m_fMin;
		}

		float CDialogBoxPointF::getMax()
		{
			return m_fMax;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxPointF::setValue(const PointF &value)
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

		bool CDialogBoxPointF::setHasMin(const bool value)
		{
			if (value != m_bHasMin)
			{
				m_bHasMin = value;
				return true;
			}
			return false;
		}

		bool CDialogBoxPointF::setHasMax(const bool value)
		{
			if (value != m_bHasMax)
			{
				m_bHasMax = value;
				return true;
			}
			return false;
		}

		bool CDialogBoxPointF::setMin(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMin) || !m_bHasMin)
			{
				m_fMin = value;
				m_bHasMin = true;
				return true;
			}
			return false;
		}

		bool CDialogBoxPointF::setMax(const float value)
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
		void CDialogBoxPointF::ActivateFirstEnabledInput()
		{
			m_pEditX->SelectAll();
			m_pEditX->setFocus();
		}
	#pragma endregion
	}
}