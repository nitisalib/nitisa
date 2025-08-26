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
		CFindDialog::CFindDialog() :
			CComponent(L"FindDialog"),
			m_bMatchWholeWords{ false },
			m_bMatchCase{ false },
			m_eSearchDirection{ IFormFind::SearchDirection::Down },
			m_bUseDialogBox{ false },
			m_pDialogBoxFind{ nullptr },
			m_cDialogBoxListener{ this },
			m_pFormFind{ nullptr },
			m_bShown{ false }
		{
			OnSearch = nullptr;

			setService(new CFindDialogService(this), true);
		}

		CFindDialog::CFindDialog(IForm *parent) :CFindDialog()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		String CFindDialog::getText()
		{
			if (m_bShown)
			{
				if (m_pDialogBoxFind)
					return m_pDialogBoxFind->getText();
				return getFormFind()->getText();
			}
			return m_sText;
		}

		bool CFindDialog::isMatchWholeWords()
		{
			if (m_bShown)
			{
				if (m_pDialogBoxFind)
					return m_pDialogBoxFind->isMatchWholeWords();
				return getFormFind()->isMatchWholeWords();
			}
			return m_bMatchWholeWords;
		}

		bool CFindDialog::isMatchCase()
		{
			if (m_bShown)
			{
				if (m_pDialogBoxFind)
					return m_pDialogBoxFind->isMatchCase();
				return getFormFind()->isMatchCase();
			}
			return m_bMatchCase;
		}

		IFormFind::SearchDirection CFindDialog::getSearchDirection()
		{
			if (m_bShown)
			{
				if (m_pDialogBoxFind)
					m_pDialogBoxFind->getSearchDirection();
				return getFormFind()->getSearchDirection();
			}
			return m_eSearchDirection;
		}

		bool CFindDialog::isUseDialogBox()
		{
			return m_bUseDialogBox;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFindDialog::setText(const String &value)
		{
			if (m_bShown)
			{
				if (m_pDialogBoxFind)
					m_pDialogBoxFind->setText(value);
				else
					getFormFind()->setText(value);
			}
			if (value != m_sText)
			{
				m_sText = value;
				return true;
			}
			return false;
		}

		bool CFindDialog::setMatchWholeWords(const bool value)
		{
			if (m_bShown)
			{
				if (m_pDialogBoxFind)
					m_pDialogBoxFind->setMatchWholeWords(value);
				else
					getFormFind()->setMatchWholeWords(value);
			}
			if (value != m_bMatchWholeWords)
			{
				m_bMatchWholeWords = value;
				return true;
			}
			return false;
		}

		bool CFindDialog::setMatchCase(const bool value)
		{
			if (m_bShown)
			{
				if (m_pDialogBoxFind)
					m_pDialogBoxFind->setMatchCase(value);
				else
					getFormFind()->setMatchCase(value);
			}
			if (value != m_bMatchCase)
			{
				m_bMatchCase = value;
				return true;
			}
			return false;
		}

		bool CFindDialog::setSearchDirection(const IFormFind::SearchDirection value)
		{
			if (m_bShown)
			{
				if (m_pDialogBoxFind)
					m_pDialogBoxFind->setSearchDirection(value);
				else
					getFormFind()->setSearchDirection(value);
			}
			if (value != m_eSearchDirection)
			{
				m_eSearchDirection = value;
				return true;
			}
			return false;
		}

		bool CFindDialog::setUseDialogBox(const bool value)
		{
			if (value != m_bUseDialogBox)
			{
				m_bUseDialogBox = value;
				if (!m_bUseDialogBox && m_pDialogBoxFind)
				{
					m_pDialogBoxFind->Release();
					m_pDialogBoxFind = nullptr;
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		CFormFind *CFindDialog::getFormFind()
		{
			if (!m_pFormFind && getForm() && getForm()->QueryService()->getWindow() && getForm()->getRenderer())
				m_pFormFind = new CFormFind(getForm()->QueryService()->getWindow()->CreateInstance(), getForm()->getRenderer()->CreateInstance());
			return m_pFormFind;
		}
	#pragma endregion

	#pragma region Interface helpers
		bool CFindDialog::Execute()
		{
			if (m_bShown)
				return false;
			if (m_bUseDialogBox)
			{
				CLockRepaint lock{ getForm() };
				if (!m_pDialogBoxFind)
					m_pDialogBoxFind = new CDialogBoxFind(getForm());
				m_pDialogBoxFind->OnSearch = OnSearch;
				m_pDialogBoxFind->setText(m_sText);
				m_pDialogBoxFind->setMatchWholeWords(m_bMatchWholeWords);
				m_pDialogBoxFind->setMatchCase(m_bMatchCase);
				m_pDialogBoxFind->setSearchDirection(m_eSearchDirection);
				m_pDialogBoxFind->setDialogBoxListener(&m_cDialogBoxListener);
				m_bShown = true;
				m_pDialogBoxFind->Show();
				return true;
			}
			else
			{
				CFormFind *form{ getFormFind() };
				if (form)
				{
					m_bShown = true;
					form->OnSearch = OnSearch;
					form->setText(m_sText);
					form->setMatchWholeWords(m_bMatchWholeWords);
					form->setMatchCase(m_bMatchCase);
					form->setSearchDirection(m_eSearchDirection);
					form->Show();
					m_sText = form->getText();
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