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
		CScrollBox::CScrollListener::CScrollListener(CScrollBox *scrollbox) :
			m_pScrollBox{ scrollbox }
		{

		}

		void CScrollBox::CScrollListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pScrollBox->m_pCanvas)
				m_pScrollBox->m_pCanvas->setValid(false);
			m_pScrollBox->Repaint(false);
		}

		void CScrollBox::CScrollListener::NotifyOnScroll(IBuiltInControl *sender)
		{
			m_pScrollBox->UpdateTransformControls();
			if (m_pScrollBox->m_pCanvas)
				m_pScrollBox->m_pCanvas->setValid(false);
			m_pScrollBox->Repaint(false);
		}
	}
}