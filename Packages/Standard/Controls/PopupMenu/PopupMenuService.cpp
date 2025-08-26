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
		CPopupMenuService::CPopupMenuService(CPopupMenu *menu) :
			CControlService(menu),
			m_pMenu{ menu },
			m_bIgnoreKeyUp{ false },
			m_bIgnoreMouseUp{ false }
		{

		}
	#pragma endregion

	#pragma region Helpers
		IListItemMenu *CPopupMenuService::FindHotkeyOwner(IListItem *parent)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible())
				{
					IListItemMenu *itemmenu{ cast<IListItemMenu*>(parent->getItem(i)) };
					if (itemmenu && itemmenu->getHotkeyCount() == (int)m_pMenu->m_aLastHotkeys.size())
					{
						bool match{ true };
						for (int j = 0; j < itemmenu->getHotkeyCount(); j++)
							if (itemmenu->getHotkey(j).Key != m_pMenu->m_aLastHotkeys[j].Key ||
								itemmenu->getHotkey(j).Ctrl != m_pMenu->m_aLastHotkeys[j].Ctrl ||
								itemmenu->getHotkey(j).Alt != m_pMenu->m_aLastHotkeys[j].Alt ||
								itemmenu->getHotkey(j).Shift != m_pMenu->m_aLastHotkeys[j].Shift ||
								itemmenu->getHotkey(j).Down != m_pMenu->m_aLastHotkeys[j].Down)
							{
								match = false;
								break;
							}
						if (match)
							return itemmenu;
					}
					IListItemMenu *item{ FindHotkeyOwner(parent->getItem(i)) };
					if (item)
						return item;
				}
			return nullptr;
		}

		void CPopupMenuService::CloseSubmenu(IListItem *parent, const bool deactivate_parent)
		{
			// Close submenu
			int index{ m_pMenu->FindItemIndex(parent) };
			if (index > 0 && m_pMenu->m_aItems[index].Opended)
			{
				m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(index), false);
				m_pMenu->m_aItems[index].Opended = false;
			}
			// Deactivate and dehover item
			if (deactivate_parent)
			{
				parent->setActive(false);
				parent->QueryService()->setHovered(false);
			}
			// Close submenus
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible())
					CloseSubmenu(parent->getItem(i), true);
		}

		void CPopupMenuService::MouseDown(const MessageMouse &m)
		{
			m_pMenu->MouseDownCancel();
			if (m_pMenu->m_bHoverTopScroller || m_pMenu->m_bHoverBottomScroller)
				return;
			if (!m_pMenu->m_pHoveredItem)
			{
				IListItem *i;
				if (!FindSubmenu(&m_pMenu->m_cRootItem, m.Position, &i))
					m_pMenu->Hide();
				return;
			}
			if (!m_pMenu->m_pHoveredItem->isEnabled())
				return;
			if (m_pMenu->m_pHoveredItem->getItemCount() > 0)
			{
				int index{ m_pMenu->FindItemIndex(m_pMenu->m_pHoveredItem) };
				if (!m_pMenu->m_aItems[index].Opended)
				{
					m_pMenu->m_aItems[index].Opended = true;
					m_pMenu->UpdateSubmenuPosition(m_pMenu->m_pHoveredItem);
					m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(index), false);
				}
				return;
			}
			int parent_index{ m_pMenu->FindItemIndex(m_pMenu->m_pHoveredItem->getParent()) };
			PointF position{
				m.Position.X - m_pMenu->m_aItems[parent_index].Position.X,
				m.Position.Y - m_pMenu->m_aItems[parent_index].Position.Y - m_pMenu->m_aItems[parent_index].Scroll };
			m_pMenu->m_pDownItem = m_pMenu->m_pHoveredItem;
			if (m_pMenu->m_pHoveredItem->QueryService()->NotifyOnMouseDown(position, m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				m_pMenu->Hide();
				m_bIgnoreMouseUp = true;
			}
		}

		void CPopupMenuService::MouseUp(const MessageMouse &m)
		{
			if (!m_pMenu->m_pDownItem)
				return;
			if (m_pMenu->m_pHoveredItem != m_pMenu->m_pDownItem || m_pMenu->m_bHoverTopScroller || m_pMenu->m_bHoverBottomScroller)
			{
				m_pMenu->MouseDownCancel();
				return;
			}
			int parent_index{ m_pMenu->FindItemIndex(m_pMenu->m_pHoveredItem->getParent()) };
			PointF position{
				m.Position.X - m_pMenu->m_aItems[parent_index].Position.X,
				m.Position.Y - m_pMenu->m_aItems[parent_index].Position.Y - m_pMenu->m_aItems[parent_index].Scroll };
			m_pMenu->m_pDownItem = nullptr;
			if (m_pMenu->m_pHoveredItem->QueryService()->NotifyOnMouseUp(position, m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pMenu->Hide();
		}

		bool CPopupMenuService::FindSubmenu(IListItem *parent, const PointF &position, IListItem **item)
		{
			*item = nullptr;
			int parent_index{ m_pMenu->FindItemIndex(parent) };
			if (position.X >= m_pMenu->m_aItems[parent_index].Position.X && position.X < m_pMenu->m_aItems[parent_index].Position.X + m_pMenu->m_aItems[parent_index].Size.X &&
				position.Y >= m_pMenu->m_aItems[parent_index].Position.Y && position.Y < m_pMenu->m_aItems[parent_index].Position.Y + m_pMenu->m_aItems[parent_index].Size.Y)
			{
				*item = parent;
				return true;
			}
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				int index{ m_pMenu->FindItemIndex(parent->getItem(i)) };
				if (m_pMenu->m_aItems[index].Opended && FindSubmenu(parent->getItem(i), position, item))
					return true;
			}
			return false;
		}

		IListItem *CPopupMenuService::FindLastSubmenu(IListItem *parent)
		{
			IListItem *result{ parent };
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible() && parent->getItem(i)->getItemCount() > 0 && m_pMenu->m_aItems[m_pMenu->FindItemIndex(parent->getItem(i))].Opended)
				{
					IListItem *item{ FindLastSubmenu(parent->getItem(i)) };
					if (item)
					{
						result = item;
						break;
					}
				}
			return result;
		}

		void CPopupMenuService::ScrollToItem(IListItem *item)
		{
			int parent_index{ m_pMenu->FindItemIndex(item->getParent()) };
			if (ntl::IsGreater<float>(m_pMenu->m_aItems[parent_index].ScrollMax, 0))
			{
				RectF client{ m_pMenu->getClientRect(item->getParent()) };
				if (item->getPosition().Y - m_pMenu->m_aItems[parent_index].Scroll < client.Top)
					m_pMenu->m_aItems[parent_index].Scroll -= client.Top - item->getPosition().Y + m_pMenu->m_aItems[parent_index].Scroll;
				else if (item->getPosition().Y - m_pMenu->m_aItems[parent_index].Scroll + item->getSize().Y >= client.Bottom)
					m_pMenu->m_aItems[parent_index].Scroll += item->getPosition().Y - m_pMenu->m_aItems[parent_index].Scroll + item->getSize().Y - client.Bottom;
			}
		}

		void CPopupMenuService::ProcessKeyUp()
		{
			IListItem *parent{ FindLastSubmenu(&m_pMenu->m_cRootItem) };
			int new_active_index{ parent->getItemCount() - 1 }, active_index{ -1 };
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible() && parent->getItem(i)->isEnabled() && parent->getItem(i)->isActive())
				{
					active_index = i;
					new_active_index = i - 1;
					if (new_active_index < 0)
						new_active_index = parent->getItemCount() - 1;
					break;
				}
			while (new_active_index >= 0 && (!parent->getItem(new_active_index)->isVisible() || !parent->getItem(new_active_index)->isEnabled()))
				new_active_index--;
			if (new_active_index != active_index)
			{
				if (new_active_index >= 0)
				{
					parent->getItem(new_active_index)->setActive(true);
					ScrollToItem(parent->getItem(new_active_index));
					UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
				}
				else if (active_index >= 0)
					parent->getItem(active_index)->setActive(false);
				m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent), false);
			}
		}

		void CPopupMenuService::ProcessKeyDown()
		{
			IListItem *parent{ FindLastSubmenu(&m_pMenu->m_cRootItem) };
			int new_active_index{ 0 }, active_index{ -1 };
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible() && parent->getItem(i)->isEnabled() && parent->getItem(i)->isActive())
				{
					active_index = i;
					new_active_index = i + 1;
					if (new_active_index >= parent->getItemCount())
						new_active_index = 0;
					break;
				}
			while (new_active_index < parent->getItemCount() && (!parent->getItem(new_active_index)->isVisible() || !parent->getItem(new_active_index)->isEnabled()))
				new_active_index++;
			if (new_active_index != active_index)
			{
				if (new_active_index < parent->getItemCount())
				{
					parent->getItem(new_active_index)->setActive(true);
					ScrollToItem(parent->getItem(new_active_index));
					UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
				}
				else if (active_index >= 0)
					parent->getItem(active_index)->setActive(false);
				m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent), false);
			}
		}

		void CPopupMenuService::ProcessKeyLeft()
		{
			IListItem *parent{ FindLastSubmenu(&m_pMenu->m_cRootItem) };
			if (parent != &m_pMenu->m_cRootItem)
			{
				m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent), false);
				CloseSubmenu(parent, false);
				UnhoverItems(parent);
			}
		}

		void CPopupMenuService::ProcessKeyRight()
		{
			IListItem *parent{ FindLastSubmenu(&m_pMenu->m_cRootItem) };
			int active_index{ -1 };
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible() && parent->getItem(i)->isEnabled() && parent->getItem(i)->isActive())
				{
					active_index = i;
					break;
				}
			if (active_index < 0) // Activate first proper item
			{
				active_index = 0;
				while (active_index < parent->getItemCount() && (!parent->getItem(active_index)->isVisible() || !parent->getItem(active_index)->isEnabled()))
					active_index++;
				if (active_index < parent->getItemCount())
				{
					parent->getItem(active_index)->setActive(true);
					ScrollToItem(parent->getItem(active_index));
					UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
					m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent), false);
				}
			}
			else if (parent->getItem(active_index)->getItemCount() > 0) // Open submenu
			{
				// Open submenu
				int index{ m_pMenu->FindItemIndex(parent->getItem(active_index)) };
				m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(index), false);
				m_pMenu->m_aItems[index].Opended = true;
				m_pMenu->UpdateSubmenuPosition(parent->getItem(active_index));
				// Activate first item of submenu
				int i{ 0 };
				while (i < parent->getItem(active_index)->getItemCount() && (!parent->getItem(active_index)->getItem(i)->isVisible() || !parent->getItem(active_index)->getItem(i)->isEnabled()))
					i++;
				if (i < parent->getItem(active_index)->getItemCount())
				{
					parent->getItem(active_index)->getItem(i)->setActive(true);
					ScrollToItem(parent->getItem(active_index)->getItem(i));
					UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
				}
				m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent), false);
			}
		}

		void CPopupMenuService::ProcessKeyHome()
		{
			IListItem *parent{ FindLastSubmenu(&m_pMenu->m_cRootItem) };
			int active_index{ 0 }, old_active_index{ -1 };
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible() && parent->getItem(i)->isEnabled() && parent->getItem(i)->isActive())
				{
					old_active_index = i;
					break;
				}
			while (active_index < parent->getItemCount() && (!parent->getItem(active_index)->isVisible() || !parent->getItem(active_index)->isEnabled()))
				active_index++;
			if (active_index != old_active_index)
			{
				if (active_index < parent->getItemCount())
				{
					parent->getItem(active_index)->setActive(true);
					ScrollToItem(parent->getItem(active_index));
					UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
				}
				else if (old_active_index >= 0)
					parent->getItem(old_active_index)->setActive(false);
				m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent), false);
			}
		}

		void CPopupMenuService::ProcessKeyEnd()
		{
			IListItem *parent{ FindLastSubmenu(&m_pMenu->m_cRootItem) };
			int active_index{ parent->getItemCount() - 1 }, old_active_index{ -1 };
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible() && parent->getItem(i)->isEnabled() && parent->getItem(i)->isActive())
				{
					old_active_index = i;
					break;
				}
			while (active_index >= 0 && (!parent->getItem(active_index)->isVisible() || !parent->getItem(active_index)->isEnabled()))
				active_index--;
			if (active_index != old_active_index)
			{
				if (active_index >= 0)
				{
					parent->getItem(active_index)->setActive(true);
					ScrollToItem(parent->getItem(active_index));
					UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
				}
				else if (old_active_index >= 0)
					parent->getItem(old_active_index)->setActive(false);
				m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent), false);
			}
		}

		void CPopupMenuService::ProcessKeyEsc()
		{
			IListItem *parent{ FindLastSubmenu(&m_pMenu->m_cRootItem) };
			if (parent != &m_pMenu->m_cRootItem)
			{
				CloseSubmenu(parent, false);
				UnhoverItems(parent);
			}
			else
				m_pMenu->Hide();
		}

		void CPopupMenuService::ProcessOnKeyDown(const MessageKey &m)
		{
			IListItem *item{ FindLastActiveItem() };
			if (item)
			{
				bool ctrl, alt, shift;
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (item->QueryService()->NotifyOnKeyDown(m.Key, ctrl, alt, shift))
				{
					m_bIgnoreKeyUp = true;
					m_pMenu->Hide();
				}
			}
		}

		void CPopupMenuService::ProcessOnKeyUp(const MessageKey &m)
		{
			IListItem *item{ FindLastActiveItem() };
			if (item)
			{
				bool ctrl, alt, shift;
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (item->QueryService()->NotifyOnKeyUp(m.Key, ctrl, alt, shift))
					m_pMenu->Hide();
			}
		}

		void CPopupMenuService::UpdateHoveredItem(const PointF &position)
		{
			if (m_pMenu->isVisible(false))
			{
				bool t, b;
				IListItem *item{ m_pMenu->getItem(&m_pMenu->m_cRootItem, position, t, b) };
				if (t || b)
					item = nullptr;
				UnhoverItems(&m_pMenu->m_cRootItem);
				if (item)
					item->QueryService()->setHovered(true);
			}
		}

		void CPopupMenuService::UnhoverItems(IListItem *parent)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				parent->getItem(i)->QueryService()->setHovered(false);
				UnhoverItems(parent->getItem(i));
			}
		}

		void CPopupMenuService::ProcessMouseMove(const MessageMouse &m)
		{
			bool top_scroller, bottom_scroller;
			IListItem *item{ m_pMenu->getItem(&m_pMenu->m_cRootItem, m.Position, top_scroller, bottom_scroller) };
			if (item && !top_scroller && !bottom_scroller && !item->isEnabled())
				item = nullptr;
			if (item != m_pMenu->m_pHoveredItem || top_scroller != m_pMenu->m_bHoverTopScroller || bottom_scroller != m_pMenu->m_bHoverBottomScroller)
			{
				if (m_pMenu->m_bHoverTopScroller || m_pMenu->m_bHoverBottomScroller)
					m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(m_pMenu->m_pHoveredItem), false);
				if (top_scroller || bottom_scroller)
					m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(item), false);
				// Close opened submenu on same level as new active item and deactivate submenu parent items
				if (item && !top_scroller && !bottom_scroller)
					for (int i = 0; i < item->getParent()->getItemCount(); i++)
						if (item->getParent()->getItem(i) != item && item->getParent()->getItem(i)->isVisible())
							CloseSubmenu(item->getParent()->getItem(i), true);
				// Deactivate current active item if no inew active item found and current one have no submenu
				if (m_pMenu->m_pHoveredItem && !item && m_pMenu->m_pHoveredItem->getItemCount() == 0)
					m_pMenu->m_pHoveredItem->setActive(false);
				// Set new active item and open submenu if exists
				m_pMenu->m_pHoveredItem = item;
				if (m_pMenu->m_pHoveredItem && !top_scroller && !bottom_scroller)
				{
					int index{ m_pMenu->FindItemIndex(m_pMenu->m_pHoveredItem) };
					bool need_open{ !m_pMenu->m_aItems[index].Opended && m_pMenu->m_pHoveredItem->getItemCount() > 0 };
					m_pMenu->m_pHoveredItem->setActive(true);
					if (need_open)
					{
						m_pMenu->m_aItems[index].Opended = true;
						m_pMenu->UpdateSubmenuPosition(m_pMenu->m_pHoveredItem);
						m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(index), false);
					}
					m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(m_pMenu->m_pHoveredItem->getParent()), false);
				}
				m_pMenu->m_bHoverTopScroller = top_scroller;
				m_pMenu->m_bHoverBottomScroller = bottom_scroller;
				UpdateHoveredItem(m.Position);
			}
		}

		void CPopupMenuService::ProcessMouseDown(const MessageMouse &m)
		{
			m_pMenu->MouseDownCancel();
			if (!m_pMenu->m_bHoverTopScroller && !m_pMenu->m_bHoverBottomScroller && m_pMenu->m_pHoveredItem)
			{
				int parent_index{ m_pMenu->FindItemIndex(m_pMenu->m_pHoveredItem->getParent()) };
				PointF position{
					m.Position.X - m_pMenu->m_aItems[parent_index].Position.X,
					m.Position.Y - m_pMenu->m_aItems[parent_index].Position.Y - m_pMenu->m_aItems[parent_index].Scroll };
				if (m_pMenu->m_pHoveredItem->QueryService()->NotifyOnMouseDown(position, m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					m_pMenu->Hide();
			}
			m_bIgnoreMouseUp = true;
		}

		void CPopupMenuService::ProcessMouseUp(const MessageMouse &m)
		{
			m_pMenu->MouseDownCancel();
			if (!m_bIgnoreMouseUp && !m_pMenu->m_bHoverTopScroller && !m_pMenu->m_bHoverBottomScroller && m_pMenu->m_pHoveredItem)
			{
				int parent_index{ m_pMenu->FindItemIndex(m_pMenu->m_pHoveredItem->getParent()) };
				PointF position{
					m.Position.X - m_pMenu->m_aItems[parent_index].Position.X,
					m.Position.Y - m_pMenu->m_aItems[parent_index].Position.Y - m_pMenu->m_aItems[parent_index].Scroll };
				if (m_pMenu->m_pHoveredItem->QueryService()->NotifyOnMouseDown(position, m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					m_pMenu->Hide();
			}
			m_bIgnoreMouseUp = false;
		}

		void CPopupMenuService::ProcessMouseDoubleClick(const MessageMouse &m)
		{
			m_pMenu->MouseDownCancel();
			if (!m_pMenu->m_bHoverTopScroller && !m_pMenu->m_bHoverBottomScroller && m_pMenu->m_pHoveredItem)
			{
				int parent_index{ m_pMenu->FindItemIndex(m_pMenu->m_pHoveredItem->getParent()) };
				PointF position{
					m.Position.X - m_pMenu->m_aItems[parent_index].Position.X,
					m.Position.Y - m_pMenu->m_aItems[parent_index].Position.Y - m_pMenu->m_aItems[parent_index].Scroll };
				if (m_pMenu->m_pHoveredItem->QueryService()->NotifyOnMouseDoubleClick(position, m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					m_pMenu->Hide();
			}
		}

		void CPopupMenuService::ProcessMouseVerticalWheel(const MessageMouseWheel &m)
		{
			IListItem *parent;
			if (FindSubmenu(&m_pMenu->m_cRootItem, m.Position, &parent))
			{
				int parent_index{ m_pMenu->FindItemIndex(parent) };
				if (m.Delta < 0 && ntl::IsLess<float>(m_pMenu->m_aItems[parent_index].Scroll, m_pMenu->m_aItems[parent_index].ScrollMax))
				{
					m_pMenu->m_aItems[parent_index].Scroll = ntl::Min<float>(m_pMenu->m_aItems[parent_index].ScrollMax, m_pMenu->m_aItems[parent_index].Scroll + m_pMenu->m_fDeltaScrollWheel);
					UpdateHoveredItem(m.Position);
					m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent_index), false);
				}
				else if (m.Delta > 0 && ntl::IsGreater<float>(m_pMenu->m_aItems[parent_index].Scroll, 0))
				{
					m_pMenu->m_aItems[parent_index].Scroll = ntl::Max<float>(0, m_pMenu->m_aItems[parent_index].Scroll - m_pMenu->m_fDeltaScrollWheel);
					UpdateHoveredItem(m.Position);
					m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent_index), false);
				}
			}
		}

		void CPopupMenuService::ProcessDropFiles(const MessageDropFiles &m)
		{
			m_pMenu->MouseDownCancel();
			if (!m_pMenu->m_bHoverTopScroller && !m_pMenu->m_bHoverBottomScroller && m_pMenu->m_pHoveredItem)
			{
				int parent_index{ m_pMenu->FindItemIndex(m_pMenu->m_pHoveredItem->getParent()) };
				PointF position{
					m.Position.X - m_pMenu->m_aItems[parent_index].Position.X,
					m.Position.Y - m_pMenu->m_aItems[parent_index].Position.Y - m_pMenu->m_aItems[parent_index].Scroll };
				if (m_pMenu->m_pHoveredItem->QueryService()->NotifyOnDropFiles(position, m.FileNames))
					m_pMenu->Hide();
			}
		}

		void CPopupMenuService::ProcessChar(const MessageChar &m)
		{
			IListItem *item{ FindLastActiveItem() };
			if (item)
			{
				bool ctrl, alt, shift;
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (item->QueryService()->NotifyOnChar(m.Char, ctrl, alt, shift))
					m_pMenu->Hide();
			}
		}

		IListItem *CPopupMenuService::FindLastActiveItem()
		{
			IListItem *parent{ FindLastSubmenu(&m_pMenu->m_cRootItem) }, *result{ nullptr };
			while (!result && parent)
			{
				for (int i = 0; i < parent->getItemCount(); i++)
					if (parent->getItem(i)->isVisible() && parent->getItem(i)->isEnabled() && parent->getItem(i)->isActive())
					{
						result = parent->getItem(i);
						break;
					}
				if (result)
					break;
				parent = parent->getParent();
			}
			return result;
		}

		void CPopupMenuService::NotifyFreeResources(IListItem *item)
		{
			item->QueryService()->NotifyOnFreeResources();
			for (int i = 0; i < item->getItemCount(); i++)
				NotifyFreeResources(item->getItem(i));
		}
	#pragma endregion

	#pragma region Application notifications
		void CPopupMenuService::NotifyOnTranslateChange()
		{
			m_pMenu->Repaint(false);
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CPopupMenuService::NotifyOnParentStyleChange()
		{
			if (m_pMenu->getStyle())
			{
				m_pMenu->UpdateFromStyle(m_pMenu->getStyle());
				m_pMenu->UpdateSubmenu(&m_pMenu->m_cRootItem, true);
				m_pMenu->UpdateSubmenuPosition(&m_pMenu->m_cRootItem);
				if (m_pMenu->getForm())
					UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
			}
		}

		void CPopupMenuService::NotifyOnParentFontChange()
		{
			m_pMenu->UpdateSubmenu(&m_pMenu->m_cRootItem, true);
			m_pMenu->UpdateSubmenuPosition(&m_pMenu->m_cRootItem);
			if (m_pMenu->getForm())
				UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
		}

		void CPopupMenuService::NotifyOnParentResize()
		{
			m_pMenu->UpdateSubmenuPosition(&m_pMenu->m_cRootItem);
			if (m_pMenu->getForm())
				UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
		}

		void CPopupMenuService::NotifyOnDeactivate()
		{
			m_pMenu->Hide();
		}
	#pragma endregion

	#pragma region State change notifications
		void CPopupMenuService::NotifyOnShow()
		{
			m_pMenu->UpdateSubmenuPosition(&m_pMenu->m_cRootItem);
			UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
			m_pMenu->getForm()->CaptureKeyboard(m_pMenu);
			m_pMenu->getForm()->CaptureMouse(m_pMenu, false);
			m_pMenu->getForm()->setActiveControl(m_pMenu);
			m_pMenu->m_hScrollTimer = m_pMenu->getForm()->CreateTimer(this, m_pMenu->m_fScrollInterval);
		}

		void CPopupMenuService::NotifyOnHide()
		{
			CloseSubmenu(&m_pMenu->m_cRootItem, false);
			m_pMenu->m_pHoveredItem = nullptr;
			m_pMenu->m_bHoverTopScroller = m_pMenu->m_bHoverBottomScroller = false;
			if (m_pMenu->m_hScrollTimer)
			{
				m_pMenu->getForm()->DeleteTimer(m_pMenu->m_hScrollTimer);
				m_pMenu->m_hScrollTimer = 0;
			}
			m_pMenu->MouseDownCancel();
			UnhoverItems(&m_pMenu->m_cRootItem);
		}

		void CPopupMenuService::NotifyOnAttach()
		{
			if (m_pMenu->getForm())
			{
				m_pMenu->UpdateSubmenu(&m_pMenu->m_cRootItem, true);
				m_pMenu->UpdateSubmenuPosition(&m_pMenu->m_cRootItem);
				UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
			}
		}

		void CPopupMenuService::NotifyOnDetaching()
		{
			m_pMenu->Hide();
		}

		void CPopupMenuService::NotifyOnFreeResources()
		{
			NotifyFreeResources(&m_pMenu->m_cRootItem);
		}

		void CPopupMenuService::NotifyOnResize()
		{
			m_pMenu->UpdateSubmenu(&m_pMenu->m_cRootItem, true);
			m_pMenu->UpdateSubmenuPosition(&m_pMenu->m_cRootItem);
			UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
		}

		void CPopupMenuService::NotifyOnStyleChange()
		{
			if (m_pMenu->getStyle())
			{
				m_pMenu->UpdateFromStyle(m_pMenu->getStyle());
				m_pMenu->UpdateSubmenu(&m_pMenu->m_cRootItem, true);
				m_pMenu->UpdateSubmenuPosition(&m_pMenu->m_cRootItem);
				if (m_pMenu->getForm())
					UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
			}
		}

		void CPopupMenuService::NotifyOnFontChange()
		{
			m_pMenu->UpdateSubmenu(&m_pMenu->m_cRootItem, true);
			m_pMenu->UpdateSubmenuPosition(&m_pMenu->m_cRootItem);
			if (m_pMenu->getForm())
				UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
		}
	#pragma endregion

	#pragma region Paint notifications
		void CPopupMenuService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (m.LastPass)
				m_pMenu->Render();
		}
	#pragma endregion

	#pragma region Other components/controls/objects change notifications
		void CPopupMenuService::NotifyOnComponentDetach(IComponent *component)
		{
			IImageList *list{ cast<IImageList*>(component) };
			if (list && (list == m_pMenu->m_pImageListEnabled || list == m_pMenu->m_pImageListDisabled))
			{
				m_pMenu->Repaint(false);
				if (list == m_pMenu->m_pImageListEnabled)
					m_pMenu->m_pImageListEnabled = nullptr;
				if (list == m_pMenu->m_pImageListDisabled)
					m_pMenu->m_pImageListDisabled = nullptr;
				m_pMenu->UpdateSubmenu(&m_pMenu->m_cRootItem, true);
				m_pMenu->UpdateSubmenuPosition(&m_pMenu->m_cRootItem);
				if (m_pMenu->getForm())
					UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
				m_pMenu->Repaint(false);
			}
		}

		void CPopupMenuService::NotifyOnControlDetach(IControl *control)
		{
			IImageList *list{ cast<IImageList*>(control) };
			if (list && (list == m_pMenu->m_pImageListEnabled || list == m_pMenu->m_pImageListDisabled))
			{
				m_pMenu->Repaint(false);
				if (list == m_pMenu->m_pImageListEnabled)
					m_pMenu->m_pImageListEnabled = nullptr;
				if (list == m_pMenu->m_pImageListDisabled)
					m_pMenu->m_pImageListDisabled = nullptr;
				m_pMenu->UpdateSubmenu(&m_pMenu->m_cRootItem, true);
				m_pMenu->UpdateSubmenuPosition(&m_pMenu->m_cRootItem);
				if (m_pMenu->getForm())
					UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
				m_pMenu->Repaint(false);
			}
		}

		void CPopupMenuService::NotifyOnComponentChange(IComponent *component)
		{
			IImageList *list{ cast<IImageList*>(component) };
			if (list && (list == m_pMenu->m_pImageListEnabled || list == m_pMenu->m_pImageListDisabled))
			{
				m_pMenu->Repaint(false);
				m_pMenu->UpdateSubmenu(&m_pMenu->m_cRootItem, true);
				m_pMenu->UpdateSubmenuPosition(&m_pMenu->m_cRootItem);
				if (m_pMenu->getForm())
					UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
				m_pMenu->Repaint(false);
			}
		}

		void CPopupMenuService::NotifyOnControlChange(IControl *control)
		{
			IImageList *list{ cast<IImageList*>(control) };
			if (list && (list == m_pMenu->m_pImageListEnabled || list == m_pMenu->m_pImageListDisabled))
			{
				m_pMenu->Repaint(false);
				m_pMenu->UpdateSubmenu(&m_pMenu->m_cRootItem, true);
				m_pMenu->UpdateSubmenuPosition(&m_pMenu->m_cRootItem);
				if (m_pMenu->getForm())
					UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
				m_pMenu->Repaint(false);
			}
		}

		void CPopupMenuService::NotifyOnHotkey(const MessageHotkey &m)
		{
			std::chrono::milliseconds duration{ std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_pMenu->m_sLastHotkey) };
			if ((float)duration.count() > m_pMenu->m_fHotkeyMaxInterval * 0.001f)
				m_pMenu->m_aLastHotkeys.clear();
			m_pMenu->m_aLastHotkeys.push_back({ m.Key, m.Ctrl, m.Alt, m.Shift, m.Down });
			IListItemMenu *item{ FindHotkeyOwner(&m_pMenu->m_cRootItem) };
			if (item)
			{
				m_pMenu->m_aLastHotkeys.clear();
				IListItemMenuService *service{ cast<IListItemMenuService*>(item->QueryService()) };
				if (service && service->NotifyOnHotkey())
					m_pMenu->Hide();
			}
			m_pMenu->m_sLastHotkey = std::chrono::steady_clock::now();
		}
	#pragma endregion

	#pragma region Input notifications
		void CPopupMenuService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			ProcessMouseMove(m);
		}

		void CPopupMenuService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			m_bIgnoreMouseUp = false;
			MouseDown(m);
		}

		void CPopupMenuService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m_bIgnoreMouseUp)
				MouseUp(m);
			m_bIgnoreMouseUp = false;
		}

		void CPopupMenuService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			ProcessMouseDoubleClick(m);
		}

		void CPopupMenuService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			m_bIgnoreMouseUp = false;
			MouseDown(m);
		}

		void CPopupMenuService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m_bIgnoreMouseUp)
				MouseUp(m);
			m_bIgnoreMouseUp = false;
		}

		void CPopupMenuService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			ProcessMouseDoubleClick(m);
		}

		void CPopupMenuService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			ProcessMouseDown(m);
		}

		void CPopupMenuService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			ProcessMouseUp(m);
		}

		void CPopupMenuService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			ProcessMouseDoubleClick(m);
		}

		void CPopupMenuService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			ProcessMouseVerticalWheel(m);
		}

		void CPopupMenuService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			ProcessChar(m);
		}

		void CPopupMenuService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			m_bIgnoreKeyUp = false;
			switch (m.Key)
			{
			case Key::Up:
			case Key::Numpad8:
				if (m.Key == Key::Up || !Application->Keyboard->isToggled(Key::NumLock))
				{
					ProcessKeyUp();
					m_bIgnoreKeyUp = true;
				}
				break;
			case Key::Down:
			case Key::Numpad2:
				if (m.Key == Key::Down || !Application->Keyboard->isToggled(Key::NumLock))
				{
					ProcessKeyDown();
					m_bIgnoreKeyUp = true;
				}
				break;
			case Key::Tab:
				if (Application->Keyboard->isDown(Key::Shift))
					ProcessKeyUp();
				else
					ProcessKeyDown();
				m_bIgnoreKeyUp = true;
				break;
			case Key::Left:
			case Key::Numpad4:
				if (m.Key == Key::Left || !Application->Keyboard->isToggled(Key::NumLock))
				{
					ProcessKeyLeft();
					m_bIgnoreKeyUp = true;
				}
				break;
			case Key::Right:
			case Key::Numpad6:
				if (m.Key == Key::Right || !Application->Keyboard->isToggled(Key::NumLock))
				{
					ProcessKeyRight();
					m_bIgnoreKeyUp = true;
				}
				break;
			case Key::Home:
			case Key::Numpad7:
				if (m.Key == Key::Home || !Application->Keyboard->isToggled(Key::NumLock))
				{
					ProcessKeyHome();
					m_bIgnoreKeyUp = true;
				}
				break;
			case Key::End:
			case Key::Numpad1:
				if (m.Key == Key::End || !Application->Keyboard->isToggled(Key::NumLock))
				{
					ProcessKeyEnd();
					m_bIgnoreKeyUp = true;
				}
				break;
			case Key::Escape:
				ProcessKeyEsc();
				m_bIgnoreKeyUp = true;
				break;
			default:
				ProcessOnKeyDown(m);
				break;
			}
		}

		void CPopupMenuService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m_bIgnoreKeyUp)
				m_bIgnoreKeyUp = false;
			else
				ProcessOnKeyUp(m);
		}

		void CPopupMenuService::NotifyOnDropFiles(const MessageDropFiles &m, bool &processed, bool &accepted)
		{
			processed = true;
			ProcessDropFiles(m);
		}
	#pragma endregion

	#pragma region Timer notification
		void CPopupMenuService::NotifyOnTimer(const PlatformHandle id)
		{
			if (m_pMenu->m_bHoverTopScroller)
			{
				if (m_pMenu->m_pHoveredItem)
				{
					int index{ m_pMenu->FindItemIndex(m_pMenu->m_pHoveredItem) };
					if (ntl::IsGreater<float>(m_pMenu->m_aItems[index].Scroll, 0))
					{
						m_pMenu->m_aItems[index].Scroll = ntl::Max<float>(0, m_pMenu->m_aItems[index].Scroll - m_pMenu->m_fDeltaScrollTimer);
						UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
						m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(index), false);
					}
				}
				else
				{
					if (ntl::IsGreater<float>(m_pMenu->m_aItems[0].Scroll, 0))
					{
						m_pMenu->m_aItems[0].Scroll = ntl::Max<float>(0, m_pMenu->m_aItems[0].Scroll - m_pMenu->m_fDeltaScrollTimer);
						UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
						m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(0), false);
					}
				}
			}
			else if (m_pMenu->m_bHoverBottomScroller)
			{
				if (m_pMenu->m_pHoveredItem)
				{
					int index{ m_pMenu->FindItemIndex(m_pMenu->m_pHoveredItem) };
					if (ntl::IsLess<float>(m_pMenu->m_aItems[index].Scroll, m_pMenu->m_aItems[index].ScrollMax))
					{
						m_pMenu->m_aItems[index].Scroll = ntl::Min<float>(m_pMenu->m_aItems[index].ScrollMax, m_pMenu->m_aItems[index].Scroll + m_pMenu->m_fDeltaScrollTimer);
						UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
						m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(index), false);
					}
				}
				else
				{
					if (ntl::IsLess<float>(m_pMenu->m_aItems[0].Scroll, m_pMenu->m_aItems[0].ScrollMax))
					{
						m_pMenu->m_aItems[0].Scroll = ntl::Min<float>(m_pMenu->m_aItems[0].ScrollMax, m_pMenu->m_aItems[0].Scroll + m_pMenu->m_fDeltaScrollTimer);
						UpdateHoveredItem((PointF)m_pMenu->getForm()->ScreenToClient(Application->Mouse->getPosition()));
						m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(0), false);
					}
				}
			}
		}
	#pragma endregion
	}
}