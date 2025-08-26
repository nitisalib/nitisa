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
		CGradientEditorService::CGradientEditorService(CGradientEditor *editor) :
			CControlService(editor),
			m_pEditor{ editor }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CGradientEditorService::CancelDown(const bool check_capture, const PointF &position)
		{
			if (m_pEditor->m_bDown)
			{
				m_pEditor->m_bDown = false;
				m_pEditor->UpdateHoveredArrow(position);
				if (m_pEditor->OnChange)
					m_pEditor->OnChange(m_pEditor);
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
				if (check_capture && m_pEditor->isCaptureMouse())
					m_pEditor->getForm()->ReleaseCaptureMouse();
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CGradientEditorService::NotifyOnParentStyleChange()
		{
			if (m_pEditor->getStyle())
			{
				m_pEditor->UpdateFromStyle(m_pEditor->getStyle());
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CGradientEditorService::NotifyOnFreeResources()
		{
			if (m_pEditor->m_pCanvas)
			{
				m_pEditor->m_pCanvas->Release();
				m_pEditor->m_pCanvas = nullptr;
			}
		}

		void CGradientEditorService::NotifyOnResize()
		{
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
		}

		void CGradientEditorService::NotifyOnStyleChange()
		{
			if (m_pEditor->getStyle())
			{
				m_pEditor->UpdateFromStyle(m_pEditor->getStyle());
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
			}
		}

		void CGradientEditorService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false, m_pEditor->FormToLocal((PointF)m_pEditor->getForm()->ScreenToClient(Application->Mouse->getPosition())));
		}
	#pragma endregion

	#pragma region Paint notifications
		void CGradientEditorService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pEditor->getWidth(), 0) && ntl::IsGreater<float>(m_pEditor->getHeight(), 0))
				m_pEditor->Render();
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CGradientEditorService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (!m_pEditor->m_bDown && m_pEditor->UpdateHoveredArrow(m_pEditor->FormToLocal(m.Position)))
			{
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CGradientEditorService::NotifyOnMouseLeave()
		{
			if (!m_pEditor->m_bDown && m_pEditor->m_iHoveredPoint >= 0)
			{
				m_pEditor->m_iHoveredPoint = -1;
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CGradientEditorService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pEditor->m_bDown)
			{
				float p{ ntl::Clamp<float>((m_pEditor->FormToLocal(m.Position).X - m_pEditor->m_fArrowSize / 2) / (m_pEditor->getWidth() - m_pEditor->m_fArrowSize), 0.0f, 1.0f) };
				if (ntl::IsNotEqual<float>(p, m_pEditor->m_cGradient.getPoint(m_pEditor->m_iActivePoint).Position))
				{
					m_pEditor->m_cGradient.setPointPosition(m_pEditor->m_iActivePoint, p);
					if (m_pEditor->OnChange)
						m_pEditor->OnChange(m_pEditor);
				}
			}
			else if (m_pEditor->UpdateHoveredArrow(m_pEditor->FormToLocal(m.Position)))
			{
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CGradientEditorService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m_pEditor->m_bDown && !m.Middle && !m.Right && ntl::IsGreater<float>(m_pEditor->getWidth() - m_pEditor->m_fArrowSize, 0))
			{
				m_pEditor->m_bDown = true;
				m_pEditor->getForm()->CaptureMouse(m_pEditor, true);
				if (m_pEditor->m_iHoveredPoint >= 0)
				{
					if (m_pEditor->setActivePoint(m_pEditor->m_iHoveredPoint))
					{
						if (m_pEditor->OnChange)
							m_pEditor->OnChange(m_pEditor);
						if (m_pEditor->m_pCanvas)
							m_pEditor->m_pCanvas->setValid(false);
						m_pEditor->Repaint(false);
					}
				}
				else
				{
					float p{ ntl::Clamp<float>((m_pEditor->FormToLocal(m.Position).X - m_pEditor->m_fArrowSize / 2) / (m_pEditor->getWidth() - m_pEditor->m_fArrowSize), 0.0f, 1.0f) };
					m_pEditor->m_bIgnoreGradient = true;
					m_pEditor->m_cGradient.AddPoint(p, m_pEditor->m_cGradient.getColor(p));
					m_pEditor->m_iActivePoint = m_pEditor->m_cGradient.getPointCount() - 1;
					m_pEditor->m_bIgnoreGradient = false;
					if (m_pEditor->OnChange)
						m_pEditor->OnChange(m_pEditor);
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}

		void CGradientEditorService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			CancelDown(true, m_pEditor->FormToLocal(m.Position));
		}

		void CGradientEditorService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, m_pEditor->FormToLocal(m.Position));
		}

		void CGradientEditorService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			CancelDown(true, m_pEditor->FormToLocal(m.Position));
			if (!m.Left && !m.Middle && m_pEditor->m_iHoveredPoint >= 0)
			{
				if (m_pEditor->m_iActivePoint >= 0)
				{
					if (m_pEditor->m_iActivePoint > m_pEditor->m_iHoveredPoint)
						m_pEditor->m_iActivePoint--;
					else if (m_pEditor->m_iActivePoint == m_pEditor->m_iHoveredPoint)
						m_pEditor->m_iActivePoint = -1;
				}
				m_pEditor->m_cGradient.DeletePoint(m_pEditor->m_iHoveredPoint);
				m_pEditor->UpdateHoveredArrow(m_pEditor->FormToLocal(m.Position));
				if (m_pEditor->OnChange)
					m_pEditor->OnChange(m_pEditor);
			}
		}

		void CGradientEditorService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			CancelDown(true, m_pEditor->FormToLocal(m.Position));
		}

		void CGradientEditorService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, m_pEditor->FormToLocal(m.Position));
		}

		void CGradientEditorService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, m_pEditor->FormToLocal(m.Position));
		}

		void CGradientEditorService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, m_pEditor->FormToLocal(m.Position));
		}

		void CGradientEditorService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, m_pEditor->FormToLocal(m.Position));
		}
	#pragma endregion
	}
}