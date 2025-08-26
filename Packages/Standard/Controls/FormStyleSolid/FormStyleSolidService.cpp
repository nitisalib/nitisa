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
		CFormStyleSolidService::CFormStyleSolidService(CFormStyleSolid *control) :
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region State change notifications
		void CFormStyleSolidService::NotifyOnAttach()
		{
			m_pControl->getForm()->setBorderWidth(m_pControl->m_sBorderWidth);
		}

		void CFormStyleSolidService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pCanvasHeader)
			{
				m_pControl->m_pCanvasHeader->Release();
				m_pControl->m_pCanvasHeader = nullptr;
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CFormStyleSolidService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvasHeader)
					m_pControl->m_pCanvasHeader->setValid(false);
			}
		}

		void CFormStyleSolidService::NotifyOnParentFontChange()
		{
			if (m_pControl->m_pCanvasHeader)
				m_pControl->m_pCanvasHeader->setValid(false);
		}

		void CFormStyleSolidService::NotifyOnParentResize()
		{
			if (m_pControl->m_pCanvasHeader)
				m_pControl->m_pCanvasHeader->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CFormStyleSolidService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvasHeader)
					m_pControl->m_pCanvasHeader->setValid(false);
			}
		}

		void CFormStyleSolidService::NotifyOnFontChange()
		{
			if (m_pControl->m_pCanvasHeader)
				m_pControl->m_pCanvasHeader->setValid(false);
		}

		void CFormStyleSolidService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CFormStyleSolidService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!Application->Editor && m.LastPass && m_pControl->m_sBorderWidth.has_positive())
				m_pControl->Render();
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CFormStyleSolidService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pControl->UpdateHoveredElement(m.Position))
			{
				if (m_pControl->m_pCanvasHeader)
					m_pControl->m_pCanvasHeader->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CFormStyleSolidService::NotifyOnMouseLeave()
		{
			if (m_pControl->UpdateHoveredElement(PointF{ -1, -1 }))
			{
				if (m_pControl->m_pCanvasHeader)
					m_pControl->m_pCanvasHeader->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CFormStyleSolidService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			bool repaint{ m_pControl->UpdateHoveredElement(m.Position) };
			switch (m_pControl->m_eDown)
			{
			case CFormStyleSolid::Element::LeftBorder:
				repaint = ResizeLeft(Round(m.Position)) || repaint;
				break;
			case CFormStyleSolid::Element::TopBorder:
				repaint = ResizeTop(Round(m.Position)) || repaint;
				break;
			case CFormStyleSolid::Element::RightBorder:
				repaint = ResizeRight(Round(m.Position)) || repaint;
				break;
			case CFormStyleSolid::Element::BottomBorder:
				repaint = ResizeBottom(Round(m.Position)) || repaint;
				break;
			case CFormStyleSolid::Element::LeftTopCorner:
				repaint = ResizeLeftTop(Round(m.Position)) || repaint;
				break;
			case CFormStyleSolid::Element::RightTopCorner:
				repaint = ResizeRightTop(Round(m.Position)) || repaint;
				break;
			case CFormStyleSolid::Element::LeftBottomCorner:
				repaint = ResizeLeftBottom(Round(m.Position)) || repaint;
				break;
			case CFormStyleSolid::Element::RightBottomCorner:
				repaint = ResizeRightBottom(Round(m.Position)) || repaint;
				break;
			case CFormStyleSolid::Element::Header:
				Move(Round(m.Position));
				break;
			default:
				break;
			}
			if (repaint)
			{
				if (m_pControl->m_pCanvasHeader)
					m_pControl->m_pCanvasHeader->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CFormStyleSolidService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_eDown == CFormStyleSolid::Element::None && !m.Middle && !m.Right && m_pControl->DownAllowed())
			{
				processed = true;
				m_pControl->m_eDown = m_pControl->m_eHovered;
				m_sDownPosition = m_pControl->getForm()->ClientToScreen(Round(m.Position));
				m_sFormSize = m_pControl->getForm()->getSize();
				m_sFormPosition = m_pControl->getForm()->getPosition();
				m_pControl->getForm()->CaptureMouse(m_pControl, true);
				if (m_pControl->m_pCanvasHeader)
					m_pControl->m_pCanvasHeader->setValid(false);
				m_pControl->Repaint(false);
			}
			else
				CancelDown(true);
		}

		void CFormStyleSolidService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_eDown != CFormStyleSolid::Element::None)
			{
				processed = true;
				if (m_pControl->m_eHovered == m_pControl->m_eDown)
				{
					switch (m_pControl->m_eDown)
					{
					case CFormStyleSolid::Element::BtnMinimize:
						m_pControl->getForm()->Minimize();
						break;
					case CFormStyleSolid::Element::BtnRestore:
						m_pControl->getForm()->getState() == WindowState::Maximized ? m_pControl->getForm()->Restore() : m_pControl->getForm()->Maximize();
						break;
					case CFormStyleSolid::Element::BtnClose:
						m_pControl->getForm()->Close();
						break;
					default:
						break;
					}
				}
			}
			CancelDown(true);
		}

		void CFormStyleSolidService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->m_eHovered == CFormStyleSolid::Element::Header && !m.Middle && !m.Right)
			{
				processed = true;
				if (m_pControl->getForm()->getState() == WindowState::Maximized)
					m_pControl->getForm()->Restore();
				else
					m_pControl->getForm()->Maximize();
			}
			else
				CancelDown(true);
		}

		void CFormStyleSolidService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CFormStyleSolidService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CFormStyleSolidService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CFormStyleSolidService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CFormStyleSolidService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CFormStyleSolidService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}
	#pragma endregion

	#pragma region Moving and resizing
		bool CFormStyleSolidService::ResizeLeft(const Point &position)
		{
			Point p{ m_pControl->getForm()->ClientToScreen(position) };
			int d{ p.X - m_sDownPosition.X };
			bool result{ m_pControl->getForm()->setLeft(m_sFormPosition.X + d) };
			result = m_pControl->getForm()->setWidth(m_sFormSize.X - d) || result;
			return result;
		}

		bool CFormStyleSolidService::ResizeTop(const Point &position)
		{
			Point p{ m_pControl->getForm()->ClientToScreen(position) };
			int d{ p.Y - m_sDownPosition.Y };
			bool result{ m_pControl->getForm()->setTop(m_sFormPosition.Y + d) };
			result = m_pControl->getForm()->setHeight(m_sFormSize.Y - d) || result;
			return result;
		}

		bool CFormStyleSolidService::ResizeRight(const Point &position)
		{
			Point p{ m_pControl->getForm()->ClientToScreen(position) };
			int d{ p.X - m_sDownPosition.X };
			return m_pControl->getForm()->setWidth(m_sFormSize.X + d);
		}

		bool CFormStyleSolidService::ResizeBottom(const Point &position)
		{
			Point p{ m_pControl->getForm()->ClientToScreen(position) };
			int d{ p.Y - m_sDownPosition.Y };
			return m_pControl->getForm()->setHeight(m_sFormSize.Y + d);
		}

		bool CFormStyleSolidService::ResizeLeftTop(const Point &position)
		{
			Point p{ m_pControl->getForm()->ClientToScreen(position) };
			Point d{ p.X - m_sDownPosition.X, p.Y - m_sDownPosition.Y };
			bool result{ m_pControl->getForm()->setPosition({m_sFormPosition.X + d.X, m_sFormPosition.Y + d.Y}) };
			result = m_pControl->getForm()->setSize(Point{ m_sFormSize.X - d.X, m_sFormSize.Y - d.Y }) || result;
			return result;
		}

		bool CFormStyleSolidService::ResizeRightTop(const Point &position)
		{
			Point p{ m_pControl->getForm()->ClientToScreen(position) };
			Point d{ p.X - m_sDownPosition.X, p.Y - m_sDownPosition.Y };
			bool result{ m_pControl->getForm()->setSize({m_sFormSize.X + d.X, m_sFormSize.Y - d.Y}) };
			result = m_pControl->getForm()->setTop(m_sFormPosition.Y + d.Y) || result;
			return result;
		}

		bool CFormStyleSolidService::ResizeLeftBottom(const Point &position)
		{
			Point p{ m_pControl->getForm()->ClientToScreen(position) };
			Point d{ p.X - m_sDownPosition.X, p.Y - m_sDownPosition.Y };
			bool result{ m_pControl->getForm()->setLeft(m_sFormPosition.X + d.X) };
			result = m_pControl->getForm()->setSize(Point{ m_sFormSize.X - d.X, m_sFormSize.Y + d.Y }) || result;
			return result;
		}

		bool CFormStyleSolidService::ResizeRightBottom(const Point &position)
		{
			Point p{ m_pControl->getForm()->ClientToScreen(position) };
			Point d{ p.X - m_sDownPosition.X, p.Y - m_sDownPosition.Y };
			return m_pControl->getForm()->setSize(Point{m_sFormSize.X + d.X, m_sFormSize.Y + d.Y});
		}

		void CFormStyleSolidService::Move(const Point &position)
		{
			Point p{ m_pControl->getForm()->ClientToScreen(position) };
			Point d{ p.X - m_sDownPosition.X, p.Y - m_sDownPosition.Y };
			m_pControl->getForm()->setPosition(Point{ m_sFormPosition.X + d.X, m_sFormPosition.Y + d.Y });
		}

		void CFormStyleSolidService::CancelDown(const bool check_capture)
		{
			if (m_pControl->m_eDown != CFormStyleSolid::Element::None)
			{
				m_pControl->m_eDown = CFormStyleSolid::Element::None;
				if (m_pControl->m_pCanvasHeader)
					m_pControl->m_pCanvasHeader->setValid(false);
				m_pControl->Repaint(false);
			}
			if (check_capture && m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}
	#pragma endregion
	}
}