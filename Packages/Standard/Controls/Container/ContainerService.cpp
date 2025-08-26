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
		CContainerService::CContainerService(CContainer *container) :
			CControlService(container),
			m_pContainer{ container }
		{

		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CContainerService::NotifyOnParentStyleChange()
		{
			if (m_pContainer->getStyle())
				m_pContainer->UpdateFromStyle(m_pContainer->getStyle());
		}
	#pragma endregion

	#pragma region State change notifications
		void CContainerService::NotifyOnFreeResources()
		{
			if (m_pContainer->m_pMask)
			{
				m_pContainer->m_pMask->Release();
				m_pContainer->m_pMask = nullptr;
			}
		}

		void CContainerService::NotifyOnResize()
		{
			if (m_pContainer->m_pMask)
				m_pContainer->m_pMask->setValid(false);
		}

		void CContainerService::NotifyOnStyleChange()
		{
			if (m_pContainer->getStyle())
				m_pContainer->UpdateFromStyle(m_pContainer->getStyle());
		}
	#pragma endregion

	#pragma region Paint notifications
		void CContainerService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			m_bMaskActive = false;
			if (!m.LastPass)
			{
				if (ntl::IsGreater<float>(m_pContainer->getWidth(), 0) && ntl::IsGreater<float>(m_pContainer->getHeight(), 0))
				{
					IRenderer *renderer{ m_pContainer->getForm()->getRenderer() };
					Mat4f matrix{ m_pContainer->getTransformMatrix() };
					if (m_pContainer->m_cBackgroundGradient.getPointCount() >= 2 || m_pContainer->m_sBackgroundColor.A > 0 || (m_pContainer->m_bOutlineInEditor && Application->Editor))
						m_pContainer->Render(renderer, matrix);
					if (m_pContainer->m_bUseMask && m_pContainer->getControlCount() > 0)
					{
						m_pContainer->RenderMask(renderer, matrix);
						if (m_pContainer->m_pMask)
						{
							renderer->PushMask(m_pContainer->m_pMask, matrix);
							m_bMaskActive = true;
						}
					}
				}
				else if (m_pContainer->m_bUseMask && m_pContainer->getControlCount() > 0)
					draw_children = false;
			}
		}

		void CContainerService::NotifyOnPaintEnd(const MessagePaint &m)
		{
			if (!m.LastPass && m_bMaskActive)
			{
				m_pContainer->getForm()->getRenderer()->PopMask();
				m_bMaskActive = false;
			}
		}
	#pragma endregion
	}
}