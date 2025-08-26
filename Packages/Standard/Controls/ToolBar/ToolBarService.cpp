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
		CToolBarService::CToolBarService(CToolBar *toolbar) :
			CControlService(toolbar),
			m_pToolBar{ toolbar },
			m_bIgnoreAlign{ false },
			m_bDown{ false },
			m_hTimer{ nullptr }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CToolBarService::AlignControls()
		{
			if (!m_bIgnoreAlign)
			{
				CLockRepaint lock{ m_pToolBar };
				m_bIgnoreAlign = true;
				RectF client{
					m_pToolBar->m_sBorderWidth.Left + m_pToolBar->m_sPadding.Left,
					m_pToolBar->m_sBorderWidth.Top + m_pToolBar->m_sPadding.Top,
					m_pToolBar->getWidth() - m_pToolBar->m_sBorderWidth.Right - m_pToolBar->m_sPadding.Right,
					m_pToolBar->getHeight() - m_pToolBar->m_sBorderWidth.Bottom - m_pToolBar->m_sPadding.Bottom };
				float width{ 0 };
				// Update size
				for (int i = 0; i < m_pToolBar->getControlCount(); i++)
				{
					if (!m_pToolBar->getControl(i)->isVisible(false))
						continue;
					PointF size{ AdjustByConstraints(m_pToolBar->getControl(i)->getSize(), m_pToolBar->getControl(i)->getConstraints()) };
					size = PointF{ size.X, client.height() };
					if (m_pToolBar->m_eAlignTo == IToolBar::AlignTo::Left)
						client.Left += size.X + m_pToolBar->m_fDistance;
					else
						client.Right -= size.X + m_pToolBar->m_fDistance;
					if (IsNotEqual(size, m_pToolBar->getControl(i)->getSize()))
					{
						m_pToolBar->getControl(i)->QueryService()->setSize(size);
						m_pToolBar->getControl(i)->QueryService()->AlignControls();
						NotifyResize(m_pToolBar->getControl(i));
					}
					width += m_pToolBar->getControl(i)->getWidth() + m_pToolBar->m_fDistance;
				}
				// Update scroll
				if (ntl::IsGreater<float>(width, 0))
					width -= m_pToolBar->m_fDistance;
				if (ntl::IsGreater<float>(width, m_pToolBar->getWidth() - m_pToolBar->m_sBorderWidth.Left - m_pToolBar->m_sBorderWidth.Right - m_pToolBar->m_sPadding.Left - m_pToolBar->m_sPadding.Right))
				{
					m_pToolBar->m_fScrollMax = width - m_pToolBar->getWidth() + m_pToolBar->m_sBorderWidth.Left + m_pToolBar->m_sBorderWidth.Right + m_pToolBar->m_sPadding.Left + m_pToolBar->m_sPadding.Right + 2 * m_pToolBar->m_fScrollerSize;
					m_pToolBar->m_fScroll = ntl::Min<float>(m_pToolBar->m_fScroll, m_pToolBar->m_fScrollMax);
				}
				else
					m_pToolBar->m_fScrollMax = m_pToolBar->m_fScroll = 0;
				// Update position
				UpdatePositions();
				if (m_pToolBar->m_pCanvas)
					m_pToolBar->m_pCanvas->setValid(false);
				if (m_pToolBar->m_pMask)
					m_pToolBar->m_pMask->setValid(false);
				m_pToolBar->Repaint(false);
				m_bIgnoreAlign = false;
			}
		}

		void CToolBarService::NotifyResize(IControl *control)
		{
			control->QueryService()->NotifyOnResize();
			if (control->OnResize)
				control->OnResize(control);
			for (int i = 0; i < control->getControlCount(); i++)
			{
				control->getControl(i)->QueryService()->NotifyOnParentResize();
				if (control->getControl(i)->OnParentResize)
					control->getControl(i)->OnParentResize(control->getControl(i));
			}
		}

		void CToolBarService::CancelDown(const bool check_capture)
		{
			if (m_bDown)
			{
				m_bDown = false;
				if (m_hTimer)
				{
					m_pToolBar->getForm()->DeleteTimer(m_hTimer);
					m_hTimer = nullptr;
				}
				m_pToolBar->m_eDownElement = CToolBar::Element::None;
				if (check_capture && m_pToolBar->isCaptureMouse())
					m_pToolBar->getForm()->ReleaseCaptureMouse();
				if (m_pToolBar->m_pCanvas)
					m_pToolBar->m_pCanvas->setValid(false);
				m_pToolBar->Repaint(false);
			}
		}

		void CToolBarService::UpdatePositions()
		{
			if (m_pToolBar->m_eAlignTo == IToolBar::AlignTo::Left)
			{
				float left{ m_pToolBar->m_sBorderWidth.Left + m_pToolBar->m_sPadding.Left + (ntl::IsGreater<float>(m_pToolBar->m_fScrollMax, 0 )? m_pToolBar->m_fScrollerSize : 0) };
				for (int i = 0; i < m_pToolBar->getControlCount(); i++)
				{
					if (!m_pToolBar->getControl(i)->isVisible(false))
						continue;
					m_pToolBar->getControl(i)->getTransform()->QueryService()->Transform(left - m_pToolBar->m_fScroll, m_pToolBar->m_sBorderWidth.Top + m_pToolBar->m_sPadding.Top, 0, 1, 1, 1, 0, 0, 0);
					left += m_pToolBar->getControl(i)->getWidth() + m_pToolBar->m_fDistance;
				}
			}
			else
			{
				float right{ m_pToolBar->getWidth() - m_pToolBar->m_sBorderWidth.Right - m_pToolBar->m_sPadding.Right - (ntl::IsGreater<float>(m_pToolBar->m_fScrollMax, 0) ? m_pToolBar->m_fScrollerSize : 0) };
				for (int i = 0; i < m_pToolBar->getControlCount(); i++)
				{
					if (!m_pToolBar->getControl(i)->isVisible(false))
						continue;
					m_pToolBar->getControl(i)->getTransform()->QueryService()->Transform(
						right - m_pToolBar->getControl(i)->getWidth() - (m_pToolBar->m_eAlignTo == IToolBar::AlignTo::Left ? 1 : -1 ) * m_pToolBar->m_fScroll,
						m_pToolBar->m_sBorderWidth.Top + m_pToolBar->m_sPadding.Top, 0, 1, 1, 1, 0, 0, 0);
					right -= m_pToolBar->getControl(i)->getWidth() + m_pToolBar->m_fDistance;
				}
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CToolBarService::NotifyOnParentStyleChange()
		{
			if (m_pToolBar->getStyle())
			{
				m_pToolBar->UpdateFromStyle(m_pToolBar->getStyle());
				if (m_pToolBar->m_pCanvas)
					m_pToolBar->m_pCanvas->setValid(false);
				if (m_pToolBar->m_pMask)
					m_pToolBar->m_pMask->setValid(false);
			}
		}
	#pragma endregion

	#pragma region Notifications from child controls
		void CToolBarService::NotifyOnChildTransform(IControl *control)
		{
			AlignControls();
		}

		void CToolBarService::NotifyOnChildResize(IControl *control)
		{
			AlignControls();
		}

		void CToolBarService::NotifyOnChildShow(IControl *control)
		{
			AlignControls();
		}

		void CToolBarService::NotifyOnChildHide(IControl *control)
		{
			AlignControls();
		}

		void CToolBarService::NotifyOnChildAttach(IControl *control)
		{
			AlignControls();
		}

		void CToolBarService::NotifyOnChildDetach(IControl *control)
		{
			AlignControls();
		}
	#pragma endregion

	#pragma region State change notifications
		void CToolBarService::NotifyOnFreeResources()
		{
			if (m_pToolBar->m_pCanvas)
			{
				m_pToolBar->m_pCanvas->Release();
				m_pToolBar->m_pCanvas = nullptr;
			}
			if (m_pToolBar->m_pMask)
			{
				m_pToolBar->m_pMask->Release();
				m_pToolBar->m_pMask = nullptr;
			}
		}

		void CToolBarService::NotifyOnStyleChange()
		{
			if (m_pToolBar->getStyle())
			{
				m_pToolBar->UpdateFromStyle(m_pToolBar->getStyle());
				if (m_pToolBar->m_pCanvas)
					m_pToolBar->m_pCanvas->setValid(false);
				if (m_pToolBar->m_pMask)
					m_pToolBar->m_pMask->setValid(false);
			}
		}

		void CToolBarService::NotifyOnResize()
		{
			if (m_pToolBar->m_pCanvas)
				m_pToolBar->m_pCanvas->setValid(false);
			if (m_pToolBar->m_pMask)
				m_pToolBar->m_pMask->setValid(false);
		}

		void CToolBarService::NotifyOnEnable()
		{
			if (m_pToolBar->m_pCanvas)
				m_pToolBar->m_pCanvas->setValid(false);
		}

		void CToolBarService::NotifyOnDisable()
		{
			if (m_pToolBar->m_pCanvas)
				m_pToolBar->m_pCanvas->setValid(false);
		}

		void CToolBarService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pToolBar->UpdateHoveredElement(m_pToolBar->FormToLocal(m.Position)))
			{
				if (m_pToolBar->m_pCanvas)
					m_pToolBar->m_pCanvas->setValid(false);
				m_pToolBar->Repaint(false);
			}
		}

		void CToolBarService::NotifyOnMouseLeave()
		{
			if (m_pToolBar->m_eHoveredElement != CToolBar::Element::None)
			{
				m_pToolBar->m_eHoveredElement = CToolBar::Element::None;
				if (m_pToolBar->m_pCanvas)
					m_pToolBar->m_pCanvas->setValid(false);
				m_pToolBar->Repaint(false);
			}
		}

		void CToolBarService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CToolBarService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			m_bMaskActive = false;
			if (!m.LastPass)
			{
				if (ntl::IsGreater<float>(m_pToolBar->getWidth(), 0) && ntl::IsGreater<float>(m_pToolBar->getHeight(), 0))
				{
					IRenderer *renderer{ m_pToolBar->getForm()->getRenderer() };
					Mat4f matrix{ m_pToolBar->getTransformMatrix() };
					m_pToolBar->Render(renderer, matrix);
					if (m_pToolBar->m_bUseMask && ntl::IsGreater<float>(m_pToolBar->m_fScrollMax, 0))
					{
						m_pToolBar->RenderMask(renderer);
						if (m_pToolBar->m_pMask)
						{
							renderer->PushMask(m_pToolBar->m_pMask, matrix);
							m_bMaskActive = true;
						}
					}
				}
				else
					draw_children = false;
			}
		}

		void CToolBarService::NotifyOnPaintEnd(const MessagePaint &m)
		{
			if (m_bMaskActive)
			{
				m_pToolBar->getForm()->getRenderer()->PopMask();
				m_bMaskActive = false;
			}
		}
	#pragma endregion

	#pragma region Input notifications
		void CToolBarService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pToolBar->UpdateHoveredElement(m_pToolBar->FormToLocal(m.Position)))
			{
				if (m_pToolBar->m_pCanvas)
					m_pToolBar->m_pCanvas->setValid(false);
				m_pToolBar->Repaint(false);
			}
		}

		void CToolBarService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m_bDown && !m.Middle && !m.Right && (m_pToolBar->m_eHoveredElement == CToolBar::Element::LeftScroller || m_pToolBar->m_eHoveredElement == CToolBar::Element::RightScroller))
			{
				m_bDown = true;
				m_pToolBar->m_eDownElement = m_pToolBar->m_eHoveredElement;
				float last_scroll{ m_pToolBar->m_fScroll };
				switch (m_pToolBar->m_eDownElement)
				{
				case CToolBar::Element::LeftScroller:
					m_pToolBar->m_fScroll = ntl::Min<float>(m_pToolBar->m_fScrollMax, ntl::Max<float>(0, m_pToolBar->m_fScroll - (m_pToolBar->m_eAlignTo == IToolBar::AlignTo::Left ? 1 : -1) * m_pToolBar->m_fScrollDeltaTimer));
					break;
				case CToolBar::Element::RightScroller:
					m_pToolBar->m_fScroll = ntl::Min<float>(m_pToolBar->m_fScrollMax, ntl::Max<float>(0, m_pToolBar->m_fScroll + (m_pToolBar->m_eAlignTo == IToolBar::AlignTo::Left ? 1 : -1) * m_pToolBar->m_fScrollDeltaTimer));
					break;
				default:
					break;
				}
				m_hTimer = m_pToolBar->getForm()->CreateTimer(this, m_pToolBar->m_fScrollInterval);
				m_pToolBar->getForm()->CaptureMouse(m_pToolBar, true);
				if (ntl::IsNotEqual<float>(m_pToolBar->m_fScroll, last_scroll))
				{
					UpdatePositions();
					if (m_pToolBar->m_pCanvas)
						m_pToolBar->m_pCanvas->setValid(false);
					m_pToolBar->Repaint(false);
				}
			}
		}

		void CToolBarService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			CancelDown(true);
		}

		void CToolBarService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CToolBarService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CToolBarService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CToolBarService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CToolBarService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CToolBarService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CToolBarService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CToolBarService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			if (ntl::IsGreater<float>(m_pToolBar->m_fScrollMax, 0))
			{
				processed = true;
				if (!m_bDown)
				{
					PointF p{ m_pToolBar->FormToLocal(m.Position) };
					if (p.X >= 0 && p.X < m_pToolBar->getWidth() && p.Y >= 0 && p.Y < m_pToolBar->getHeight())
					{
						if (m.Delta > 0)
						{
							if (ntl::IsGreater<float>(m_pToolBar->m_fScroll, 0))
							{
								m_pToolBar->m_fScroll = ntl::Max<float>(0, m_pToolBar->m_fScroll - m_pToolBar->m_fScrollDeltaTimer);
								UpdatePositions();
								if (m_pToolBar->m_pCanvas)
									m_pToolBar->m_pCanvas->setValid(false);
								m_pToolBar->Repaint(false);
							}
						}
						else
							if (ntl::IsLess<float>(m_pToolBar->m_fScroll, m_pToolBar->m_fScrollMax))
							{
								m_pToolBar->m_fScroll = ntl::Min<float>(m_pToolBar->m_fScrollMax, m_pToolBar->m_fScroll + m_pToolBar->m_fScrollDeltaTimer);
								UpdatePositions();
								if (m_pToolBar->m_pCanvas)
									m_pToolBar->m_pCanvas->setValid(false);
								m_pToolBar->Repaint(false);
							}
					}
				}
			}
		}

		void CToolBarService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			NotifyOnMouseVerticalWheel(m, processed);
		}
	#pragma endregion

	#pragma region Timer notification
		void CToolBarService::NotifyOnTimer(const PlatformHandle id)
		{
			if (m_pToolBar->m_eDownElement == CToolBar::Element::LeftScroller/* && service->m_pToolBar->m_iScroll > 0*/)
			{
				float last_scroll{ m_pToolBar->m_fScroll };
				m_pToolBar->m_fScroll = ntl::Min<float>(m_pToolBar->m_fScrollMax, ntl::Max<float>(0, m_pToolBar->m_fScroll - (m_pToolBar->m_eAlignTo == IToolBar::AlignTo::Left ? 1 : -1) * m_pToolBar->m_fScrollDeltaTimer));
				if (ntl::IsNotEqual<float>(m_pToolBar->m_fScroll, last_scroll))
				{
					UpdatePositions();
					if (m_pToolBar->m_pCanvas)
						m_pToolBar->m_pCanvas->setValid(false);
					m_pToolBar->Repaint(false);
				}
			}
			else if (m_pToolBar->m_eDownElement == CToolBar::Element::RightScroller/* && service->m_pToolBar->m_iScroll < service->m_pToolBar->m_iScrollMax*/)
			{
				float last_scroll{ m_pToolBar->m_fScroll };
				m_pToolBar->m_fScroll = ntl::Min<float>(m_pToolBar->m_fScrollMax, ntl::Max<float>(0, m_pToolBar->m_fScroll + (m_pToolBar->m_eAlignTo == IToolBar::AlignTo::Left ? 1 : -1) * m_pToolBar->m_fScrollDeltaTimer));
				if (ntl::IsNotEqual<float>(m_pToolBar->m_fScroll, last_scroll))
				{
					UpdatePositions();
					if (m_pToolBar->m_pCanvas)
						m_pToolBar->m_pCanvas->setValid(false);
					m_pToolBar->Repaint(false);
				}
			}
		}
	#pragma endregion
	}
}