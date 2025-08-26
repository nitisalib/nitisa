// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#if defined(__linux__) && !defined(__ANDROID__)

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
			CApplicationService::CApplicationService(CApplication *application) :
				m_pApplication{ application }
			{

			}

			void CApplicationService::Release()
			{
				delete this;
			}

			void CApplicationService::Add(IForm *form)
			{
				if (form)
					for (int i = 0; i < m_pApplication->getWindowCount(); i++)
						if (form->QueryService()->getWindow() == m_pApplication->getWindow(i))
						{
							m_pApplication->setForm(i, form);
							break;
						}
			}

			void CApplicationService::Remove(IForm *form)
			{
				for (int i = 0; i < m_pApplication->getWindowCount(); i++)
					if (m_pApplication->getWindowForm(i) == form)
					{
						m_pApplication->setForm(i, nullptr);
						break;
					}
			}

			void CApplicationService::SendTranslateChangeNotification()
			{
				IForm *form;
				for (int i = 0; i < m_pApplication->getWindowCount(); i++)
					if ((form = m_pApplication->getWindowForm(i)))
					{
						CLockRepaint lock{ form };
						CNotifier::TranslateChange(form);
						form->UpdateHoveredControl();
					}
			}
		}
	}
}
#endif