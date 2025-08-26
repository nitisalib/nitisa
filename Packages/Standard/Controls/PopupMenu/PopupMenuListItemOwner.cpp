// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
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
		CPopupMenu::CPopupMenuListItemOwner::CPopupMenuListItemOwner(CPopupMenu *menu) :
			m_pMenu{ menu }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CPopupMenu::CPopupMenuListItemOwner::getControl()
		{
			return m_pMenu;
		}

		IRenderer *CPopupMenu::CPopupMenuListItemOwner::getRenderer()
		{
			if (m_pMenu->getForm())
				return m_pMenu->getForm()->getRenderer();
			return nullptr;
		}

		IFont *CPopupMenu::CPopupMenuListItemOwner::getFont(IListItem *item)
		{
			return m_pMenu->getFont();
		}

		IStyle *CPopupMenu::CPopupMenuListItemOwner::getStyle(IListItem *item)
		{
			return m_pMenu->getStyle();
		}

		ITexture *CPopupMenu::CPopupMenuListItemOwner::getImage(const bool enabled, const bool active, const bool hovered, const int index, RectF &rect)
		{
			if (enabled && m_pMenu->m_pImageListEnabled)
			{
				ITexture *r{ m_pMenu->m_pImageListEnabled->getTexture(index) };
				if (r)
					rect = RectF{ 0, 0, r->Widthf, r->Heightf };
				return r;
			}
			if (!enabled && m_pMenu->m_pImageListDisabled)
			{
				ITexture *r{ m_pMenu->m_pImageListDisabled->getTexture(index) };
				if (r)
					rect = RectF{ 0, 0, r->Widthf, r->Heightf };
				return r;
			}
			return nullptr;
		}
	#pragma endregion

	#pragma region Helpers
		bool CPopupMenu::CPopupMenuListItemOwner::DeleteItem(IListItem *item)
		{
			bool result{ false };
			for (int i = 0; i < item->getItemCount(); i++)
				if (DeleteItem(item->getItem(i)))
					result = true;
			if (item == m_pMenu->m_pDownItem)
				m_pMenu->MouseDownCancel();
			int index{ m_pMenu->FindItemIndex(item) };
			if (index >= 0)
			{
				IListItemMenu *menuitem{ cast<IListItemMenu*>(item) };
				if (menuitem && m_pMenu->getForm())
					for (int i = 0; i < menuitem->getHotkeyCount(); i++)
						m_pMenu->getForm()->QueryService()->UnregisterHotkey(m_pMenu, menuitem->getHotkey(i).Key, menuitem->getHotkey(i).Ctrl, menuitem->getHotkey(i).Alt, menuitem->getHotkey(i).Shift, menuitem->getHotkey(i).Down);
				m_pMenu->m_aItems.erase(m_pMenu->m_aItems.begin() + index);
				result = true;
			}
			return result;
		}

		void CPopupMenu::CPopupMenuListItemOwner::UpdateAndRepaint(IListItem *parent)
		{
			CLockRepaint lock{ m_pMenu };
			m_pMenu->UpdateSubmenu(parent, false);
			m_pMenu->UpdateSubmenuPosition(parent);
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent), false);
		}

		void CPopupMenu::CPopupMenuListItemOwner::UpdateItemOwner(IListItem *item, IListItemOwner *owner)
		{
			item->QueryService()->setOwner(owner);
			item->QueryService()->setDPI(m_pMenu->getDPI());
			for (int i = 0; i < item->getItemCount(); i++)
				UpdateItemOwner(item->getItem(i), owner);
		}
	#pragma endregion

	#pragma region Notifications
		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnSizeChange(IListItem *item)
		{
			UpdateAndRepaint(item->getParent());
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnRepaintRequired(IListItem *item)
		{
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(item->getParent()), false);
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnBeforeAddItem(IListItem *item, IListItem *parent)
		{
			if (m_pMenu->getForm())
			{
				m_pMenu->getForm()->LockRepaint();
				m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent), false);
			}
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnAddItem(IListItem *item)
		{
			int index{ m_pMenu->FindItemIndex(item) }; // Root items are added by PopupMenu, so check first if item already in list
			if (index < 0)
				m_pMenu->m_aItems.push_back({ item, false, 0, 0, PointF{ 0, 0 }, PointF{ 0, 0 } });
			m_pMenu->m_aLastHotkeys.clear();
			IListItemMenu *menuitem{ cast<IListItemMenu*>(item) };
			if (menuitem && m_pMenu->getForm())
				for (int i = 0; i < menuitem->getHotkeyCount(); i++)
					m_pMenu->getForm()->QueryService()->RegisterHotkey(m_pMenu, menuitem->getHotkey(i).Key, menuitem->getHotkey(i).Ctrl, menuitem->getHotkey(i).Alt, menuitem->getHotkey(i).Shift, menuitem->getHotkey(i).Down);
			UpdateItemOwner(item, m_pMenu->QueryListItemOwner());
			UpdateAndRepaint(item->getParent());
			if (m_pMenu->getForm())
				m_pMenu->getForm()->UnlockRepaint();
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnBeforeDeleteItem(IListItem *item)
		{
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(item->getParent()), false);
			m_pMenu->m_aLastHotkeys.clear();
			if (m_pMenu->m_pHoveredItem && (item == m_pMenu->m_pHoveredItem || item->hasItem(m_pMenu->m_pHoveredItem) || m_pMenu->m_pHoveredItem->hasItem(item)))
				m_pMenu->m_pHoveredItem = nullptr;
			DeleteItem(item);
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnDeleteItem(IListItem *item, IListItem *parent)
		{
			if (m_pMenu->OnDeleteItem)
				m_pMenu->OnDeleteItem(m_pMenu, item);
			if (m_pMenu->m_aItems.size() > 0)
			{
				m_pMenu->UpdateSubmenu(&m_pMenu->m_cRootItem, true);
				m_pMenu->UpdateSubmenuPosition(&m_pMenu->m_cRootItem);
				m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent), false);
			}
			else
				m_pMenu->Hide();
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnBeforeDeleteItems(IListItem *parent)
		{
			// Nothing
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnDeleteItems(IListItem *parent)
		{
			if (m_pMenu->OnDeleteItems)
				m_pMenu->OnDeleteItems(m_pMenu);
			if (m_pMenu->m_aItems.size() > 0)
			{
				m_pMenu->UpdateSubmenu(&m_pMenu->m_cRootItem, true);
				m_pMenu->UpdateSubmenuPosition(&m_pMenu->m_cRootItem);
				m_pMenu->Repaint(false);
			}
			else
				m_pMenu->Hide();
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnAddHotkey(IListItemMenu *listitem, const Hotkey &hotkey)
		{
			m_pMenu->m_aLastHotkeys.clear();
			if (m_pMenu->getForm())
				m_pMenu->getForm()->QueryService()->RegisterHotkey(m_pMenu, hotkey.Key, hotkey.Ctrl, hotkey.Alt, hotkey.Shift, hotkey.Down);
			UpdateAndRepaint(listitem->getParent());
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnDeleteHotkey(IListItemMenu *listitem, const Hotkey &hotkey)
		{
			m_pMenu->m_aLastHotkeys.clear();
			if (m_pMenu->getForm())
				m_pMenu->getForm()->QueryService()->UnregisterHotkey(m_pMenu, hotkey.Key, hotkey.Ctrl, hotkey.Alt, hotkey.Shift, hotkey.Down);
			UpdateAndRepaint(listitem->getParent());
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnShow(IListItem *item)
		{
			UpdateAndRepaint(item->getParent());
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnHide(IListItem *item)
		{
			if (m_pMenu->m_pDownItem && (item == m_pMenu->m_pDownItem || item->hasItem(m_pMenu->m_pDownItem)))
				m_pMenu->MouseDownCancel();
			UpdateAndRepaint(item->getParent());
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnEnable(IListItem *item)
		{
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(item->getParent()), false);
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnDisable(IListItem *item)
		{
			if (m_pMenu->m_pDownItem && (item == m_pMenu->m_pDownItem || item->hasItem(m_pMenu->m_pDownItem)))
				m_pMenu->MouseDownCancel();
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(item->getParent()), false);
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnSelect(IListItem *item)
		{
			if (m_pMenu->OnSelectItem)
				m_pMenu->OnSelectItem(m_pMenu, item);
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(item->getParent()), false);
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnDeselect(IListItem *item)
		{
			if (m_pMenu->OnDeselectItem)
				m_pMenu->OnDeselectItem(m_pMenu, item);
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(item->getParent()), false);
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnActivate(IListItem *item)
		{
			CLockRepaint lock{ m_pMenu };
			if (m_pMenu->OnActivateItem)
				m_pMenu->OnActivateItem(m_pMenu, item);
			int parent_index{ m_pMenu->FindItemIndex(item->getParent()) };
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent_index), false);
			for (int i = 0; i < item->getParent()->getItemCount(); i++)
				if (item->getParent()->getItem(i) != item && item->getParent()->getItem(i)->isActive())
					cast<CPopupMenuService*>(m_pMenu->QueryService())->CloseSubmenu(item->getParent()->getItem(i), true);
		}

		void CPopupMenu::CPopupMenuListItemOwner::NotifyOnDeactivate(IListItem *item)
		{
			CLockRepaint lock{ m_pMenu };
			if (m_pMenu->OnDeactivateItem)
				m_pMenu->OnDeactivateItem(m_pMenu, item);
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(item->getParent()), false);
			cast<CPopupMenuService*>(m_pMenu->QueryService())->CloseSubmenu(item, true);
		}
	#pragma endregion
	}
}