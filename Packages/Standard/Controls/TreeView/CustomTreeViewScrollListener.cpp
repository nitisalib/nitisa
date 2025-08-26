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
		CCustomTreeView::CScrollListener::CScrollListener(CCustomTreeView *treeview) :
			m_pTreeView{ treeview }
		{

		}

		void CCustomTreeView::CScrollListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pTreeView->m_pCanvas)
				m_pTreeView->m_pCanvas->setValid(false);
			m_pTreeView->Repaint(false);
		}

		void CCustomTreeView::CScrollListener::NotifyOnScroll(IBuiltInControl *sender)
		{
			m_pTreeView->LockUpdate();
			m_pTreeView->UnlockUpdate();
		}
	}
}