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
	namespace ide
	{
		CHierarchyEditor::CListItemOwner::CListItemOwner(CHierarchyEditor *editor) :
			CCustomTreeViewListItemOwner(editor),
			m_pEditor{ editor }
		{

		}

		standard::IImageList *CHierarchyEditor::CListItemOwner::getImageList()
		{
			return m_pEditor->getImageList();
		}
	}
}