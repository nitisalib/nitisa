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
		CScrollBar::CScrollListener::CScrollListener(CScrollBar *scrollbar) :
			m_pScrollBar{ scrollbar }
		{

		}

		void CScrollBar::CScrollListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pScrollBar->m_pCanvas)
				m_pScrollBar->m_pCanvas->setValid(false);
			m_pScrollBar->Repaint(false);
		}

		void CScrollBar::CScrollListener::NotifyOnScroll(IBuiltInControl *sender)
		{
			if (m_pScrollBar->OnScroll)
				m_pScrollBar->OnScroll(m_pScrollBar);
			if (m_pScrollBar->m_pCanvas)
				m_pScrollBar->m_pCanvas->setValid(false);
			m_pScrollBar->Repaint(false);
		}
	}
}