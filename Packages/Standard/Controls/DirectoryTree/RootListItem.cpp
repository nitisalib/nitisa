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
		CDirectoryTree::CRootListItem::CRootListItem() :CListItem(L"DirectoryTreeRootListItem", true)
		{

		}

		IListItem *CDirectoryTree::CRootListItem::Clone()
		{
			CDirectoryTree::CRootListItem *result{ new CDirectoryTree::CRootListItem() };
			Copy(result);
			return result;
		}
	}
}