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
		CCustomDropDown::CDropDownListener::CDropDownListener(CCustomDropDown *dropdown) :
			m_pDropDown{ dropdown }
		{

		}

		void CCustomDropDown::CDropDownListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			m_pDropDown->Repaint(rect, true);
		}

		void CCustomDropDown::CDropDownListener::NotifyOnTextChange(IBuiltInControl *sender)
		{
			if (m_pDropDown->OnChange)
				m_pDropDown->OnChange(m_pDropDown);
		}

		void CCustomDropDown::CDropDownListener::NotifyOnSelect(IBuiltInControl *sender, const int index)
		{
			if (m_pDropDown->OnSelect)
				m_pDropDown->OnSelect(m_pDropDown, index);
		}

		void CCustomDropDown::CDropDownListener::NotifyOnOpen(IBuiltInControl *sender)
		{
			if (!m_pDropDown->isCaptureMouse() && m_pDropDown->getForm())
				m_pDropDown->getForm()->CaptureMouse(m_pDropDown, true);
		}

		void CCustomDropDown::CDropDownListener::NotifyOnClose(IBuiltInControl *sender)
		{
			if (m_pDropDown->isCaptureMouse())
			{
				m_pDropDown->m_bIgnoreKillCaptureMouse = true;
				m_pDropDown->getForm()->ReleaseCaptureMouse();
				m_pDropDown->m_bIgnoreKillCaptureMouse = false;
			}
		}
	}
}