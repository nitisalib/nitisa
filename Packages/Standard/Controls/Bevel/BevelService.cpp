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
		CBevelService::CBevelService(CBevel *bevel) :
			CControlService(bevel),
			m_pBevel{ bevel }
		{

		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CBevelService::NotifyOnParentStyleChange()
		{
			if (m_pBevel->getStyle())
			{
				m_pBevel->UpdateFromStyle(m_pBevel->getStyle());
				if (m_pBevel->m_pCanvas)
					m_pBevel->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CBevelService::NotifyOnFreeResources()
		{
			if (m_pBevel->m_pCanvas)
			{
				m_pBevel->m_pCanvas->Release();
				m_pBevel->m_pCanvas = nullptr;
			}
		}

		void CBevelService::NotifyOnResize()
		{
			if (m_pBevel->m_pCanvas)
				m_pBevel->m_pCanvas->setValid(false);
		}

		void CBevelService::NotifyOnStyleChange()
		{
			if (m_pBevel->getStyle())
			{
				m_pBevel->UpdateFromStyle(m_pBevel->getStyle());
				if (m_pBevel->m_pCanvas)
					m_pBevel->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region Paint notifications
		void CBevelService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pBevel->getWidth(), 0) && ntl::IsGreater<float>(m_pBevel->getHeight(), 0))
				m_pBevel->Render();
		}
	#pragma endregion
	}
}