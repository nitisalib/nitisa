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
	namespace fb
	{
	#pragma region Constructor & destructor
		CFormMain::CPackageControlListener::CPackageControlListener(CFormMain *form) :
			m_pForm{ form }
		{

		}
	#pragma endregion

	#pragma region Events
		void CFormMain::CPackageControlListener::OnCreateChild(IPackageControl *sender, IControl *parent, IControl *control)
		{
			m_pForm->OnCreateChild(m_pInfo, control, m_pActive);
		}

		void CFormMain::CPackageControlListener::OnCreateListItem(IPackageControl *sender, IListItem *parent, IListItem *item)
		{
			m_pForm->OnCreateListItem(item, m_pActive);
		}
	#pragma endregion
	}
}