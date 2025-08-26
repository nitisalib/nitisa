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
	#pragma region Constructor & destructor
		CPropertyEditor::CScroll::CScroll(CPropertyEditor *editor) :
			CBuiltInScroll(),
			m_pEditor{ editor }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CPropertyEditor::CScroll::getControl()
		{
			return m_pEditor;
		}
	#pragma endregion
	}
}