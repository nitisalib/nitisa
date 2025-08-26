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
		CMaskEdit::CMaskEditListener::CMaskEditListener(CMaskEdit *edit) :
			m_pEdit{ edit }
		{

		}

		void CMaskEdit::CMaskEditListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (!m_pEdit->m_bIgnoreText)
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(rect, true);
			}
		}

		void CMaskEdit::CMaskEditListener::NotifyOnTextChanged(IBuiltInControl *sender)
		{
			if (!m_pEdit->m_bIgnoreText && m_pEdit->OnChange)
				m_pEdit->OnChange(m_pEdit);
		}
	}
}