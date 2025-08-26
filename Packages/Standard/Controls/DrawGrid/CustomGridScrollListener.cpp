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
		CCustomGrid::CScrollListener::CScrollListener(CCustomGrid *control) :
			m_pControl{ control }
		{

		}

		void CCustomGrid::CScrollListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CCustomGrid::CScrollListener::NotifyOnScroll(IBuiltInControl *sender)
		{
			PointF old{ m_pControl->m_sScroll };
			if (cast<IBuiltInScroll*>(sender) == m_pControl->m_pVScroll)
				m_pControl->m_sScroll.Y = ntl::Clamp<float>(cast<IBuiltInScroll*>(sender)->getScroll(), 0, m_pControl->m_sMaxScroll.Y);
			else
				m_pControl->m_sScroll.X = ntl::Clamp<float>(cast<IBuiltInScroll*>(sender)->getScroll(), 0, m_pControl->m_sMaxScroll.X);
			if (IsNotEqual(m_pControl->m_sScroll, old))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	}
}