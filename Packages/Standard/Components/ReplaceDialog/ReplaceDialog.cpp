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
		CReplaceDialog::CReplaceDialog() :
			CComponent(L"ReplaceDialog"),
			m_bMatchWholeWords{ false },
			m_bMatchCase{ false },
			m_eSearchDirection{ IFormReplace::SearchDirection::Down },
			m_bUseDialogBox{ false },
			m_pDialogBoxReplace{ nullptr },
			m_cDialogBoxListener{ this },
			m_pFormReplace{ nullptr },
			m_bShown{ false }
		{
			OnReplace = nullptr;
			OnReplaceAll = nullptr;

			setService(new CReplaceDialogService(this), true);
		}

		CReplaceDialog::CReplaceDialog(IForm *parent) :CReplaceDialog()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		String CReplaceDialog::getText()
		{
			if (m_bShown)
			{
				if (m_pDialogBoxReplace)
					m_pDialogBoxReplace->getText();
				return getFormReplace()->getText();
			}
			return m_sText;
		}

		String CReplaceDialog::getReplace()
		{
			if (m_bShown)
			{
				if (m_pDialogBoxReplace)
					m_pDialogBoxReplace->getReplace();
				return getFormReplace()->getReplace();
			}
			return m_sReplace;
		}

		bool CReplaceDialog::isMatchWholeWords()
		{
			if (m_bShown)
			{
				if (m_pDialogBoxReplace)
					m_pDialogBoxReplace->isMatchWholeWords();
				return getFormReplace()->isMatchWholeWords();
			}
			return m_bMatchWholeWords;
		}

		bool CReplaceDialog::isMatchCase()
		{
			if (m_bShown)
			{
				if (m_pDialogBoxReplace)
					m_pDialogBoxReplace->isMatchCase();
				return getFormReplace()->isMatchCase();
			}
			return m_bMatchCase;
		}

		IFormReplace::SearchDirection CReplaceDialog::getSearchDirection()
		{
			if (m_bShown)
			{
				if (m_pDialogBoxReplace)
					m_pDialogBoxReplace->getSearchDirection();
				return getFormReplace()->getSearchDirection();
			}
			return m_eSearchDirection;
		}

		bool CReplaceDialog::isUseDialogBox()
		{
			return m_bUseDialogBox;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CReplaceDialog::setText(const String &value)
		{
			if (m_bShown)
			{
				if (m_pDialogBoxReplace)
					m_pDialogBoxReplace->setText(value);
				else
					getFormReplace()->setText(value);
			}
			if (value != m_sText)
			{
				m_sText = value;
				return true;
			}
			return false;
		}

		bool CReplaceDialog::setReplace(const String &value)
		{
			if (m_bShown)
			{
				if (m_pDialogBoxReplace)
					m_pDialogBoxReplace->setReplace(value);
				else
					getFormReplace()->setReplace(value);
			}
			if (value != m_sReplace)
			{
				m_sReplace = value;
				return true;
			}
			return false;
		}

		bool CReplaceDialog::setMatchWholeWords(const bool value)
		{
			if (m_bShown)
			{
				if (m_pDialogBoxReplace)
					m_pDialogBoxReplace->setMatchWholeWords(value);
				else
					getFormReplace()->setMatchWholeWords(value);
			}
			if (value != m_bMatchWholeWords)
			{
				m_bMatchWholeWords = value;
				return true;
			}
			return false;
		}

		bool CReplaceDialog::setMatchCase(const bool value)
		{
			if (m_bShown)
			{
				if (m_pDialogBoxReplace)
					m_pDialogBoxReplace->setMatchCase(value);
				else
					getFormReplace()->setMatchCase(value);
			}
			if (value != m_bMatchCase)
			{
				m_bMatchCase = value;
				return true;
			}
			return false;
		}

		bool CReplaceDialog::setSearchDirection(const IFormReplace::SearchDirection value)
		{
			if (m_bShown)
			{
				if (m_pDialogBoxReplace)
					m_pDialogBoxReplace->setSearchDirection(value);
				else
					getFormReplace()->setSearchDirection(value);
			}
			if (value != m_eSearchDirection)
			{
				m_eSearchDirection = value;
				return true;
			}
			return false;
		}

		bool CReplaceDialog::setUseDialogBox(const bool value)
		{
			if (value != m_bUseDialogBox)
			{
				m_bUseDialogBox = value;
				if (!m_bUseDialogBox && m_pDialogBoxReplace)
				{
					m_pDialogBoxReplace->Release();
					m_pDialogBoxReplace = nullptr;
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		CFormReplace *CReplaceDialog::getFormReplace()
		{
			if (!m_pFormReplace && getForm() && getForm()->QueryService()->getWindow() && getForm()->getRenderer())
				m_pFormReplace = new CFormReplace(getForm()->QueryService()->getWindow()->CreateInstance(), getForm()->getRenderer()->CreateInstance());
			return m_pFormReplace;
		}
	#pragma endregion

	#pragma region Interface helpers
		bool CReplaceDialog::Execute()
		{
			if (m_bShown)
				return false;
			if (m_bUseDialogBox)
			{
				CLockRepaint lock{ getForm() };
				if (!m_pDialogBoxReplace)
					m_pDialogBoxReplace = new CDialogBoxReplace(getForm());
				m_pDialogBoxReplace->OnReplace = OnReplace;
				m_pDialogBoxReplace->OnReplaceAll = OnReplaceAll;
				m_pDialogBoxReplace->setText(m_sText);
				m_pDialogBoxReplace->setReplace(m_sReplace);
				m_pDialogBoxReplace->setMatchWholeWords(m_bMatchWholeWords);
				m_pDialogBoxReplace->setMatchCase(m_bMatchCase);
				m_pDialogBoxReplace->setSearchDirection(m_eSearchDirection);
				m_pDialogBoxReplace->setDialogBoxListener(&m_cDialogBoxListener);
				m_bShown = true;
				m_pDialogBoxReplace->Show();
				return true;
			}
			else
			{
				CFormReplace *form{ getFormReplace() };
				if (form)
				{
					m_bShown = true;
					form->OnReplace = OnReplace;
					form->OnReplaceAll = OnReplaceAll;
					form->setText(m_sText);
					form->setText(m_sReplace);
					form->setMatchWholeWords(m_bMatchWholeWords);
					form->setMatchCase(m_bMatchCase);
					form->setSearchDirection(m_eSearchDirection);
					form->Show();
					m_sText = form->getText();
					m_sReplace = form->getReplace();
					m_bMatchWholeWords = form->isMatchWholeWords();
					m_bMatchCase = form->isMatchCase();
					m_eSearchDirection = form->getSearchDirection();
					m_bShown = false;
					return true;
				}
			}
			return false;
		}
	#pragma endregion
	}
}