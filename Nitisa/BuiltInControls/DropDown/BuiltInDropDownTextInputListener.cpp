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
	CBuiltInDropDown::CTextInputListener::CTextInputListener(CBuiltInDropDown *dropdown) :
		m_pDropDown{ dropdown }
	{

	}

	void CBuiltInDropDown::CTextInputListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
	{
		if (m_pDropDown->m_pListener)
		{
			if (m_pDropDown->m_pCanvasControl)
				m_pDropDown->m_pCanvasControl->setValid(false);
			m_pDropDown->m_pListener->NotifyOnRepaint(m_pDropDown, rect);
		}
	}

	void CBuiltInDropDown::CTextInputListener::NotifyOnTextChanged(IBuiltInControl *sender)
	{
		IBuiltInDropDownListener *listener{ cast<IBuiltInDropDownListener*>(m_pDropDown->m_pListener) };
		if (listener)
			listener->NotifyOnTextChange(m_pDropDown);
	}
}