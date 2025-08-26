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
	#pragma region Constructor & destructor
		CFindDialogService::CFindDialogService(CFindDialog *control) :
			CComponentService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region State change notifications
		void CFindDialogService::NotifyOnAttach()
		{
			if (m_pControl->m_pDialogBoxFind)
				m_pControl->m_pDialogBoxFind->setForm(m_pControl->getForm());
		}

		void CFindDialogService::NotifyOnDetaching()
		{
			if (m_pControl->m_pDialogBoxFind)
				m_pControl->m_pDialogBoxFind->setForm(nullptr);
		}
	#pragma endregion

	#pragma region Control notifications
		void CFindDialogService::NotifyOnControlDetach(IControl *control)
		{
			if (m_pControl->m_pDialogBoxFind == control)
			{
				m_pControl->m_pDialogBoxFind = nullptr;
				m_pControl->m_bShown = false;
			}
		}
	#pragma endregion
	}
}