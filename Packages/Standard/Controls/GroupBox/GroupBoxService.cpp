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
		CGroupBoxService::CGroupBoxService(CGroupBox *groupbox) :
			CControlService(groupbox),
			m_pGroupBox{ groupbox }
		{

		}
	#pragma endregion

	#pragma region Notifications
		void CGroupBoxService::NotifyOnAttach()
		{
			if (!m_pGroupBox->m_bCaptionChanged && m_pGroupBox->getForm())
				m_pGroupBox->setCaption(m_pGroupBox->m_sName);
		}

		void CGroupBoxService::NotifyOnFreeResources()
		{
			if (m_pGroupBox->m_pCanvas)
			{
				m_pGroupBox->m_pCanvas->Release();
				m_pGroupBox->m_pCanvas = nullptr;
			}
			if (m_pGroupBox->m_pMask)
			{
				m_pGroupBox->m_pMask->Release();
				m_pGroupBox->m_pMask = nullptr;
			}
		}

		void CGroupBoxService::NotifyOnParentStyleChange()
		{
			if (m_pGroupBox->getStyle())
			{
				m_pGroupBox->UpdateFromStyle(m_pGroupBox->getStyle());
				if (m_pGroupBox->m_pCanvas)
					m_pGroupBox->m_pCanvas->setValid(false);
				if (m_pGroupBox->m_pMask)
					m_pGroupBox->m_pMask->setValid(false);
			}
		}

		void CGroupBoxService::NotifyOnParentFontChange()
		{
			if (m_pGroupBox->m_pCanvas)
				m_pGroupBox->m_pCanvas->setValid(false);
			if (m_pGroupBox->m_pMask)
				m_pGroupBox->m_pMask->setValid(false);
		}

		void CGroupBoxService::NotifyOnResize()
		{
			if (m_pGroupBox->m_pCanvas)
				m_pGroupBox->m_pCanvas->setValid(false);
			if (m_pGroupBox->m_pMask)
				m_pGroupBox->m_pMask->setValid(false);
		}

		void CGroupBoxService::NotifyOnStyleChange()
		{
			if (m_pGroupBox->getStyle())
			{
				m_pGroupBox->UpdateFromStyle(m_pGroupBox->getStyle());
				if (m_pGroupBox->m_pCanvas)
					m_pGroupBox->m_pCanvas->setValid(false);
				if (m_pGroupBox->m_pMask)
					m_pGroupBox->m_pMask->setValid(false);
			}
		}

		void CGroupBoxService::NotifyOnFontChange()
		{
			if (m_pGroupBox->m_pCanvas)
				m_pGroupBox->m_pCanvas->setValid(false);
			if (m_pGroupBox->m_pMask)
				m_pGroupBox->m_pMask->setValid(false);
		}

		void CGroupBoxService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			m_bMaskActive = false;
			if (!m.LastPass)
			{
				if (ntl::IsGreater<float>(m_pGroupBox->getWidth(), 0) && ntl::IsGreater<float>(m_pGroupBox->getHeight(), 0))
				{
					IRenderer *renderer{ m_pGroupBox->getForm()->getRenderer() };
					Mat4f matrix{ m_pGroupBox->getTransformMatrix() };
					m_pGroupBox->Render(renderer, matrix);
					if (m_pGroupBox->getControlCount() > 0 && m_pGroupBox->m_bUseMask)
					{
						m_pGroupBox->RenderMask(renderer);
						if (m_pGroupBox->m_pMask)
						{
							renderer->PushMask(m_pGroupBox->m_pMask, matrix);
							m_bMaskActive = true;
						}
					}
				}
				else if (m_pGroupBox->getControlCount() > 0 && m_pGroupBox->m_bUseMask)
					draw_children = false;
			}
		}

		void CGroupBoxService::NotifyOnPaintEnd(const MessagePaint &m)
		{
			if (m_bMaskActive)
			{
				m_pGroupBox->getForm()->getRenderer()->PopMask();
				m_bMaskActive = false;
			}
		}
	#pragma endregion
	}
}