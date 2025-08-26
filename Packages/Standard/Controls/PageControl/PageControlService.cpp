// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
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
		CPageControlService::CPageControlService(CPageControl *page) :
			CControlService(page),
			m_pPage{ page },
			m_bIgnoreChildShow{ false },
			m_bIgnoreChildHide{ false },
			m_hTimer{ nullptr }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CPageControlService::UpdateActiveIndex()
		{
			int old{ m_pPage->m_iActiveIndex };
			m_pPage->m_iActiveIndex = -1;
			for (int i = 0; i < m_pPage->getControlCount(); i++)
				if (m_pPage->getControl(i)->isVisible(false))
				{
					m_pPage->m_iActiveIndex = i;
					if (i != old && i >= 0 && m_pPage->OnActivateTabSheet)
						m_pPage->OnActivateTabSheet(m_pPage, i);
					break;
				}
		}

		void CPageControlService::MouseUp(const bool check_capture)
		{
			m_pPage->m_eDownElement = CPageControl::Element::None;
			if (m_hTimer)
			{
				m_pPage->getForm()->DeleteTimer(m_hTimer);
				m_hTimer = nullptr;
			}
			if (check_capture && m_pPage->isCaptureMouse())
				m_pPage->getForm()->ReleaseCaptureMouse();
		}
	#pragma endregion

	#pragma region State change notifications
		void CPageControlService::NotifyOnAttach()
		{
			if (m_pPage->getForm())
				m_pPage->Update();
		}

		void CPageControlService::NotifyOnFreeResources()
		{
			if (m_pPage->m_pCanvas)
			{
				m_pPage->m_pCanvas->Release();
				m_pPage->m_pCanvas = nullptr;
			}
			if (m_pPage->m_pMask)
			{
				m_pPage->m_pMask->Release();
				m_pPage->m_pMask = nullptr;
			}
		}
	#pragma endregion

	#pragma region Other components/controls/objects change notifications
		void CPageControlService::NotifyOnComponentDetach(IComponent *component)
		{
			if (m_pPage->m_pImageList && cast<IImageList*>(component) == m_pPage->m_pImageList)
			{
				m_pPage->m_pImageList = nullptr;
				m_pPage->Update();
				AlignControls();
				if (m_pPage->m_pCanvas)
					m_pPage->m_pCanvas->setValid(false);
				m_pPage->Repaint(false);
			}
		}

		void CPageControlService::NotifyOnControlDetach(IControl *control)
		{
			if (m_pPage->m_pImageList && cast<IImageList*>(control) == m_pPage->m_pImageList)
			{
				m_pPage->m_pImageList = nullptr;
				m_pPage->Update();
				AlignControls();
				if (m_pPage->m_pCanvas)
					m_pPage->m_pCanvas->setValid(false);
				m_pPage->Repaint(false);
			}
		}

		void CPageControlService::NotifyOnComponentChange(IComponent *component)
		{
			if (m_pPage->m_pImageList && cast<IImageList*>(component) == m_pPage->m_pImageList)
			{
				m_pPage->Update();
				AlignControls();
				if (m_pPage->m_pCanvas)
					m_pPage->m_pCanvas->setValid(false);
				m_pPage->Repaint(false);
			}
		}

		void CPageControlService::NotifyOnControlChange(IControl *control)
		{
			if (m_pPage->m_pImageList && cast<IImageList*>(control) == m_pPage->m_pImageList)
			{
				m_pPage->Update();
				AlignControls();
				if (m_pPage->m_pCanvas)
					m_pPage->m_pCanvas->setValid(false);
				m_pPage->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CPageControlService::NotifyOnParentStyleChange()
		{
			if (m_pPage->getStyle())
			{
				m_pPage->UpdateFromStyle(m_pPage->getStyle());
				if (m_pPage->m_pCanvas)
					m_pPage->m_pCanvas->setValid(false);
				if (m_pPage->m_pMask)
					m_pPage->m_pMask->setValid(false);
			}
		}

		void CPageControlService::NotifyOnParentFontChange()
		{
			m_pPage->Update();
			AlignControls();
			if (m_pPage->m_pCanvas)
				m_pPage->m_pCanvas->setValid(false);
			if (m_pPage->m_pMask && ntl::IsLessOrEqual<float>(m_pPage->m_sHeaderSize.Y, 0))
				m_pPage->m_pMask->setValid(false);
		}
	#pragma endregion

	#pragma region Notifications from child controls
		void CPageControlService::NotifyOnChildShow(IControl *control)
		{
			if (!m_bIgnoreChildShow)
			{
				int index{ cast<ITabSheet*>(control)->getIndex() };
				if (m_pPage->m_iActiveIndex != index)
				{
					if (m_pPage->m_iActiveIndex >= 0)
					{
						m_bIgnoreChildHide = true;
						m_pPage->getTabSheet(m_pPage->m_iActiveIndex)->setVisible(false);
						m_bIgnoreChildHide = false;
					}
					m_pPage->m_iActiveIndex = index;
					if (m_pPage->OnActivateTabSheet)
						m_pPage->OnActivateTabSheet(m_pPage, m_pPage->m_iActiveIndex);
					m_pPage->Update();
					if (m_pPage->m_pCanvas)
						m_pPage->m_pCanvas->setValid(false);
					m_pPage->Repaint(false);
				}
			}
		}

		void CPageControlService::NotifyOnChildHide(IControl *control)
		{
			if (!m_bIgnoreChildHide)
			{
				int index{ cast<ITabSheet*>(control)->getIndex() };
				if (index > 0)
					index--;
				else
					index++;
				if (index >= m_pPage->getControlCount())
					index = -1;
				m_pPage->m_iActiveIndex = index;
				if (m_pPage->m_iActiveIndex >= 0)
				{
					m_bIgnoreChildShow = true;
					m_pPage->getTabSheet(m_pPage->m_iActiveIndex)->setVisible(true);
					m_bIgnoreChildShow = false;
					if (m_pPage->OnActivateTabSheet)
						m_pPage->OnActivateTabSheet(m_pPage, m_pPage->m_iActiveIndex);
				}
				m_pPage->Update();
				if (m_pPage->m_pCanvas)
					m_pPage->m_pCanvas->setValid(false);
				m_pPage->Repaint(false);
			}
		}

		void CPageControlService::NotifyOnChildAttach(IControl *control)
		{
			// Activate attached one
			ITabSheet *tab{ cast<ITabSheet*>(control) };
			if (tab->isVisible(false))
			{
				int index{ tab->getIndex() };
				m_bIgnoreChildHide = true;
				for (int i = 0; i < m_pPage->getControlCount(); i++)
					if (i != index)
						m_pPage->getControl(i)->setVisible(false);
				m_bIgnoreChildHide = false;
			}
			UpdateActiveIndex();
			m_pPage->Update();
			AlignControls();
			if (m_pPage->m_pCanvas)
				m_pPage->m_pCanvas->setValid(false);
			m_pPage->Repaint(false);
		}

		void CPageControlService::NotifyOnChildDetach(IControl *control)
		{
			UpdateActiveIndex();
			if (m_pPage->m_iActiveIndex < 0)
				m_pPage->setActiveIndex(0);
			m_pPage->Update();
			AlignControls();
			if (m_pPage->m_pCanvas)
				m_pPage->m_pCanvas->setValid(false);
			m_pPage->Repaint(false);
		}

		void CPageControlService::NotifyOnChildEnable(IControl *control)
		{
			if (m_pPage->m_pCanvas)
				m_pPage->m_pCanvas->setValid(false);
			m_pPage->Repaint(false);
		}

		void CPageControlService::NotifyOnChildDisable(IControl *control)
		{
			if (m_pPage->m_pCanvas)
				m_pPage->m_pCanvas->setValid(false);
			m_pPage->Repaint(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CPageControlService::NotifyOnStyleChange()
		{
			if (m_pPage->getStyle())
			{
				m_pPage->UpdateFromStyle(m_pPage->getStyle());
				if (m_pPage->m_pCanvas)
					m_pPage->m_pCanvas->setValid(false);
				if (m_pPage->m_pMask)
					m_pPage->m_pMask->setValid(false);
			}
		}

		void CPageControlService::NotifyOnFontChange()
		{
			m_pPage->Update();
			AlignControls();
			if (m_pPage->m_pCanvas)
				m_pPage->m_pCanvas->setValid(false);
			if (m_pPage->m_pMask && ntl::IsLessOrEqual<float>(m_pPage->m_sHeaderSize.Y, 0))
				m_pPage->m_pMask->setValid(false);
		}

		void CPageControlService::NotifyOnEnable()
		{
			if (m_pPage->m_pCanvas)
				m_pPage->m_pCanvas->setValid(false);
		}

		void CPageControlService::NotifyOnDisable()
		{
			if (m_pPage->m_pCanvas)
				m_pPage->m_pCanvas->setValid(false);
		}

		void CPageControlService::NotifyOnResize()
		{
			if (m_pPage->m_pCanvas)
				m_pPage->m_pCanvas->setValid(false);
			if (m_pPage->m_pMask)
				m_pPage->m_pMask->setValid(false);
			m_pPage->Update();
			AlignControls();
		}

		void CPageControlService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pPage->m_pCanvas)
				m_pPage->m_pCanvas->setValid(false);
			m_pPage->Repaint(false);
		}

		void CPageControlService::NotifyOnKillFocus()
		{
			if (m_pPage->m_pCanvas)
				m_pPage->m_pCanvas->setValid(false);
			m_pPage->Repaint(false);
		}

		void CPageControlService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pPage->UpdateHoveredElement(m_pPage->FormToLocal(m.Position)))
			{
				if (m_pPage->m_pCanvas)
					m_pPage->m_pCanvas->setValid(false);
				m_pPage->Repaint(false);
			}
		}

		void CPageControlService::NotifyOnMouseLeave()
		{
			if (m_pPage->m_eHoveredElement != CPageControl::Element::None)
			{
				m_pPage->m_eHoveredElement = CPageControl::Element::None;
				if (m_pPage->m_pCanvas)
					m_pPage->m_pCanvas->setValid(false);
				m_pPage->Repaint(false);
			}
		}

		void CPageControlService::NotifyOnSetCaptureMouse()
		{
			m_hTimer = m_pPage->getForm()->CreateTimer(this, m_pPage->m_fScrollInterval);
		}

		void CPageControlService::NotifyOnKillCaptureMouse()
		{
			if (m_hTimer)
			{
				m_pPage->getForm()->DeleteTimer(m_hTimer);
				m_hTimer = nullptr;
			}
			MouseUp(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CPageControlService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			m_bMaskActive = false;
			if (!m.LastPass)
			{
				if (ntl::IsGreater<float>(m_pPage->getWidth(), 0) && ntl::IsGreater<float>(m_pPage->getHeight(), 0))
				{
					IRenderer *renderer{ m_pPage->getForm()->getRenderer() };
					Mat4f matrix{ m_pPage->getTransformMatrix() };
					m_pPage->Render(renderer, matrix);
					if (m_pPage->m_iActiveIndex >= 0 && m_pPage->m_bUseMask && m_pPage->getActiveTabSheet()->getControlCount() > 0)
					{
						m_pPage->RenderMask(renderer);
						if (m_pPage->m_pMask)
						{
							renderer->PushMask(m_pPage->m_pMask, matrix);
							m_bMaskActive = true;
						}
					}
				}
				else if (m_pPage->m_iActiveIndex >= 0 && m_pPage->m_bUseMask && m_pPage->getActiveTabSheet()->getControlCount() > 0)
					draw_children = false;
			}
		}

		void CPageControlService::NotifyOnPaintEnd(const MessagePaint &m)
		{
			if (m_bMaskActive)
			{
				m_pPage->getForm()->getRenderer()->PopMask();
				m_bMaskActive = false;
			}
		}
	#pragma endregion

	#pragma region Input notifications
		void CPageControlService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			int index{ m_pPage->m_iActiveIndex };
			switch (m.Key)
			{
			case Key::Right:
				index++;
				if (index >= m_pPage->getControlCount())
					index = ntl::Min<int>(0, m_pPage->getControlCount() - 1);
				break;
			case Key::Left:
				index--;
				if (index < 0)
					index = m_pPage->getControlCount() - 1;
				break;
			default:
				break;
			}
			if (m_pPage->setActiveIndex(index) && index >= 0 && m_pPage->OnActivateTabSheet)
				m_pPage->OnActivateTabSheet(m_pPage, m_pPage->m_iActiveIndex);
		}

		void CPageControlService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pPage->UpdateHoveredElement(m_pPage->FormToLocal(m.Position)))
			{
				if (m_pPage->m_pCanvas)
					m_pPage->m_pCanvas->setValid(false);
				m_pPage->Repaint(false);
			}
		}

		void CPageControlService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pPage->m_eDownElement == CPageControl::Element::None)
			{
				switch (m_pPage->m_eHoveredElement)
				{
				case CPageControl::Element::ScrollStart:
					if (ntl::IsGreater<float>(m_pPage->m_fScroll, 0))
					{
						m_pPage->m_fScroll = ntl::Max<float>(0, m_pPage->m_fScroll - m_pPage->m_fDeltaScrollTimer);
						m_pPage->m_eDownElement = CPageControl::Element::ScrollStart;
						m_pPage->getForm()->CaptureMouse(m_pPage, true);
						if (m_pPage->m_pCanvas)
							m_pPage->m_pCanvas->setValid(false);
						m_pPage->Repaint(false);
					}
					break;
				case CPageControl::Element::ScrollEnd:
					if (ntl::IsLess<float>(m_pPage->m_fScroll, m_pPage->m_fScrollMax))
					{
						m_pPage->m_fScroll = ntl::Min<float>(m_pPage->m_fScrollMax, m_pPage->m_fScroll + m_pPage->m_fDeltaScrollTimer);
						m_pPage->m_eDownElement = CPageControl::Element::ScrollEnd;
						m_pPage->getForm()->CaptureMouse(m_pPage, true);
						if (m_pPage->m_pCanvas)
							m_pPage->m_pCanvas->setValid(false);
						m_pPage->Repaint(false);
					}
					break;
				case CPageControl::Element::Tab:
					if (m_pPage->m_iHoveredTab != m_pPage->m_iActiveIndex)
						if (m_pPage->setActiveIndex(m_pPage->m_iHoveredTab) && m_pPage->m_iActiveIndex >= 0 && m_pPage->OnActivateTabSheet)
							m_pPage->OnActivateTabSheet(m_pPage, m_pPage->m_iActiveIndex);
					break;
				default:
					break;
				}
			}
			else
				MouseUp(true);
		}

		void CPageControlService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			MouseUp(true);
		}

		void CPageControlService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CPageControlService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CPageControlService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CPageControlService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CPageControlService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CPageControlService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CPageControlService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(true);
		}

		void CPageControlService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pPage->m_eDownElement == CPageControl::Element::None && !m_pPage->m_bMultiline && ntl::IsGreater<float>(m_pPage->m_fScrollMax, 0))
			{
				PointF p{ m_pPage->FormToLocal(m.Position) };
				RectF header{ m_pPage->getHeaderRect() };
				if (p.X >= header.Left && p.X < header.Right && p.Y >= header.Top && p.Y < header.Bottom)
				{
					int delta{ (m_pPage->m_eHeaderPosition == CPageControl::HeaderPosition::Left ? -1 : 1) * m.Delta };
					float new_scroll{
						delta > 0 ?
						ntl::Max<float>(0, m_pPage->m_fScroll - m_pPage->m_fDeltaScrollWheel) :
						ntl::Min<float>(m_pPage->m_fScrollMax, m_pPage->m_fScroll + m_pPage->m_fDeltaScrollWheel)
					};
					if (ntl::IsNotEqual<float>(new_scroll, m_pPage->m_fScroll))
					{
						m_pPage->m_fScroll = new_scroll;
						m_pPage->UpdateHoveredElement(p);
						if (m_pPage->m_pCanvas)
							m_pPage->m_pCanvas->setValid(false);
						m_pPage->Repaint(false);
					}
				}
			}
		}
	#pragma endregion

	#pragma region Timer notification
		void CPageControlService::NotifyOnTimer(const PlatformHandle id)
		{
			if ((m_pPage->m_eHoveredElement == CPageControl::Element::ScrollStart || m_pPage->m_eHoveredElement == CPageControl::Element::ScrollEnd) &&
				(m_pPage->m_eDownElement == CPageControl::Element::ScrollStart || m_pPage->m_eDownElement == CPageControl::Element::ScrollEnd))
			{
				float new_scroll{ m_pPage->m_fScroll };
				switch (m_pPage->m_eDownElement)
				{
				case CPageControl::Element::ScrollStart:
					new_scroll = ntl::Max<float>(0, m_pPage->m_fScroll - m_pPage->m_fDeltaScrollTimer);
					break;
				case CPageControl::Element::ScrollEnd:
					new_scroll = ntl::Min<float>(m_pPage->m_fScrollMax, m_pPage->m_fScroll + m_pPage->m_fDeltaScrollTimer);
					break;
				default:
					break;
				}
				if (ntl::IsNotEqual<float>(new_scroll, m_pPage->m_fScroll))
				{
					m_pPage->m_fScroll = new_scroll;
					if (m_pPage->m_pCanvas)
						m_pPage->m_pCanvas->setValid(false);
					m_pPage->Repaint(false);
				}
			}
		}
	#pragma endregion

	#pragma region TabSheet notifications
		void CPageControlService::NotifyOnTabSheetChanged(ITabSheet *tab)
		{
			// Caption or icon index was changed. Canvas invalidation and repaint will be called by sender
			UpdateActiveIndex();
			m_pPage->Update();
			AlignControls();
			if (m_pPage->m_pCanvas)
				m_pPage->m_pCanvas->setValid(false);
			if (m_pPage->m_pMask && ntl::IsLessOrEqual<float>(m_pPage->m_sHeaderSize.Y, 0))
				m_pPage->m_pMask->setValid(false);
			m_pPage->Repaint(false);
		}
	#pragma endregion
	}
}