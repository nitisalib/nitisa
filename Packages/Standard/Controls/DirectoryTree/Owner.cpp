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
		CDirectoryTree::COwner::COwner(CDirectoryTree *directory_tree) :
			m_pDirectoryTree{ directory_tree }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CDirectoryTree::COwner::getControl()
		{
			return m_pDirectoryTree;
		}

		IRenderer *CDirectoryTree::COwner::getRenderer()
		{
			if (m_pDirectoryTree->getForm())
				return m_pDirectoryTree->getForm()->getRenderer();
			return nullptr;
		}

		IFont *CDirectoryTree::COwner::getFont(IListItem *item)
		{
			return m_pDirectoryTree->getFont();
		}

		IStyle *CDirectoryTree::COwner::getStyle(IListItem *item)
		{
			return m_pDirectoryTree->getStyle();
		}

		ITexture *CDirectoryTree::COwner::getIcon(IListItemIcon *item, RectF &part)
		{
			if (m_pDirectoryTree->getForm() && m_pDirectoryTree->getForm()->getRenderer())
			{
				String name{ m_pDirectoryTree->m_sClassName + L".Icon." };
				if (m_pDirectoryTree->m_aItems[m_pDirectoryTree->FindItemIndex(item)].Folded)
					name += L"Closed";
				else
					name += L"Opened";
				if (m_pDirectoryTree->getStyle())
				{
					IStyleSkin *skin{ m_pDirectoryTree->getStyle()->getSkin(name) };
					if (skin && skin->getImage())
					{
						part = skin->Rect;
						return m_pDirectoryTree->getForm()->getRenderer()->CreateTextureFromImage(skin->getImage()->Image, 1, TextureFormat::RGBA, true);
					}
				}
				if (Application->Styles->getStyle(0))
				{
					IStyleSkin *skin{ Application->Styles->getStyle(0)->getSkin(name) };
					if (skin && skin->getImage())
					{
						part = skin->Rect;
						return m_pDirectoryTree->getForm()->getRenderer()->CreateTextureFromImage(skin->getImage()->Image, 1, TextureFormat::RGBA, true);
					}
				}
			}
			return nullptr;
		}
	#pragma endregion

	#pragma region Notifications
		void CDirectoryTree::COwner::NotifyOnSizeChange(IListItem *item)
		{
			if (!isIgnoreSizeChange())
			{
				m_pDirectoryTree->LockUpdate();
				m_pDirectoryTree->UnlockUpdate();
			}
		}

		void CDirectoryTree::COwner::NotifyOnRepaintRequired(IListItem *item)
		{
			if (!isIgnoreRepaintRequired())
			{
				if (m_pDirectoryTree->m_pCanvas)
					m_pDirectoryTree->m_pCanvas->setValid(false);
				m_pDirectoryTree->Repaint(false);
			}
		}

		void CDirectoryTree::COwner::NotifyOnBeforeAddItem(IListItem *item, IListItem *parent)
		{
			// Nothing
		}

		void CDirectoryTree::COwner::NotifyOnAddItem(IListItem *item)
		{
			m_pDirectoryTree->m_aItems.push_back({ item, true });
			m_pDirectoryTree->m_bItemsSorted = false;
			item->QueryService()->setOwner(&m_pDirectoryTree->m_cOwner);
			item->QueryService()->setDPI(m_pDirectoryTree->getDPI());
			if (item->isSelected() && !m_pDirectoryTree->m_bMultiselect)
				item->setSelected(false);
			for (int i = 0; i < item->getItemCount(); i++)
				NotifyOnAddItem(item->getItem(i));
		}

		void CDirectoryTree::COwner::NotifyOnBeforeDeleteItem(IListItem *item)
		{
			// Nothing
		}

		void CDirectoryTree::COwner::NotifyOnDeleteItem(IListItem *item, IListItem *parent)
		{
			for (int i = 0; i < item->getItemCount(); i++)
				NotifyOnDeleteItem(item->getItem(i), item);
			m_pDirectoryTree->SortItems();
			if (item == m_pDirectoryTree->m_pHoveredItem)
				m_pDirectoryTree->m_pHoveredItem = nullptr;
			if (item->isActive() && m_pDirectoryTree->OnDeactivateDirectory)
				m_pDirectoryTree->OnDeactivateDirectory(m_pDirectoryTree, m_pDirectoryTree->getItemPath(item));
			if (item->isSelected() && m_pDirectoryTree->OnDeselectDirectory)
				m_pDirectoryTree->OnDeselectDirectory(m_pDirectoryTree, m_pDirectoryTree->getItemPath(item));
			CDirectoryTree::ITEM s{ item };
			auto pos{ std::lower_bound(m_pDirectoryTree->m_aItems.begin(), m_pDirectoryTree->m_aItems.end(), s, [](const CDirectoryTree::ITEM &a, const CDirectoryTree::ITEM &b) {return a.Item < b.Item; }) };
			m_pDirectoryTree->m_aItems.erase(pos);
		}

		void CDirectoryTree::COwner::NotifyOnBeforeDeleteItems(IListItem *parent)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
				NotifyOnDeleteItem(parent->getItem(i), parent);
			m_pDirectoryTree->m_pHoveredItem = nullptr;
			if (m_pDirectoryTree->m_eHoveredElement == CDirectoryTree::Element::Item || m_pDirectoryTree->m_eHoveredElement == CDirectoryTree::Element::Folder)
				m_pDirectoryTree->UpdateHoveredElement();
		}

		void CDirectoryTree::COwner::NotifyOnDeleteItems(IListItem *parent)
		{
			// Nothing
		}

		void CDirectoryTree::COwner::NotifyOnShow(IListItem *item)
		{
			// Not used
		}

		void CDirectoryTree::COwner::NotifyOnHide(IListItem *item)
		{
			// Not used
		}

		void CDirectoryTree::COwner::NotifyOnEnable(IListItem *item)
		{
			// Not used
		}

		void CDirectoryTree::COwner::NotifyOnDisable(IListItem *item)
		{
			// Not used
		}

		void CDirectoryTree::COwner::NotifyOnSelect(IListItem *item)
		{
			if (!m_pDirectoryTree->m_bMultiselect)
				m_pDirectoryTree->DeselectAllExceptItem(&m_pDirectoryTree->m_cRootItem, item);
			if (m_pDirectoryTree->OnSelectDirectory)
				m_pDirectoryTree->OnSelectDirectory(m_pDirectoryTree, m_pDirectoryTree->getItemPath(item));
			if (m_pDirectoryTree->m_pCanvas)
				m_pDirectoryTree->m_pCanvas->setValid(false);
			m_pDirectoryTree->Repaint(false);
		}

		void CDirectoryTree::COwner::NotifyOnDeselect(IListItem *item)
		{
			if (!isIgnoreDeselect())
			{
				if (m_pDirectoryTree->OnDeselectDirectory)
					m_pDirectoryTree->OnDeselectDirectory(m_pDirectoryTree, m_pDirectoryTree->getItemPath(item));
				if (m_pDirectoryTree->m_pCanvas)
					m_pDirectoryTree->m_pCanvas->setValid(false);
				m_pDirectoryTree->Repaint(false);
			}
			else if (m_pDirectoryTree->OnDeselectDirectory)
				m_pDirectoryTree->OnDeselectDirectory(m_pDirectoryTree, m_pDirectoryTree->getItemPath(item));
		}

		void CDirectoryTree::COwner::NotifyOnActivate(IListItem *item)
		{
			CLockRepaint lock(m_pDirectoryTree);
			setIgnoreDeactivate(true);
			m_pDirectoryTree->DeactivateAllExceptItem(&m_pDirectoryTree->m_cRootItem, item);
			m_pDirectoryTree->DoOnActivateItem(item);
			setIgnoreDeactivate(false);
			if (m_pDirectoryTree->m_pCanvas)
				m_pDirectoryTree->m_pCanvas->setValid(false);
			m_pDirectoryTree->Repaint(false);
		}

		void CDirectoryTree::COwner::NotifyOnDeactivate(IListItem *item)
		{
			if (!isIgnoreDeactivate())
			{
				m_pDirectoryTree->DoOnDeactivateItem(item);
				if (m_pDirectoryTree->m_pCanvas)
					m_pDirectoryTree->m_pCanvas->setValid(false);
				m_pDirectoryTree->Repaint(false);
			}
			else
				m_pDirectoryTree->DoOnDeactivateItem(item);
		}
	#pragma endregion
	}
}