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
		CPaintBoxService::CPaintBoxService(CPaintBox *paintbox) :
			CControlService(paintbox),
			m_pPaintBox{ paintbox }
		{

		}
	#pragma endregion

	#pragma region State change notifications
		void CPaintBoxService::NotifyOnFreeResources()
		{
			if (m_pPaintBox->m_pCanvas)
			{
				m_pPaintBox->DrawEnd();
				m_pPaintBox->m_pCanvas->Release();
				m_pPaintBox->m_pCanvas = nullptr;
			}
		}

		void CPaintBoxService::NotifyOnResize()
		{
			if (m_pPaintBox->m_pCanvas)
				m_pPaintBox->m_pCanvas->setValid(false);
			m_pPaintBox->DrawEnd();
		}
	#pragma endregion

	#pragma region Paint notifications
		void CPaintBoxService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pPaintBox->getWidth(), 0) && ntl::IsGreater<float>(m_pPaintBox->getHeight(), 0))
				m_pPaintBox->Render();
		}
	#pragma endregion
	}
}