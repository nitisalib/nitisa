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
		CReplaceDialogService::CReplaceDialogService(CReplaceDialog *control) :
			CComponentService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region State change notifications
		void CReplaceDialogService::NotifyOnAttach()
		{
			if (m_pControl->m_pDialogBoxReplace)
				m_pControl->m_pDialogBoxReplace->setForm(m_pControl->getForm());
		}

		void CReplaceDialogService::NotifyOnDetaching()
		{
			if (m_pControl->m_pDialogBoxReplace)
				m_pControl->m_pDialogBoxReplace->setForm(nullptr);
		}
	#pragma endregion

	#pragma region Control notifications
		void CReplaceDialogService::NotifyOnControlDetach(IControl *control)
		{
			if (m_pControl->m_pDialogBoxReplace == control)
			{
				m_pControl->m_pDialogBoxReplace = nullptr;
				m_pControl->m_bShown = false;
			}
		}
	#pragma endregion
	}
}