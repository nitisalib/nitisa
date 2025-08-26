#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
		CRegistration::CTextInputListener::CTextInputListener(CRegistration *control) :
			m_pControl{ control }
		{

		}

		void CRegistration::CTextInputListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(rect, true);
		}

		void CRegistration::CTextInputListener::NotifyOnTextChanged(IBuiltInControl *sender)
		{
			if (m_pControl->OnChange)
				m_pControl->OnChange(m_pControl);
		}
	}
}