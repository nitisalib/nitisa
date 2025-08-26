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
	CBuiltInDropDown::CScrollListener::CScrollListener(CBuiltInDropDown *dropdown) :
		m_pDropDown{ dropdown }
	{

	}

	void CBuiltInDropDown::CScrollListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
	{
		if (m_pDropDown->m_pListener)
		{
			if (m_pDropDown->m_pCanvasList)
				m_pDropDown->m_pCanvasList->setValid(false);
			m_pDropDown->m_pListener->NotifyOnRepaint(m_pDropDown, m_pDropDown->getListRenderRect()); // Change rect due list area is changed also but rect is only a scroll rect
		}
	}

	void CBuiltInDropDown::CScrollListener::NotifyOnScroll(IBuiltInControl *sender)
	{
		if (m_pDropDown->m_pListener)
		{
			m_pDropDown->m_fListScroll = m_pDropDown->getScroll()->getScroll();
			m_pDropDown->UpdateHoveredItem();
			if (m_pDropDown->m_pCanvasList)
				m_pDropDown->m_pCanvasList->setValid(false);
			m_pDropDown->m_pListener->NotifyOnRepaint(m_pDropDown, m_pDropDown->getListRenderRect());
		}
	}
}