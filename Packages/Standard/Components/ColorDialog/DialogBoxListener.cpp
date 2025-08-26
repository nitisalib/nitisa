// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		CColorDialog::CDialogBoxListener::CDialogBoxListener(CColorDialog *component) :
			m_pComponent{ component }
		{

		}
	#pragma endregion

	#pragma region Notifications
		void CColorDialog::CDialogBoxListener::OnClose(IDialogBox *sender)
		{
			if (sender->getModalResult() == ModalResult::Ok)
			{
				m_pComponent->m_sColor = cast<CDialogBoxColor*>(sender)->getValue();
				if (m_pComponent->m_pColorDialogListener)
					m_pComponent->m_pColorDialogListener->OnApply(m_pComponent);
				if (m_pComponent->OnApply)
					m_pComponent->OnApply(m_pComponent);
			}
		}

		void CColorDialog::CDialogBoxListener::OnRestore(IDialogBox *sender)
		{

		}

		void CColorDialog::CDialogBoxListener::OnMinimize(IDialogBox *sender)
		{

		}

		void CColorDialog::CDialogBoxListener::OnMaximize(IDialogBox *sender)
		{

		}
	#pragma endregion
	}
}