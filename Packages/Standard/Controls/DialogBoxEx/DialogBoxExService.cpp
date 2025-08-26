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
		CDialogBoxExService::CDialogBoxExService(CDialogBoxEx *control) :
			CDialogBoxService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CDialogBoxExService::CancelDown(const bool check_capture)
		{
			m_pControl->m_eDownElement = CDialogBoxEx::Element::None;
			if (m_pControl->m_hTimerBlink)
			{
				m_pControl->getForm()->DeleteTimer(m_pControl->m_hTimerBlink);
				m_pControl->m_hTimerBlink = nullptr;
			}
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
			if (check_capture && m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}
	#pragma endregion

	#pragma region State change notifications
		void CDialogBoxExService::NotifyOnAttach()
		{
			m_pControl->HandleAttach();
		}

		void CDialogBoxExService::NotifyOnFreeResources()
		{
			if (m_pControl->m_hTimerBlink)
			{
				m_pControl->getForm()->DeleteTimer(m_pControl->m_hTimerBlink);
				m_pControl->m_hTimerBlink = nullptr;
			}
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

	#pragma region Component notifications
		void CDialogBoxExService::NotifyOnComponentDetach(IComponent *component)
		{
			if (component == m_pControl->m_pButtonIcons || component == m_pControl->m_pIcons)
			{
				if (component == m_pControl->m_pButtonIcons)
					m_pControl->m_pButtonIcons = nullptr;
				if (component == m_pControl->m_pIcons)
					m_pControl->m_pIcons = nullptr;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CDialogBoxExService::NotifyOnComponentChange(IComponent *component)
		{
			if (component == m_pControl->m_pButtonIcons || component == m_pControl->m_pIcons)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Control notifications
		void CDialogBoxExService::NotifyOnControlDetach(IControl *control)
		{
			if (control == cast<IControl*>(m_pControl->m_pButtonIcons) || control == cast<IControl*>(m_pControl->m_pIcons))
			{
				if (control == cast<IControl*>(m_pControl->m_pButtonIcons))
					m_pControl->m_pButtonIcons = nullptr;
				if (control == cast<IControl*>(m_pControl->m_pIcons))
					m_pControl->m_pIcons = nullptr;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CDialogBoxExService::NotifyOnControlChange(IControl *control)
		{
			if (control == cast<IControl*>(m_pControl->m_pButtonIcons) || control == cast<IControl*>(m_pControl->m_pIcons))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CDialogBoxExService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_bUseMask && m_pControl->m_pMask)
					m_pControl->m_pMask->setValid(false);
			}
		}

		void CDialogBoxExService::NotifyOnParentFontChange()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CDialogBoxExService::NotifyOnParentResize()
		{
			if (m_pControl->m_eState == WindowState::Maximized)
				m_pControl->FitInParent();
		}
	#pragma endregion

	#pragma region State change notifications
		void CDialogBoxExService::NotifyOnShow()
		{
			if (m_pControl->m_eState == WindowState::Hidden)
				m_pControl->m_eState = m_pControl->m_eHideState;
		}

		void CDialogBoxExService::NotifyOnHide()
		{
			m_pControl->m_eHideState = m_pControl->m_eState;
			if (m_pControl->m_eState != WindowState::Hidden)
				m_pControl->m_eState = WindowState::Hidden;
		}

		void CDialogBoxExService::NotifyOnEnable()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CDialogBoxExService::NotifyOnDisable()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CDialogBoxExService::NotifyOnResize()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			if (m_pControl->m_bUseMask && m_pControl->m_pMask)
				m_pControl->m_pMask->setValid(false);
			if (m_pControl->m_eState == WindowState::Normal)
				m_pControl->m_sNormalSize = m_pControl->getSize();
		}

		void CDialogBoxExService::NotifyOnTransform()
		{
			if (m_pControl->m_eState == WindowState::Normal)
				m_pControl->m_sNormalTransform = m_pControl->getTransform()->getTransform();
		}

		void CDialogBoxExService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_bUseMask && m_pControl->m_pMask)
					m_pControl->m_pMask->setValid(false);
			}
		}

		void CDialogBoxExService::NotifyOnFontChange()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CDialogBoxExService::NotifyOnSetModal()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CDialogBoxExService::NotifyOnKillModal()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}

		void CDialogBoxExService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CDialogBoxExService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			m_bMaskActive = false;
			if (!m.LastPass)
			{
				if (ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
				{
					IRenderer *renderer{ m_pControl->getForm()->getRenderer() };
					Mat4f matrix{ m_pControl->getTransformMatrix() };
					m_pControl->Render(renderer, matrix);
					if (m_pControl->m_eState == WindowState::Minimized)
						draw_children = false;
					else
						if (m_pControl->getControlCount() > 0 && m_pControl->m_bUseMask)
						{
							if (m_pControl->getClientRect().is_zero())
								draw_children = false;
							else
							{
								m_pControl->RenderMask(renderer);
								if (m_pControl->m_pMask)
								{
									renderer->PushMask(m_pControl->m_pMask, matrix);
									m_bMaskActive = true;
								}
							}
						}
				}
				else
					draw_children = false;
			}
			else if (m_pControl->m_eState == WindowState::Minimized)
				draw_children = false;
		}

		void CDialogBoxExService::NotifyOnPaintEnd(const MessagePaint &m)
		{
			if (m_bMaskActive)
			{
				m_pControl->getForm()->getRenderer()->PopMask();
				m_bMaskActive = false;
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CDialogBoxExService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pControl->isEnabled(true) && m_pControl->UpdateHoveredElement(m_pControl->FormToLocal(m.Position)))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CDialogBoxExService::NotifyOnMouseLeave()
		{
			if (m_pControl->isEnabled(true) && m_pControl->UpdateHoveredElement())
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CDialogBoxExService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				switch (m_pControl->m_eDownElement)
				{
				case CDialogBoxEx::Element::LeftTopCorner:
					ProcessMoveLeftTopCorner(m.Position);
					break;
				case CDialogBoxEx::Element::RightTopCorner:
					ProcessMoveRightTopCorner(m.Position);
					break;
				case CDialogBoxEx::Element::RightBottomCorner:
					ProcessMoveRightBottomCorner(m.Position);
					break;
				case CDialogBoxEx::Element::LeftBottomCorner:
					ProcessMoveLeftBottomCorner(m.Position);
					break;
				case CDialogBoxEx::Element::LeftBorder:
					ProcessMoveLeftBorder(m.Position);
					break;
				case CDialogBoxEx::Element::TopBorder:
					ProcessMoveTopBorder(m.Position);
					break;
				case CDialogBoxEx::Element::RightBorder:
					ProcessMoveRightBorder(m.Position);
					break;
				case CDialogBoxEx::Element::BottomBorder:
					ProcessMoveBottomBorder(m.Position);
					break;
				case CDialogBoxEx::Element::Caption:
					ProcessMoveCaption(m.Position);
					break;
				default:
					break;
				}
				if (m_pControl->UpdateHoveredElement(m_pControl->FormToLocal(m.Position)))
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
		}

		void CDialogBoxExService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				if (m_pControl->m_eDownElement == CDialogBoxEx::Element::None)
				{
					if (!m.Middle && !m.Right)
					{
						switch (m_pControl->m_eHoveredElement)
						{
						case CDialogBoxEx::Element::LeftTopCorner:
						case CDialogBoxEx::Element::RightTopCorner:
						case CDialogBoxEx::Element::RightBottomCorner:
						case CDialogBoxEx::Element::LeftBottomCorner:
						case CDialogBoxEx::Element::LeftBorder:
						case CDialogBoxEx::Element::TopBorder:
						case CDialogBoxEx::Element::RightBorder:
						case CDialogBoxEx::Element::BottomBorder:
							if (m_pControl->m_eState != WindowState::Normal)
								return;
						case CDialogBoxEx::Element::Caption:
							if (m_pControl->m_eState != WindowState::Normal && m_pControl->m_eState != WindowState::Minimized)
								return;
						case CDialogBoxEx::Element::ButtonMinimize:
						case CDialogBoxEx::Element::ButtonMaximize:
						case CDialogBoxEx::Element::ButtonRestore:
						case CDialogBoxEx::Element::ButtonClose:
						case CDialogBoxEx::Element::Icon:
							break;
						case CDialogBoxEx::Element::Client:
							return;
						default: // Outside control. Start blinking if the control is in modal state
							if (m_pControl->isModal())
							{
								if (!m_pControl->m_hTimerBlink && m_pControl->m_iBlinkCount > 0)
								{
									m_pControl->m_iBlinkCounter = 0;
									m_pControl->m_hTimerBlink = m_pControl->getForm()->CreateTimer(&m_pControl->m_cTimerListener, m_pControl->m_fBlinkInterval);
								}
								return;
							}
						}
						m_pControl->m_eDownElement = m_pControl->m_eHoveredElement;
						if (m_pControl->m_eDownElement != CDialogBoxEx::Element::None)
						{
							m_sDownLocal = m_pControl->FormToLocal(m.Position);
							m_sDownTransform.X = m_pControl->getTransform()->getTx();
							m_sDownTransform.Y = m_pControl->getTransform()->getTy();
							m_sDownMatrixInversed = ntl::Inversed<float>(m_pControl->getTransformMatrix());
							m_sDownSize = m_pControl->getSize();
							m_pControl->getForm()->CaptureMouse(m_pControl, true);
							if (m_pControl->m_pCanvas)
								m_pControl->m_pCanvas->setValid(false);
							m_pControl->Repaint(false);
						}
					}
				}
				else
					CancelDown(true);
			}
		}

		void CDialogBoxExService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			CDialogBoxEx::Element down_element{ m_pControl->m_eDownElement };
			if (m_pControl->m_eDownElement != CDialogBoxEx::Element::None)
				CancelDown(true);
			if (down_element == m_pControl->m_eHoveredElement)
			{
				switch (down_element)
				{
				case CDialogBoxEx::Element::ButtonMinimize:
					m_pControl->Minimize();
					break;
				case CDialogBoxEx::Element::ButtonMaximize:
					m_pControl->Maximize();
					break;
				case CDialogBoxEx::Element::ButtonRestore:
					m_pControl->Restore();
					break;
				case CDialogBoxEx::Element::ButtonClose:
					m_pControl->Close();
					break;
				default:
					break;
				}
			}
		}

		void CDialogBoxExService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true) && m_pControl->m_eHoveredElement == CDialogBoxEx::Element::Caption)
			{
				switch (m_pControl->m_eState)
				{
				case WindowState::Normal:
					m_pControl->Maximize();
					break;
				case WindowState::Maximized:
				case WindowState::Minimized:
					m_pControl->Restore();
					break;
				default:
					break;
				}
			}
		}

		void CDialogBoxExService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CDialogBoxExService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CDialogBoxExService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CDialogBoxExService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CDialogBoxExService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CDialogBoxExService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}
	#pragma endregion

	#pragma region Dialog box notifications
		void CDialogBoxExService::NotifyOnSetActive()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CDialogBoxExService::NotifyOnKillActive()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}
	#pragma endregion

	#pragma region Process move
		void CDialogBoxExService::ProcessMoveLeftTopCorner(const PointF &position)
		{
			Vec4f v{ m_sDownMatrixInversed * Vec4f{ position.X, position.Y, 0, 1 } };
			PointF d{ v.X - m_sDownLocal.X, v.Y - m_sDownLocal.Y };
			m_pControl->getTransform()->Translate(m_sDownTransform.X + d.X, m_sDownTransform.Y + d.Y, 0);
			m_pControl->setSize(PointF{ m_sDownSize.X - d.X, m_sDownSize.Y - d.Y });
		}

		void CDialogBoxExService::ProcessMoveRightTopCorner(const PointF &position)
		{
			Vec4f v{ m_sDownMatrixInversed * Vec4f{ position.X, position.Y, 0, 1 } };
			PointF d{ v.X - m_sDownLocal.X, v.Y - m_sDownLocal.Y };
			m_pControl->getTransform()->Translate(m_sDownTransform.X, m_sDownTransform.Y + d.Y, 0);
			m_pControl->setSize(PointF{ m_sDownSize.X + d.X, m_sDownSize.Y - d.Y });
		}

		void CDialogBoxExService::ProcessMoveRightBottomCorner(const PointF &position)
		{
			Vec4f v{ m_sDownMatrixInversed * Vec4f{ position.X, position.Y, 0, 1 } };
			PointF d{ v.X - m_sDownLocal.X, v.Y - m_sDownLocal.Y };
			m_pControl->setSize(PointF{ m_sDownSize.X + d.X, m_sDownSize.Y + d.Y });
		}

		void CDialogBoxExService::ProcessMoveLeftBottomCorner(const PointF &position)
		{
			Vec4f v{ m_sDownMatrixInversed * Vec4f{ position.X, position.Y, 0, 1 } };
			PointF d{ v.X - m_sDownLocal.X, v.Y - m_sDownLocal.Y };
			m_pControl->getTransform()->Translate(m_sDownTransform.X + d.X, m_sDownTransform.Y, 0);
			m_pControl->setSize(PointF{ m_sDownSize.X - d.X, m_sDownSize.Y + d.Y });
		}

		void CDialogBoxExService::ProcessMoveLeftBorder(const PointF &position)
		{
			Vec4f v{ m_sDownMatrixInversed * Vec4f{ position.X, position.Y, 0, 1 } };
			PointF d{ v.X - m_sDownLocal.X, v.Y - m_sDownLocal.Y };
			m_pControl->getTransform()->Translate(m_sDownTransform.X + d.X, m_sDownTransform.Y, 0);
			m_pControl->setWidth(m_sDownSize.X - d.X);
		}

		void CDialogBoxExService::ProcessMoveTopBorder(const PointF &position)
		{
			Vec4f v{ m_sDownMatrixInversed * Vec4f{ position.X, position.Y, 0, 1 } };
			PointF d{ v.X - m_sDownLocal.X, v.Y - m_sDownLocal.Y };
			m_pControl->getTransform()->Translate(m_sDownTransform.X, m_sDownTransform.Y + d.Y, 0);
			m_pControl->setHeight(m_sDownSize.Y - d.Y);
		}

		void CDialogBoxExService::ProcessMoveRightBorder(const PointF &position)
		{
			Vec4f v{ m_sDownMatrixInversed * Vec4f{ position.X, position.Y, 0, 1 } };
			PointF d{ v.X - m_sDownLocal.X, v.Y - m_sDownLocal.Y };
			m_pControl->setWidth(m_sDownSize.X + d.X);
		}

		void CDialogBoxExService::ProcessMoveBottomBorder(const PointF &position)
		{
			Vec4f v{ m_sDownMatrixInversed * Vec4f{ position.X, position.Y, 0, 1 } };
			PointF d{ v.X - m_sDownLocal.X, v.Y - m_sDownLocal.Y };
			m_pControl->setHeight(m_sDownSize.Y + d.Y);
		}

		void CDialogBoxExService::ProcessMoveCaption(const PointF &position)
		{
			Vec4f v{ m_sDownMatrixInversed * Vec4f{ position.X, position.Y, 0, 1 } };
			PointF d{ v.X - m_sDownLocal.X, v.Y - m_sDownLocal.Y };
			m_pControl->getTransform()->Translate(m_sDownTransform.X + d.X, m_sDownTransform.Y + d.Y, 0);
		}
	#pragma endregion
	}
}