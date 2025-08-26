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
		CCustomListBox::CCustomListBoxListItemOwner::CCustomListBoxListItemOwner(CCustomListBox *listbox) :
			CListItemOwner(),
			m_pListBox{ listbox }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CCustomListBox::CCustomListBoxListItemOwner::getControl()
		{
			return m_pListBox;
		}

		IRenderer *CCustomListBox::CCustomListBoxListItemOwner::getRenderer()
		{
			if (m_pListBox->getForm())
				return m_pListBox->getForm()->getRenderer();
			return nullptr;
		}

		IFont *CCustomListBox::CCustomListBoxListItemOwner::getFont(IListItem *item)
		{
			return m_pListBox->getFont();
		}

		IStyle *CCustomListBox::CCustomListBoxListItemOwner::getStyle(IListItem *item)
		{
			return m_pListBox->getStyle();
		}
	#pragma endregion

	#pragma region Notifications
		void CCustomListBox::CCustomListBoxListItemOwner::NotifyOnSizeChange(IListItem *item)
		{
			if (!isIgnoreSizeChange() && !item->getParent())
			{
				m_pListBox->m_bSorted = false;
				m_pListBox->UpdateList();
				m_pListBox->UpdateHoveredItem();
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
		}

		void CCustomListBox::CCustomListBoxListItemOwner::NotifyOnRepaintRequired(IListItem *item)
		{
			if (!item->getParent())
			{
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
		}

		void CCustomListBox::CCustomListBoxListItemOwner::NotifyOnBeforeAddItem(IListItem *item, IListItem *parent)
		{
			// Nothing. Children are not supported
		}

		void CCustomListBox::CCustomListBoxListItemOwner::NotifyOnAddItem(IListItem *item)
		{
			item->QueryService()->setOwner(m_pListBox->QueryListItemOwner());
			item->QueryService()->setDPI(m_pListBox->getDPI());
		}

		void CCustomListBox::CCustomListBoxListItemOwner::NotifyOnBeforeDeleteItem(IListItem *item)
		{
			// Nothing. Children are not supported
		}

		void CCustomListBox::CCustomListBoxListItemOwner::NotifyOnDeleteItem(IListItem *item, IListItem *parent)
		{
			// Nothing. Children are not supported
		}

		void CCustomListBox::CCustomListBoxListItemOwner::NotifyOnBeforeDeleteItems(IListItem *parent)
		{
			// Nothing. Children are not supported
		}

		void CCustomListBox::CCustomListBoxListItemOwner::NotifyOnDeleteItems(IListItem *parent)
		{
			// Nothing. Children are not supported
		}

		void CCustomListBox::CCustomListBoxListItemOwner::NotifyOnShow(IListItem *item)
		{
			// Nothing. All items are visible independing on visibility state
		}

		void CCustomListBox::CCustomListBoxListItemOwner::NotifyOnHide(IListItem *item)
		{
			// Nothing. All items are visible independing on visibility state
		}

		void CCustomListBox::CCustomListBoxListItemOwner::NotifyOnEnable(IListItem *item)
		{
			if (!isIgnoreEnable() && !item->getParent())
			{
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
		}

		void CCustomListBox::CCustomListBoxListItemOwner::NotifyOnDisable(IListItem *item)
		{
			if (!isIgnoreEnable() && !item->getParent())
			{
				if (m_pListBox->m_iActiveIndex >= 0 && m_pListBox->getItemIndex(item) == m_pListBox->m_iActiveIndex)
				{
					setIgnoreActivate(true);
					m_pListBox->m_iActiveIndex = -1;
					item->setActive(false);
					setIgnoreActivate(false);
				}
				if (item->isSelected())
				{
					setIgnoreSelect(true);
					item->setSelected(false);
					setIgnoreSelect(false);
				}
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
		}

		void CCustomListBox::CCustomListBoxListItemOwner::NotifyOnSelect(IListItem *item)
		{
			if (!isIgnoreSelect() && !item->getParent())
			{
				CLockRepaint lock{ m_pListBox };
				if (!m_pListBox->m_bMultiselect)
					for (auto pos = m_pListBox->m_aItems.begin(); pos != m_pListBox->m_aItems.end(); pos++)
						if (*pos != item && (*pos)->isSelected())
							(*pos)->setSelected(false);
				if (m_pListBox->OnSelect)
					m_pListBox->OnSelect(m_pListBox, item);
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
			else if (isIgnoreSelect() && !item->getParent() && m_pListBox->OnSelect)
				m_pListBox->OnSelect(m_pListBox, item);
		}

		void CCustomListBox::CCustomListBoxListItemOwner::NotifyOnDeselect(IListItem *item)
		{
			if (!isIgnoreSelect() && !item->getParent())
			{
				if (m_pListBox->OnDeselect)
					m_pListBox->OnDeselect(m_pListBox, item);
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
			else if (isIgnoreSelect() && !item->getParent() && m_pListBox->OnDeselect)
				m_pListBox->OnDeselect(m_pListBox, item);
		}

		void CCustomListBox::CCustomListBoxListItemOwner::NotifyOnActivate(IListItem *item)
		{
			if (!isIgnoreActivate() && !item->getParent())
			{
				CLockRepaint lock{ m_pListBox };
				int index{ 0 };
				for (auto pos = m_pListBox->m_aItems.begin(); pos != m_pListBox->m_aItems.end(); pos++, index++)
					if (*pos != item && (*pos)->isActive())
						(*pos)->setActive(false);
					else if (*pos == item)
						m_pListBox->m_iActiveIndex = index;
				if (m_pListBox->OnActivate)
					m_pListBox->OnActivate(m_pListBox, m_pListBox->m_iActiveIndex);
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
			else if (isIgnoreActivate() && !item->getParent() && m_pListBox->OnActivate)
				m_pListBox->OnActivate(m_pListBox, m_pListBox->getItemIndex(item));
		}

		void CCustomListBox::CCustomListBoxListItemOwner::NotifyOnDeactivate(IListItem *item)
		{
			if (!isIgnoreActivate() && !item->getParent())
			{
				CLockRepaint lock{ m_pListBox };
				if (m_pListBox->m_iActiveIndex >= 0 && m_pListBox->getItemIndex(item) == m_pListBox->m_iActiveIndex)
					m_pListBox->m_iActiveIndex = -1;
				if (m_pListBox->m_pCanvas)
					m_pListBox->m_pCanvas->setValid(false);
				m_pListBox->Repaint(false);
			}
		}
	#pragma endregion
	}
}