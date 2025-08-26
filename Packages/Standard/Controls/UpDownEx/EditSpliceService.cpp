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
		CUpDownEx::CEditSpliceService::CEditSpliceService(IEdit *edit, CUpDownEx *updown) :
			CControlSpliceService(edit),
			m_pUpDown{ updown }
		{

		}

		void CUpDownEx::CEditSpliceService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			CControlSpliceService::NotifyOnKeyDown(m, processed);
			m_pUpDown->QueryService()->NotifyOnKeyDown(m, processed);
		}

		void CUpDownEx::CEditSpliceService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			CControlSpliceService::NotifyOnKeyUp(m, processed);
			m_pUpDown->QueryService()->NotifyOnKeyUp(m, processed);
		}

		void CUpDownEx::CEditSpliceService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			CControlSpliceService::NotifyOnMouseVerticalWheel(m, processed);
			m_pUpDown->QueryService()->NotifyOnMouseVerticalWheel(m, processed);
		}
	}
}