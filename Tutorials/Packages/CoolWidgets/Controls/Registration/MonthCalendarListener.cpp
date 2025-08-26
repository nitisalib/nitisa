#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
		CRegistration::CMonthCalendarListener::CMonthCalendarListener(CRegistration *control) :
			m_pControl{ control }
		{

		}

		void CRegistration::CMonthCalendarListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pControl->m_pCanvasCalendar)
				m_pControl->m_pCanvasCalendar->setValid(false);
			m_pControl->Repaint(false);
		}

		void CRegistration::CMonthCalendarListener::NotifyOnChange(IBuiltInControl *sender)
		{
			m_pControl->CloseCalendar();
			if (m_pControl->OnChange)
				m_pControl->OnChange(m_pControl);
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}
	}
}