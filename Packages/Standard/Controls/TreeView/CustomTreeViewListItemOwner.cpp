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
		CCustomTreeViewListItemOwner::CCustomTreeViewListItemOwner(CCustomTreeView *treeview) :
			m_pTreeView{ treeview }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CCustomTreeViewListItemOwner::getControl()
		{
			return m_pTreeView;
		}

		IRenderer *CCustomTreeViewListItemOwner::getRenderer()
		{
			if (m_pTreeView->getForm())
				return m_pTreeView->getForm()->getRenderer();
			return nullptr;
		}

		IFont *CCustomTreeViewListItemOwner::getFont(IListItem *item)
		{
			return m_pTreeView->getFont();
		}

		IStyle *CCustomTreeViewListItemOwner::getStyle(IListItem *item)
		{
			return m_pTreeView->getStyle();
		}
	#pragma endregion

	#pragma region Notifications
		void CCustomTreeViewListItemOwner::NotifyOnSizeChange(IListItem *item)
		{
			if (!isIgnoreSizeChange())
			{
				m_pTreeView->LockUpdate();
				m_pTreeView->UnlockUpdate();
			}
		}

		void CCustomTreeViewListItemOwner::NotifyOnRepaintRequired(IListItem *item)
		{
			if (!isIgnoreRepaintRequired())
			{
				if (m_pTreeView->m_pCanvas)
					m_pTreeView->m_pCanvas->setValid(false);
				m_pTreeView->Repaint(false);
			}
		}

		void CCustomTreeViewListItemOwner::NotifyOnBeforeAddItem(IListItem *item, IListItem *parent)
		{
			// Nothing
		}

		void CCustomTreeViewListItemOwner::NotifyOnAddItem(IListItem *item)
		{
			m_pTreeView->LockUpdate();
			m_pTreeView->m_aItems.push_back({ item, true });
			m_pTreeView->m_bItemsSorted = false;
			item->QueryService()->setOwner(m_pTreeView->QueryListItemOwner());
			item->QueryService()->setDPI(m_pTreeView->getDPI());
			if (item->isSelected() && !m_pTreeView->m_bMultiselect)
				item->setSelected(false);
			for (int i = 0; i < item->getItemCount(); i++)
				NotifyOnAddItem(item->getItem(i));
			m_pTreeView->UnlockUpdate();
		}

		void CCustomTreeViewListItemOwner::NotifyOnBeforeDeleteItem(IListItem *item)
		{
			// Nothing
		}

		void CCustomTreeViewListItemOwner::NotifyOnDeleteItem(IListItem *item, IListItem *parent)
		{
			m_pTreeView->LockUpdate();
			for (int i = 0; i < item->getItemCount(); i++)
				NotifyOnDeleteItem(item->getItem(i), item);
			m_pTreeView->SortItems();
			if (item == m_pTreeView->m_pHoveredItem)
				m_pTreeView->m_pHoveredItem = nullptr;
			if (item->isActive() && m_pTreeView->OnDeactivateItem)
				m_pTreeView->OnDeactivateItem(m_pTreeView, item);
			if (item->isSelected() && m_pTreeView->OnDeselectItem)
				m_pTreeView->OnDeselectItem(m_pTreeView, item);
			CCustomTreeView::ITEM s{ item };
			auto pos{ std::lower_bound(m_pTreeView->m_aItems.begin(), m_pTreeView->m_aItems.end(), s, [](const CCustomTreeView::ITEM &a, const CCustomTreeView::ITEM &b) {return a.Item < b.Item; }) };
			m_pTreeView->m_aItems.erase(pos);
			m_pTreeView->UnlockUpdate();
		}

		void CCustomTreeViewListItemOwner::NotifyOnBeforeDeleteItems(IListItem *parent)
		{
			m_pTreeView->LockUpdate();
			for (int i = 0; i < parent->getItemCount(); i++)
				NotifyOnDeleteItem(parent->getItem(i), parent);
			m_pTreeView->m_pHoveredItem = nullptr;
			if (m_pTreeView->m_eHoveredElement == CCustomTreeView::Element::Item || m_pTreeView->m_eHoveredElement == CCustomTreeView::Element::Folder)
				m_pTreeView->m_eHoveredElement = CCustomTreeView::Element::None;
			m_pTreeView->UnlockUpdate();
		}

		void CCustomTreeViewListItemOwner::NotifyOnDeleteItems(IListItem *parent)
		{
			// Nothing
		}

		void CCustomTreeViewListItemOwner::NotifyOnShow(IListItem *item)
		{
			m_pTreeView->LockUpdate();
			m_pTreeView->UnlockUpdate();
		}

		void CCustomTreeViewListItemOwner::NotifyOnHide(IListItem *item)
		{
			m_pTreeView->LockUpdate();
			m_pTreeView->UnlockUpdate();
		}

		void CCustomTreeViewListItemOwner::NotifyOnEnable(IListItem *item)
		{
			if (m_pTreeView->m_pCanvas)
				m_pTreeView->m_pCanvas->setValid(false);
			m_pTreeView->Repaint(false);
		}

		void CCustomTreeViewListItemOwner::NotifyOnDisable(IListItem *item)
		{
			if (m_pTreeView->m_pCanvas)
				m_pTreeView->m_pCanvas->setValid(false);
			m_pTreeView->Repaint(false);
		}

		void CCustomTreeViewListItemOwner::NotifyOnSelect(IListItem *item)
		{
			if (!m_pTreeView->m_bMultiselect)
				m_pTreeView->DeselectAllExceptItem(&m_pTreeView->m_cRootItem, item);
			if (m_pTreeView->OnSelectItem)
				m_pTreeView->OnSelectItem(m_pTreeView, item);
			if (m_pTreeView->m_pCanvas)
				m_pTreeView->m_pCanvas->setValid(false);
			m_pTreeView->Repaint(false);
		}

		void CCustomTreeViewListItemOwner::NotifyOnDeselect(IListItem *item)
		{
			if (!isIgnoreDeselect())
			{
				if (m_pTreeView->OnDeselectItem)
					m_pTreeView->OnDeselectItem(m_pTreeView, item);
				if (m_pTreeView->m_pCanvas)
					m_pTreeView->m_pCanvas->setValid(false);
				m_pTreeView->Repaint(false);
			}
			else if (m_pTreeView->OnDeselectItem)
				m_pTreeView->OnDeselectItem(m_pTreeView, item);
		}

		void CCustomTreeViewListItemOwner::NotifyOnActivate(IListItem *item)
		{
			CLockRepaint lock(m_pTreeView);
			setIgnoreDeactivate(true);
			m_pTreeView->DeactivateAllExceptItem(&m_pTreeView->m_cRootItem, item);
			if (m_pTreeView->OnActivateItem)
				m_pTreeView->OnActivateItem(m_pTreeView, item);
			setIgnoreDeactivate(false);
			if (m_pTreeView->m_pCanvas)
				m_pTreeView->m_pCanvas->setValid(false);
			m_pTreeView->Repaint(false);
		}

		void CCustomTreeViewListItemOwner::NotifyOnDeactivate(IListItem *item)
		{
			if (!isIgnoreDeactivate())
			{
				if (m_pTreeView->OnDeactivateItem)
					m_pTreeView->OnDeactivateItem(m_pTreeView, item);
				if (m_pTreeView->m_pCanvas)
					m_pTreeView->m_pCanvas->setValid(false);
				m_pTreeView->Repaint(false);
			} else if (m_pTreeView->OnDeactivateItem)
				m_pTreeView->OnDeactivateItem(m_pTreeView, item);
		}
	#pragma endregion
	}
}