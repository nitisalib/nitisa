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
		CFrameService::CFrameService(CFrame *frame) :
			CControlService(frame),
			m_pFrame{ frame },
			m_eDownPart{ DownPart::None }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CFrameService::UpdateHoveredButton(const PointF &position)
		{
			DownPart part{ m_pFrame->getPart(position) };
			bool updated{ false };
			if (m_pFrame->m_bMinimizable &&
				(m_pFrame->m_sBtnMinimizeRestore.State == CFrame::ButtonState::Hovered || m_pFrame->m_sBtnMinimizeRestore.State == CFrame::ButtonState::ActiveHovered) &&
				part != DownPart::MinimizeRestoreButton)
			{
				if (m_eDownPart == DownPart::MinimizeRestoreButton)
					m_pFrame->m_sBtnMinimizeRestore.State = CFrame::ButtonState::Active;
				else
					m_pFrame->m_sBtnMinimizeRestore.State = CFrame::ButtonState::Normal;
				updated = true;
			}
			if (m_pFrame->m_bMaximizable &&
				(m_pFrame->m_sBtnMaximizeRestore.State == CFrame::ButtonState::Hovered || m_pFrame->m_sBtnMaximizeRestore.State == CFrame::ButtonState::ActiveHovered) &&
				part != DownPart::MaximizeRestoreButton)
			{
				if (m_eDownPart == DownPart::MaximizeRestoreButton)
					m_pFrame->m_sBtnMaximizeRestore.State = CFrame::ButtonState::Active;
				else
					m_pFrame->m_sBtnMaximizeRestore.State = CFrame::ButtonState::Normal;
				updated = true;
			}
			if (m_pFrame->m_bClosable &&
				(m_pFrame->m_sBtnClose.State == CFrame::ButtonState::Hovered || m_pFrame->m_sBtnClose.State == CFrame::ButtonState::ActiveHovered) &&
				part != DownPart::CloseButton)
			{
				if (m_eDownPart == DownPart::CloseButton)
					m_pFrame->m_sBtnClose.State = CFrame::ButtonState::Active;
				else
					m_pFrame->m_sBtnClose.State = CFrame::ButtonState::Normal;
				updated = true;
			}

			if (m_pFrame->m_bMinimizable &&
				m_pFrame->m_sBtnMinimizeRestore.State != CFrame::ButtonState::Hovered &&
				m_pFrame->m_sBtnMinimizeRestore.State != CFrame::ButtonState::ActiveHovered &&
				part == DownPart::MinimizeRestoreButton)
			{
				if (m_eDownPart == DownPart::MinimizeRestoreButton)
					m_pFrame->m_sBtnMinimizeRestore.State = CFrame::ButtonState::ActiveHovered;
				else
					m_pFrame->m_sBtnMinimizeRestore.State = CFrame::ButtonState::Hovered;
				updated = true;
			}
			if (m_pFrame->m_bMaximizable &&
				m_pFrame->m_sBtnMaximizeRestore.State != CFrame::ButtonState::Hovered &&
				m_pFrame->m_sBtnMaximizeRestore.State != CFrame::ButtonState::ActiveHovered &&
				part == DownPart::MaximizeRestoreButton)
			{
				if (m_eDownPart == DownPart::MaximizeRestoreButton)
					m_pFrame->m_sBtnMaximizeRestore.State = CFrame::ButtonState::ActiveHovered;
				else
					m_pFrame->m_sBtnMaximizeRestore.State = CFrame::ButtonState::Hovered;
				updated = true;
			}
			if (m_pFrame->m_bClosable && m_pFrame->m_sBtnClose.State != CFrame::ButtonState::Hovered && m_pFrame->m_sBtnClose.State != CFrame::ButtonState::ActiveHovered && part == DownPart::CloseButton)
			{
				if (m_eDownPart == DownPart::CloseButton)
					m_pFrame->m_sBtnClose.State = CFrame::ButtonState::ActiveHovered;
				else
					m_pFrame->m_sBtnClose.State = CFrame::ButtonState::Hovered;
				updated = true;
			}
			if (updated)
			{
				if (m_pFrame->m_pCanvas)
					m_pFrame->m_pCanvas->setValid(false);
				m_pFrame->Repaint(m_pFrame->getCaptionRenderRect(), true);
			}
		}

		void CFrameService::MouseUp(const bool check_capture)
		{
			m_eDownPart = DownPart::None;
			bool updated{ false };
			if (m_pFrame->m_bMinimizable && (m_pFrame->m_sBtnMinimizeRestore.State == CFrame::ButtonState::Active || m_pFrame->m_sBtnMinimizeRestore.State == CFrame::ButtonState::ActiveHovered))
			{
				if (m_pFrame->m_sBtnMinimizeRestore.State == CFrame::ButtonState::Active)
					m_pFrame->m_sBtnMinimizeRestore.State = CFrame::ButtonState::Normal;
				else
					m_pFrame->m_sBtnMinimizeRestore.State = CFrame::ButtonState::Hovered;
				updated = true;
			}
			if (m_pFrame->m_bMaximizable && (m_pFrame->m_sBtnMaximizeRestore.State == CFrame::ButtonState::Active || m_pFrame->m_sBtnMaximizeRestore.State == CFrame::ButtonState::ActiveHovered))
			{
				if (m_pFrame->m_sBtnMaximizeRestore.State == CFrame::ButtonState::Active)
					m_pFrame->m_sBtnMaximizeRestore.State = CFrame::ButtonState::Normal;
				else
					m_pFrame->m_sBtnMaximizeRestore.State = CFrame::ButtonState::Hovered;
				updated = true;
			}
			if (m_pFrame->m_bClosable && (m_pFrame->m_sBtnClose.State == CFrame::ButtonState::Active || m_pFrame->m_sBtnClose.State == CFrame::ButtonState::ActiveHovered))
			{
				if (m_pFrame->m_sBtnClose.State == CFrame::ButtonState::Active)
					m_pFrame->m_sBtnClose.State = CFrame::ButtonState::Normal;
				else
					m_pFrame->m_sBtnClose.State = CFrame::ButtonState::Hovered;
				updated = true;
			}
			if (check_capture && m_pFrame->isCaptureMouse())
				m_pFrame->getForm()->ReleaseCaptureMouse();
			if (updated)
			{
				if (m_pFrame->m_pCanvas)
					m_pFrame->m_pCanvas->setValid(false);
				m_pFrame->Repaint(m_pFrame->getCaptionRenderRect(), true);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CFrameService::NotifyOnAttach()
		{
			if (!m_pFrame->m_bCaptionChanged && m_pFrame->getForm())
				m_pFrame->setCaption(m_pFrame->m_sName);
		}

		void CFrameService::NotifyOnFreeResources()
		{
			if (m_pFrame->m_pCanvas)
			{
				m_pFrame->m_pCanvas->Release();
				m_pFrame->m_pCanvas = nullptr;
			}
			if (m_pFrame->m_pMask)
			{
				m_pFrame->m_pMask->Release();
				m_pFrame->m_pMask = nullptr;
			}
		}
	#pragma endregion

	#pragma region Other components/controls/objects change notifications
		void CFrameService::NotifyOnControlSetFocus(IControl *control, const MessageFocus &m)
		{
			if (m_pFrame->hasChild(control) && m_pFrame->m_eLastRenderState != m_pFrame->getState())
			{
				if (m_pFrame->m_pCanvas)
					m_pFrame->m_pCanvas->setValid(false);
				m_pFrame->Repaint(false);
			}
		}

		void CFrameService::NotifyOnControlKillFocus(IControl *control)
		{
			if (m_pFrame->hasChild(control))
			{
				if (m_pFrame->m_pCanvas)
					m_pFrame->m_pCanvas->setValid(false);
				m_pFrame->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CFrameService::NotifyOnParentStyleChange()
		{
			if (m_pFrame->getStyle())
			{
				m_pFrame->UpdateFromStyle(m_pFrame->getStyle());
				if (m_pFrame->m_pMask)
					m_pFrame->m_pMask->setValid(false);
				if (m_pFrame->m_pCanvas)
					m_pFrame->m_pCanvas->setValid(false);
			}
		}

		void CFrameService::NotifyOnParentFontChange()
		{
			if (m_pFrame->m_pCanvas)
				m_pFrame->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CFrameService::NotifyOnStyleChange()
		{
			if (m_pFrame->getStyle())
			{
				m_pFrame->UpdateFromStyle(m_pFrame->getStyle());
				if (m_pFrame->m_pMask)
					m_pFrame->m_pMask->setValid(false);
				if (m_pFrame->m_pCanvas)
					m_pFrame->m_pCanvas->setValid(false);
			}
		}

		void CFrameService::NotifyOnFontChange()
		{
			if (m_pFrame->m_pCanvas)
				m_pFrame->m_pCanvas->setValid(false);
		}

		void CFrameService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_eDownPart == DownPart::None)
			{
				UpdateHoveredButton(m_pFrame->FormToLocal(m.Position));
				if (m_pFrame->m_pCanvas)
					m_pFrame->m_pCanvas->setValid(false);
				m_pFrame->Repaint(false);
			}
		}

		void CFrameService::NotifyOnMouseLeave()
		{
			if (m_eDownPart == DownPart::None)
			{
				if (m_pFrame->m_bMinimizable)
					m_pFrame->m_sBtnMinimizeRestore.State = m_pFrame->m_sBtnMinimizeRestore.State == CFrame::ButtonState::Hovered ? CFrame::ButtonState::Normal : CFrame::ButtonState::Active;
				if (m_pFrame->m_bMaximizable)
					m_pFrame->m_sBtnMaximizeRestore.State = m_pFrame->m_sBtnMaximizeRestore.State == CFrame::ButtonState::Hovered ? CFrame::ButtonState::Normal : CFrame::ButtonState::Active;
				if (m_pFrame->m_bClosable)
					m_pFrame->m_sBtnClose.State = m_pFrame->m_sBtnClose.State == CFrame::ButtonState::Hovered ? CFrame::ButtonState::Normal : CFrame::ButtonState::Active;
				if (m_pFrame->m_pCanvas)
					m_pFrame->m_pCanvas->setValid(false);
				m_pFrame->Repaint(false);
			}
		}

		void CFrameService::NotifyOnKillCaptureMouse()
		{
			MouseUp(false);
		}

		void CFrameService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pFrame->m_pCanvas)
				m_pFrame->m_pCanvas->setValid(false);
			m_pFrame->Repaint(false);
		}

		void CFrameService::NotifyOnKillFocus()
		{
			if (m_pFrame->m_pCanvas)
				m_pFrame->m_pCanvas->setValid(false);
			m_pFrame->Repaint(false);
		}

		void CFrameService::NotifyOnResize()
		{
			CFrame::State state{ m_pFrame->getState() };
			if (m_pFrame->m_aMiddleBorderGradient[(int)state].getPointCount() == 5)
			{
				m_pFrame->m_bIgnoreGradient = true;
				float top{ m_pFrame->m_sOuterBorderWidth.Top + m_pFrame->m_sMiddleBorderWidth.Top + m_pFrame->m_sInnerBorderWidth.Top };
				float y1{ top / m_pFrame->getHeight() }, y2{ (y1 + (m_pFrame->getHeight() - top)) * 0.25f / (m_pFrame->getHeight() - top) };
				m_pFrame->m_aMiddleBorderGradient[(int)CFrame::State::Active].setPointPosition(1, y1);
				m_pFrame->m_aMiddleBorderGradient[(int)CFrame::State::Active].setPointPosition(2, y2);
				m_pFrame->m_aMiddleBorderGradient[(int)CFrame::State::Active].setPointPosition(3, y2 + 0.001f);
				m_pFrame->m_bIgnoreGradient = false;
			}
			if (m_pFrame->m_pCanvas)
				m_pFrame->m_pCanvas->setValid(false);
			if (m_pFrame->m_pMask)
				m_pFrame->m_pMask->setValid(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CFrameService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			m_pFrame->m_bMaskActive = false;
			if (!m.LastPass)
			{
				if (ntl::IsGreater<float>(m_pFrame->getWidth(), 0) && ntl::IsGreater<float>(m_pFrame->getHeight(), 0))
				{
					IRenderer *renderer{ m_pFrame->getForm()->getRenderer() };
					Mat4f matrix{ m_pFrame->getTransformMatrix() };
					m_pFrame->Render(renderer, matrix);
					if (m_pFrame->getControlCount() > 0 && m_pFrame->m_bUseMask && m_pFrame->m_eFrameState != CFrame::FrameState::Minimized)
					{
						m_pFrame->RenderMask(renderer);
						if (m_pFrame->m_pMask)
						{
							renderer->PushMask(m_pFrame->m_pMask, matrix);
							m_pFrame->m_bMaskActive = true;
						}
					}
				}
				else if (m_pFrame->getControlCount() > 0 && m_pFrame->m_bUseMask && m_pFrame->m_eFrameState != CFrame::FrameState::Minimized)
					draw_children = false;
			}
			if (m_pFrame->m_eFrameState == CFrame::FrameState::Minimized)
				draw_children = false;
		}

		void CFrameService::NotifyOnPaintEnd(const MessagePaint &m)
		{
			if (m_pFrame->m_bMaskActive)
			{
				m_pFrame->getForm()->getRenderer()->PopMask();
				m_pFrame->m_bMaskActive = false;
			}
		}
	#pragma endregion

	#pragma region Input notifications
		void CFrameService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			switch (m_eDownPart)
			{
			case DownPart::Caption:
				if (m_pFrame->m_bMovable && m_pFrame->m_eFrameState != CFrame::FrameState::Maximized)
				{
					PointF p_form{ m.Position };
					Vec4f v{ m_sDownMatrixInversed * Vec4f{ p_form.X, p_form.Y, 0, 1 } };
					PointF d{ v.X - m_sDownPosLocal.X, v.Y - m_sDownPosLocal.Y };
					m_pFrame->getTransform()->Translate(m_sDownTransform.X + d.X, m_sDownTransform.Y + d.Y, 0);
				}
				break;
			case DownPart::LeftBorder:
				if (m_pFrame->m_bResizable && m_pFrame->m_eFrameState == CFrame::FrameState::Normal)
				{
					PointF p_form{ m.Position };
					Vec4f v{ m_sDownMatrixInversed * Vec4f{ p_form.X, p_form.Y, 0, 1 } };
					PointF d{ v.X - m_sDownPosLocal.X, v.Y - m_sDownPosLocal.Y };
					m_pFrame->getTransform()->Translate(m_sDownTransform.X + d.X, m_sDownTransform.Y, 0);
					m_pFrame->setWidth(m_sDownSize.X - d.X);
				}
				break;
			case DownPart::TopBorder:
				if (m_pFrame->m_bResizable && m_pFrame->m_eFrameState == CFrame::FrameState::Normal)
				{
					Vec4f v{ m_sDownMatrixInversed * Vec4f{ m.Position.X, m.Position.Y, 0, 1 } };
					PointF d{ v.X - m_sDownPosLocal.X, v.Y - m_sDownPosLocal.Y };
					m_pFrame->getTransform()->Translate(m_sDownTransform.X, m_sDownTransform.Y + d.Y, 0);
					m_pFrame->setHeight(m_sDownSize.Y - d.Y);
				}
				break;
			case DownPart::RightBorder:
				if (m_pFrame->m_bResizable && m_pFrame->m_eFrameState == CFrame::FrameState::Normal)
				{
					Vec4f v{ m_sDownMatrixInversed * Vec4f{ m.Position.X, m.Position.Y, 0, 1 } };
					PointF d{ v.X - m_sDownPosLocal.X, v.Y - m_sDownPosLocal.Y };
					m_pFrame->setWidth(m_sDownSize.X + d.X);
				}
				break;
			case DownPart::BottomBorder:
				if (m_pFrame->m_bResizable && m_pFrame->m_eFrameState == CFrame::FrameState::Normal)
				{
					Vec4f v{ m_sDownMatrixInversed * Vec4f{ m.Position.X, m.Position.Y, 0, 1 } };
					PointF d{ v.X - m_sDownPosLocal.X, v.Y - m_sDownPosLocal.Y };
					m_pFrame->setHeight(m_sDownSize.Y + d.Y);
				}
				break;
			case DownPart::LeftTopCorner:
				if (m_pFrame->m_bResizable && m_pFrame->m_eFrameState == CFrame::FrameState::Normal)
				{
					Vec4f v{ m_sDownMatrixInversed * Vec4f{ m.Position.X, m.Position.Y, 0, 1 } };
					PointF d{ v.X - m_sDownPosLocal.X, v.Y - m_sDownPosLocal.Y };
					m_pFrame->getTransform()->Translate(m_sDownTransform.X + d.X, m_sDownTransform.Y + d.Y, 0);
					m_pFrame->setSize(PointF{ m_sDownSize.X - d.X, m_sDownSize.Y - d.Y });
				}
				break;
			case DownPart::RightTopCorner:
				if (m_pFrame->m_bResizable && m_pFrame->m_eFrameState == CFrame::FrameState::Normal)
				{
					Vec4f v{ m_sDownMatrixInversed * Vec4f{ m.Position.X, m.Position.Y, 0, 1 } };
					PointF d{ v.X - m_sDownPosLocal.X, v.Y - m_sDownPosLocal.Y };
					m_pFrame->getTransform()->Translate(m_sDownTransform.X, m_sDownTransform.Y + d.Y, 0);
					m_pFrame->setSize(PointF{ m_sDownSize.X + d.X, m_sDownSize.Y - d.Y });
				}
				break;
			case DownPart::RightBottomCorner:
				if (m_pFrame->m_bResizable && m_pFrame->m_eFrameState == CFrame::FrameState::Normal)
				{
					Vec4f v{ m_sDownMatrixInversed * Vec4f{ m.Position.X, m.Position.Y, 0, 1 } };
					PointF d{ v.X - m_sDownPosLocal.X, v.Y - m_sDownPosLocal.Y };
					m_pFrame->setSize(PointF{ m_sDownSize.X + d.X, m_sDownSize.Y + d.Y });
				}
				break;
			case DownPart::LeftBottomCorner:
				if (m_pFrame->m_bResizable && m_pFrame->m_eFrameState == CFrame::FrameState::Normal)
				{
					Vec4f v{ m_sDownMatrixInversed * Vec4f{ m.Position.X, m.Position.Y, 0, 1 } };
					PointF d{ v.X - m_sDownPosLocal.X, v.Y - m_sDownPosLocal.Y };
					m_pFrame->getTransform()->Translate(m_sDownTransform.X + d.X, m_sDownTransform.Y, 0);
					m_pFrame->setSize(PointF{ m_sDownSize.X - d.X, m_sDownSize.Y + d.Y });
				}
				break;
			default:
				UpdateHoveredButton(m_pFrame->FormToLocal(m.Position));
			}
		}

		void CFrameService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m.Middle && !m.Right)
			{
				m_eDownPart = m_pFrame->getPart(m_pFrame->FormToLocal(m.Position));
				m_sDownPosLocal = m_pFrame->FormToLocal(m.Position);
				m_sDownTransform.X = m_pFrame->getTransform()->getTx();
				m_sDownTransform.Y = m_pFrame->getTransform()->getTy();
				m_sDownMatrixInversed = ntl::Inversed<float>(m_pFrame->getTransformMatrix());
				m_sDownSize = m_pFrame->getSize();
				if (m_pFrame->m_bMinimizable && m_eDownPart == DownPart::MinimizeRestoreButton)
				{
					m_pFrame->m_sBtnMinimizeRestore.State = CFrame::ButtonState::ActiveHovered;
					m_pFrame->Repaint(m_pFrame->getMinimizeRestoreButtonRenderRect(), true);
				}
				if (m_pFrame->m_bMaximizable && m_eDownPart == DownPart::MaximizeRestoreButton)
				{
					m_pFrame->m_sBtnMaximizeRestore.State = CFrame::ButtonState::ActiveHovered;
					m_pFrame->Repaint(m_pFrame->getMaximizeRestoreButtonRenderRect(), true);
				}
				if (m_pFrame->m_bClosable && m_eDownPart == DownPart::CloseButton)
				{
					m_pFrame->m_sBtnClose.State = CFrame::ButtonState::ActiveHovered;
					m_pFrame->Repaint(m_pFrame->getCloseButtonRenderRect(), true);
				}
				m_pFrame->getForm()->CaptureMouse(m_pFrame, true);
			}
			else
				MouseUp(true);
		}

		void CFrameService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			DownPart part{ m_pFrame->getPart(m_pFrame->FormToLocal(m.Position)) };
			switch (m_eDownPart)
			{
			case DownPart::MinimizeRestoreButton:
				if (part == DownPart::MinimizeRestoreButton && m_pFrame->m_bMinimizable)
				{
					if (m_pFrame->m_eFrameState == CFrame::FrameState::Minimized)
					{
						if (m_pFrame->Restore() && m_pFrame->OnRestore)
							m_pFrame->OnRestore(m_pFrame);
					}
					else
					{
						if (m_pFrame->Minimize() && m_pFrame->OnMinimize)
							m_pFrame->OnMinimize(m_pFrame);
					}
				}
				break;
			case DownPart::MaximizeRestoreButton:
				if (part == DownPart::MaximizeRestoreButton && m_pFrame->m_bMaximizable)
				{
					if (m_pFrame->m_eFrameState == CFrame::FrameState::Maximized)
					{
						if (m_pFrame->Restore() && m_pFrame->OnRestore)
							m_pFrame->OnRestore(m_pFrame);
					}
					else
					{
						if (m_pFrame->Maximize() && m_pFrame->OnMaximize)
							m_pFrame->OnMaximize(m_pFrame);
					}
				}
				break;
			case DownPart::CloseButton:
				if (part == DownPart::CloseButton && m_pFrame->m_bClosable)
				{
					CloseAction action{ CloseAction::Free };
					if (m_pFrame->OnClose)
						m_pFrame->OnClose(m_pFrame, action);
					if (action != CloseAction::None)
						m_pFrame->Hide();
				}
				break;
			default:
				break;
			}
			MouseUp(true);
		}

		void CFrameService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m.Middle && !m.Right && m_pFrame->m_bMaximizable && m_pFrame->getPart(m_pFrame->FormToLocal(m.Position)) == DownPart::Caption)
				m_pFrame->m_eFrameState == CFrame::FrameState::Maximized ? m_pFrame->Restore() : m_pFrame->Maximize();
			MouseUp(true);
		}

		void CFrameService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CFrameService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CFrameService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CFrameService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CFrameService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CFrameService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}
	#pragma endregion
	}
}