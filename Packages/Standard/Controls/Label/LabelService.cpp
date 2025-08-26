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
		CLabelService::CLabelService(CLabel *label) :
			CControlService{ label },
			m_pLabel{ label }
		{

		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CLabelService::NotifyOnParentStyleChange()
		{
			if (m_pLabel->getStyle())
			{
				m_pLabel->UpdateFromStyle(m_pLabel->getStyle());
				if (m_pLabel->m_pCanvas)
					m_pLabel->m_pCanvas->setValid(false);
			}
		}

		void CLabelService::NotifyOnParentFontChange()
		{
			m_pLabel->UpdateAutoSize();
			if (m_pLabel->m_pCanvas)
				m_pLabel->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CLabelService::NotifyOnFreeResources()
		{
			if (m_pLabel->m_pCanvas)
			{
				m_pLabel->m_pCanvas->Release();
				m_pLabel->m_pCanvas = nullptr;
			}
		}

		void CLabelService::NotifyOnAttach()
		{
			if (m_pLabel->getForm())
			{
				if (!m_pLabel->m_bCaptionChanged)
					m_pLabel->setCaption(m_pLabel->m_sName);
				m_pLabel->UpdateAutoSize();
			}
		}

		void CLabelService::NotifyOnStyleChange()
		{
			if (m_pLabel->getStyle())
			{
				m_pLabel->UpdateFromStyle(m_pLabel->getStyle());
				if (m_pLabel->m_pCanvas)
					m_pLabel->m_pCanvas->setValid(false);
			}
		}

		void CLabelService::NotifyOnFontChange()
		{
			m_pLabel->UpdateAutoSize();
			if (m_pLabel->m_pCanvas)
				m_pLabel->m_pCanvas->setValid(false);
		}

		void CLabelService::NotifyOnResize()
		{
			if (m_pLabel->m_pCanvas)
				m_pLabel->m_pCanvas->setValid(false);
		}

		void CLabelService::NotifyOnEnable()
		{
			if (m_pLabel->m_pCanvas)
				m_pLabel->m_pCanvas->setValid(false);
		}

		void CLabelService::NotifyOnDisable()
		{
			if (m_pLabel->m_pCanvas)
				m_pLabel->m_pCanvas->setValid(false);
		}

		void CLabelService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pLabel->m_pCanvas)
				m_pLabel->m_pCanvas->setValid(false);
			m_pLabel->Repaint(false);
		}

		void CLabelService::NotifyOnMouseLeave()
		{
			if (m_pLabel->m_pCanvas)
				m_pLabel->m_pCanvas->setValid(false);
			m_pLabel->Repaint(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CLabelService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pLabel->getWidth(), 0) && ntl::IsGreater<float>(m_pLabel->getHeight(), 0))
				m_pLabel->Render();
		}
	#pragma endregion
	}
}