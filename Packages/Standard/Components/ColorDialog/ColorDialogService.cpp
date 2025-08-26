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
		CColorDialogService::CColorDialogService(CColorDialog *control):
			CComponentService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region State change notifications
		void CColorDialogService::NotifyOnAttach()
		{
			if (m_pControl->m_pDialogBoxColor)
				m_pControl->m_pDialogBoxColor->setForm(m_pControl->getForm());
		}

		void CColorDialogService::NotifyOnDetaching()
		{
			if (m_pControl->m_pDialogBoxColor)
				m_pControl->m_pDialogBoxColor->setForm(nullptr);
		}
	#pragma endregion

	#pragma region Control notifications
		void CColorDialogService::NotifyOnControlDetach(IControl *control)
		{
			if (m_pControl->m_pDialogBoxColor == control)
				m_pControl->m_pDialogBoxColor = nullptr;
		}
	#pragma endregion
	}
}