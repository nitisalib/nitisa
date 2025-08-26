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
		CTreeViewListItemOwner::CTreeViewListItemOwner(CTreeView *treeview) :
			CCustomTreeViewListItemOwner(treeview),
			m_pTreeView{ treeview }
		{

		}

		IImageList *CTreeViewListItemOwner::getImageList()
		{
			return m_pTreeView->getImageList();
		}
	}
}