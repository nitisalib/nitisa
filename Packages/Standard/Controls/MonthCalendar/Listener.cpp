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
		CMonthCalendar::CListener::CListener(CMonthCalendar *control) :
			m_pControl{ control }
		{

		}

		void CMonthCalendar::CListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CMonthCalendar::CListener::NotifyOnChange(IBuiltInControl *sender)
		{
			if (m_pControl->OnChange)
				m_pControl->OnChange(m_pControl);
		}
	}
}