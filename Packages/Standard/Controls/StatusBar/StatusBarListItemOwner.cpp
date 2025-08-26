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
		CStatusBar::CStatusBarListItemOwner::CStatusBarListItemOwner(CStatusBar *statusbar) :
			m_pStatusBar{ statusbar }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CStatusBar::CStatusBarListItemOwner::getControl()
		{
			return m_pStatusBar;
		}

		IRenderer *CStatusBar::CStatusBarListItemOwner::getRenderer()
		{
			if (m_pStatusBar->getForm())
				return m_pStatusBar->getForm()->getRenderer();
			return nullptr;
		}

		IFont *CStatusBar::CStatusBarListItemOwner::getFont(IListItem *item)
		{
			return m_pStatusBar->getFont();
		}

		IStyle *CStatusBar::CStatusBarListItemOwner::getStyle(IListItem *item)
		{
			return m_pStatusBar->getStyle();
		}
	#pragma endregion

	#pragma region Notifications
		void CStatusBar::CStatusBarListItemOwner::NotifyOnSizeChange(IListItem *item)
		{
			CLockRepaint lock{ m_pStatusBar };
			m_pStatusBar->Update();
			if (m_pStatusBar->m_pCanvas)
				m_pStatusBar->m_pCanvas->setValid(false);
			m_pStatusBar->Repaint(false);
		}

		void CStatusBar::CStatusBarListItemOwner::NotifyOnRepaintRequired(IListItem *item)
		{
			if (m_pStatusBar->m_pCanvas)
				m_pStatusBar->m_pCanvas->setValid(false);
			m_pStatusBar->Repaint(false);
		}

		void CStatusBar::CStatusBarListItemOwner::NotifyOnBeforeAddItem(IListItem *item, IListItem *parent)
		{
			// Subitems are not allowed
		}

		void CStatusBar::CStatusBarListItemOwner::NotifyOnAddItem(IListItem *item)
		{
			item->QueryService()->setOwner(m_pStatusBar->QueryListItemOwner());
			item->QueryService()->setDPI(m_pStatusBar->getDPI());
		}

		void CStatusBar::CStatusBarListItemOwner::NotifyOnBeforeDeleteItem(IListItem *item)
		{
			// Subitems are not allowed
		}

		void CStatusBar::CStatusBarListItemOwner::NotifyOnDeleteItem(IListItem *item, IListItem *parent)
		{
			// Subitems are not allowed
		}

		void CStatusBar::CStatusBarListItemOwner::NotifyOnBeforeDeleteItems(IListItem *parent)
		{
			// Subitems are not allowed
		}

		void CStatusBar::CStatusBarListItemOwner::NotifyOnDeleteItems(IListItem *parent)
		{
			// Subitems are not allowed
		}

		void CStatusBar::CStatusBarListItemOwner::NotifyOnShow(IListItem *item)
		{
			CLockRepaint lock{ m_pStatusBar };
			if (m_pStatusBar->Update())
			{
				if (m_pStatusBar->m_pCanvas)
					m_pStatusBar->m_pCanvas->setValid(false);
				m_pStatusBar->Repaint(false);
			}
		}

		void CStatusBar::CStatusBarListItemOwner::NotifyOnHide(IListItem *item)
		{
			CLockRepaint lock{ m_pStatusBar };
			if (m_pStatusBar->Update())
			{
				if (m_pStatusBar->m_pCanvas)
					m_pStatusBar->m_pCanvas->setValid(false);
				m_pStatusBar->Repaint(false);
			}
		}

		void CStatusBar::CStatusBarListItemOwner::NotifyOnEnable(IListItem *item)
		{
			if (item->isVisible())
			{
				if (m_pStatusBar->m_pCanvas)
					m_pStatusBar->m_pCanvas->setValid(false);
				m_pStatusBar->Repaint(false);
			}
		}

		void CStatusBar::CStatusBarListItemOwner::NotifyOnDisable(IListItem *item)
		{
			if (item->isVisible())
			{
				if (m_pStatusBar->m_pCanvas)
					m_pStatusBar->m_pCanvas->setValid(false);
				m_pStatusBar->Repaint(false);
			}
		}

		void CStatusBar::CStatusBarListItemOwner::NotifyOnSelect(IListItem *item)
		{
			if (item->isVisible())
			{
				if (m_pStatusBar->m_pCanvas)
					m_pStatusBar->m_pCanvas->setValid(false);
				m_pStatusBar->Repaint(false);
			}
		}

		void CStatusBar::CStatusBarListItemOwner::NotifyOnDeselect(IListItem *item)
		{
			if (item->isVisible())
			{
				if (m_pStatusBar->m_pCanvas)
					m_pStatusBar->m_pCanvas->setValid(false);
				m_pStatusBar->Repaint(false);
			}
		}

		void CStatusBar::CStatusBarListItemOwner::NotifyOnActivate(IListItem *item)
		{
			if (item->isVisible())
			{
				if (m_pStatusBar->m_pCanvas)
					m_pStatusBar->m_pCanvas->setValid(false);
				m_pStatusBar->Repaint(false);
			}
		}

		void CStatusBar::CStatusBarListItemOwner::NotifyOnDeactivate(IListItem *item)
		{
			if (item->isVisible())
			{
				if (m_pStatusBar->m_pCanvas)
					m_pStatusBar->m_pCanvas->setValid(false);
				m_pStatusBar->Repaint(false);
			}
		}
	#pragma endregion
	}
}