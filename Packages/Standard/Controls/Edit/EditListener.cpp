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
		CEdit::CEditListener::CEditListener(CEdit *edit) :
			m_pEdit{ edit }
		{

		}

		void CEdit::CEditListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pEdit->m_pCanvas)
				m_pEdit->m_pCanvas->setValid(false);
			m_pEdit->Repaint(rect, true);
		}

		void CEdit::CEditListener::NotifyOnTextChanged(IBuiltInControl *sender)
		{
			if (m_pEdit->OnChange)
				m_pEdit->OnChange(m_pEdit);
		}
	}
}