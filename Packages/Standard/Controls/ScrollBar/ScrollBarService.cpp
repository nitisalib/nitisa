// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
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
		CScrollBarService::CScrollBarService(CScrollBar *scrollbar) :
			CControlService(scrollbar),
			m_pScrollBar{ scrollbar }
		{

		}
	#pragma endregion

	#pragma region Notifications
		void CScrollBarService::NotifyOnParentStyleChange()
		{
			if (m_pScrollBar->getStyle())
			{
				m_pScrollBar->getScroll()->UpdateFromStyle(m_pScrollBar->getStyle(), m_pScrollBar->m_sClassName);
				if (m_pScrollBar->m_pCanvas)
					m_pScrollBar->m_pCanvas->setValid(false);
			}
		}

		void CScrollBarService::NotifyOnAttach()
		{
			if (m_pScrollBar->getForm())
				m_pScrollBar->getScroll()->NotifyOnAttach();
		}

		void CScrollBarService::NotifyOnFreeResources()
		{
			if (m_pScrollBar->m_pScroll)
				m_pScrollBar->m_pScroll->NotifyOnFreeResources();
			if (m_pScrollBar->m_pCanvas)
			{
				m_pScrollBar->m_pCanvas->Release();
				m_pScrollBar->m_pCanvas = nullptr;
			}
		}

		void CScrollBarService::NotifyOnEnable()
		{
			m_pScrollBar->getScroll()->setEnabled(true);
			if (m_pScrollBar->m_pCanvas)
				m_pScrollBar->m_pCanvas->setValid(false);
		}

		void CScrollBarService::NotifyOnDisable()
		{
			m_pScrollBar->getScroll()->setEnabled(false);
			if (m_pScrollBar->m_pCanvas)
				m_pScrollBar->m_pCanvas->setValid(false);
		}

		void CScrollBarService::NotifyOnResize()
		{
			m_pScrollBar->getScroll()->setSize(m_pScrollBar->getSize());
			if (m_pScrollBar->m_pCanvas)
				m_pScrollBar->m_pCanvas->setValid(false);
		}

		void CScrollBarService::NotifyOnStyleChange()
		{
			if (m_pScrollBar->getStyle())
			{
				m_pScrollBar->getScroll()->UpdateFromStyle(m_pScrollBar->getStyle(), m_pScrollBar->m_sClassName);
				if (m_pScrollBar->m_pCanvas)
					m_pScrollBar->m_pCanvas->setValid(false);
			}
		}

		void CScrollBarService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pScrollBar->getScroll()->NotifyOnMouseHover(m_pScrollBar->FormToLocal(m.Position)))
			{
				if (m_pScrollBar->m_pCanvas)
					m_pScrollBar->m_pCanvas->setValid(false);
				m_pScrollBar->Repaint(false);
			}
		}

		void CScrollBarService::NotifyOnMouseLeave()
		{
			if (m_pScrollBar->getScroll()->NotifyOnMouseLeave())
			{
				if (m_pScrollBar->m_pCanvas)
					m_pScrollBar->m_pCanvas->setValid(false);
				m_pScrollBar->Repaint(false);
			}
		}

		void CScrollBarService::NotifyOnKillCaptureMouse()
		{
			if (m_pScrollBar->m_pScroll)
				m_pScrollBar->m_pScroll->NotifyOnMouseDownCancel();
		}

		void CScrollBarService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pScrollBar->getWidth(), 0) && ntl::IsGreater<float>(m_pScrollBar->getHeight(), 0))
				m_pScrollBar->Render();
		}

		void CScrollBarService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pScrollBar->getScroll()->NotifyOnMouseMove(m_pScrollBar->FormToLocal(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				if (m_pScrollBar->m_pCanvas)
					m_pScrollBar->m_pCanvas->setValid(false);
				m_pScrollBar->Repaint(false);
			}
		}

		void CScrollBarService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pScrollBar->getScroll()->NotifyOnMouseLeftDown(m_pScrollBar->FormToLocal(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				m_pScrollBar->getForm()->CaptureMouse(m_pScrollBar, true);
				if (m_pScrollBar->m_pCanvas)
					m_pScrollBar->m_pCanvas->setValid(false);
				m_pScrollBar->Repaint(false);
			}
		}

		void CScrollBarService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			MouseUp(m.Position);
		}

		void CScrollBarService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CScrollBarService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CScrollBarService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CScrollBarService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CScrollBarService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CScrollBarService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CScrollBarService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CScrollBarService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pScrollBar->getScroll()->NotifyOnMouseVerticalWheel(m_pScrollBar->FormToLocal(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
			{
				if (m_pScrollBar->m_pCanvas)
					m_pScrollBar->m_pCanvas->setValid(false);
				m_pScrollBar->Repaint(false);
			}
		}

		void CScrollBarService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pScrollBar->getScroll()->NotifyOnMouseHorizontalWheel(m_pScrollBar->FormToLocal(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
			{
				if (m_pScrollBar->m_pCanvas)
					m_pScrollBar->m_pCanvas->setValid(false);
				m_pScrollBar->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Helpers
		void CScrollBarService::MouseUp(const PointF &pos)
		{
			if (m_pScrollBar->getScroll()->NotifyOnMouseLeftUp(m_pScrollBar->FormToLocal(pos), false, false, false, false, false))
			{
				if (m_pScrollBar->m_pCanvas)
					m_pScrollBar->m_pCanvas->setValid(false);
				m_pScrollBar->Repaint(false);
			}
			if (m_pScrollBar->isCaptureMouse())
				m_pScrollBar->getForm()->ReleaseCaptureMouse();
		}
	#pragma endregion
	}
}