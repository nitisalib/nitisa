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
		const String CFormColor::ClassName{ L"FormColor" };
		CFormColor *CFormColor::m_pInstance{ nullptr };

	#pragma region Service
		CFormColor::CFormColorService::CFormColorService(CFormColor *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormColor::CFormColorService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormColor::CFormColor(IWindow *window, IRenderer *renderer) :
			IFormColorProto(window, renderer, ClassName),
			m_sColor{ 255, 255, 255, 255 }
		{
			setService(new CFormColorService(this), true);
			if (!m_pInstance)
				m_pInstance = this;
			CLockRepaint lock{ this };
			LoadTranslatableTexts();
			UpdateEdits();
		}

		CFormColor::~CFormColor()
		{
			if (m_pInstance == this)
				m_pInstance = nullptr;
		}

		void CFormColor::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Select Color"));
			m_pLabelHue->setCaption(Application->Translate->t(ClassName, L"H:"));
			m_pLabelSaturation->setCaption(Application->Translate->t(ClassName, L"S:"));
			m_pLabelValue->setCaption(Application->Translate->t(ClassName, L"V:"));
			m_pLabelR->setCaption(Application->Translate->t(ClassName, L"R:"));
			m_pLabelG->setCaption(Application->Translate->t(ClassName, L"G:"));
			m_pLabelB->setCaption(Application->Translate->t(ClassName, L"B:"));
			m_pLabelA->setCaption(Application->Translate->t(ClassName, L"A:"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormColor::FormColorProto_OnKeyUp(IForm *sender, const MessageKey &m)
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

		void CFormColor::HSVPlane_OnChange(IControl *sender)
		{
			float r, g, b;
			HSVToRGB((float)m_pHSVPlane->getHue() / 360.0f, m_pHSVPlane->getSaturation(), m_pHSVPlane->getValue(), r, g, b);
			m_sColor.R = ntl::Round<unsigned char>(r * 255);
			m_sColor.G = ntl::Round<unsigned char>(g * 255);
			m_sColor.B = ntl::Round<unsigned char>(b * 255);
			UpdateEdits();
		}

		void CFormColor::HSVBar_OnChange(IControl *sender)
		{
			m_pHSVPlane->setHue(m_pHSVBar->getHue());
			float r, g, b;
			HSVToRGB((float)m_pHSVPlane->getHue() / 360.0f, m_pHSVPlane->getSaturation(), m_pHSVPlane->getValue(), r, g, b);
			m_sColor.R = ntl::Round<unsigned char>(r * 255);
			m_sColor.G = ntl::Round<unsigned char>(g * 255);
			m_sColor.B = ntl::Round<unsigned char>(b * 255);
			UpdateEdits();
		}

		void CFormColor::AlphaBar_OnChange(IControl *sender)
		{
			m_sColor.A = (unsigned char)m_pAlphaBar->getAlpha();
			UpdateEdits();
		}

		void CFormColor::EditHue_OnKillFocus(IControl *sender)
		{
			m_pEditHue->setText(ToString(m_pHSVPlane->getHue()));
		}

		void CFormColor::EditHue_OnChange(IControl *sender)
		{
			int hue;
			if (TryStringToInt(m_pEditHue->getText(), hue))
			{
				hue = ntl::Clamp<int>(hue, 0, 360);
				m_pHSVPlane->setHue(hue);
				m_pHSVBar->setHue(hue);
				float r, g, b;
				HSVToRGB((float)m_pHSVPlane->getHue() / 360.0f, m_pHSVPlane->getSaturation(), m_pHSVPlane->getValue(), r, g, b);
				m_sColor.R = ntl::Round<unsigned char>(r * 255);
				m_sColor.G = ntl::Round<unsigned char>(g * 255);
				m_sColor.B = ntl::Round<unsigned char>(b * 255);
				UpdateEdits();
			}
		}

		void CFormColor::EditSaturation_OnKillFocus(IControl *sender)
		{
			m_pEditSaturation->setText(ToString(ntl::Round<int>(100 * m_pHSVPlane->getSaturation())));
		}

		void CFormColor::EditSaturation_OnChange(IControl *sender)
		{
			float sat;
			if (TryStringToFloat(m_pEditSaturation->getText(), sat))
			{
				sat = ntl::Clamp<float>(sat, 0, 100);
				m_pHSVPlane->setSaturation(sat * 0.01f);
				float r, g, b;
				HSVToRGB((float)m_pHSVPlane->getHue() / 360.0f, m_pHSVPlane->getSaturation(), m_pHSVPlane->getValue(), r, g, b);
				m_sColor.R = ntl::Round<unsigned char>(r * 255);
				m_sColor.G = ntl::Round<unsigned char>(g * 255);
				m_sColor.B = ntl::Round<unsigned char>(b * 255);
				UpdateEdits();
			}
		}

		void CFormColor::EditValue_OnKillFocus(IControl *sender)
		{
			m_pEditValue->setText(ToString(ntl::Round<int>(100 * m_pHSVPlane->getValue())));
		}

		void CFormColor::EditValue_OnChange(IControl *sender)
		{
			float val;
			if (TryStringToFloat(m_pEditValue->getText(), val))
			{
				val = ntl::Clamp<float>(val, 0, 100);
				m_pHSVPlane->setValue(val * 0.01f);
				float r, g, b;
				HSVToRGB((float)m_pHSVPlane->getHue() / 360.0f, m_pHSVPlane->getSaturation(), m_pHSVPlane->getValue(), r, g, b);
				m_sColor.R = ntl::Round<unsigned char>(r * 255);
				m_sColor.G = ntl::Round<unsigned char>(g * 255);
				m_sColor.B = ntl::Round<unsigned char>(b * 255);
				UpdateEdits();
			}
		}

		void CFormColor::EditR_OnKillFocus(IControl *sender)
		{
			m_pEditR->setText(ToString(m_sColor.R));
		}

		void CFormColor::EditR_OnChange(IControl *sender)
		{
			int r;
			if (TryStringToInt(m_pEditR->getText(), r))
			{
				r = ntl::Clamp<int>(r, 0, 255);
				m_sColor.R = (unsigned char)r;
				float h, s, v;
				RGBToHSV(m_sColor.R / 255.0f, m_sColor.G / 255.0f, m_sColor.B / 255.0f, h, s, v);
				m_pHSVPlane->setHue(ntl::Round<int>(h * 360));
				m_pHSVPlane->setSaturation(s);
				m_pHSVPlane->setValue(v);
				m_pHSVBar->setHue(ntl::Round<int>(h * 360));
				UpdateEdits();
			}
		}

		void CFormColor::EditG_OnKillFocus(IControl *sender)
		{
			m_pEditG->setText(ToString(m_sColor.G));
		}

		void CFormColor::EditG_OnChange(IControl *sender)
		{
			int g;
			if (TryStringToInt(m_pEditG->getText(), g))
			{
				g = ntl::Clamp<int>(g, 0, 255);
				m_sColor.G = (unsigned char)g;
				float h, s, v;
				RGBToHSV(m_sColor.R / 255.0f, m_sColor.G / 255.0f, m_sColor.B / 255.0f, h, s, v);
				m_pHSVPlane->setHue(ntl::Round<int>(h * 360));
				m_pHSVPlane->setSaturation(s);
				m_pHSVPlane->setValue(v);
				m_pHSVBar->setHue(ntl::Round<int>(h * 360));
				UpdateEdits();
			}
		}

		void CFormColor::EditB_OnKillFocus(IControl *sender)
		{
			m_pEditB->setText(ToString(m_sColor.B));
		}

		void CFormColor::EditB_OnChange(IControl *sender)
		{
			int b;
			if (TryStringToInt(m_pEditB->getText(), b))
			{
				b = ntl::Clamp<int>(b, 0, 255);
				m_sColor.B = (unsigned char)b;
				float h, s, v;
				RGBToHSV(m_sColor.R / 255.0f, m_sColor.G / 255.0f, m_sColor.B / 255.0f, h, s, v);
				m_pHSVPlane->setHue(ntl::Round<int>(h * 360));
				m_pHSVPlane->setSaturation(s);
				m_pHSVPlane->setValue(v);
				m_pHSVBar->setHue(ntl::Round<int>(h * 360));
				UpdateEdits();
			}
		}

		void CFormColor::EditA_OnKillFocus(IControl *sender)
		{
			int a;
			if (TryStringToInt(m_pEditA->getText(), a))
				a = ntl::Clamp<int>(a, 0, 255);
			else
				a = m_sColor.A;
			m_sColor.A = (unsigned char)a;
			m_pEditA->setText(ToString(m_sColor.A));
			m_pAlphaBar->setAlpha(a);
		}

		void CFormColor::EditA_OnChange(IControl *sender)
		{
			int a;
			if (TryStringToInt(m_pEditA->getText(), a))
			{
				a = ntl::Clamp<int>(a, 0, 255);
				m_sColor.A = (unsigned char)a;
				m_pAlphaBar->setAlpha(a);
				UpdateEdits();
			}
		}

		void CFormColor::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormColor::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		Color CFormColor::getValue()
		{
			return m_sColor;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormColor::setValue(const Color &value)
		{
			if (value != m_sColor)
			{
				CLockRepaint lock{ this };
				m_sColor = value;
				float h, s, v;
				RGBToHSV(m_sColor.R / 255.0f, m_sColor.G / 255.0f, m_sColor.B / 255.0f, h, s, v);
				m_pHSVPlane->setHue(ntl::Round<int>(h * 360));
				m_pHSVPlane->setSaturation(s);
				m_pHSVPlane->setValue(v);
				m_pHSVBar->setHue(ntl::Round<int>(h * 360));
				m_pAlphaBar->setAlpha(m_sColor.A);
				UpdateEdits();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface methods
		void CFormColor::ActivateFirstEnabledInput()
		{
			m_pEditR->SelectAll();
			m_pEditR->setFocus();
		}
	#pragma endregion

	#pragma region Getters
		CFormColor *CFormColor::getInstance()
		{
			return m_pInstance;
		}
	#pragma endregion

	#pragma region Helpers
		void CFormColor::UpdateEdits()
		{
			m_pEditHue->setText(ToString(m_pHSVPlane->getHue()));
			m_pEditHue->DeselectAll();
			m_pEditSaturation->setText(ToString(ntl::Round<int>(m_pHSVPlane->getSaturation() * 100)));
			m_pEditSaturation->DeselectAll();
			m_pEditValue->setText(ToString(ntl::Round<int>(m_pHSVPlane->getValue() * 100)));
			m_pEditValue->DeselectAll();
			m_pEditR->setText(ToString(m_sColor.R));
			m_pEditR->DeselectAll();
			m_pEditG->setText(ToString(m_sColor.G));
			m_pEditG->DeselectAll();
			m_pEditB->setText(ToString(m_sColor.B));
			m_pEditB->DeselectAll();
			m_pEditA->setText(ToString(m_sColor.A));
			m_pEditA->DeselectAll();
		}
	#pragma endregion
	}
}