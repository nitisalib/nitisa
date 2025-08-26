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
	namespace ide
	{
	#pragma region Constructor & destructor
		CFormViewService::CFormViewService(CFormView *formview) :
			CControlService(formview),
			m_pFormView{ formview },
			m_bDown{ false }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CFormViewService::CancelDown(const bool check_capture)
		{
			if (m_bDown)
			{
				m_bDown = false;
				if (check_capture && m_pFormView->isCaptureMouse())
					m_pFormView->getForm()->ReleaseCaptureMouse();
			}
		}

		CFormViewService::Element CFormViewService::ElementAtCursor(const PointF &position)
		{
			PointF p{ m_pFormView->FormToLocal(position) };
			if (p.X >= 0 && p.X < m_pFormView->getWidth() && p.Y >= 0 && p.Y < m_pFormView->getHeight())
			{
				if (p.X >= m_pFormView->getWidth() - m_pFormView->m_sLayout.Left.Size - m_pFormView->m_sBorderWidth.Right && p.X < m_pFormView->getWidth() - m_pFormView->m_sBorderWidth.Right)
				{
					if (p.Y >= m_pFormView->getHeight() - m_pFormView->m_sLayout.Bottom.Size - m_pFormView->m_sBorderWidth.Bottom && p.Y < m_pFormView->getHeight() - m_pFormView->m_sBorderWidth.Bottom)
						return Element::Corner;
					return Element::Right;
				}
				if (p.Y >= m_pFormView->getHeight() - m_pFormView->m_sLayout.Bottom.Size - m_pFormView->m_sBorderWidth.Bottom && p.Y < m_pFormView->getHeight() - m_pFormView->m_sBorderWidth.Bottom)
					return Element::Bottom;
			}
			return Element::None;
		}
	#pragma endregion

	#pragma region Control notifications
		void CFormViewService::NotifyOnControlSetFocus(IControl *control, const MessageFocus &m)
		{
			if (control == m_pFormView->getControl(0))
			{
				if (m_pFormView->m_pCanvas)
					m_pFormView->m_pCanvas->setValid(false);
				m_pFormView->Repaint(false);
			}
		}

		void CFormViewService::NotifyOnControlKillFocus(IControl *control)
		{
			if (control == m_pFormView->getControl(0))
			{
				if (m_pFormView->m_pCanvas)
					m_pFormView->m_pCanvas->setValid(false);
				m_pFormView->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CFormViewService::NotifyOnParentFontChange()
		{
			if (m_pFormView->m_pCanvas)
				m_pFormView->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CFormViewService::NotifyOnFreeResources()
		{
			m_pFormView->FreeLayoutTextures();
			if (m_pFormView->m_pCanvas)
			{
				m_pFormView->m_pCanvas->Release();
				m_pFormView->m_pCanvas = nullptr;
			}
		}

		void CFormViewService::NotifyOnResize()
		{
			if (m_pFormView->m_pCanvas)
				m_pFormView->m_pCanvas->setValid(false);
		}

		void CFormViewService::NotifyOnFontChange()
		{
			if (m_pFormView->m_pCanvas)
				m_pFormView->m_pCanvas->setValid(false);
		}

		void CFormViewService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CFormViewService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pFormView->getWidth(), 0) && ntl::IsGreater<float>(m_pFormView->getHeight(), 0))
				m_pFormView->Render();
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CFormViewService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_bDown)
			{
				PointF p{ m_pFormView->getParent() ? m_pFormView->getParent()->FormToLocal(m.Position) : m.Position };
				switch (m_eDownElement)
				{
				case Element::Right:
					m_pFormView->setWidth(m_sDownSize.X + (p.X - m_sDownPosition.X));
					break;
				case Element::Bottom:
					m_pFormView->setHeight(m_sDownSize.Y + (p.Y - m_sDownPosition.Y));
					break;
				case Element::Corner:
					m_pFormView->setSize(PointF{ m_sDownSize.X + (p.X - m_sDownPosition.X), m_sDownSize.Y + (p.Y - m_sDownPosition.Y) });
					break;
				default:
					break;
				}
			}
		}

		void CFormViewService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m_bDown && !m.Middle && !m.Right)
			{
				m_eDownElement = ElementAtCursor(m.Position);
				if (m_eDownElement != Element::None)
				{
					m_sDownPosition = m_pFormView->getParent() ? m_pFormView->getParent()->FormToLocal(m.Position) : m.Position;
					m_sDownSize = m_pFormView->getSize();
					m_bDown = true;
					m_pFormView->getForm()->CaptureMouse(m_pFormView, true);
				}
				else
					CancelDown(true);
			}
			else
				CancelDown(true);
		}

		void CFormViewService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			CancelDown(true);
		}

		void CFormViewService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CFormViewService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CFormViewService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CFormViewService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CFormViewService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CFormViewService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CFormViewService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}
	#pragma endregion
	}
}