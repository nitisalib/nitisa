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
		const String CFormTransform::ClassName{ L"FormTransform" };

	#pragma region Service
		CFormTransform::CFormTransformService::CFormTransformService(CFormTransform *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormTransform::CFormTransformService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormTransform::CFormTransform(IWindow *window, IRenderer *renderer) :
			IFormTransformProto(window, renderer, ClassName),
			m_sValue{ 0, 0, 0, 1, 1, 1, 0, 0, 0, RotateOrder::XYZ, TransformOrder::RST },
			m_bTx{ true },
			m_bTy{ true },
			m_bTz{ true },
			m_bRx{ true },
			m_bRy{ true },
			m_bRz{ true },
			m_bSx{ true },
			m_bSy{ true },
			m_bSz{ true },
			m_bRotateOrder{ true },
			m_bTransformOrder{ true },
			m_bMinTx{ false },
			m_bMinTy{ false },
			m_bMinTz{ false },
			m_bMinRx{ false },
			m_bMinRy{ false },
			m_bMinRz{ false },
			m_bMinSx{ false },
			m_bMinSy{ false },
			m_bMinSz{ false },
			m_bMaxTx{ false },
			m_bMaxTy{ false },
			m_bMaxTz{ false },
			m_bMaxRx{ false },
			m_bMaxRy{ false },
			m_bMaxRz{ false },
			m_bMaxSx{ false },
			m_bMaxSy{ false },
			m_bMaxSz{ false },
			m_fMinTx{ 0 },
			m_fMinTy{ 0 },
			m_fMinTz{ 0 },
			m_fMinRx{ 0 },
			m_fMinRy{ 0 },
			m_fMinRz{ 0 },
			m_fMinSx{ 0 },
			m_fMinSy{ 0 },
			m_fMinSz{ 0 },
			m_fMaxTx{ 0 },
			m_fMaxTy{ 0 },
			m_fMaxTz{ 0 },
			m_fMaxRx{ 0 },
			m_fMaxRy{ 0 },
			m_fMaxRz{ 0 },
			m_fMaxSx{ 0 },
			m_fMaxSy{ 0 },
			m_fMaxSz{ 0 }
		{
			setService(new CFormTransformService(this), true);
			CLockRepaint lock{ this };
			InitControls();
			LoadTranslatableTexts();
		}

		void CFormTransform::InitControls()
		{
			auto ro_items{ RotateOrderItems() };
			for (auto pos : ro_items)
				m_pDropDownRO->Add(pos);
			m_pDropDownRO->setActiveIndex((int)m_sValue.RotateOrder);
			m_pDropDownRO->setOpenDirection(CBuiltInDropDown::OpenDirection::Up);

			auto to_items{ TransformOrderItems() };
			for (auto pos : to_items)
				m_pDropDownTO->Add(pos);
			m_pDropDownTO->setActiveIndex((int)m_sValue.TransformOrder);
			m_pDropDownTO->setOpenDirection(CBuiltInDropDown::OpenDirection::Up);
		}

		void CFormTransform::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Transform"));
			m_pGroupBoxT->setCaption(Application->Translate->t(ClassName, L"Translate"));
			m_pGroupBoxS->setCaption(Application->Translate->t(ClassName, L"Scale"));
			m_pGroupBoxR->setCaption(Application->Translate->t(ClassName, L"Rotate"));
			m_pGroupBoxO->setCaption(Application->Translate->t(ClassName, L"Orders"));
			m_pLabelTx->setCaption(Application->Translate->t(ClassName, L"X:"));
			m_pLabelTy->setCaption(Application->Translate->t(ClassName, L"Y:"));
			m_pLabelTz->setCaption(Application->Translate->t(ClassName, L"Z:"));
			m_pLabelSx->setCaption(Application->Translate->t(ClassName, L"X:"));
			m_pLabelSy->setCaption(Application->Translate->t(ClassName, L"Y:"));
			m_pLabelSz->setCaption(Application->Translate->t(ClassName, L"Z:"));
			m_pLabelRx->setCaption(Application->Translate->t(ClassName, L"X:"));
			m_pLabelRy->setCaption(Application->Translate->t(ClassName, L"Y:"));
			m_pLabelRz->setCaption(Application->Translate->t(ClassName, L"Z:"));
			m_pLabelRO->setCaption(Application->Translate->t(ClassName, L"Rotate:"));
			m_pLabelTO->setCaption(Application->Translate->t(ClassName, L"Transform:"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormTransform::FormTransformProto_OnKeyUp(IForm *sender, const MessageKey &m)
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

		void CFormTransform::EditTx_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			float v;
			if (!TryStringToFloat(edit->getText(), v))
				v = m_sValue.Tx;
			if (m_bMinTx && ntl::IsLess<float>(v, m_fMinTx))
				v = m_fMinTx;
			else if (m_bMaxTx && ntl::IsGreater<float>(v, m_fMaxTx))
				v = m_fMaxTx;
			m_sValue.Tx = v;
			edit->setText(ToStringCompact(v));
		}

		void CFormTransform::EditTy_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			float v;
			if (!TryStringToFloat(edit->getText(), v))
				v = m_sValue.Ty;
			if (m_bMinTy && ntl::IsLess<float>(v, m_fMinTy))
				v = m_fMinTy;
			else if (m_bMaxTy && ntl::IsGreater<float>(v, m_fMaxTy))
				v = m_fMaxTy;
			m_sValue.Ty = v;
			edit->setText(ToStringCompact(v));
		}

		void CFormTransform::EditTz_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			float v;
			if (!TryStringToFloat(edit->getText(), v))
				v = m_sValue.Tz;
			if (m_bMinTz && ntl::IsLess<float>(v, m_fMinTz))
				v = m_fMinTz;
			else if (m_bMaxTz && ntl::IsGreater<float>(v, m_fMaxTz))
				v = m_fMaxTz;
			m_sValue.Tz = v;
			edit->setText(ToStringCompact(v));
		}

		void CFormTransform::EditSx_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			float v;
			if (!TryStringToFloat(edit->getText(), v))
				v = m_sValue.Sx;
			if (m_bMinSx && ntl::IsLess<float>(v, m_fMinSx))
				v = m_fMinSx;
			else if (m_bMaxSx && ntl::IsGreater<float>(v, m_fMaxSx))
				v = m_fMaxSx;
			m_sValue.Sx = v;
			edit->setText(ToStringCompact(v));
		}

		void CFormTransform::EditSy_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			float v;
			if (!TryStringToFloat(edit->getText(), v))
				v = m_sValue.Sy;
			if (m_bMinSy && ntl::IsLess<float>(v, m_fMinSy))
				v = m_fMinSy;
			else if (m_bMaxSy && ntl::IsGreater<float>(v, m_fMaxSy))
				v = m_fMaxSy;
			m_sValue.Sy = v;
			edit->setText(ToStringCompact(v));
		}

		void CFormTransform::EditSz_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			float v;
			if (!TryStringToFloat(edit->getText(), v))
				v = m_sValue.Sz;
			if (m_bMinSz && ntl::IsLess<float>(v, m_fMinSz))
				v = m_fMinSz;
			else if (m_bMaxSz && ntl::IsGreater<float>(v, m_fMaxSz))
				v = m_fMaxSz;
			m_sValue.Sz = v;
			edit->setText(ToStringCompact(v));
		}

		void CFormTransform::EditRx_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			float v;
			if (!TryStringToFloat(edit->getText(), v))
				v = m_sValue.Rx;
			if (m_bMinRx && ntl::IsLess<float>(v, m_fMinRx))
				v = m_fMinRx;
			else if (m_bMaxRx && ntl::IsGreater<float>(v, m_fMaxRx))
				v = m_fMaxRx;
			m_sValue.Rx = v;
			edit->setText(ToStringCompact(v));
		}

		void CFormTransform::EditRy_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			float v;
			if (!TryStringToFloat(edit->getText(), v))
				v = m_sValue.Ry;
			if (m_bMinRy && ntl::IsLess<float>(v, m_fMinRy))
				v = m_fMinRy;
			else if (m_bMaxRy && ntl::IsGreater<float>(v, m_fMaxRy))
				v = m_fMaxRy;
			m_sValue.Ry = v;
			edit->setText(ToStringCompact(v));
		}

		void CFormTransform::EditRz_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			float v;
			if (!TryStringToFloat(edit->getText(), v))
				v = m_sValue.Rz;
			if (m_bMinRz && ntl::IsLess<float>(v, m_fMinRz))
				v = m_fMinRz;
			else if (m_bMaxRz && ntl::IsGreater<float>(v, m_fMaxRz))
				v = m_fMaxRz;
			m_sValue.Rz = v;
			edit->setText(ToStringCompact(v));
		}

		void CFormTransform::DropDownRO_OnSelect(IControl *sender, const int index)
		{
			m_sValue.RotateOrder = (RotateOrder)index;
		}

		void CFormTransform::DropDownTO_OnSelect(IControl *sender, const int index)
		{
			m_sValue.TransformOrder = (TransformOrder)index;
		}

		void CFormTransform::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormTransform::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		Transform CFormTransform::getValue()
		{
			return m_sValue;
		}

		bool CFormTransform::isAllowedTx() const
		{
			return m_bTx;
		}

		bool CFormTransform::isAllowedTy() const
		{
			return m_bTy;
		}

		bool CFormTransform::isAllowedTz() const
		{
			return m_bTz;
		}

		bool CFormTransform::isAllowedSx() const
		{
			return m_bSx;
		}

		bool CFormTransform::isAllowedSy() const
		{
			return m_bSy;
		}

		bool CFormTransform::isAllowedSz() const
		{
			return m_bSz;
		}

		bool CFormTransform::isAllowedRx() const
		{
			return m_bRx;
		}

		bool CFormTransform::isAllowedRy() const
		{
			return m_bRy;
		}

		bool CFormTransform::isAllowedRz() const
		{
			return m_bRz;
		}

		bool CFormTransform::isAllowedRotateOrder() const
		{
			return m_bRotateOrder;
		}

		bool CFormTransform::isAllowedTransformOrder() const
		{
			return m_bTransformOrder;
		}

		bool CFormTransform::hasMinTx() const
		{
			return m_bMinTx;
		}

		bool CFormTransform::hasMinTy() const
		{
			return m_bMinTy;
		}

		bool CFormTransform::hasMinTz() const
		{
			return m_bMinTz;
		}

		bool CFormTransform::hasMinSx() const
		{
			return m_bMinSx;
		}

		bool CFormTransform::hasMinSy() const
		{
			return m_bMinSy;
		}

		bool CFormTransform::hasMinSz() const
		{
			return m_bMinSz;
		}

		bool CFormTransform::hasMinRx() const
		{
			return m_bMinRx;
		}

		bool CFormTransform::hasMinRy() const
		{
			return m_bMinRy;
		}

		bool CFormTransform::hasMinRz() const
		{
			return m_bMinRz;
		}

		bool CFormTransform::hasMaxTx() const
		{
			return m_bMaxTx;
		}

		bool CFormTransform::hasMaxTy() const
		{
			return m_bMaxTy;
		}

		bool CFormTransform::hasMaxTz() const
		{
			return m_bMaxTz;
		}

		bool CFormTransform::hasMaxSx() const
		{
			return m_bMaxSx;
		}

		bool CFormTransform::hasMaxSy() const
		{
			return m_bMaxSy;
		}

		bool CFormTransform::hasMaxSz() const
		{
			return m_bMaxSz;
		}

		bool CFormTransform::hasMaxRx() const
		{
			return m_bMaxRx;
		}

		bool CFormTransform::hasMaxRy() const
		{
			return m_bMaxRy;
		}

		bool CFormTransform::hasMaxRz() const
		{
			return m_bMaxRz;
		}

		float CFormTransform::getMinTx() const
		{
			return m_fMinTx;
		}

		float CFormTransform::getMinTy() const
		{
			return m_fMinTy;
		}

		float CFormTransform::getMinTz() const
		{
			return m_fMinTz;
		}

		float CFormTransform::getMinSx() const
		{
			return m_fMinSx;
		}

		float CFormTransform::getMinSy() const
		{
			return m_fMinSy;
		}

		float CFormTransform::getMinSz() const
		{
			return m_fMinSz;
		}

		float CFormTransform::getMinRx() const
		{
			return m_fMinRx;
		}

		float CFormTransform::getMinRy() const
		{
			return m_fMinRy;
		}

		float CFormTransform::getMinRz() const
		{
			return m_fMinRz;
		}

		float CFormTransform::getMaxTx() const
		{
			return m_fMaxTx;
		}

		float CFormTransform::getMaxTy() const
		{
			return m_fMaxTy;
		}

		float CFormTransform::getMaxTz() const
		{
			return m_fMaxTz;
		}

		float CFormTransform::getMaxSx() const
		{
			return m_fMaxSx;
		}

		float CFormTransform::getMaxSy() const
		{
			return m_fMaxSy;
		}

		float CFormTransform::getMaxSz() const
		{
			return m_fMaxSz;
		}

		float CFormTransform::getMaxRx() const
		{
			return m_fMaxRx;
		}

		float CFormTransform::getMaxRy() const
		{
			return m_fMaxRy;
		}

		float CFormTransform::getMaxRz() const
		{
			return m_fMaxRz;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormTransform::setValue(const Transform &value)
		{
			if (IsNotEqual(value, m_sValue))
			{
				CLockRepaint lock{ this };
				m_sValue = value;
				m_pEditTx->setText(ToStringCompact(m_sValue.Tx));
				m_pEditTy->setText(ToStringCompact(m_sValue.Ty));
				m_pEditTz->setText(ToStringCompact(m_sValue.Tz));
				m_pEditSx->setText(ToStringCompact(m_sValue.Sx));
				m_pEditSy->setText(ToStringCompact(m_sValue.Sy));
				m_pEditSz->setText(ToStringCompact(m_sValue.Sz));
				m_pEditRx->setText(ToStringCompact(m_sValue.Rx));
				m_pEditRy->setText(ToStringCompact(m_sValue.Ry));
				m_pEditRz->setText(ToStringCompact(m_sValue.Rz));
				m_pDropDownRO->setActiveIndex((int)m_sValue.RotateOrder);
				m_pDropDownTO->setActiveIndex((int)m_sValue.TransformOrder);
				return true;
			}
			return false;
		}

		bool CFormTransform::setAllowedTx(const bool value)
		{
			if (value != m_bTx)
			{
				m_bTx = value;
				m_pEditTx->setEnabled(value);
				return true;
			}
			return false;
		}

		bool CFormTransform::setAllowedTy(const bool value)
		{
			if (value != m_bTy)
			{
				m_bTy = value;
				m_pEditTy->setEnabled(value);
				return true;
			}
			return false;
		}

		bool CFormTransform::setAllowedTz(const bool value)
		{
			if (value != m_bTz)
			{
				m_bTz = value;
				m_pEditTz->setEnabled(value);
				return true;
			}
			return false;
		}

		bool CFormTransform::setAllowedSx(const bool value)
		{
			if (value != m_bSx)
			{
				m_bSx = value;
				m_pEditSx->setEnabled(value);
				return true;
			}
			return false;
		}

		bool CFormTransform::setAllowedSy(const bool value)
		{
			if (value != m_bSy)
			{
				m_bSy = value;
				m_pEditSy->setEnabled(value);
				return true;
			}
			return false;
		}

		bool CFormTransform::setAllowedSz(const bool value)
		{
			if (value != m_bSz)
			{
				m_bSz = value;
				m_pEditSz->setEnabled(value);
				return true;
			}
			return false;
		}

		bool CFormTransform::setAllowedRx(const bool value)
		{
			if (value != m_bRx)
			{
				m_bRx = value;
				m_pEditRx->setEnabled(value);
				return true;
			}
			return false;
		}

		bool CFormTransform::setAllowedRy(const bool value)
		{
			if (value != m_bRy)
			{
				m_bRy = value;
				m_pEditRy->setEnabled(value);
				return true;
			}
			return false;
		}

		bool CFormTransform::setAllowedRz(const bool value)
		{
			if (value != m_bRz)
			{
				m_bRz = value;
				m_pEditRz->setEnabled(value);
				return true;
			}
			return false;
		}

		bool CFormTransform::setAllowedRotateOrder(const bool value)
		{
			if (value != m_bRotateOrder)
			{
				m_bRotateOrder = value;
				m_pDropDownRO->setEnabled(value);
				return true;
			}
			return false;
		}

		bool CFormTransform::setAllowedTransformOrder(const bool value)
		{
			if (value != m_bTransformOrder)
			{
				m_bTransformOrder = value;
				m_pDropDownTO->setEnabled(value);
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMinTx(const bool value)
		{
			if (value != m_bMinTx)
			{
				m_bMinTx = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMinTy(const bool value)
		{
			if (value != m_bMinTy)
			{
				m_bMinTy = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMinTz(const bool value)
		{
			if (value != m_bMinTz)
			{
				m_bMinTz = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMinSx(const bool value)
		{
			if (value != m_bMinSx)
			{
				m_bMinSx = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMinSy(const bool value)
		{
			if (value != m_bMinSy)
			{
				m_bMinSy = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMinSz(const bool value)
		{
			if (value != m_bMinSz)
			{
				m_bMinSz = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMinRx(const bool value)
		{
			if (value != m_bMinRx)
			{
				m_bMinRx = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMinRy(const bool value)
		{
			if (value != m_bMinRy)
			{
				m_bMinRy = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMinRz(const bool value)
		{
			if (value != m_bMinRz)
			{
				m_bMinRz = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMaxTx(const bool value)
		{
			if (value != m_bMaxTx)
			{
				m_bMaxTx = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMaxTy(const bool value)
		{
			if (value != m_bMaxTy)
			{
				m_bMaxTy = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMaxTz(const bool value)
		{
			if (value != m_bMaxTz)
			{
				m_bMaxTz = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMaxSx(const bool value)
		{
			if (value != m_bMaxSx)
			{
				m_bMaxSx = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMaxSy(const bool value)
		{
			if (value != m_bMaxSy)
			{
				m_bMaxSy = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMaxSz(const bool value)
		{
			if (value != m_bMaxSz)
			{
				m_bMaxSz = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMaxRx(const bool value)
		{
			if (value != m_bMaxRx)
			{
				m_bMaxRx = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMaxRy(const bool value)
		{
			if (value != m_bMaxRy)
			{
				m_bMaxRy = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setHasMaxRz(const bool value)
		{
			if (value != m_bMaxRz)
			{
				m_bMaxRz = value;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMinTx(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMinTx) || !m_bMinTx)
			{
				m_fMinTx = value;
				m_bMinTx = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMinTy(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMinTy) || !m_bMinTy)
			{
				m_fMinTy = value;
				m_bMinTy = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMinTz(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMinTz) || !m_bMinTz)
			{
				m_fMinTz = value;
				m_bMinTz = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMinSx(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMinSx) || !m_bMinSx)
			{
				m_fMinSx = value;
				m_bMinSx = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMinSy(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMinSy) || !m_bMinSy)
			{
				m_fMinSy = value;
				m_bMinSy = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMinSz(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMinSz) || !m_bMinSz)
			{
				m_fMinSz = value;
				m_bMinSz = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMinRx(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMinRx) || !m_bMinRx)
			{
				m_fMinRx = value;
				m_bMinRx = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMinRy(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMinRy) || !m_bMinRy)
			{
				m_fMinRy = value;
				m_bMinRy = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMinRz(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMinRz) || !m_bMinRz)
			{
				m_fMinRz = value;
				m_bMinRz = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMaxTx(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMaxTx) || !m_bMaxTx)
			{
				m_fMaxTx = value;
				m_bMaxTx = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMaxTy(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMaxTy) || !m_bMaxTy)
			{
				m_fMaxTy = value;
				m_bMaxTy = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMaxTz(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMaxTz) || !m_bMaxTz)
			{
				m_fMaxTz = value;
				m_bMaxTz = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMaxSx(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMaxSx) || !m_bMaxSx)
			{
				m_fMaxSx = value;
				m_bMaxSx = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMaxSy(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMaxSy) || !m_bMaxSy)
			{
				m_fMaxSy = value;
				m_bMaxSy = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMaxSz(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMaxSz) || !m_bMaxSz)
			{
				m_fMaxSz = value;
				m_bMaxSz = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMaxRx(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMaxRx) || !m_bMaxRx)
			{
				m_fMaxRx = value;
				m_bMaxRx = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMaxRy(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMaxRy) || !m_bMaxRy)
			{
				m_fMaxRy = value;
				m_bMaxRy = true;
				return true;
			}
			return false;
		}

		bool CFormTransform::setMaxRz(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fMaxRz) || !m_bMaxRz)
			{
				m_fMaxRz = value;
				m_bMaxRz = true;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface methods
		void CFormTransform::ActivateFirstEnabledInput()
		{
			if (m_pEditTx->isEnabled(false))
			{
				m_pEditTx->SelectAll();
				m_pEditTx->setFocus();
			}
			else if (m_pEditTy->isEnabled(false))
			{
				m_pEditTy->SelectAll();
				m_pEditTy->setFocus();
			}
			else if (m_pEditTz->isEnabled(false))
			{
				m_pEditTz->SelectAll();
				m_pEditTz->setFocus();
			}
			else if (m_pEditSx->isEnabled(false))
			{
				m_pEditSx->SelectAll();
				m_pEditSx->setFocus();
			}
			else if (m_pEditSy->isEnabled(false))
			{
				m_pEditSy->SelectAll();
				m_pEditSy->setFocus();
			}
			else if (m_pEditSz->isEnabled(false))
			{
				m_pEditSz->SelectAll();
				m_pEditSz->setFocus();
			}
			else if (m_pEditRx->isEnabled(false))
			{
				m_pEditRx->SelectAll();
				m_pEditRx->setFocus();
			}
			else if (m_pEditRy->isEnabled(false))
			{
				m_pEditRy->SelectAll();
				m_pEditRy->setFocus();
			}
			else if (m_pEditRz->isEnabled(false))
			{
				m_pEditRz->SelectAll();
				m_pEditRz->setFocus();
			}
		}
	#pragma endregion
	}
}