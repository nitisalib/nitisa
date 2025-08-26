// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

#ifdef __ANDROID__
namespace nitisa
{
	namespace platform
	{
		namespace android
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
					for (auto &pos : m_pApplication->m_aWindows)
						if (form->QueryService()->getWindow() == pos.Window)
						{
							pos.Form = form;
							break;
						}
			}

			void CApplicationService::Remove(IForm *form)
			{
				for (auto &pos : m_pApplication->m_aWindows)
					if (pos.Form == form)
					{
						pos.Form = nullptr;
						break;
					}
			}

			void CApplicationService::SendTranslateChangeNotification()
			{
				for (auto pos : m_pApplication->m_aWindows)
					if (pos.Form)
					{
						CLockRepaint lock{ pos.Form };
						CNotifier::TranslateChange(pos.Form);
						pos.Form->UpdateHoveredControl();
					}
			}
		}
	}
}
#endif