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
		CImageService::CImageService(CImage *image) :
			CControlService(image),
			m_pImage{ image }
		{

		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CImageService::NotifyOnParentStyleChange()
		{
			if (m_pImage->getStyle())
			{
				m_pImage->UpdateFromStyle(m_pImage->getStyle());
				if (m_pImage->m_pCanvas)
					m_pImage->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CImageService::NotifyOnFreeResources()
		{
			if (m_pImage->m_pImage)
			{
				m_pImage->m_pImage->Release();
				m_pImage->m_pImage = nullptr;
			}
			if (m_pImage->m_pCanvas)
			{
				m_pImage->m_pCanvas->Release();
				m_pImage->m_pCanvas = nullptr;
			}
		}

		void CImageService::NotifyOnStyleChange()
		{
			if (m_pImage->getStyle())
			{
				m_pImage->UpdateFromStyle(m_pImage->getStyle());
				if (m_pImage->m_pCanvas)
					m_pImage->m_pCanvas->setValid(false);
			}
		}

		void CImageService::NotifyOnResize()
		{
			if (m_pImage->m_pCanvas)
				m_pImage->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CImageService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pImage->getWidth(), 0) && ntl::IsGreater<float>(m_pImage->getHeight(), 0))
				m_pImage->Render();
		}
	#pragma endregion
	}
}