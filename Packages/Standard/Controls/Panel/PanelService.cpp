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
		CPanelService::CPanelService(CPanel *panel) :
			CControlService{ panel },
			m_pPanel{ panel }
		{

		}
	#pragma endregion

	#pragma region Notifications
		void CPanelService::NotifyOnAttach()
		{
			if (!m_pPanel->m_bCaptionChanged && m_pPanel->getForm())
				m_pPanel->setCaption(m_pPanel->m_sName);
		}

		void CPanelService::NotifyOnFreeResources()
		{
			if (m_pPanel->m_pCanvas)
			{
				m_pPanel->m_pCanvas->Release();
				m_pPanel->m_pCanvas = nullptr;
			}
			if (m_pPanel->m_pMask)
			{
				m_pPanel->m_pMask->Release();
				m_pPanel->m_pMask = nullptr;
			}
		}

		void CPanelService::NotifyOnParentStyleChange()
		{
			if (m_pPanel->getStyle())
			{
				m_pPanel->UpdateFromStyle(m_pPanel->getStyle());
				if (m_pPanel->m_pCanvas)
					m_pPanel->m_pCanvas->setValid(false);
				if (m_pPanel->m_pMask)
					m_pPanel->m_pMask->setValid(false);
			}
		}

		void CPanelService::NotifyOnParentFontChange()
		{
			if (m_pPanel->m_pCanvas)
				m_pPanel->m_pCanvas->setValid(false);
		}

		void CPanelService::NotifyOnStyleChange()
		{
			if (m_pPanel->getStyle())
			{
				m_pPanel->UpdateFromStyle(m_pPanel->getStyle());
				if (m_pPanel->m_pCanvas)
					m_pPanel->m_pCanvas->setValid(false);
				if (m_pPanel->m_pMask)
					m_pPanel->m_pMask->setValid(false);
			}
		}

		void CPanelService::NotifyOnFontChange()
		{
			if (m_pPanel->m_pCanvas)
				m_pPanel->m_pCanvas->setValid(false);
		}

		void CPanelService::NotifyOnResize()
		{
			if (m_pPanel->m_pCanvas)
				m_pPanel->m_pCanvas->setValid(false);
			if (m_pPanel->m_pMask)
				m_pPanel->m_pMask->setValid(false);
		}

		void CPanelService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			m_bMaskActive = false;
			if (!m.LastPass)
			{
				if (ntl::IsGreater<float>(m_pPanel->getWidth(), 0) && ntl::IsGreater<float>(m_pPanel->getHeight(), 0))
				{
					IRenderer *renderer{ m_pPanel->getForm()->getRenderer() };
					Mat4f matrix{ m_pPanel->getTransformMatrix() };
					m_pPanel->Render(renderer, matrix);
					if (m_pPanel->getControlCount() > 0 && m_pPanel->m_bUseMask)
					{
						m_pPanel->RenderMask(renderer);
						if (m_pPanel->m_pMask)
						{
							renderer->PushMask(m_pPanel->m_pMask, matrix);
							m_bMaskActive = true;
						}
					}
				}
				else if (m_pPanel->getControlCount() > 0 && m_pPanel->m_bUseMask)
					draw_children = false;
			}
		}

		void CPanelService::NotifyOnPaintEnd(const MessagePaint &m)
		{
			if (m_bMaskActive)
			{
				m_pPanel->getForm()->getRenderer()->PopMask();
				m_bMaskActive = false;
			}
		}
	#pragma endregion
	}
}