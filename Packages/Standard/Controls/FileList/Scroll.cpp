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
	#pragma region Constructor & destructor
		CFileList::CScroll::CScroll(CFileList *filelist) :
			CBuiltInScroll(),
			m_pFileList{ filelist }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CFileList::CScroll::getControl()
		{
			return m_pFileList;
		}
	#pragma endregion
	}
}