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
		CImageListEditor::CScroll::CScroll(CImageListEditor *editor) :
			CBuiltInScroll(),
			m_pEditor{ editor }
		{

		}

		IControl *CImageListEditor::CScroll::getControl()
		{
			return m_pEditor;
		}
	}
}