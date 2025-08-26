// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
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
		CCoolBar::CToggleListScrollListener::CToggleListScrollListener(CCoolBar *control) :
			m_pControl{ control }
		{

		}

		void CCoolBar::CToggleListScrollListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pControl->m_pCanvasToggleList)
				m_pControl->m_pCanvasToggleList->setValid(false);
			m_pControl->Repaint(false);
		}

		void CCoolBar::CToggleListScrollListener::NotifyOnScroll(IBuiltInControl *sender)
		{
			m_pControl->UpdateHoveredElement();
			if (m_pControl->m_pCanvasToggleList)
				m_pControl->m_pCanvasToggleList->setValid(false);
			m_pControl->Repaint(false);
		}
	}
}