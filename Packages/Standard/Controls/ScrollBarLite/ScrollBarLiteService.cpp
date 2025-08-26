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
		CScrollBarLiteService::CScrollBarLiteService(CScrollBarLite *control) :
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Notifications
		void CScrollBarLiteService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->getScroll()->UpdateFromStyle(m_pControl->getStyle(), m_pControl->m_sClassName);
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CScrollBarLiteService::NotifyOnAttach()
		{
			if (m_pControl->getForm())
				m_pControl->getScroll()->NotifyOnAttach();
		}

		void CScrollBarLiteService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pScroll)
				m_pControl->m_pScroll->NotifyOnFreeResources();
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
		}

		void CScrollBarLiteService::NotifyOnEnable()
		{
			m_pControl->getScroll()->setEnabled(true);
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CScrollBarLiteService::NotifyOnDisable()
		{
			m_pControl->getScroll()->setEnabled(false);
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CScrollBarLiteService::NotifyOnResize()
		{
			m_pControl->getScroll()->setSize(m_pControl->getSize());
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CScrollBarLiteService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->getScroll()->UpdateFromStyle(m_pControl->getStyle(), m_pControl->m_sClassName);
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CScrollBarLiteService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pControl->getScroll()->NotifyOnMouseHover(m_pControl->FormToLocal(m.Position)))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CScrollBarLiteService::NotifyOnMouseLeave()
		{
			if (m_pControl->getScroll()->NotifyOnMouseLeave())
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CScrollBarLiteService::NotifyOnKillCaptureMouse()
		{
			if (m_pControl->m_pScroll)
				m_pControl->m_pScroll->NotifyOnMouseDownCancel();
		}

		void CScrollBarLiteService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
				m_pControl->Render();
		}

		void CScrollBarLiteService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->getScroll()->NotifyOnMouseMove(m_pControl->FormToLocal(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CScrollBarLiteService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->getScroll()->NotifyOnMouseLeftDown(m_pControl->FormToLocal(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				m_pControl->getForm()->CaptureMouse(m_pControl, true);
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CScrollBarLiteService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			MouseUp(m.Position);
		}

		void CScrollBarLiteService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CScrollBarLiteService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CScrollBarLiteService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CScrollBarLiteService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CScrollBarLiteService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CScrollBarLiteService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CScrollBarLiteService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m.Position);
		}

		void CScrollBarLiteService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->getScroll()->NotifyOnMouseVerticalWheel(m_pControl->FormToLocal(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CScrollBarLiteService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->getScroll()->NotifyOnMouseHorizontalWheel(m_pControl->FormToLocal(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Helpers
		void CScrollBarLiteService::MouseUp(const PointF &pos)
		{
			if (m_pControl->getScroll()->NotifyOnMouseLeftUp(m_pControl->FormToLocal(pos), false, false, false, false, false))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}
	#pragma endregion
	}
}