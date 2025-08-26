// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		CGroupFoldService::CGroupFoldService(CGroupFold *control):
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CGroupFoldService::AlignControls()
		{
			if (!m_pControl->m_bFolded)
				CControlService::AlignControls();
		}
	#pragma endregion

	#pragma region State change notifications
		void CGroupFoldService::NotifyOnAttach()
		{
			if (!m_pControl->m_bCaptionChanged && m_pControl->getForm())
				m_pControl->setCaption(m_pControl->m_sName);
		}

		void CGroupFoldService::NotifyOnDetach()
		{
			m_pControl->m_bHovered = false;
		}
	#pragma endregion

	#pragma region State change notifications
		void CGroupFoldService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
			if (m_pControl->m_pMask)
			{
				m_pControl->m_pMask->Release();
				m_pControl->m_pMask = nullptr;
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CGroupFoldService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_pMask)
					m_pControl->m_pMask->setValid(false);
			}
		}

		void CGroupFoldService::NotifyOnParentFontChange()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			if (m_pControl->m_pMask)
				m_pControl->m_pMask->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CGroupFoldService::NotifyOnEnable()
		{
			AlignControls();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			if (m_pControl->m_pMask)
				m_pControl->m_pMask->setValid(false);
		}

		void CGroupFoldService::NotifyOnDisable()
		{
			m_pControl->m_bHovered = false;
			AlignControls();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			if (m_pControl->m_pMask)
				m_pControl->m_pMask->setValid(false);
		}

		void CGroupFoldService::NotifyOnResize()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			if (m_pControl->m_pMask)
				m_pControl->m_pMask->setValid(false);
			if (!m_pControl->m_bFolded)
				m_pControl->m_fUnfoldedHeight = m_pControl->getHeight();
		}

		void CGroupFoldService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_pMask)
					m_pControl->m_pMask->setValid(false);
			}
		}

		void CGroupFoldService::NotifyOnFontChange()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			if (m_pControl->m_pMask)
				m_pControl->m_pMask->setValid(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CGroupFoldService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			m_bMaskActive = false;
			if (!m.LastPass)
			{
				if (ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
				{
					IRenderer *renderer{ m_pControl->getForm()->getRenderer() };
					Mat4f matrix{ m_pControl->getTransformMatrix() };
					m_pControl->Render(renderer, matrix);
					if (!m_pControl->m_bFolded && m_pControl->getControlCount() > 0 && m_pControl->m_bUseMask)
					{
						m_pControl->RenderMask(renderer);
						if (m_pControl->m_pMask)
						{
							renderer->PushMask(m_pControl->m_pMask, matrix);
							m_bMaskActive = true;
						}
					}
				}
				else if (m_pControl->getControlCount() > 0 && m_pControl->m_bUseMask)
					draw_children = false;
			}
			if (m_pControl->m_bFolded)
				draw_children = false;
		}

		void CGroupFoldService::NotifyOnPaintEnd(const MessagePaint &m)
		{
			if (m_bMaskActive)
			{
				m_pControl->getForm()->getRenderer()->PopMask();
				m_bMaskActive = false;
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CGroupFoldService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pControl->isEnabled(true) && m_pControl->UpdateHovered(m_pControl->FormToLocal(m.Position)))
			{
				if (!m_pControl->m_bFolded)
					AlignControls();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_pMask)
					m_pControl->m_pMask->setValid(false);
			}
		}

		void CGroupFoldService::NotifyOnMouseLeave()
		{
			if (m_pControl->isEnabled(true) && m_pControl->m_bHovered)
			{
				m_pControl->m_bHovered = false;
				if (!m_pControl->m_bFolded)
					AlignControls();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_pMask)
					m_pControl->m_pMask->setValid(false);
			}
		}

		void CGroupFoldService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isEnabled(true) && m_pControl->UpdateHovered(m_pControl->FormToLocal(m.Position)))
			{
				if (!m_pControl->m_bFolded)
					AlignControls();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_pMask)
					m_pControl->m_pMask->setValid(false);
			}
		}

		void CGroupFoldService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isEnabled(true) && !m.Middle && !m.Right && !m.Alt && !m.Ctrl && !m.Shift && m_pControl->m_bHovered)
			{
				m_pControl->Toggle();
				if (m_pControl->OnToggle)
					m_pControl->OnToggle(m_pControl);
				processed = true;
			}
		}
	#pragma endregion
	}
}