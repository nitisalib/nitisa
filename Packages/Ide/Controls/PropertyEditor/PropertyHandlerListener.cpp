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
	namespace ide
	{
		CPropertyEditor::CPropertyHandlerListener::CPropertyHandlerListener(CPropertyEditor *editor) :
			m_pEditor{ editor }
		{

		}

		void CPropertyEditor::CPropertyHandlerListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
			m_pEditor->Repaint(rect, true);
		}

		void CPropertyEditor::CPropertyHandlerListener::NotifyOnPropertyChange(IBuiltInControl *sender, IProperty *property)
		{
			m_pEditor->NotifyOnPropertyChange(property);
		}
	}
}