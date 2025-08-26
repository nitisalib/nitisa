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
		CPasswordEdit::CPasswordEditListener::CPasswordEditListener(CPasswordEdit *edit) :
			m_pEdit{ edit }
		{

		}

		void CPasswordEdit::CPasswordEditListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (!m_pEdit->m_bIgnoreTextInput)
			{
				if (m_pEdit->m_pCanvas)
					m_pEdit->m_pCanvas->setValid(false);
				m_pEdit->Repaint(rect, true);
			}
		}

		void CPasswordEdit::CPasswordEditListener::NotifyOnTextChanged(IBuiltInControl *sender)
		{
			if (!m_pEdit->m_bIgnoreTextInput)
			{
				if (m_pEdit->OnChange)
					m_pEdit->OnChange(m_pEdit);
			}
		}
	}
}