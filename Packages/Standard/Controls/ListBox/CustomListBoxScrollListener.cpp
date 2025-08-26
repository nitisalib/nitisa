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
		CCustomListBox::CScrollListener::CScrollListener(CCustomListBox *listbox) :
			m_pListBox{ listbox }
		{

		}

		void CCustomListBox::CScrollListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pListBox->m_pCanvas)
				m_pListBox->m_pCanvas->setValid(false);
			m_pListBox->Repaint(false);
		}

		void CCustomListBox::CScrollListener::NotifyOnScroll(IBuiltInControl *sender)
		{
			m_pListBox->UpdateHoveredItem();
			if (m_pListBox->m_pCanvas)
				m_pListBox->m_pCanvas->setValid(false);
			m_pListBox->Repaint(false);
		}
	}
}