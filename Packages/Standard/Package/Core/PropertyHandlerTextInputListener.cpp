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
		CPropertyHandlerTextInputListener::CPropertyHandlerTextInputListener(CPropertyHandlerTextInput *handler) :
			m_pHandler{ handler }
		{

		}

		void CPropertyHandlerTextInputListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pHandler->m_pListener)
				m_pHandler->m_pListener->NotifyOnRepaint(m_pHandler, rect);
		}

		void CPropertyHandlerTextInputListener::NotifyOnTextChanged(IBuiltInControl *sender)
		{
			// Do nothing
		}
	}
}