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
		CFileList::CScrollListener::CScrollListener(CFileList *filelist) :
			m_pFileList{ filelist }
		{

		}

		void CFileList::CScrollListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pFileList->m_pCanvas)
				m_pFileList->m_pCanvas->setValid(false);
			m_pFileList->Repaint(false);
		}

		void CFileList::CScrollListener::NotifyOnScroll(IBuiltInControl *sender)
		{
			m_pFileList->UpdateHoveredItem();
			if (m_pFileList->m_pCanvas)
				m_pFileList->m_pCanvas->setValid(false);
			m_pFileList->Repaint(false);
		}
	}
}