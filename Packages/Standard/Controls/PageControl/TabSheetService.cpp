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
		CTabSheetService::CTabSheetService(CTabSheet *tabsheet) :
			CControlService(tabsheet),
			m_pTabSheet{ tabsheet }
		{

		}
	#pragma endregion

		// State change notifications
		void CTabSheetService::NotifyOnAttach()
		{
			if (!m_pTabSheet->m_bCaptionChanged && m_pTabSheet->getForm())
				m_pTabSheet->setCaption(m_pTabSheet->m_sName);
		}
	}
}