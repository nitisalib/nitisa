// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	CFeedback::CFeedback(IFeedbackListener *listener)
	{
		m_pListener = listener;
	}

	bool CFeedback::setListener(IFeedbackListener *listener)
	{
		if (listener != m_pListener)
		{
			m_pListener = listener;
			return true;
		}
		return false;
	}
}