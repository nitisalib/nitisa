// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
	#pragma region Constructor & destructor
		CColorDialog::CColorDialog() :
			CComponent(L"ColorDialog"),
			m_sColor{ 0, 0, 0, 255 },
			m_bUseDialogBox{ false },
			m_pDialogBoxColor{ nullptr },
			m_pColorDialogListener{ nullptr },
			m_cDialogBoxListener{ this }
		{
			OnApply = nullptr;

			setService(new CColorDialogService(this), true);
		}

		CColorDialog::CColorDialog(IForm *parent) :CColorDialog()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		Color CColorDialog::getColor()
		{
			return m_sColor;
		}

		bool CColorDialog::isUseDialogBox()
		{
			return m_bUseDialogBox;
		}

		IColorDialogListener *CColorDialog::getColorDialogListener()
		{
			return m_pColorDialogListener;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CColorDialog::setColor(const Color &value)
		{
			if (value != m_sColor)
			{
				m_sColor = value;
				return true;
			}
			return false;
		}

		bool CColorDialog::setUseDialogBox(const bool value)
		{
			if (value != m_bUseDialogBox)
			{
				m_bUseDialogBox = value;
				if (!m_bUseDialogBox && m_pDialogBoxColor)
				{
					m_pDialogBoxColor->Release();
					m_pDialogBoxColor = nullptr;
				}
				return true;
			}
			return false;
		}

		void CColorDialog::setColorDialogListener(IColorDialogListener *value)
		{
			m_pColorDialogListener = value;
		}
	#pragma endregion

	#pragma region Interface helpers
		bool CColorDialog::Execute()
		{
			if (m_bUseDialogBox)
			{
				CLockRepaint lock{ getForm() };
				if (!m_pDialogBoxColor)
				{
					m_pDialogBoxColor = new CDialogBoxColor(); // Need to split so that getDialogBox() can return proper pointer
					m_pDialogBoxColor->setForm(getForm());
				}
				m_pDialogBoxColor->setValue(m_sColor);
				m_pDialogBoxColor->setDialogBoxListener(&m_cDialogBoxListener);
				m_pDialogBoxColor->ShowModal();
				return true;
			}
			else
			{
				CFormColor *form{ CFormColor::getInstance() };
				if (!form && getForm() && getForm()->QueryService()->getWindow() && getForm()->getRenderer())
					form = new CFormColor(getForm()->QueryService()->getWindow()->CreateInstance(), getForm()->getRenderer()->CreateInstance());
				if (form)
				{
					form->setValue(m_sColor);
					if (form->ShowModal() == ModalResult::Ok)
					{
						m_sColor = form->getValue();
						if (m_pColorDialogListener)
							m_pColorDialogListener->OnApply(this);
						if (OnApply)
							OnApply(this);
						return true;
					}
				}
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		CDialogBoxColor *CColorDialog::getDialogBox()
		{
			return m_pDialogBoxColor;
		}
	#pragma endregion
	}
}