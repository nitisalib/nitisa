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
		CImageListEditorService::CImageListEditorService(CImageListEditor *editor) :
			CControlService(editor),
			m_pEditor{ editor },
			m_bDown{ false }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CImageListEditorService::CancelDown(const bool check_capture)
		{
			if (m_bDown)
			{
				m_bDown = false;
				m_pEditor->getScroll()->NotifyOnMouseDownCancel();
				if (check_capture && m_pEditor->isCaptureMouse())
					m_pEditor->getForm()->ReleaseCaptureMouse();
			}
		}

		PointF CImageListEditorService::FormToScroll(const PointF &position)
		{
			PointF result{ (PointF)m_pEditor->FormToLocal(position) };
			return PointF{ result.X - m_pEditor->getScroll()->getLeft(), result.Y - m_pEditor->getScroll()->getTop() };
		}
	#pragma endregion

	#pragma region State change notifications
		void CImageListEditorService::NotifyOnAttach()
		{
			if (m_pEditor->getForm())
			{
				if (m_pEditor->m_pScroll)
					m_pEditor->m_pScroll->NotifyOnAttach();
				m_pEditor->Update();
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
			}
		}

		void CImageListEditorService::NotifyOnDetaching()
		{
			m_pEditor->ImageListDetach(m_pEditor->m_pImageList);
			if (m_pEditor->m_pScroll)
				m_pEditor->m_pScroll->NotifyOnDeactivate();
		}

		void CImageListEditorService::NotifyOnFreeResources()
		{
			if (m_pEditor->m_pCanvas)
			{
				m_pEditor->m_pCanvas->Release();
				m_pEditor->m_pCanvas = nullptr;
			}
			if (m_pEditor->m_pScroll)
				m_pEditor->m_pScroll->NotifyOnFreeResources();
		}
	#pragma endregion

	#pragma region Component notifications
		void CImageListEditorService::NotifyOnComponentDetach(IComponent *component)
		{
			m_pEditor->ImageListDetach(cast<IImageList*>(component));
		}

		void CImageListEditorService::NotifyOnComponentChange(IComponent *component)
		{
			m_pEditor->ImageListChange(cast<IImageList*>(component));
		}
	#pragma endregion

	#pragma region Control notifications
		void CImageListEditorService::NotifyOnControlDetach(IControl *control)
		{
			m_pEditor->ImageListDetach(cast<IImageList*>(control));
		}

		void CImageListEditorService::NotifyOnControlChange(IControl *control)
		{
			m_pEditor->ImageListChange(cast<IImageList*>(control));
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CImageListEditorService::NotifyOnParentStyleChange()
		{
			if (m_pEditor->getStyle())
			{
				m_pEditor->UpdateFromStyle(m_pEditor->getStyle());
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
			}
		}

		void CImageListEditorService::NotifyOnParentFontChange()
		{
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CImageListEditorService::NotifyOnEnable()
		{
			m_pEditor->Update();
			m_pEditor->UpdateHoveredElement();
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
		}

		void CImageListEditorService::NotifyOnDisable()
		{
			m_pEditor->Update();
			m_pEditor->UpdateHoveredElement();
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
		}

		void CImageListEditorService::NotifyOnResize()
		{
			m_pEditor->Update();
			m_pEditor->UpdateHoveredElement();
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
		}

		void CImageListEditorService::NotifyOnStyleChange()
		{
			if (m_pEditor->getStyle())
			{
				m_pEditor->UpdateFromStyle(m_pEditor->getStyle());
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
			}
		}

		void CImageListEditorService::NotifyOnFontChange()
		{
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
		}

		void CImageListEditorService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CImageListEditorService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pEditor->getWidth(), 0) && ntl::IsGreater<float>(m_pEditor->getHeight(), 0))
				m_pEditor->Render();
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CImageListEditorService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pEditor->UpdateHoveredElement(m_pEditor->FormToLocal(m.Position)))
			{
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CImageListEditorService::NotifyOnMouseLeave()
		{
			if (m_pEditor->UpdateHoveredElement())
			{
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CImageListEditorService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_bDown)
			{
				if (m_pEditor->getScroll()->NotifyOnMouseMove(FormToScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
				return;
			}
			bool changed{ m_pEditor->UpdateHoveredElement(m_pEditor->FormToLocal(m.Position)) };
			switch (m_pEditor->m_eHoveredElement)
			{
			case CImageListEditor::Element::Scroll:
				changed = m_pEditor->getScroll()->NotifyOnMouseMove(FormToScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift) || changed;
				break;
			default:
				break;
			}
			if (changed)
			{
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				m_pEditor->Repaint(false);
			}
		}

		void CImageListEditorService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pEditor->isEnabled(true) && !m_bDown && !m.Middle && !m.Right)
			{
				bool changed{ false };
				switch (m_pEditor->m_eHoveredElement)
				{
				case CImageListEditor::Element::Scroll:
					changed = m_pEditor->getScroll()->NotifyOnMouseLeftDown(FormToScroll(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift);
					m_bDown = true;
					m_pEditor->getForm()->CaptureMouse(m_pEditor, true);
					break;
				case CImageListEditor::Element::Item:
					if (m.Ctrl)
					{
						m_pEditor->m_aItems[m_pEditor->m_iHoveredItemIndex].Selected = !m_pEditor->m_aItems[m_pEditor->m_iHoveredItemIndex].Selected;
						changed = true;
					}
					else
					{
						for (auto pos = m_pEditor->m_aItems.begin(); pos != m_pEditor->m_aItems.end(); pos++)
							if (pos - m_pEditor->m_aItems.begin() == m_pEditor->m_iHoveredItemIndex)
							{
								if (!pos->Selected)
								{
									pos->Selected = true;
									changed = true;
								}
							}
							else if (pos->Selected)
							{
								pos->Selected = false;
								changed = true;
							}
					}
					break;
				default:
					break;
				}
				if (changed)
				{
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
			else
				CancelDown(true);
		}

		void CImageListEditorService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			CancelDown(true);
		}

		void CImageListEditorService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CImageListEditorService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CImageListEditorService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CImageListEditorService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CImageListEditorService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CImageListEditorService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CImageListEditorService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CImageListEditorService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pEditor->isEnabled(true))
			{
				bool changed{ false };
				switch (m_pEditor->m_eHoveredElement)
				{
				case CImageListEditor::Element::Scroll:
					changed = m_pEditor->getScroll()->NotifyOnMouseVerticalWheel(FormToScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta);
					break;
				default:
					if (m_pEditor->getScroll()->setScroll(m_pEditor->getScroll()->getScroll() + m_pEditor->getScroll()->getDeltaMedium() * (m.Delta < 0 ? 1 : -1)))
					{
						changed = true;
						m_pEditor->UpdateHoveredElement(m_pEditor->FormToLocal(m.Position));
					}
				}
				if (changed)
				{
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}

		void CImageListEditorService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pEditor->isEnabled(true))
			{
				bool changed{ false };
				switch (m_pEditor->m_eHoveredElement)
				{
				case CImageListEditor::Element::Scroll:
					changed = m_pEditor->getScroll()->NotifyOnMouseHorizontalWheel(FormToScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta);
					break;
				default:
					if (m_pEditor->getScroll()->setScroll(m_pEditor->getScroll()->getScroll() + m_pEditor->getScroll()->getDeltaMedium() * (m.Delta > 0 ? 1 : -1)))
					{
						changed = true;
						m_pEditor->UpdateHoveredElement(m_pEditor->FormToLocal(m.Position));
					}
				}
				if (changed)
				{
					if (m_pEditor->m_pCanvas)
						m_pEditor->m_pCanvas->setValid(false);
					m_pEditor->Repaint(false);
				}
			}
		}
	#pragma endregion
	}
}