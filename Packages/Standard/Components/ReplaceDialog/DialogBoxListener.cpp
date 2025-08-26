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
		CReplaceDialog::CDialogBoxListener::CDialogBoxListener(CReplaceDialog *component) :
			m_pComponent{ component }
		{

		}
	#pragma endregion

	#pragma region Notifications
		void CReplaceDialog::CDialogBoxListener::OnClose(IDialogBox *sender)
		{
			CDialogBoxReplace *dlg{ cast<CDialogBoxReplace*>(sender) };
			m_pComponent->m_sText = dlg->getText();
			m_pComponent->m_sReplace = dlg->getReplace();
			m_pComponent->m_bMatchWholeWords = dlg->isMatchWholeWords();
			m_pComponent->m_bMatchCase = dlg->isMatchCase();
			m_pComponent->m_eSearchDirection = dlg->getSearchDirection();
			m_pComponent->m_bShown = false;
		}

		void CReplaceDialog::CDialogBoxListener::OnRestore(IDialogBox *sender)
		{

		}

		void CReplaceDialog::CDialogBoxListener::OnMinimize(IDialogBox *sender)
		{

		}

		void CReplaceDialog::CDialogBoxListener::OnMaximize(IDialogBox *sender)
		{

		}
	#pragma endregion
	}
}