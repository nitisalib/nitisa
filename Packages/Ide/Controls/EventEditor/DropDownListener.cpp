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
	namespace ide
	{
		CEventEditor::CDropDownListener::CDropDownListener(CEventEditor *editor) :
			m_pEditor{ editor }
		{

		}

		void CEventEditor::CDropDownListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
			m_pEditor->Repaint(false);
		}

		void CEventEditor::CDropDownListener::NotifyOnTextChange(IBuiltInControl *sender)
		{
			if (m_pEditor->m_aEvents[m_pEditor->m_iFocusedEventIndex]->setValue(m_pEditor->m_pHandler->getText()))
				m_pEditor->NotifyOnEventChange(m_pEditor->m_aEvents[m_pEditor->m_iFocusedEventIndex]);
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
			m_pEditor->Repaint(false);
		}

		void CEventEditor::CDropDownListener::NotifyOnSelect(IBuiltInControl *sender, const int index)
		{
			if (m_pEditor->m_aEvents[m_pEditor->m_iFocusedEventIndex]->setValue(m_pEditor->m_pHandler->getText()))
				m_pEditor->NotifyOnEventChange(m_pEditor->m_aEvents[m_pEditor->m_iFocusedEventIndex]);
		}

		void CEventEditor::CDropDownListener::NotifyOnOpen(IBuiltInControl *sender)
		{

		}

		void CEventEditor::CDropDownListener::NotifyOnClose(IBuiltInControl *sender)
		{

		}
	}
}