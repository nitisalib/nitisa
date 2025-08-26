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
		CMemo::CTextAreaListener::CTextAreaListener(CMemo *memo) :
			m_pMemo{ memo }
		{

		}

		void CMemo::CTextAreaListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pMemo->m_pCanvas)
				m_pMemo->m_pCanvas->setValid(false);
			m_pMemo->Repaint(false);
		}

		void CMemo::CTextAreaListener::NotifyOnTextChanged(IBuiltInControl *sender)
		{
			m_pMemo->AdjustElements();
			m_pMemo->getTextArea()->ScrollToCaret();
			m_pMemo->UpdateScrollPositions();
			if (m_pMemo->m_pCanvas)
				m_pMemo->m_pCanvas->setValid(false);
			if (m_pMemo->OnChange)
				m_pMemo->OnChange(m_pMemo);
			m_pMemo->Repaint(false);
		}

		void CMemo::CTextAreaListener::NotifyOnChanged(IBuiltInControl *sender)
		{
			m_pMemo->UpdateScrollPositions();
			if (m_pMemo->m_pCanvas)
				m_pMemo->m_pCanvas->setValid(false);
			m_pMemo->Repaint(false);
		}
	}
}