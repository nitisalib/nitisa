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
	#pragma region Constructor & destructor
		CProgressBarService::CProgressBarService(CProgressBar *progressbar) :
			CControlService(progressbar),
			m_pProgressBar{ progressbar }
		{

		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CProgressBarService::NotifyOnParentStyleChange()
		{
			if (m_pProgressBar->getStyle())
			{
				m_pProgressBar->UpdateFromStyle(m_pProgressBar->getStyle());
				if (m_pProgressBar->m_pCanvas)
					m_pProgressBar->m_pCanvas->setValid(false);
			}
		}

		void CProgressBarService::NotifyOnParentFontChange()
		{
			if (m_pProgressBar->m_pCanvas)
				m_pProgressBar->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CProgressBarService::NotifyOnFreeResources()
		{
			if (m_pProgressBar->m_pCanvas)
			{
				m_pProgressBar->m_pCanvas->Release();
				m_pProgressBar->m_pCanvas = nullptr;
			}
		}

		void CProgressBarService::NotifyOnStyleChange()
		{
			if (m_pProgressBar->getStyle())
			{
				m_pProgressBar->UpdateFromStyle(m_pProgressBar->getStyle());
				if (m_pProgressBar->m_pCanvas)
					m_pProgressBar->m_pCanvas->setValid(false);
			}
		}

		void CProgressBarService::NotifyOnFontChange()
		{
			if (m_pProgressBar->m_pCanvas)
				m_pProgressBar->m_pCanvas->setValid(false);
		}

		void CProgressBarService::NotifyOnResize()
		{
			if (m_pProgressBar->m_pCanvas)
				m_pProgressBar->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CProgressBarService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pProgressBar->getWidth(), 0) && ntl::IsGreater<float>(m_pProgressBar->getHeight(), 0))
				m_pProgressBar->Render();
		}
	#pragma endregion
	}
}