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
		CCustomTreeViewService::CCustomTreeViewService(CCustomTreeView *treeview) :
			CControlService(treeview),
			m_pTreeView{ treeview },
			m_hTimer{ nullptr },
			m_bMoving{ false }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CCustomTreeViewService::CancelDown(const bool check_capture)
		{
			m_pTreeView->m_eDownElement = CCustomTreeView::Element::None;
			if (m_hTimer)
			{
				m_pTreeView->getForm()->DeleteTimer(m_hTimer);
				m_hTimer = nullptr;
			}
			if (check_capture && m_pTreeView->isCaptureMouse())
				m_pTreeView->getForm()->ReleaseCaptureMouse();
		}

		PointF CCustomTreeViewService::FormToHScroll(const PointF &pos)
		{
			PointF p{ m_pTreeView->FormToLocal(pos) };
			return PointF{ p.X - m_pTreeView->m_sBorderWidth.Left, p.Y - (m_pTreeView->getHeight() - m_pTreeView->m_sBorderWidth.Bottom - m_pTreeView->getHScroll()->getHeight()) };
		}

		PointF CCustomTreeViewService::FormToVScroll(const PointF &pos)
		{
			PointF p{ m_pTreeView->FormToLocal(pos) };
			return PointF{ p.X - (m_pTreeView->getWidth() - m_pTreeView->m_sBorderWidth.Right - m_pTreeView->getVScroll()->getWidth()), p.Y - m_pTreeView->m_sBorderWidth.Top };
		}

		bool CCustomTreeViewService::FindActiveItem(IListItem *parent, PointF &current, PointF &item_size, const float line_height)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible())
				{
					PointF size{ parent->getItem(i)->QueryService()->getRequiredSize() };
					float height{ ntl::IsGreater<float>(m_pTreeView->m_fItemHeight, 0) ? m_pTreeView->m_fItemHeight : (ntl::IsEqual<float>(m_pTreeView->m_fItemHeight, 0) ? line_height : size.Y) };
					if (parent->getItem(i)->isActive())
					{
						item_size = PointF{ size.X, height };
						return true;
					}
					
					current.Y += height;
					if (parent->getItem(i)->getItemCount() > 0 && !m_pTreeView->m_aItems[m_pTreeView->FindItemIndex(parent->getItem(i))].Folded)
					{
						current.X += height;
						bool b{ FindActiveItem(parent->getItem(i), current, item_size, line_height) };
						if (b)
							return true;
						current.X -= height;
					}
				}
			return false;
		}

		void CCustomTreeViewService::ScrollToActiveItem()
		{
			PointF current{
				m_pTreeView->m_sBorderWidth.Left + m_pTreeView->m_sPadding.Left - (m_pTreeView->getHScroll()->isEnabled() ? m_pTreeView->getHScroll()->getScroll() : 0),
				m_pTreeView->m_sBorderWidth.Top + m_pTreeView->m_sPadding.Top - (m_pTreeView->getVScroll()->isEnabled() ? m_pTreeView->getVScroll()->getScroll() : 0)
			}, size;
			if (FindActiveItem(&m_pTreeView->m_cRootItem, current, size, m_pTreeView->getFont()->getPlatformFont(m_pTreeView->getForm()->getRenderer())->getStringSize(L"Wy", m_pTreeView->getFont()->Distance).Y))
			{
				RectF client{ m_pTreeView->getClientRect() };
				if (current.X + size.X >= client.Right)
					m_pTreeView->getHScroll()->setScroll(m_pTreeView->getHScroll()->getScroll() + (current.X + size.X - client.Right));
				if (current.X < client.Left)
					m_pTreeView->getHScroll()->setScroll(m_pTreeView->getHScroll()->getScroll() - (client.Left - current.X));

				if (current.Y + size.Y >= client.Bottom)
					m_pTreeView->getVScroll()->setScroll(m_pTreeView->getVScroll()->getScroll() + (current.Y + size.Y - client.Bottom));
				if (current.Y < client.Top)
					m_pTreeView->getVScroll()->setScroll(m_pTreeView->getVScroll()->getScroll() - (client.Top - current.Y));
			}
		}

		IListItem *CCustomTreeViewService::FindActiveItem(IListItem *parent)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible())
				{
					if (parent->getItem(i)->isActive())
						return parent->getItem(i);
					IListItem *result{ FindActiveItem(parent->getItem(i)) };
					if (result)
						return result;
				}
			return nullptr;
		}
	#pragma endregion

	#pragma region State change notifications
		void CCustomTreeViewService::NotifyOnAttach()
		{
			if (m_pTreeView->m_pVScroll)
				m_pTreeView->m_pVScroll->NotifyOnAttach();
			if (m_pTreeView->m_pHScroll)
				m_pTreeView->m_pHScroll->NotifyOnAttach();
			m_pTreeView->Update();
			if (m_pTreeView->m_pCanvas)
				m_pTreeView->m_pCanvas->setValid(false);
		}

		void CCustomTreeViewService::NotifyOnDetaching()
		{
			if (m_pTreeView->m_pVScroll)
				m_pTreeView->m_pVScroll->NotifyOnDeactivate();
			if (m_pTreeView->m_pHScroll)
				m_pTreeView->m_pHScroll->NotifyOnDeactivate();
		}

		void CCustomTreeViewService::NotifyOnFreeResources()
		{
			if (m_pTreeView->m_pCanvas)
			{
				m_pTreeView->m_pCanvas->Release();
				m_pTreeView->m_pCanvas = nullptr;
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CCustomTreeViewService::NotifyOnParentStyleChange()
		{
			if (m_pTreeView->getStyle())
			{
				m_pTreeView->UpdateFromStyle(m_pTreeView->getStyle());
				if (m_pTreeView->m_pCanvas)
					m_pTreeView->m_pCanvas->setValid(false);
			}
		}

		void CCustomTreeViewService::NotifyOnParentFontChange()
		{
			m_pTreeView->Update();
			m_pTreeView->UpdateHoveredElement();
			if (m_pTreeView->m_pCanvas)
				m_pTreeView->m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CCustomTreeViewService::NotifyOnEnable()
		{
			m_pTreeView->getHScroll()->setEnabled(true);
			m_pTreeView->getVScroll()->setEnabled(true);
			m_pTreeView->Update();
			m_pTreeView->UpdateHoveredElement();
			if (m_pTreeView->m_pCanvas)
				m_pTreeView->m_pCanvas->setValid(false);
		}

		void CCustomTreeViewService::NotifyOnDisable()
		{
			m_pTreeView->getHScroll()->setEnabled(false);
			m_pTreeView->getVScroll()->setEnabled(false);
			m_pTreeView->UpdateHoveredElement();
			if (m_pTreeView->m_pCanvas)
				m_pTreeView->m_pCanvas->setValid(false);
		}

		void CCustomTreeViewService::NotifyOnResize()
		{
			m_pTreeView->Update();
			m_pTreeView->UpdateHoveredElement();
			if (m_pTreeView->m_pCanvas)
				m_pTreeView->m_pCanvas->setValid(false);
		}

		void CCustomTreeViewService::NotifyOnStyleChange()
		{
			if (m_pTreeView->getStyle())
			{
				m_pTreeView->UpdateFromStyle(m_pTreeView->getStyle());
				if (m_pTreeView->m_pCanvas)
					m_pTreeView->m_pCanvas->setValid(false);
			}
		}

		void CCustomTreeViewService::NotifyOnFontChange()
		{
			m_pTreeView->Update();
			m_pTreeView->UpdateHoveredElement();
			if (m_pTreeView->m_pCanvas)
				m_pTreeView->m_pCanvas->setValid(false);
		}

		void CCustomTreeViewService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pTreeView->m_pCanvas)
				m_pTreeView->m_pCanvas->setValid(false);
			m_pTreeView->Repaint(false);
		}

		void CCustomTreeViewService::NotifyOnKillFocus()
		{
			if (m_pTreeView->m_pCanvas)
				m_pTreeView->m_pCanvas->setValid(false);
			m_pTreeView->Repaint(false);
		}

		void CCustomTreeViewService::NotifyOnSetCaptureMouse()
		{
			m_hTimer = m_pTreeView->getForm()->CreateTimer(this, m_pTreeView->m_fScrollInterval);
		}

		void CCustomTreeViewService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CCustomTreeViewService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pTreeView->getWidth(), 0) && ntl::IsGreater<float>(m_pTreeView->getHeight(), 0))
				m_pTreeView->Render();
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CCustomTreeViewService::NotifyOnMouseHover(const MessagePosition &m)
		{
			m_pTreeView->UpdateHoveredElement(m_pTreeView->FormToLocal(m.Position));
			if (m_pTreeView->m_pCanvas)
				m_pTreeView->m_pCanvas->setValid(false);
			m_pTreeView->Repaint(false);
		}

		void CCustomTreeViewService::NotifyOnMouseLeave()
		{
			m_pTreeView->UpdateHoveredElement();
			if (m_pTreeView->m_pCanvas)
				m_pTreeView->m_pCanvas->setValid(false);
			m_pTreeView->Repaint(false);
		}

		void CCustomTreeViewService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			switch (m_pTreeView->m_eDownElement)
			{
			case CCustomTreeView::Element::HScroll:
				if (m_pTreeView->getHScroll()->NotifyOnMouseMove(FormToHScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pTreeView->m_pCanvas)
						m_pTreeView->m_pCanvas->setValid(false);
					m_pTreeView->Repaint(false);
				}
				return;
			case CCustomTreeView::Element::VScroll:
				if (m_pTreeView->getVScroll()->NotifyOnMouseMove(FormToVScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					if (m_pTreeView->m_pCanvas)
						m_pTreeView->m_pCanvas->setValid(false);
					m_pTreeView->Repaint(false);
				}
				return;
			default:
				break;
			}
			if (m_pTreeView->isEnabled(true))
			{
				PointF p{ m_pTreeView->FormToLocal(m.Position) };
				IListItem *hovered_was{ m_pTreeView->m_eHoveredElement == CCustomTreeView::Element::Item ? m_pTreeView->m_pHoveredItem : nullptr };
				bool changed{ m_pTreeView->UpdateHoveredElement(p) };
				if (changed && m_pTreeView->isCaptureMouse())
				{
					IListItem *hovered_new{ m_pTreeView->m_eHoveredElement == CCustomTreeView::Element::Item ? m_pTreeView->m_pHoveredItem : nullptr };
					m_bMoving = true;
					if (hovered_new != hovered_was && m_pTreeView->OnMovingSelection)
						m_pTreeView->OnMovingSelection(m_pTreeView, hovered_new);
				}
				else
				{
					switch (m_pTreeView->m_eHoveredElement)
					{
					case CCustomTreeView::Element::HScroll:
						if (m_pTreeView->getHScroll()->NotifyOnMouseMove(FormToHScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
						{
							if (m_pTreeView->m_pCanvas)
								m_pTreeView->m_pCanvas->setValid(false);
							m_pTreeView->Repaint(false);
						}
						break;
					case CCustomTreeView::Element::VScroll:
						if (m_pTreeView->getVScroll()->NotifyOnMouseMove(FormToVScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
						{
							if (m_pTreeView->m_pCanvas)
								m_pTreeView->m_pCanvas->setValid(false);
							m_pTreeView->Repaint(false);
						}
						break;
					default:
						break;
					}
				}
				if (changed)
				{
					if (m_pTreeView->m_pCanvas)
						m_pTreeView->m_pCanvas->setValid(false);
					m_pTreeView->Repaint(false);
				}
			}
		}

		void CCustomTreeViewService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			m_pTreeView->m_eDownElement = CCustomTreeView::Element::None;
			if (m_pTreeView->isEnabled(true))
			{
				if (!m_pTreeView->isCaptureMouse() && !m.Middle && !m.Right)
				{
					switch (m_pTreeView->m_eHoveredElement)
					{
					case CCustomTreeView::Element::Folder:
					{
						int index{ m_pTreeView->FindItemIndex(m_pTreeView->m_pHoveredItem) };
						m_pTreeView->m_aItems[index].Folded = !m_pTreeView->m_aItems[index].Folded;
						m_pTreeView->Update();
						m_pTreeView->UpdateHoveredElement(m.Position);
						if (m_pTreeView->m_pCanvas)
							m_pTreeView->m_pCanvas->setValid(false);
						m_pTreeView->Repaint(false);
					}
					break;
					case CCustomTreeView::Element::HScroll:
						if (m_pTreeView->getHScroll()->NotifyOnMouseLeftDown(FormToHScroll(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
						{
							m_pTreeView->m_eDownElement = CCustomTreeView::Element::HScroll;
							m_pTreeView->getForm()->CaptureMouse(m_pTreeView, true);
							if (m_pTreeView->m_pCanvas)
								m_pTreeView->m_pCanvas->setValid(false);
							m_pTreeView->Repaint(false);
						}
						break;
					case CCustomTreeView::Element::VScroll:
						if (m_pTreeView->getVScroll()->NotifyOnMouseLeftDown(FormToVScroll(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
						{
							m_pTreeView->m_eDownElement = CCustomTreeView::Element::VScroll;
							m_pTreeView->getForm()->CaptureMouse(m_pTreeView, true);
							if (m_pTreeView->m_pCanvas)
								m_pTreeView->m_pCanvas->setValid(false);
							m_pTreeView->Repaint(false);
						}
						break;
					case CCustomTreeView::Element::Item:
						if (m.Shift)
						{
							IListItem *active{ m_pTreeView->getActiveItem() };
							if (active && m_pTreeView->m_pHoveredItem->getParent() == active->getParent())
							{
								int active_index{ -1 }, hovered_index{ -1 };
								for (int i = 0; i < active->getParent()->getItemCount(); i++)
								{
									if (active->getParent()->getItem(i) == active)
									{
										active_index = i;
										if (hovered_index >= 0)
											break;
									}
									if (active->getParent()->getItem(i) == m_pTreeView->m_pHoveredItem)
									{
										hovered_index = i;
										if (active_index >= 0)
											break;
									}
								}
								bool changed{ m_pTreeView->DeselectAllExceptParent(active->getParent()) };
								if (active_index > hovered_index)
									ntl::Swap<int>(active_index, hovered_index);
								for (int i = 0; i < active->getParent()->getItemCount(); i++)
								{
									if ((i < active_index || i > hovered_index) && active->getParent()->getItem(i)->isSelected())
										changed = active->getParent()->getItem(i)->setSelected(false) || changed;
									if (i >= active_index && i <= hovered_index && !active->getParent()->getItem(i)->isSelected())
										changed = active->getParent()->getItem(i)->setSelected(true) || changed;
								}
								if (changed)
								{
									if (m_pTreeView->m_pCanvas)
										m_pTreeView->m_pCanvas->setValid(false);
									m_pTreeView->Repaint(false);
								}
							}
						}
						else
						{
							bool changed;
							if (m.Ctrl)
								changed = m_pTreeView->m_pHoveredItem->setSelected(!m_pTreeView->m_pHoveredItem->isSelected());
							else
								changed = m_pTreeView->m_pHoveredItem->setSelected(true);
							if (m_pTreeView->m_pHoveredItem->isSelected())
							{
								m_pTreeView->getForm()->CaptureMouse(m_pTreeView, true);
								m_bMoving = false;
							}
							if (m_pTreeView->m_pHoveredItem->setActive(true))
							{
								m_pTreeView->DeactivateAllExceptItem(&m_pTreeView->m_cRootItem, m_pTreeView->m_pHoveredItem);
								changed = true;
							}
							if (changed)
							{
								if (m_pTreeView->m_pCanvas)
									m_pTreeView->m_pCanvas->setValid(false);
								m_pTreeView->Repaint(false);
							}
						}
						break;
					default:
						break;
					}
				}
				else
					CancelDown(true);
			}
		}

		void CCustomTreeViewService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pTreeView->isCaptureMouse())
			{
				switch (m_pTreeView->m_eDownElement)
				{
				case CCustomTreeView::Element::HScroll:
					if (m_pTreeView->getHScroll()->NotifyOnMouseLeftUp(FormToHScroll(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						if (m_pTreeView->m_pCanvas)
							m_pTreeView->m_pCanvas->setValid(false);
						m_pTreeView->Repaint(false);
					}
					break;
				case CCustomTreeView::Element::VScroll:
					if (m_pTreeView->getVScroll()->NotifyOnMouseLeftUp(FormToVScroll(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						if (m_pTreeView->m_pCanvas)
							m_pTreeView->m_pCanvas->setValid(false);
						m_pTreeView->Repaint(false);
					}
					break;
				default:
					if (m_bMoving)
					{
						if (m_pTreeView->OnMoveSelection)
							m_pTreeView->OnMoveSelection(m_pTreeView, m_pTreeView->m_eHoveredElement == CCustomTreeView::Element::Item ? m_pTreeView->m_pHoveredItem : nullptr);
					}
					else if (!m.Ctrl && m_pTreeView->DeselectAllExceptItem(&m_pTreeView->m_cRootItem, m_pTreeView->m_pHoveredItem))
					{
						if (m_pTreeView->m_pCanvas)
							m_pTreeView->m_pCanvas->setValid(false);
						m_pTreeView->Repaint(false);
					}
				}
			}
			CancelDown(true);
		}

		void CCustomTreeViewService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CCustomTreeViewService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CCustomTreeViewService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CCustomTreeViewService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CCustomTreeViewService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CCustomTreeViewService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CCustomTreeViewService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CCustomTreeViewService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pTreeView->isEnabled(true) && !m_pTreeView->isCaptureMouse())
				switch (m_pTreeView->m_eHoveredElement)
				{
				case CCustomTreeView::Element::VScroll:
					if (m_pTreeView->getVScroll()->isEnabled() && m_pTreeView->getVScroll()->NotifyOnMouseVerticalWheel(FormToVScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
					{
						m_pTreeView->UpdateHoveredElement(m_pTreeView->FormToLocal(m.Position));
						if (m_pTreeView->m_pCanvas)
							m_pTreeView->m_pCanvas->setValid(false);
						m_pTreeView->Repaint(false);
					}
					break;
				case CCustomTreeView::Element::HScroll:
					if (m_pTreeView->getHScroll()->isEnabled() && m_pTreeView->getHScroll()->NotifyOnMouseVerticalWheel(FormToHScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
					{
						m_pTreeView->UpdateHoveredElement(m_pTreeView->FormToLocal(m.Position));
						if (m_pTreeView->m_pCanvas)
							m_pTreeView->m_pCanvas->setValid(false);
						m_pTreeView->Repaint(false);
					}
					break;
				default:
					if (m_pTreeView->getVScroll()->isEnabled() && m_pTreeView->getVScroll()->setScroll(m_pTreeView->getVScroll()->getScroll() + m_pTreeView->getVScroll()->getDeltaMedium() * (m.Delta > 0 ? -1 : 1)))
					{
						m_pTreeView->UpdateHoveredElement(m_pTreeView->FormToLocal(m.Position));
						if (m_pTreeView->m_pCanvas)
							m_pTreeView->m_pCanvas->setValid(false);
						m_pTreeView->Repaint(false);
					}
				}
		}

		void CCustomTreeViewService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pTreeView->isEnabled(true) && !m_pTreeView->isCaptureMouse())
				switch (m_pTreeView->m_eHoveredElement)
				{
				case CCustomTreeView::Element::VScroll:
					if (m_pTreeView->getVScroll()->isEnabled() && m_pTreeView->getVScroll()->NotifyOnMouseHorizontalWheel(FormToVScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
					{
						m_pTreeView->UpdateHoveredElement(m_pTreeView->FormToLocal(m.Position));
						if (m_pTreeView->m_pCanvas)
							m_pTreeView->m_pCanvas->setValid(false);
						m_pTreeView->Repaint(false);
					}
					break;
				case CCustomTreeView::Element::HScroll:
					if (m_pTreeView->getHScroll()->isEnabled() && m_pTreeView->getHScroll()->NotifyOnMouseHorizontalWheel(FormToHScroll(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
					{
						m_pTreeView->UpdateHoveredElement(m_pTreeView->FormToLocal(m.Position));
						if (m_pTreeView->m_pCanvas)
							m_pTreeView->m_pCanvas->setValid(false);
						m_pTreeView->Repaint(false);
					}
					break;
				default:
					if (m_pTreeView->getHScroll()->isEnabled() && m_pTreeView->getHScroll()->setScroll(m_pTreeView->getHScroll()->getScroll() + m_pTreeView->getHScroll()->getDeltaMedium() * (m.Delta > 0 ? -1 : 1)))
					{
						m_pTreeView->UpdateHoveredElement(m_pTreeView->FormToLocal(m.Position));
						if (m_pTreeView->m_pCanvas)
							m_pTreeView->m_pCanvas->setValid(false);
						m_pTreeView->Repaint(false);
					}
				}
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CCustomTreeViewService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m_pTreeView->isEnabled(true))
			{
				bool numlock{ Application->Keyboard->isToggled(Key::NumLock) }, changed{ false };
				switch (m.Key)
				{
				case Key::Up:
				case Key::Numpad8:
					if (m.Key == Key::Up || !numlock)
						changed = ProcessKeyUp();
					break;
				case Key::Down:
				case Key::Numpad2:
					if (m.Key == Key::Down || !numlock)
						changed = ProcessKeyDown();
					break;
				case Key::Left:
				case Key::Numpad4:
					if (m.Key == Key::Left || !numlock)
						changed = ProcessKeyLeft();
					break;
				case Key::Right:
				case Key::Numpad6:
					if (m.Key == Key::Right || !numlock)
						changed = ProcessKeyRight();
					break;
				case Key::Home:
				case Key::Numpad7:
					if (m.Key == Key::Home || !numlock)
						changed = ProcessKeyHome();
					break;
				case Key::End:
				case Key::Numpad1:
					if (m.Key == Key::End || !numlock)
						changed = ProcessKeyEnd();
					break;
				default:
					break;
				}
				if (changed)
				{
					ScrollToActiveItem();
					m_pTreeView->UpdateHoveredElement();
					if (m_pTreeView->m_pCanvas)
						m_pTreeView->m_pCanvas->setValid(false);
					m_pTreeView->Repaint(false);
				}
			}
		}
	#pragma endregion

	#pragma region Process keys
		bool CCustomTreeViewService::ProcessKeyUp()
		{
			IListItem *active{ FindActiveItem(&m_pTreeView->m_cRootItem) };
			if (active)
			{
				int active_index{ -1 };
				for (int i = 0; i < active->getParent()->getItemCount(); i++)
					if (active->getParent()->getItem(i) == active)
					{
						active_index = i;
						break;
					}
				active_index--;
				while (active_index >= 0 && !active->getParent()->getItem(active_index)->isVisible())
					active_index--;
				if (active_index >= 0)
				{
					active->getParent()->getItem(active_index)->setActive(true);
					active->getParent()->getItem(active_index)->setSelected(true);
					m_pTreeView->DeselectAllExceptItem(&m_pTreeView->m_cRootItem, active->getParent()->getItem(active_index));
					return true;
				}
			}
			else if (m_pTreeView->m_cRootItem.getItemCount() > 0)
			{
				int active_index{ m_pTreeView->m_cRootItem.getItemCount() - 1 };
				while (active_index >= 0 && !m_pTreeView->m_cRootItem.getItem(active_index)->isVisible())
					active_index--;
				if (active_index >= 0)
				{
					m_pTreeView->m_cRootItem.getItem(active_index)->setActive(true);
					m_pTreeView->m_cRootItem.getItem(active_index)->setSelected(true);
					return true;
				}
			}
			return false;
		}

		bool CCustomTreeViewService::ProcessKeyDown()
		{
			IListItem *active{ FindActiveItem(&m_pTreeView->m_cRootItem) };
			if (active)
			{
				int active_index{ -1 };
				for (int i = 0; i < active->getParent()->getItemCount(); i++)
					if (active->getParent()->getItem(i) == active)
					{
						active_index = i;
						break;
					}
				active_index++;
				while (active_index < active->getParent()->getItemCount() && !active->getParent()->getItem(active_index)->isVisible())
					active_index++;
				if (active_index < active->getParent()->getItemCount())
				{
					active->getParent()->getItem(active_index)->setActive(true);
					active->getParent()->getItem(active_index)->setSelected(true);
					m_pTreeView->DeselectAllExceptItem(&m_pTreeView->m_cRootItem, active->getParent()->getItem(active_index));
					return true;
				}
			}
			else if (m_pTreeView->m_cRootItem.getItemCount() > 0)
			{
				int active_index{ 0 };
				while (active_index < m_pTreeView->m_cRootItem.getItemCount() && !m_pTreeView->m_cRootItem.getItem(active_index)->isVisible())
					active_index++;
				if (active_index < m_pTreeView->m_cRootItem.getItemCount())
				{
					m_pTreeView->m_cRootItem.getItem(active_index)->setActive(true);
					m_pTreeView->m_cRootItem.getItem(active_index)->setSelected(true);
					return true;
				}
			}
			return false;
		}

		bool CCustomTreeViewService::ProcessKeyLeft()
		{
			IListItem *active{ FindActiveItem(&m_pTreeView->m_cRootItem) };
			if (active)
			{
				if (active->getParent() != &m_pTreeView->m_cRootItem)
				{
					active->getParent()->setActive(true);
					active->getParent()->setSelected(true);
					m_pTreeView->DeselectAllExceptItem(&m_pTreeView->m_cRootItem, active->getParent());
					return true;
				}
			}
			else if (m_pTreeView->m_cRootItem.getItemCount() > 0)
			{
				int active_index{ 0 };
				while (active_index < m_pTreeView->m_cRootItem.getItemCount() && !m_pTreeView->m_cRootItem.getItem(active_index)->isVisible())
					active_index++;
				if (active_index < m_pTreeView->m_cRootItem.getItemCount())
				{
					m_pTreeView->m_cRootItem.getItem(active_index)->setActive(true);
					m_pTreeView->m_cRootItem.getItem(active_index)->setSelected(true);
					return true;
				}
			}
			return false;
		}

		bool CCustomTreeViewService::ProcessKeyRight()
		{
			IListItem *active{ FindActiveItem(&m_pTreeView->m_cRootItem) };
			if (active)
			{
				if (active->getItemCount() > 0)
				{
					int active_index{ 0 };
					while (active_index < active->getItemCount() && !active->getItem(active_index)->isVisible())
						active_index++;
					if (active_index < active->getItemCount())
					{
						active->getItem(active_index)->setActive(true);
						active->getItem(active_index)->setSelected(true);
						m_pTreeView->DeselectAllExceptItem(&m_pTreeView->m_cRootItem, active->getItem(active_index));
						int index{ m_pTreeView->FindItemIndex(active) };
						if (m_pTreeView->m_aItems[index].Folded)
						{
							m_pTreeView->m_aItems[index].Folded = false;
							m_pTreeView->Update();
						}
						return true;
					}
				}
			}
			else if (m_pTreeView->m_cRootItem.getItemCount() > 0)
			{
				int active_index{ 0 };
				while (active_index < m_pTreeView->m_cRootItem.getItemCount() && !m_pTreeView->m_cRootItem.getItem(active_index)->isVisible())
					active_index++;
				if (active_index < m_pTreeView->m_cRootItem.getItemCount())
				{
					m_pTreeView->m_cRootItem.getItem(active_index)->setActive(true);
					m_pTreeView->m_cRootItem.getItem(active_index)->setSelected(true);
					return true;
				}
			}
			return false;
		}

		bool CCustomTreeViewService::ProcessKeyHome()
		{
			IListItem *active{ FindActiveItem(&m_pTreeView->m_cRootItem) };
			if (active)
			{
				int active_index{ 0 };
				while (active_index < active->getParent()->getItemCount() && !active->getParent()->getItem(active_index)->isVisible())
					active_index++;
				if (active_index < active->getParent()->getItemCount() && active->getParent()->getItem(active_index) != active)
				{
					active->getParent()->getItem(active_index)->setActive(true);
					active->getParent()->getItem(active_index)->setSelected(true);
					m_pTreeView->DeselectAllExceptItem(&m_pTreeView->m_cRootItem, active->getParent()->getItem(active_index));
					return true;
				}
			}
			else if (m_pTreeView->m_cRootItem.getItemCount() > 0)
			{
				int active_index{ 0 };
				while (active_index < m_pTreeView->m_cRootItem.getItemCount() && !m_pTreeView->m_cRootItem.getItem(active_index)->isVisible())
					active_index++;
				if (active_index < m_pTreeView->m_cRootItem.getItemCount())
				{
					m_pTreeView->m_cRootItem.getItem(active_index)->setActive(true);
					m_pTreeView->m_cRootItem.getItem(active_index)->setSelected(true);
					return true;
				}
			}
			return false;
		}

		bool CCustomTreeViewService::ProcessKeyEnd()
		{
			IListItem *active{ FindActiveItem(&m_pTreeView->m_cRootItem) };
			if (active)
			{
				int active_index{ active->getParent()->getItemCount() - 1 };
				while (active_index >= 0 && !active->getParent()->getItem(active_index)->isVisible())
					active_index--;
				if (active_index >= 0 && active->getParent()->getItem(active_index) != active)
				{
					active->getParent()->getItem(active_index)->setActive(true);
					active->getParent()->getItem(active_index)->setSelected(true);
					m_pTreeView->DeselectAllExceptItem(&m_pTreeView->m_cRootItem, active->getParent()->getItem(active_index));
					return true;
				}
			}
			else if (m_pTreeView->m_cRootItem.getItemCount() > 0)
			{
				int active_index{ m_pTreeView->m_cRootItem.getItemCount() - 1 };
				while (active_index >= 0 && !m_pTreeView->m_cRootItem.getItem(active_index)->isVisible())
					active_index--;
				if (active_index >= 0)
				{
					m_pTreeView->m_cRootItem.getItem(active_index)->setActive(true);
					m_pTreeView->m_cRootItem.getItem(active_index)->setSelected(true);
					return true;
				}
			}
			return false;
		}
	#pragma endregion

	#pragma region Timer notification
		void CCustomTreeViewService::NotifyOnTimer(const PlatformHandle id)
		{
			if (m_pTreeView->m_eDownElement != CCustomTreeView::Element::HScroll && m_pTreeView->m_eDownElement != CCustomTreeView::Element::VScroll)
			{
				PointF p{ m_pTreeView->FormToLocal((PointF)m_pTreeView->getForm()->ScreenToClient(Application->Mouse->getPosition())) };
				RectF client{ m_pTreeView->getClientRect() };
				float delta;
				bool changed{ false };
				if (p.X < client.Left || p.X >= client.Right)
				{
					if (m_pTreeView->getHScroll()->isEnabled())
					{
						delta = m_pTreeView->m_fScrollDelta * (p.X < client.Left ? -1 : 1);
						changed = m_pTreeView->getHScroll()->setScroll(m_pTreeView->getHScroll()->getScroll() + delta) || changed;
					}
				}
				if (p.Y < client.Top || p.Y >= client.Bottom)
				{
					if (m_pTreeView->getVScroll()->isEnabled())
					{
						delta = m_pTreeView->m_fScrollDelta * (p.Y < client.Top ? -1 : 1);
						changed = m_pTreeView->getVScroll()->setScroll(m_pTreeView->getVScroll()->getScroll() + delta) || changed;
					}
				}
				if (changed)
				{
					m_pTreeView->UpdateHoveredElement(p);
					if (m_pTreeView->m_pCanvas)
						m_pTreeView->m_pCanvas->setValid(false);
					m_pTreeView->Repaint(false);
				}
			}
		}
	#pragma endregion
	}
}