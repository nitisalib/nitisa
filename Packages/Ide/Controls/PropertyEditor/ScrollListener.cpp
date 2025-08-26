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
		CPropertyEditor::CScrollListener::CScrollListener(CPropertyEditor *editor) :
			m_pEditor{ editor }
		{

		}

		void CPropertyEditor::CScrollListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
			m_pEditor->Repaint(false);
		}

		void CPropertyEditor::CScrollListener::NotifyOnScroll(IBuiltInControl *sender)
		{
			if (m_pEditor->m_pHandler)
			{
				m_pEditor->m_fHandlerY = m_pEditor->CalculateHandlerY();
				m_pEditor->m_pHandler->setPosition(PointF{ m_pEditor->CalculateHandlerX(), m_pEditor->m_fHandlerY });
			}
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
			m_pEditor->Repaint(false);
		}
	}
}