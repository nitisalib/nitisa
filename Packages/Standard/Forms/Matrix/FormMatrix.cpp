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
		const String CFormMatrix::ClassName{ L"FormMatrix" };

	#pragma region Service
		CFormMatrix::CFormMatrixService::CFormMatrixService(CFormMatrix *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormMatrix::CFormMatrixService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormMatrix::CFormMatrix(IWindow *window, IRenderer *renderer) :
			IFormMatrixProto(window, renderer, ClassName),
			m_sMatrix{ Identity }
		{
			setService(new CFormMatrixService(this), true);
			CLockRepaint lock{ this };
			InitControls();
			LoadTranslatableTexts();
		}

		void CFormMatrix::InitControls()
		{
			m_pEdit00->Tag[L"x"] = 0; m_pEdit00->Tag[L"y"] = 0;
			m_pEdit10->Tag[L"x"] = 1; m_pEdit10->Tag[L"y"] = 0;
			m_pEdit20->Tag[L"x"] = 2; m_pEdit20->Tag[L"y"] = 0;
			m_pEdit30->Tag[L"x"] = 3; m_pEdit30->Tag[L"y"] = 0;

			m_pEdit01->Tag[L"x"] = 0; m_pEdit01->Tag[L"y"] = 1;
			m_pEdit11->Tag[L"x"] = 1; m_pEdit11->Tag[L"y"] = 1;
			m_pEdit21->Tag[L"x"] = 2; m_pEdit21->Tag[L"y"] = 1;
			m_pEdit31->Tag[L"x"] = 3; m_pEdit31->Tag[L"y"] = 1;

			m_pEdit02->Tag[L"x"] = 0; m_pEdit02->Tag[L"y"] = 2;
			m_pEdit12->Tag[L"x"] = 1; m_pEdit12->Tag[L"y"] = 2;
			m_pEdit22->Tag[L"x"] = 2; m_pEdit22->Tag[L"y"] = 2;
			m_pEdit32->Tag[L"x"] = 3; m_pEdit32->Tag[L"y"] = 2;

			m_pEdit03->Tag[L"x"] = 0; m_pEdit03->Tag[L"y"] = 3;
			m_pEdit13->Tag[L"x"] = 1; m_pEdit13->Tag[L"y"] = 3;
			m_pEdit23->Tag[L"x"] = 2; m_pEdit23->Tag[L"y"] = 3;
			m_pEdit33->Tag[L"x"] = 3; m_pEdit33->Tag[L"y"] = 3;

			UpdateEdits();
		}

		void CFormMatrix::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Matrix"));
			m_pGroupBoxMatrix->setCaption(Application->Translate->t(ClassName, L"Matrix"));
			m_pGroupBoxTranslate->setCaption(Application->Translate->t(ClassName, L"Translate"));
			m_pButtonMT->setCaption(Application->Translate->t(ClassName, L"M * T"));
			m_pButtonMT->setHintText(Application->Translate->t(ClassName, L"Add movement to current matrix"));
			m_pButtonT->setCaption(Application->Translate->t(ClassName, L"T"));
			m_pButtonT->setHintText(Application->Translate->t(ClassName, L"Replace current matrix with new movement"));
			m_pButtonTM->setCaption(Application->Translate->t(ClassName, L"T * M"));
			m_pButtonTM->setHintText(Application->Translate->t(ClassName, L"Add current matrix to movement"));
			m_pGroupBoxScale->setCaption(Application->Translate->t(ClassName, L"Scale"));
			m_pButtonMS->setCaption(Application->Translate->t(ClassName, L"M * S"));
			m_pButtonMS->setHintText(Application->Translate->t(ClassName, L"Add scaling to current matrix"));
			m_pButtonS->setCaption(Application->Translate->t(ClassName, L"S"));
			m_pButtonS->setHintText(Application->Translate->t(ClassName, L"Replace current matrix with new scaling"));
			m_pButtonSM->setCaption(Application->Translate->t(ClassName, L"S * M"));
			m_pButtonSM->setHintText(Application->Translate->t(ClassName, L"Add current matrix to scaling"));
			m_pGroupBoxRotate->setCaption(Application->Translate->t(ClassName, L"Rotate(degrees)"));
			m_pLabelRx->setCaption(Application->Translate->t(ClassName, L"Around X-axis:"));
			m_pButtonMRx->setCaption(Application->Translate->t(ClassName, L"M * R"));
			m_pButtonMRx->setHintText(Application->Translate->t(ClassName, L"Add rotation to current matrix"));
			m_pButtonRx->setCaption(Application->Translate->t(ClassName, L"R"));
			m_pButtonRx->setHintText(Application->Translate->t(ClassName, L"Replace current matrix with new rotation"));
			m_pButtonRxM->setCaption(Application->Translate->t(ClassName, L"R * M"));
			m_pButtonRxM->setHintText(Application->Translate->t(ClassName, L"Add current matrix to rotation"));
			m_pLabelRy->setCaption(Application->Translate->t(ClassName, L"Around Y-axis:"));
			m_pButtonMRy->setCaption(Application->Translate->t(ClassName, L"M * R"));
			m_pButtonMRy->setHintText(Application->Translate->t(ClassName, L"Add rotation to current matrix"));
			m_pButtonRy->setCaption(Application->Translate->t(ClassName, L"R"));
			m_pButtonRy->setHintText(Application->Translate->t(ClassName, L"Replace current matrix with new rotation"));
			m_pButtonRyM->setCaption(Application->Translate->t(ClassName, L"R * M"));
			m_pButtonRyM->setHintText(Application->Translate->t(ClassName, L"Add current matrix to rotation"));
			m_pLabelRz->setCaption(Application->Translate->t(ClassName, L"Around Z-axis:"));
			m_pButtonMRz->setCaption(Application->Translate->t(ClassName, L"M * R"));
			m_pButtonMRz->setHintText(Application->Translate->t(ClassName, L"Add rotation to current matrix"));
			m_pButtonRz->setCaption(Application->Translate->t(ClassName, L"R"));
			m_pButtonRz->setHintText(Application->Translate->t(ClassName, L"Replace current matrix with new rotation"));
			m_pButtonRzM->setCaption(Application->Translate->t(ClassName, L"R * M"));
			m_pButtonRzM->setHintText(Application->Translate->t(ClassName, L"Add current matrix to rotation"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormMatrix::FormMatrixProto_OnKeyUp(IForm *sender, const MessageKey &m)
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

		void CFormMatrix::OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			float v;
			if (!TryStringToFloat(edit->getText(), v))
				v = m_sMatrix.Rows[(unsigned char)(int)edit->Tag[L"y"]].Data[(unsigned char)(int)edit->Tag[L"x"]];
			m_sMatrix.Rows[(unsigned char)(int)edit->Tag[L"y"]].Data[(unsigned char)(int)edit->Tag[L"x"]] = v;
			edit->setText(ToStringCompact(v));
		}

		void CFormMatrix::ButtonMT_OnClick(IControl *sender)
		{
			float x, y, z;
			if (TryGetTranslate(x, y, z))
				setValue(m_sMatrix * ntl::Mat4Translate<float>(x, y, z));
		}

		void CFormMatrix::ButtonT_OnClick(IControl *sender)
		{
			float x, y, z;
			if (TryGetTranslate(x, y, z))
				setValue(ntl::Mat4Translate<float>(x, y, z));
		}

		void CFormMatrix::ButtonTM_OnClick(IControl *sender)
		{
			float x, y, z;
			if (TryGetTranslate(x, y, z))
				setValue(ntl::Mat4Translate<float>(x, y, z) * m_sMatrix);
		}

		void CFormMatrix::ButtonMS_OnClick(IControl *sender)
		{
			float x, y, z;
			if (TryGetScale(x, y, z))
				setValue(m_sMatrix * ntl::Mat4Scale<float>(x, y, z));
		}

		void CFormMatrix::ButtonS_OnClick(IControl *sender)
		{
			float x, y, z;
			if (TryGetScale(x, y, z))
				setValue(ntl::Mat4Scale<float>(x, y, z));
		}

		void CFormMatrix::ButtonSM_OnClick(IControl *sender)
		{
			float x, y, z;
			if (TryGetScale(x, y, z))
				setValue(ntl::Mat4Scale<float>(x, y, z) * m_sMatrix);
		}

		void CFormMatrix::ButtonMRx_OnClick(IControl *sender)
		{
			float v;
			if (TryGetRx(v))
				setValue(m_sMatrix * ntl::Mat4RotateX<float>(v));
		}

		void CFormMatrix::ButtonRx_OnClick(IControl *sender)
		{
			float v;
			if (TryGetRx(v))
				setValue(ntl::Mat4RotateX<float>(v));
		}

		void CFormMatrix::ButtonRxM_OnClick(IControl *sender)
		{
			float v;
			if (TryGetRx(v))
				setValue(ntl::Mat4RotateX<float>(v) * m_sMatrix);
		}

		void CFormMatrix::ButtonMRy_OnClick(IControl *sender)
		{
			float v;
			if (TryGetRy(v))
				setValue(m_sMatrix * ntl::Mat4RotateY<float>(v));
		}

		void CFormMatrix::ButtonRy_OnClick(IControl *sender)
		{
			float v;
			if (TryGetRy(v))
				setValue(ntl::Mat4RotateY<float>(v));
		}

		void CFormMatrix::ButtonRyM_OnClick(IControl *sender)
		{
			float v;
			if (TryGetRy(v))
				setValue(ntl::Mat4RotateY<float>(v) * m_sMatrix);
		}

		void CFormMatrix::ButtonMRz_OnClick(IControl *sender)
		{
			float v;
			if (TryGetRz(v))
				setValue(m_sMatrix * ntl::Mat4RotateZ<float>(v));
		}

		void CFormMatrix::ButtonRz_OnClick(IControl *sender)
		{
			float v;
			if (TryGetRz(v))
				setValue(ntl::Mat4RotateZ<float>(v));
		}

		void CFormMatrix::ButtonRzM_OnClick(IControl *sender)
		{
			float v;
			if (TryGetRz(v))
				setValue(ntl::Mat4RotateZ<float>(v) * m_sMatrix);
		}

		void CFormMatrix::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormMatrix::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		Mat4f CFormMatrix::getValue()
		{
			return m_sMatrix;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormMatrix::setValue(const Mat4f &value)
		{
			if (ntl::IsNotEqual<float>(value, m_sMatrix))
			{
				m_sMatrix = value;
				UpdateEdits();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface methods
		void CFormMatrix::ActivateFirstEnabledInput()
		{
			m_pEdit00->SelectAll();
			m_pEdit00->setFocus();
		}
	#pragma endregion

	#pragma region Helpers
		void CFormMatrix::UpdateEdits()
		{
			m_pEdit00->setText(ToStringCompact(m_sMatrix.Rows[0].X));
			m_pEdit10->setText(ToStringCompact(m_sMatrix.Rows[0].Y));
			m_pEdit20->setText(ToStringCompact(m_sMatrix.Rows[0].Z));
			m_pEdit30->setText(ToStringCompact(m_sMatrix.Rows[0].W));

			m_pEdit01->setText(ToStringCompact(m_sMatrix.Rows[1].X));
			m_pEdit11->setText(ToStringCompact(m_sMatrix.Rows[1].Y));
			m_pEdit21->setText(ToStringCompact(m_sMatrix.Rows[1].Z));
			m_pEdit31->setText(ToStringCompact(m_sMatrix.Rows[1].W));

			m_pEdit02->setText(ToStringCompact(m_sMatrix.Rows[2].X));
			m_pEdit12->setText(ToStringCompact(m_sMatrix.Rows[2].Y));
			m_pEdit22->setText(ToStringCompact(m_sMatrix.Rows[2].Z));
			m_pEdit32->setText(ToStringCompact(m_sMatrix.Rows[2].W));

			m_pEdit03->setText(ToStringCompact(m_sMatrix.Rows[3].X));
			m_pEdit13->setText(ToStringCompact(m_sMatrix.Rows[3].Y));
			m_pEdit23->setText(ToStringCompact(m_sMatrix.Rows[3].Z));
			m_pEdit33->setText(ToStringCompact(m_sMatrix.Rows[3].W));
		}

		bool CFormMatrix::TryGetTranslate(float &x, float &y, float &z)
		{
			if (!TryStringToFloat(m_pEditTx->getText(), x))
			{
				m_pEditTx->SelectAll();
				m_pEditTx->setFocus();
				return false;
			}
			if (!TryStringToFloat(m_pEditTy->getText(), y))
			{
				m_pEditTy->SelectAll();
				m_pEditTy->setFocus();
				return false;
			}
			if (!TryStringToFloat(m_pEditTz->getText(), z))
			{
				m_pEditTz->SelectAll();
				m_pEditTz->setFocus();
				return false;
			}
			return true;
		}

		bool CFormMatrix::TryGetScale(float &x, float &y, float &z)
		{
			if (!TryStringToFloat(m_pEditSx->getText(), x))
			{
				m_pEditSx->SelectAll();
				m_pEditSx->setFocus();
				return false;
			}
			if (!TryStringToFloat(m_pEditSy->getText(), y))
			{
				m_pEditSy->SelectAll();
				m_pEditSy->setFocus();
				return false;
			}
			if (!TryStringToFloat(m_pEditSz->getText(), z))
			{
				m_pEditSz->SelectAll();
				m_pEditSz->setFocus();
				return false;
			}
			return true;
		}

		bool CFormMatrix::TryGetRx(float &v)
		{
			if (!TryStringToFloat(m_pEditRx->getText(), v))
			{
				m_pEditRx->SelectAll();
				m_pEditRx->setFocus();
				return false;
			}
			v = ntl::DegToRad<float>(v);
			return true;
		}

		bool CFormMatrix::TryGetRy(float &v)
		{
			if (!TryStringToFloat(m_pEditRy->getText(), v))
			{
				m_pEditRy->SelectAll();
				m_pEditRy->setFocus();
				return false;
			}
			v = ntl::DegToRad<float>(v);
			return true;
		}

		bool CFormMatrix::TryGetRz(float &v)
		{
			if (!TryStringToFloat(m_pEditRz->getText(), v))
			{
				m_pEditRz->SelectAll();
				m_pEditRz->setFocus();
				return false;
			}
			v = ntl::DegToRad<float>(v);
			return true;
		}
	#pragma endregion
	}
}