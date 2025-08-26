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
		CMemo::CScrollListener::CScrollListener(CMemo *memo) :
			m_pMemo{ memo }
		{

		}

		void CMemo::CScrollListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pMemo->m_pCanvas)
				m_pMemo->m_pCanvas->setValid(false);
			m_pMemo->Repaint(false);
		}

		void CMemo::CScrollListener::NotifyOnScroll(IBuiltInControl *sender)
		{
			if (m_pMemo->m_bHScrollEnabled)
				m_pMemo->getTextArea()->setScroll(PointF{ -m_pMemo->getHScroll()->getScroll(), m_pMemo->getTextArea()->getScroll().Y });
			if (m_pMemo->m_bVScrollEnabled)
				m_pMemo->getTextArea()->setScroll(PointF{ m_pMemo->getTextArea()->getScroll().X, -m_pMemo->getVScroll()->getScroll() });
			if (m_pMemo->m_pCanvas)
				m_pMemo->m_pCanvas->setValid(false);
			m_pMemo->Repaint(false);
		}
	}
}