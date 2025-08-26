// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
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
	#pragma region Constructor & destructor
		CTreeViewService::CTreeViewService(CTreeView *treeview) :
			CCustomTreeViewService(treeview),
			m_pTreeView{ treeview }
		{

		}
	#pragma endregion

	#pragma region Component notifications
		void CTreeViewService::NotifyOnComponentDetach(IComponent *component)
		{
			if (m_pTreeView->m_pImageList == component)
			{
				m_pTreeView->m_pImageList = nullptr;
				m_pTreeView->LockUpdate();
				m_pTreeView->UnlockUpdate();
			}
		}

		void CTreeViewService::NotifyOnComponentChange(IComponent *component)
		{
			if (m_pTreeView->m_pImageList == component)
			{
				m_pTreeView->LockUpdate();
				m_pTreeView->UnlockUpdate();
			}
		}
	#pragma endregion
	}
}