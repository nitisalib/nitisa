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
		CDirectoryTree::CScroll::CScroll(CDirectoryTree *directory_tree) :
			CBuiltInScroll(),
			m_pDirectoryTree{ directory_tree }
		{

		}

		IControl *CDirectoryTree::CScroll::getControl()
		{
			return m_pDirectoryTree;
		}
	}
}