// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../ListItems/IListItemTreeViewLabel.h"
#include "CustomTreeViewListItemOwner.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	namespace standard
	{
		class IImageList;

		class CTreeView;

		class CTreeViewListItemOwner :public virtual IListItemOwnerTreeViewLabel, public CCustomTreeViewListItemOwner
		{
		private:
			CTreeView *m_pTreeView;
		public:
			IImageList *getImageList() override;

			CTreeViewListItemOwner(CTreeView *treeview);
		};
	}
}