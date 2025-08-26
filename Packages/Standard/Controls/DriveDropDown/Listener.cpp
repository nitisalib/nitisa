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
		CDriveDropDown::CListener::CListener(CDriveDropDown *dropdown) :
			m_pDropDown{ dropdown }
		{

		}

		void CDriveDropDown::CListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			m_pDropDown->Repaint(rect, true);
		}

		void CDriveDropDown::CListener::NotifyOnTextChange(IBuiltInControl *sender)
		{
			// Not used
		}

		void CDriveDropDown::CListener::NotifyOnSelect(IBuiltInControl *sender, const int index)
		{
			if (m_pDropDown->m_pDirectoryTree)
				m_pDropDown->m_pDirectoryTree->setRootDirectory(m_pDropDown->getSelectedDrive());
			if (m_pDropDown->OnSelect)
				m_pDropDown->OnSelect(m_pDropDown, index);
			m_pDropDown->Repaint(false);
		}

		void CDriveDropDown::CListener::NotifyOnOpen(IBuiltInControl *sender)
		{
			if (!m_pDropDown->isCaptureMouse() && m_pDropDown->getForm())
				m_pDropDown->getForm()->CaptureMouse(m_pDropDown, true);
		}

		void CDriveDropDown::CListener::NotifyOnClose(IBuiltInControl *sender)
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