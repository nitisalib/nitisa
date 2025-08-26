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
		CScrollListService::CScrollListService(CScrollList *control):
			CControlService(control),
			m_pControl{ control },
			m_bAligning{ false },
			m_bDown{ false }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CScrollListService::AlignControls()
		{
			if (!m_bAligning)
			{
				m_bAligning = true;
				CLockRepaint lock{ m_pControl };
				// Update scroll
				IControl *control;
				bool first{ true };
				m_pControl->m_fScrollMax = 0;
				for (int i = 0; i < m_pControl->getControlCount(); i++)
				{
					control = m_pControl->getControl(i);
					if (!control->isVisible(false))
						continue;
					if (m_pControl->m_eOrientation == IScrollList::Orientation::TopToBottom)
						m_pControl->m_fScrollMax += AdjustByConstraints(control->QueryService()->getSizeRequested(), control->getConstraints()).Y;
					else
						m_pControl->m_fScrollMax += AdjustByConstraints(control->QueryService()->getSizeRequested(), control->getConstraints()).X;
					if (!first)
						m_pControl->m_fScrollMax += m_pControl->m_fMargin;
					else
						first = false;
				}
				RectF client{ m_pControl->getClientRect() };
				if (m_pControl->m_eOrientation == IScrollList::Orientation::TopToBottom)
					m_pControl->m_fScrollMax = ntl::Max<float>(0, m_pControl->m_fScrollMax - client.height());
				else
					m_pControl->m_fScrollMax = ntl::Max<float>(0, m_pControl->m_fScrollMax - client.width());
				m_pControl->m_fScroll = ntl::Clamp<float>(m_pControl->m_fScroll, 0, m_pControl->m_fScrollMax);
				// Update controls
				PointF pos, size;
				if (m_pControl->m_eOrientation == IScrollList::Orientation::TopToBottom)
					pos = PointF{ client.Left, client.Top - m_pControl->m_fScroll };
				else
					pos = PointF{ client.Left - m_pControl->m_fScroll, client.Top };
				for (int i = 0; i < m_pControl->getControlCount(); i++)
				{
					control = m_pControl->getControl(i);
					if (!control->isVisible(false))
						continue;
					size = AdjustByConstraints(control->QueryService()->getSizeRequested(), control->getConstraints());
					control->getTransform()->QueryService()->Transform(pos.X, pos.Y, 0, 1, 1, 1, 0, 0, 0);
					if (m_pControl->m_eOrientation == IScrollList::Orientation::TopToBottom)
					{
						size.X = client.width();
						pos.Y += size.Y;
						pos.Y += m_pControl->m_fMargin;
					}
					else
					{
						size.Y = client.height();
						pos.X += size.X;
						pos.X += m_pControl->m_fMargin;
					}
					if (IsNotEqual(size, control->getSize()))
					{
						control->Repaint(false);
						control->QueryService()->setSize(size);
						control->QueryService()->AlignControls();
						CNotifier::Resize(control);
						control->Repaint(false);
					}
				}
				m_bAligning = false;
			}
		}

		void CScrollListService::CancelDown(const bool check_capture)
		{
			if (m_bDown)
			{
				m_bDown = false;
				m_pControl->getScrollBar()->NotifyOnMouseDownCancel();
				if (check_capture && m_pControl->isCaptureMouse())
					m_pControl->getForm()->ReleaseCaptureMouse();
			}
		}

		PointF CScrollListService::FormToScroll(const PointF &position)
		{
			return m_pControl->FormToLocal(position) - m_pControl->getScrollBar()->getPosition();
		}

		bool CScrollListService::HitTest(const PointF &position)
		{
			Vec4f v{ ntl::Inversed<float>(m_pControl->getTransformMatrix()) * Vec4f{ position.X, position.Y, 0, 1 } };
			return m_pControl->getRect().is_inside(PointF{ v.X, v.Y });
		}
	#pragma endregion

	#pragma region State change notifications
		void CScrollListService::NotifyOnFreeResources()
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
			if (m_pControl->m_pScroll)
				m_pControl->m_pScroll->NotifyOnFreeResources();
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CScrollListService::NotifyOnParentStyleChange()
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
	#pragma endregion

	#pragma region Notifications from child controls
		void CScrollListService::NotifyOnChildTransform(IControl *control)
		{
			if (!m_bAligning)
			{
				AlignControls();
				m_pControl->UpdateScrollBar();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CScrollListService::NotifyOnChildResize(IControl *control)
		{
			if (!m_bAligning)
			{
				AlignControls();
				m_pControl->UpdateScrollBar();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CScrollListService::NotifyOnChildShow(IControl *control)
		{
			if (!m_bAligning)
			{
				AlignControls();
				m_pControl->UpdateScrollBar();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CScrollListService::NotifyOnChildHide(IControl *control)
		{
			if (!m_bAligning)
			{
				AlignControls();
				m_pControl->UpdateScrollBar();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CScrollListService::NotifyOnChildAttach(IControl *control)
		{
			if (!m_bAligning)
			{
				AlignControls();
				m_pControl->UpdateScrollBar();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CScrollListService::NotifyOnChildDetach(IControl *control)
		{
			if (!m_bAligning)
			{
				AlignControls();
				m_pControl->UpdateScrollBar();
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CScrollListService::NotifyOnChildBeforeTransform(IControl *control, bool &allowed)
		{
			if (!m_bAligning)
				allowed = false;
		}
	#pragma endregion

	#pragma region State change notifications
		void CScrollListService::NotifyOnEnable()
		{
			m_pControl->UpdateScrollBar();
		}

		void CScrollListService::NotifyOnDisable()
		{
			m_pControl->UpdateScrollBar();
		}

		void CScrollListService::NotifyOnResize()
		{
			AlignControls();
			m_pControl->UpdateScrollBar();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			if (m_pControl->m_pMask)
				m_pControl->m_pMask->setValid(false);
		}

		void CScrollListService::NotifyOnStyleChange()
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

		void CScrollListService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CScrollListService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			m_bMaskActive = false;
			if (!m.LastPass)
			{
				draw_children = false;
				if (ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
				{
					IRenderer *renderer{ m_pControl->getForm()->getRenderer() };
					Mat4f matrix{ m_pControl->getTransformMatrix() };
					m_pControl->Render(renderer, matrix);
					if (m_pControl->getControlCount() > 0)
					{
						RectF client{ m_pControl->getClientRect() };
						if (!client.is_zero())
						{
							m_pControl->RenderMask(renderer);
							if (m_pControl->m_pMask)
							{
								renderer->PushMask(m_pControl->m_pMask, matrix);
								m_bMaskActive = true;
							}
							float pos;
							IControl *control;
							if (m_pControl->m_eOrientation == IScrollList::Orientation::TopToBottom)
							{
								for (int i = 0; i < m_pControl->getControlCount(); i++)
								{
									control = m_pControl->getControl(i);
									if (control->isVisible(false))
									{
										pos = control->getRenderRect().Bottom + control->getTransform()->getTy();
										if (pos <= client.Top)
											continue;
										CNotifier::Render(m_pControl->getControl(i), m, nullptr);
										if (pos >= client.Bottom)
											break;
									}
								}
							}
							else
							{
								for (int i = 0; i < m_pControl->getControlCount(); i++)
								{
									control = m_pControl->getControl(i);
									if (control->isVisible(false))
									{
										pos = control->getRenderRect().Right + control->getTransform()->getTx();
										if (pos <= client.Left)
											continue;
										CNotifier::Render(m_pControl->getControl(i), m, nullptr);
										if (pos >= client.Right)
											break;
									}
								}
							}
						}
					}
				}
			}
		}

		void CScrollListService::NotifyOnPaintEnd(const MessagePaint &m)
		{
			if (m_bMaskActive)
			{
				m_pControl->getForm()->getRenderer()->PopMask();
				m_bMaskActive = false;
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CScrollListService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pControl->isEnabled(true) && m_pControl->isScrollBarVisible())
			{
				RectF rect{ m_pControl->CalculateScrollBarRect() };
				bool changed;
				PointF p{ FormToScroll(m.Position) };
				if (rect.is_inside(p))
					changed = m_pControl->m_pScroll->NotifyOnMouseHover(p);
				else
					changed = m_pControl->m_pScroll->NotifyOnMouseLeave();
				if (changed)
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
		}

		void CScrollListService::NotifyOnMouseLeave()
		{
			if (m_pControl->isEnabled(true) && m_pControl->isScrollBarVisible() && m_pControl->getScrollBar()->NotifyOnMouseLeave())
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CScrollListService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isEnabled(true) && m_pControl->isScrollBarVisible() && m_pControl->getScrollBar()->NotifyOnMouseMove(FormToScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CScrollListService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m_bDown)
			{
				processed = true;
				CancelDown(true);
			}
			else if (m.Target == m_pControl && m_pControl->isEnabled(true) && m_pControl->isScrollBarVisible() && m_pControl->m_pScroll->NotifyOnMouseLeftDown(FormToScroll(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				processed = true;
				m_bDown = true;
				m_pControl->getForm()->CaptureMouse(m_pControl, true);
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CScrollListService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (m_bDown)
			{
				processed = true;
				CancelDown(true);
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CScrollListService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m.Target == m_pControl)
			{
				processed = true;
				CancelDown(true);
			}
		}

		void CScrollListService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m.Target == m_pControl)
			{
				processed = true;
				CancelDown(true);
			}
		}

		void CScrollListService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (m.Target == m_pControl)
			{
				processed = true;
				CancelDown(true);
			}
		}

		void CScrollListService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m.Target == m_pControl)
			{
				processed = true;
				CancelDown(true);
			}
		}

		void CScrollListService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m.Target == m_pControl)
			{
				processed = true;
				CancelDown(true);
			}
		}

		void CScrollListService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (m.Target == m_pControl)
			{
				processed = true;
				CancelDown(true);
			}
		}

		void CScrollListService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m.Target == m_pControl)
			{
				processed = true;
				CancelDown(true);
			}
		}

		void CScrollListService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			if (!m_bDown && m_pControl->isEnabled(true) && m_pControl->isScrollBarVisible() && m_pControl->getScrollBar()->isEnabled() && HitTest(m.Position))
			{
				processed = true;
				if (m_pControl->getScrollBar()->NotifyOnMouseVerticalWheel(m_pControl->FormToLocal(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
				{
					m_pControl->m_fScroll = m_pControl->m_pScroll->getScroll();
					AlignControls();
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
		}

		void CScrollListService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			if (!m_bDown && m_pControl->isEnabled(true) && m_pControl->isScrollBarVisible() && m_pControl->getScrollBar()->isEnabled() && HitTest(m.Position))
			{
				processed = true;
				if (m_pControl->getScrollBar()->NotifyOnMouseHorizontalWheel(m_pControl->FormToLocal(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
				{
					m_pControl->m_fScroll = m_pControl->m_pScroll->getScroll();
					AlignControls();
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
		}
	#pragma endregion
	}
}