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
		CImageListEditor::CScrollListener::CScrollListener(CImageListEditor *editor) :
			m_pEditor{ editor }
		{

		}

		void CImageListEditor::CScrollListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
			m_pEditor->Repaint(false);
		}

		void CImageListEditor::CScrollListener::NotifyOnScroll(IBuiltInControl *sender)
		{
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
			m_pEditor->Repaint(false);
		}
	}
}