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
		CDatePicker::CListener::CListener(CDatePicker *control) :
			m_pControl{ control }
		{

		}

		void CDatePicker::CListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pControl->m_pCanvasCalendar)
				m_pControl->m_pCanvasCalendar->setValid(false);
			m_pControl->Repaint(false);
		}

		void CDatePicker::CListener::NotifyOnChange(IBuiltInControl *sender)
		{
			m_pControl->Close();
			if (m_pControl->OnChange)
				m_pControl->OnChange(m_pControl);
		}
	}
}