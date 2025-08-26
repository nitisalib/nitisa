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
		CPropertyHandlerDropDown::CListener::CListener(CPropertyHandlerDropDown *handler) :
			m_pHandler{ handler }
		{

		}

		void CPropertyHandlerDropDown::CListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pHandler->getListener())
				m_pHandler->getListener()->NotifyOnRepaint(m_pHandler, rect);
		}

		void CPropertyHandlerDropDown::CListener::NotifyOnTextChange(IBuiltInControl *sender)
		{
			// Do nothing
		}

		void CPropertyHandlerDropDown::CListener::NotifyOnSelect(IBuiltInControl *sender, const int index)
		{
			m_pHandler->NotifyOnSelect(index);
		}

		void CPropertyHandlerDropDown::CListener::NotifyOnOpen(IBuiltInControl *sender)
		{
			if (sender->getControl()->getForm())
				sender->getControl()->getForm()->CaptureMouse(sender->getControl(), true);
		}

		void CPropertyHandlerDropDown::CListener::NotifyOnClose(IBuiltInControl *sender)
		{
			if (sender->getControl()->getForm() && sender->getControl()->isCaptureMouse())
				sender->getControl()->getForm()->ReleaseCaptureMouse();
		}
	}
}