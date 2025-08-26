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
		CEventEditor::CDropDown::CDropDown(CEventEditor *editor) :
			CBuiltInDropDown(true, nullptr, GetItemText, nullptr),
			m_pEditor{ editor }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CEventEditor::CDropDown::getControl()
		{
			return m_pEditor;
		}
	#pragma endregion

	#pragma region Helpers
		String CEventEditor::CDropDown::GetItemText(IListItem *item)
		{
			return cast<standard::IListItemLabel*>(item)->getCaption();
		}
	#pragma endregion
	}
}