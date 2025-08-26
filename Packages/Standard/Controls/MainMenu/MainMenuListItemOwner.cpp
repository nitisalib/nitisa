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
		CMainMenu::CMainMenuListItemOwner::CMainMenuListItemOwner(CMainMenu *menu) :
			m_pMenu{ menu }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CMainMenu::CMainMenuListItemOwner::getControl()
		{
			return m_pMenu;
		}

		IRenderer *CMainMenu::CMainMenuListItemOwner::getRenderer()
		{
			if (m_pMenu->getForm())
				return m_pMenu->getForm()->getRenderer();
			return nullptr;
		}

		IFont *CMainMenu::CMainMenuListItemOwner::getFont(IListItem *item)
		{
			return m_pMenu->getFont();
		}

		IStyle *CMainMenu::CMainMenuListItemOwner::getStyle(IListItem *item)
		{
			return m_pMenu->getStyle();
		}

		ITexture *CMainMenu::CMainMenuListItemOwner::getImage(const bool enabled, const bool active, const bool hovered, const int index, RectF &rect)
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
		bool CMainMenu::CMainMenuListItemOwner::DeleteItem(IListItem *item)
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

		void CMainMenu::CMainMenuListItemOwner::UpdateAndRepaint(IListItem *parent)
		{
			CLockRepaint lock{ m_pMenu };
			m_pMenu->UpdateSubmenu(parent, false);
			m_pMenu->UpdateSubmenuPosition(parent);
			if (parent == &m_pMenu->m_cRootItem && m_pMenu->m_pCanvas)
				m_pMenu->m_pCanvas->setValid(false);
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent), false);
		}

		void CMainMenu::CMainMenuListItemOwner::UpdateItemOwner(IListItem *item, IListItemOwner *owner)
		{
			item->QueryService()->setOwner(owner);
			item->QueryService()->setDPI(m_pMenu->getDPI());
			for (int i = 0; i < item->getItemCount(); i++)
				UpdateItemOwner(item->getItem(i), owner);
		}
	#pragma endregion

	#pragma region Notifications
		void CMainMenu::CMainMenuListItemOwner::NotifyOnSizeChange(IListItem *item)
		{
			UpdateAndRepaint(item->getParent());
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnRepaintRequired(IListItem *item)
		{
			if (item->getParent() == &m_pMenu->m_cRootItem && m_pMenu->m_pCanvas)
				m_pMenu->m_pCanvas->setValid(false);
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(item->getParent()), false);
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnBeforeAddItem(IListItem *item, IListItem *parent)
		{
			if (m_pMenu->getForm())
			{
				m_pMenu->getForm()->LockRepaint();
				m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent), false);
			}
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnAddItem(IListItem *item)
		{
			int index{ m_pMenu->FindItemIndex(item) }; // Root items are added by PopupMenu, so check first if item already in list
			if (index < 0)
				m_pMenu->m_aItems.push_back({ item, false, 0, 0, PointF{ 0, 0 }, PointF{ 0, 0 }, false });
			m_pMenu->m_aLastHotkeys.clear();
			IListItemMenu *menuitem{ cast<IListItemMenu*>(item) };
			if (menuitem && m_pMenu->getForm())
				for (int i = 0; i < menuitem->getHotkeyCount(); i++)
					m_pMenu->getForm()->QueryService()->RegisterHotkey(m_pMenu, menuitem->getHotkey(i).Key, menuitem->getHotkey(i).Ctrl, menuitem->getHotkey(i).Alt,
						menuitem->getHotkey(i).Shift, menuitem->getHotkey(i).Down);
			UpdateItemOwner(item, m_pMenu->QueryListItemOwner());
			UpdateAndRepaint(item->getParent());
			if (m_pMenu->getForm())
				m_pMenu->getForm()->UnlockRepaint();
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnBeforeDeleteItem(IListItem *item)
		{
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(item->getParent()), false);
			m_pMenu->m_aLastHotkeys.clear();
			if (m_pMenu->m_pHoveredItem && (item == m_pMenu->m_pHoveredItem || item->hasItem(m_pMenu->m_pHoveredItem) || m_pMenu->m_pHoveredItem->hasItem(item)))
				m_pMenu->m_pHoveredItem = nullptr;
			DeleteItem(item);
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnDeleteItem(IListItem *item, IListItem *parent)
		{
			if (m_pMenu->OnDeleteItem)
				m_pMenu->OnDeleteItem(m_pMenu, item);
			m_pMenu->UpdateSubmenu(&m_pMenu->m_cRootItem, true);
			m_pMenu->UpdateSubmenuPosition(&m_pMenu->m_cRootItem);
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent), false);
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnBeforeDeleteItems(IListItem *parent)
		{
			// Nothing
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnDeleteItems(IListItem *parent)
		{
			if (m_pMenu->OnDeleteItems)
				m_pMenu->OnDeleteItems(m_pMenu);
			m_pMenu->UpdateSubmenu(&m_pMenu->m_cRootItem, true);
			m_pMenu->UpdateSubmenuPosition(&m_pMenu->m_cRootItem);
			if (m_pMenu->m_pCanvas)
				m_pMenu->m_pCanvas->setValid(false);
			m_pMenu->Repaint(false);
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnAddHotkey(IListItemMenu *listitem, const Hotkey &hotkey)
		{
			m_pMenu->m_aLastHotkeys.clear();
			if (m_pMenu->getForm())
				m_pMenu->getForm()->QueryService()->RegisterHotkey(m_pMenu, hotkey.Key, hotkey.Ctrl, hotkey.Alt, hotkey.Shift, hotkey.Down);
			UpdateAndRepaint(listitem->getParent());
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnDeleteHotkey(IListItemMenu *listitem, const Hotkey &hotkey)
		{
			m_pMenu->m_aLastHotkeys.clear();
			if (m_pMenu->getForm())
				m_pMenu->getForm()->QueryService()->UnregisterHotkey(m_pMenu, hotkey.Key, hotkey.Ctrl, hotkey.Alt, hotkey.Shift, hotkey.Down);
			UpdateAndRepaint(listitem->getParent());
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnShow(IListItem *item)
		{
			UpdateAndRepaint(item->getParent());
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnHide(IListItem *item)
		{
			if (m_pMenu->m_pDownItem && (item == m_pMenu->m_pDownItem || item->hasItem(m_pMenu->m_pDownItem)))
				m_pMenu->MouseDownCancel();
			UpdateAndRepaint(item->getParent());
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnEnable(IListItem *item)
		{
			if (item->getParent() == &m_pMenu->m_cRootItem && m_pMenu->m_pCanvas)
				m_pMenu->m_pCanvas->setValid(false);
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(item->getParent()), false);
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnDisable(IListItem *item)
		{
			if (m_pMenu->m_pDownItem && (item == m_pMenu->m_pDownItem || item->hasItem(m_pMenu->m_pDownItem)))
				m_pMenu->MouseDownCancel();
			if (item->getParent() == &m_pMenu->m_cRootItem && m_pMenu->m_pCanvas)
				m_pMenu->m_pCanvas->setValid(false);
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(item->getParent()), false);
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnSelect(IListItem *item)
		{
			if (m_pMenu->OnSelectItem)
				m_pMenu->OnSelectItem(m_pMenu, item);
			if (item->getParent() == &m_pMenu->m_cRootItem && m_pMenu->m_pCanvas)
				m_pMenu->m_pCanvas->setValid(false);
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(item->getParent()), false);
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnDeselect(IListItem *item)
		{
			if (m_pMenu->OnDeselectItem)
				m_pMenu->OnDeselectItem(m_pMenu, item);
			if (item->getParent() == &m_pMenu->m_cRootItem && m_pMenu->m_pCanvas)
				m_pMenu->m_pCanvas->setValid(false);
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(item->getParent()), false);
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnActivate(IListItem *item)
		{
			CLockRepaint lock{ m_pMenu };
			if (m_pMenu->OnActivateItem)
				m_pMenu->OnActivateItem(m_pMenu, item);
			int parent_index{ m_pMenu->FindItemIndex(item->getParent()) };
			if (item->getParent() == &m_pMenu->m_cRootItem && m_pMenu->m_pCanvas)
				m_pMenu->m_pCanvas->setValid(false);
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(parent_index), false);
			for (int i = 0; i < item->getParent()->getItemCount(); i++)
				if (item->getParent()->getItem(i) != item && item->getParent()->getItem(i)->isActive())
					cast<CMainMenuService*>(m_pMenu->QueryService())->CloseSubmenu(item->getParent()->getItem(i), true);
		}

		void CMainMenu::CMainMenuListItemOwner::NotifyOnDeactivate(IListItem *item)
		{
			CLockRepaint lock{ m_pMenu };
			if (m_pMenu->OnDeactivateItem)
				m_pMenu->OnDeactivateItem(m_pMenu, item);
			if (item->getParent() == &m_pMenu->m_cRootItem && m_pMenu->m_pCanvas)
				m_pMenu->m_pCanvas->setValid(false);
			m_pMenu->Repaint(m_pMenu->getAbsoluteRenderRect(item->getParent()), false);
			cast<CMainMenuService*>(m_pMenu->QueryService())->CloseSubmenu(item, true);
		}
	#pragma endregion
	}
}