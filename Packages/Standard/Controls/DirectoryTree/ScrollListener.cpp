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
		CDirectoryTree::CScrollListener::CScrollListener(CDirectoryTree *directory_tree) :
			m_pDirectoryTree{ directory_tree }
		{

		}

		void CDirectoryTree::CScrollListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pDirectoryTree->m_pCanvas)
				m_pDirectoryTree->m_pCanvas->setValid(false);
			m_pDirectoryTree->Repaint(false);
		}

		void CDirectoryTree::CScrollListener::NotifyOnScroll(IBuiltInControl *sender)
		{
			m_pDirectoryTree->LockUpdate();
			m_pDirectoryTree->UnlockUpdate();
		}
	}
}