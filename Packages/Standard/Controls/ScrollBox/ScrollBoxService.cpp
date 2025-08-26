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
		CScrollBoxService::CScrollBoxService(CScrollBox *scrollbox) :
			CControlService(scrollbox),
			m_pScrollBox{ scrollbox }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CScrollBoxService::CancelDown(const bool check_capture)
		{
			switch (m_pScrollBox->m_eDownElement)
			{
			case CScrollBox::Element::VScroll:
				m_pScrollBox->m_pVScroll->NotifyOnMouseDownCancel();
				break;
			case CScrollBox::Element::HScroll:
				m_pScrollBox->m_pHScroll->NotifyOnMouseDownCancel();
				break;
			default:
				break;
			}
			m_pScrollBox->m_eDownElement = CScrollBox::Element::None;
			if (check_capture && m_pScrollBox->isCaptureMouse())
				m_pScrollBox->getForm()->ReleaseCaptureMouse();
		}

		PointF CScrollBoxService::FormToVScroll(const PointF &pos)
		{
			PointF result{ m_pScrollBox->FormToLocal(pos) };
			return PointF{ result.X - m_pScrollBox->getVScroll()->getLeft(), result.Y - m_pScrollBox->getVScroll()->getTop() };
		}

		PointF CScrollBoxService::FormToHScroll(const PointF &pos)
		{
			PointF result{ m_pScrollBox->FormToLocal(pos) };
			return PointF{ result.X - m_pScrollBox->getHScroll()->getLeft(), result.Y - m_pScrollBox->getHScroll()->getTop() };
		}
	#pragma endregion

	#pragma region State change notifications
		void CScrollBoxService::NotifyOnAttach()
		{
			if (m_pScrollBox->getForm())
			{
				if (m_pScrollBox->m_pVScroll)
					m_pScrollBox->m_pVScroll->NotifyOnAttach();
				if (m_pScrollBox->m_pHScroll)
					m_pScrollBox->m_pHScroll->NotifyOnAttach();
				m_pScrollBox->UpdateHoveredElement();
				if (m_pScrollBox->m_pCanvas)
					m_pScrollBox->m_pCanvas->setValid(false);
			}
		}

		void CScrollBoxService::NotifyOnDetaching()
		{
			CancelDown(false);
		}

		void CScrollBoxService::NotifyOnFreeResources()
		{
			if (m_pScrollBox->m_pCanvas)
			{
				m_pScrollBox->m_pCanvas->Release();
				m_pScrollBox->m_pCanvas = nullptr;
			}
			if (m_pScrollBox->m_pMask)
			{
				m_pScrollBox->m_pMask->Release();
				m_pScrollBox->m_pMask = nullptr;
			}
			if (m_pScrollBox->m_pVScroll)
				m_pScrollBox->m_pVScroll->NotifyOnFreeResources();
			if (m_pScrollBox->m_pHScroll)
				m_pScrollBox->m_pHScroll->NotifyOnFreeResources();
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CScrollBoxService::NotifyOnParentStyleChange()
		{
			if (m_pScrollBox->getStyle())
			{
				m_pScrollBox->UpdateFromStyle(m_pScrollBox->getStyle());
				if (m_pScrollBox->m_pCanvas)
					m_pScrollBox->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region Notifications from child controls
		void CScrollBoxService::NotifyOnChildTransform(IControl *control)
		{
			if (control->getAlign() == Align::None && control->isVisible(false))
			{
				m_pScrollBox->Update();
				if (m_pScrollBox->m_pCanvas)
					m_pScrollBox->m_pCanvas->setValid(false);
				if (m_pScrollBox->m_pMask)
					m_pScrollBox->m_pMask->setValid(false);
				m_pScrollBox->Repaint(false);
			}
		}

		void CScrollBoxService::NotifyOnChildResize(IControl *control)
		{
			if (control->getAlign() == Align::None && control->isVisible(false))
			{
				m_pScrollBox->Update();
				if (m_pScrollBox->m_pCanvas)
					m_pScrollBox->m_pCanvas->setValid(false);
				if (m_pScrollBox->m_pMask)
					m_pScrollBox->m_pMask->setValid(false);
				m_pScrollBox->Repaint(false);
			}
		}

		void CScrollBoxService::NotifyOnChildShow(IControl *control)
		{
			if (control->getAlign() == Align::None)
			{
				m_pScrollBox->Update();
				if (m_pScrollBox->m_pCanvas)
					m_pScrollBox->m_pCanvas->setValid(false);
				if (m_pScrollBox->m_pMask)
					m_pScrollBox->m_pMask->setValid(false);
				m_pScrollBox->Repaint(false);
			}
		}

		void CScrollBoxService::NotifyOnChildHide(IControl *control)
		{
			if (control->getAlign() == Align::None)
			{
				m_pScrollBox->Update();
				if (m_pScrollBox->m_pCanvas)
					m_pScrollBox->m_pCanvas->setValid(false);
				if (m_pScrollBox->m_pMask)
					m_pScrollBox->m_pMask->setValid(false);
				m_pScrollBox->Repaint(false);
			}
		}

		void CScrollBoxService::NotifyOnChildAttach(IControl *control)
		{
			if (control->getAlign() == Align::None && control->isVisible(false))
			{
				m_pScrollBox->Update();
				if (m_pScrollBox->m_pCanvas)
					m_pScrollBox->m_pCanvas->setValid(false);
				if (m_pScrollBox->m_pMask)
					m_pScrollBox->m_pMask->setValid(false);
				m_pScrollBox->Repaint(false);
			}
		}

		void CScrollBoxService::NotifyOnChildDetach(IControl *control)
		{
			if (control->getAlign() == Align::None && control->isVisible(false))
			{
				m_pScrollBox->Update();
				if (m_pScrollBox->m_pCanvas)
					m_pScrollBox->m_pCanvas->setValid(false);
				if (m_pScrollBox->m_pMask)
					m_pScrollBox->m_pMask->setValid(false);
				m_pScrollBox->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CScrollBoxService::NotifyOnEnable()
		{
			m_pScrollBox->Update();
			m_pScrollBox->UpdateHoveredElement();
			if (m_pScrollBox->m_pCanvas)
				m_pScrollBox->m_pCanvas->setValid(false);
		}

		void CScrollBoxService::NotifyOnDisable()
		{
			m_pScrollBox->Update();
			m_pScrollBox->UpdateHoveredElement();
			if (m_pScrollBox->m_pCanvas)
				m_pScrollBox->m_pCanvas->setValid(false);
		}

		void CScrollBoxService::NotifyOnResize()
		{
			m_pScrollBox->Update();
			m_pScrollBox->UpdateHoveredElement();
			if (m_pScrollBox->m_pCanvas)
				m_pScrollBox->m_pCanvas->setValid(false);
			if (m_pScrollBox->m_pMask)
				m_pScrollBox->m_pMask->setValid(false);
		}

		void CScrollBoxService::NotifyOnStyleChange()
		{
			if (m_pScrollBox->getStyle())
			{
				m_pScrollBox->UpdateFromStyle(m_pScrollBox->getStyle());
				if (m_pScrollBox->m_pCanvas)
					m_pScrollBox->m_pCanvas->setValid(false);
			}
		}

		void CScrollBoxService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CScrollBoxService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			m_bMaskActive = false;
			if (!m.LastPass)
			{
				if (ntl::IsGreater<float>(m_pScrollBox->getWidth(), 0) && ntl::IsGreater<float>(m_pScrollBox->getHeight(), 0))
				{
					IRenderer *renderer{ m_pScrollBox->getForm()->getRenderer() };
					Mat4f matrix{ m_pScrollBox->getTransformMatrix() };
					m_pScrollBox->Render(renderer, matrix);
					if (m_pScrollBox->getControlCount() > 0)
					{
						m_pScrollBox->RenderMask(renderer);
						if (m_pScrollBox->m_pMask)
						{
							renderer->PushMask(m_pScrollBox->m_pMask, matrix);
							m_bMaskActive = true;
						}
					}
				}
				else if (m_pScrollBox->getControlCount() > 0)
					draw_children = false;
			}
		}

		void CScrollBoxService::NotifyOnPaintEnd(const MessagePaint &m)
		{
			if (m_bMaskActive)
			{
				m_pScrollBox->getForm()->getRenderer()->PopMask();
				m_bMaskActive = false;
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CScrollBoxService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pScrollBox->isEnabled(true) && m_pScrollBox->UpdateHoveredElement(m_pScrollBox->FormToLocal(m.Position)))
			{
				if (m_pScrollBox->m_pCanvas)
					m_pScrollBox->m_pCanvas->setValid(false);
				m_pScrollBox->Repaint(false);
			}
		}

		void CScrollBoxService::NotifyOnMouseLeave()
		{
			if (m_pScrollBox->isEnabled(true) && m_pScrollBox->UpdateHoveredElement())
			{
				if (m_pScrollBox->m_pCanvas)
					m_pScrollBox->m_pCanvas->setValid(false);
				m_pScrollBox->Repaint(false);
			}
		}

		void CScrollBoxService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pScrollBox->isEnabled(true))
			{
				bool changed{ false };
				switch (m_pScrollBox->m_eDownElement)
				{
				case CScrollBox::Element::VScroll:
					changed = m_pScrollBox->getVScroll()->NotifyOnMouseMove(FormToVScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift);
					break;
				case CScrollBox::Element::HScroll:
					changed = m_pScrollBox->getHScroll()->NotifyOnMouseMove(FormToHScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift);
					break;
				default:
					changed = m_pScrollBox->UpdateHoveredElement(m_pScrollBox->FormToLocal(m.Position));
					switch (m_pScrollBox->m_eHoveredElement)
					{
					case CScrollBox::Element::VScroll:
						changed = m_pScrollBox->getVScroll()->NotifyOnMouseMove(FormToVScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift) || changed;
						break;
					case CScrollBox::Element::HScroll:
						changed = m_pScrollBox->getHScroll()->NotifyOnMouseMove(FormToHScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift) || changed;
						break;
					default:
						break;
					}
				}
				if (changed)
				{
					if (m_pScrollBox->m_pCanvas)
						m_pScrollBox->m_pCanvas->setValid(false);
					m_pScrollBox->Repaint(false);
				}
			}
		}

		void CScrollBoxService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pScrollBox->isEnabled(true) &&
				m_pScrollBox->m_eDownElement == CScrollBox::Element::None &&
				(m_pScrollBox->m_eHoveredElement == CScrollBox::Element::VScroll || m_pScrollBox->m_eHoveredElement == CScrollBox::Element::HScroll) &&
				!m.Middle && !m.Right)
			{
				m_pScrollBox->m_eDownElement = m_pScrollBox->m_eHoveredElement;
				bool changed{ false };
				switch (m_pScrollBox->m_eDownElement)
				{
				case CScrollBox::Element::VScroll:
					changed = m_pScrollBox->getVScroll()->NotifyOnMouseLeftDown(FormToVScroll(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift);
					break;
				case CScrollBox::Element::HScroll:
					changed = m_pScrollBox->getHScroll()->NotifyOnMouseLeftDown(FormToHScroll(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift);
					break;
				default:
					break;
				}
				if (changed)
				{
					if (m_pScrollBox->m_pCanvas)
						m_pScrollBox->m_pCanvas->setValid(false);
					m_pScrollBox->Repaint(false);
				}
				m_pScrollBox->getForm()->CaptureMouse(m_pScrollBox, true);
			}
			else
				CancelDown(true);
		}

		void CScrollBoxService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			CancelDown(true);
		}

		void CScrollBoxService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CScrollBoxService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CScrollBoxService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CScrollBoxService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CScrollBoxService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CScrollBoxService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CScrollBoxService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CScrollBoxService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pScrollBox->isEnabled(true))
			{
				bool changed{ false };
				switch (m_pScrollBox->m_eHoveredElement)
				{
				case CScrollBox::Element::VScroll:
					if (m_pScrollBox->getVScroll()->isEnabled())
						changed = m_pScrollBox->getVScroll()->NotifyOnMouseVerticalWheel(FormToVScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta);
					break;
				case CScrollBox::Element::HScroll:
					if (m_pScrollBox->getHScroll()->isEnabled())
						changed = m_pScrollBox->getHScroll()->NotifyOnMouseVerticalWheel(FormToHScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta);
					break;
				default:
					if (m_pScrollBox->getVScroll()->isEnabled())
						changed = m_pScrollBox->getVScroll()->setScroll(m_pScrollBox->getVScroll()->getScroll() + m_pScrollBox->getVScroll()->getDeltaMedium() * (m.Delta < 0 ? 1 : -1));
				}
				if (changed)
				{
					m_pScrollBox->UpdateTransformControls();
					if (m_pScrollBox->m_pCanvas)
						m_pScrollBox->m_pCanvas->setValid(false);
					m_pScrollBox->Repaint(false);
				}
			}
		}

		void CScrollBoxService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pScrollBox->isEnabled(true))
			{
				bool changed{ false };
				switch (m_pScrollBox->m_eHoveredElement)
				{
				case CScrollBox::Element::VScroll:
					if (m_pScrollBox->getVScroll()->isEnabled())
						changed = m_pScrollBox->getVScroll()->NotifyOnMouseHorizontalWheel(FormToVScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta);
					break;
				case CScrollBox::Element::HScroll:
					if (m_pScrollBox->getHScroll()->isEnabled())
						changed = m_pScrollBox->getHScroll()->NotifyOnMouseHorizontalWheel(FormToHScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta);
					break;
				default:
					if (m_pScrollBox->getHScroll()->isEnabled())
						changed = m_pScrollBox->getHScroll()->setScroll(m_pScrollBox->getHScroll()->getScroll() + m_pScrollBox->getHScroll()->getDeltaMedium() * (m.Delta > 0 ? 1 : -1));
				}
				if (changed)
				{
					m_pScrollBox->UpdateTransformControls();
					if (m_pScrollBox->m_pCanvas)
						m_pScrollBox->m_pCanvas->setValid(false);
					m_pScrollBox->Repaint(false);
				}
			}
		}
	#pragma endregion
	}
}