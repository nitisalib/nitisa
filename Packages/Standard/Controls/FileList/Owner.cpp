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
		CFileList::COwner::COwner(CFileList *filelist) :
			CListItemOwner(),
			m_pFileList{ filelist }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CFileList::COwner::getControl()
		{
			return m_pFileList;
		}

		IRenderer *CFileList::COwner::getRenderer()
		{
			if (m_pFileList->getForm())
				return m_pFileList->getForm()->getRenderer();
			return nullptr;
		}

		IFont *CFileList::COwner::getFont(IListItem *item)
		{
			return m_pFileList->getFont();
		}

		IStyle *CFileList::COwner::getStyle(IListItem *item)
		{
			return m_pFileList->getStyle();
		}
	#pragma endregion

	#pragma region Notifications
		void CFileList::COwner::NotifyOnSizeChange(IListItem *item)
		{
			// Not used
		}

		void CFileList::COwner::NotifyOnRepaintRequired(IListItem *item)
		{
			if (m_pFileList->m_pCanvas)
				m_pFileList->m_pCanvas->setValid(false);
			m_pFileList->Repaint(false);
		}

		void CFileList::COwner::NotifyOnBeforeAddItem(IListItem *item, IListItem *parent)
		{
			// Nothing. Children are not supported
		}

		void CFileList::COwner::NotifyOnAddItem(IListItem *item)
		{
			item->QueryService()->setOwner(&m_pFileList->m_cOwner);
			item->QueryService()->setDPI(m_pFileList->getDPI());
		}

		void CFileList::COwner::NotifyOnBeforeDeleteItem(IListItem *item)
		{
			// Nothing. Children are not supported
		}

		void CFileList::COwner::NotifyOnDeleteItem(IListItem *item, IListItem *parent)
		{
			// Nothing. Children are not supported
		}

		void CFileList::COwner::NotifyOnBeforeDeleteItems(IListItem *parent)
		{
			// Nothing. Children are not supported
		}

		void CFileList::COwner::NotifyOnDeleteItems(IListItem *parent)
		{
			// Nothing. Children are not supported
		}

		void CFileList::COwner::NotifyOnShow(IListItem *item)
		{
			// Nothing. All items are visible independing on visibility state
		}

		void CFileList::COwner::NotifyOnHide(IListItem *item)
		{
			// Nothing. All items are visible independing on visibility state
		}

		void CFileList::COwner::NotifyOnEnable(IListItem *item)
		{
			// Not used
		}

		void CFileList::COwner::NotifyOnDisable(IListItem *item)
		{
			// Not used
		}

		void CFileList::COwner::NotifyOnSelect(IListItem *item)
		{
			if (!isIgnoreSelect())
			{
				CLockRepaint lock{ m_pFileList };
				if (!m_pFileList->m_bMultiselect)
					for (auto pos = m_pFileList->m_aItems.begin(); pos != m_pFileList->m_aItems.end(); pos++)
						if (*pos != item && (*pos)->isSelected())
							(*pos)->setSelected(false);
				if (m_pFileList->OnSelect)
					m_pFileList->OnSelect(m_pFileList, cast<IListItemLabel*>(item)->getCaption());
				if (m_pFileList->m_pCanvas)
					m_pFileList->m_pCanvas->setValid(false);
				m_pFileList->Repaint(false);
			}
			else if (m_pFileList->OnSelect)
				m_pFileList->OnSelect(m_pFileList, cast<IListItemLabel*>(item)->getCaption());
		}

		void CFileList::COwner::NotifyOnDeselect(IListItem *item)
		{
			if (!isIgnoreSelect())
			{
				if (m_pFileList->OnDeselect)
					m_pFileList->OnDeselect(m_pFileList, cast<IListItemLabel*>(item)->getCaption());
				if (m_pFileList->m_pCanvas)
					m_pFileList->m_pCanvas->setValid(false);
				m_pFileList->Repaint(false);
			}
			else if (m_pFileList->OnDeselect)
				m_pFileList->OnDeselect(m_pFileList, cast<IListItemLabel*>(item)->getCaption());
		}

		void CFileList::COwner::NotifyOnActivate(IListItem *item)
		{
			if (!isIgnoreActivate())
			{
				CLockRepaint lock{ m_pFileList };
				int index{ 0 };
				for (auto pos = m_pFileList->m_aItems.begin(); pos != m_pFileList->m_aItems.end(); pos++, index++)
					if (*pos != item && (*pos)->isActive())
						(*pos)->setActive(false);
					else if (*pos == item)
						m_pFileList->m_iActiveIndex = index;
				if (m_pFileList->OnActivate)
					m_pFileList->OnActivate(m_pFileList, cast<IListItemLabel*>(item)->getCaption());
				if (m_pFileList->m_pCanvas)
					m_pFileList->m_pCanvas->setValid(false);
				m_pFileList->Repaint(false);
			}
			else if (m_pFileList->OnActivate)
				m_pFileList->OnActivate(m_pFileList, cast<IListItemLabel*>(item)->getCaption());
		}

		void CFileList::COwner::NotifyOnDeactivate(IListItem *item)
		{
			if (!isIgnoreActivate())
			{
				CLockRepaint lock{ m_pFileList };
				if (m_pFileList->m_iActiveIndex >= 0 && m_pFileList->getItemIndex(item) == m_pFileList->m_iActiveIndex)
					m_pFileList->m_iActiveIndex = -1;
				if (m_pFileList->OnDeactivate)
					m_pFileList->OnDeactivate(m_pFileList, cast<IListItemLabel*>(item)->getCaption());
				if (m_pFileList->m_pCanvas)
					m_pFileList->m_pCanvas->setValid(false);
				m_pFileList->Repaint(false);
			}
			else if (m_pFileList->OnDeactivate)
				m_pFileList->OnDeactivate(m_pFileList, cast<IListItemLabel*>(item)->getCaption());
		}
	#pragma endregion
	}
}