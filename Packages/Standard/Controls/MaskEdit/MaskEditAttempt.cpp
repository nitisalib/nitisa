// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
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
		CMaskEdit::CAttempt::CAttempt(CMaskEdit *edit) :
			m_pEdit{ edit },
			m_bSuccess{ false }
		{
			if (m_pEdit->getForm())
				m_pEdit->getForm()->LockRepaint();
			m_pEdit->m_bIgnoreText = true;
			m_pInput = edit->getTextInput();
			m_sText = m_pInput->getText();
			m_iCaret = m_pInput->getCaretPosition();
			m_sSelection = m_pInput->getSelection();
			m_fScroll = m_pInput->getScroll();
		}

		CMaskEdit::CAttempt::~CAttempt()
		{
			if (!m_bSuccess)
			{
				m_pInput->setText(m_sText);
				m_pInput->setCaretPosition(m_iCaret);
				m_pInput->setSelection(m_sSelection);
				m_pInput->setScroll(m_fScroll);
			}
			else if (m_pEdit->getText() != m_sText && m_pEdit->OnChange)
				m_pEdit->OnChange(m_pEdit);
			m_pEdit->m_bIgnoreText = false;
			if (m_pEdit->getForm())
				m_pEdit->getForm()->UnlockRepaint();
		}

		void CMaskEdit::CAttempt::Success()
		{
			m_bSuccess = true;
		}

		const String &CMaskEdit::CAttempt::Text() const
		{
			return m_sText;
		}
	}
}