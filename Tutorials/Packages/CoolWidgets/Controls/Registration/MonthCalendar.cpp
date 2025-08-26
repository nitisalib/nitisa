#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
		CRegistration::CMonthCalendar::CMonthCalendar(CRegistration *control) :
			CBuiltInMonthCalendar(),
			m_pControl{ control }
		{

		}

		IControl * CRegistration::CMonthCalendar::getControl()
		{
			return m_pControl;
		}
	}
}