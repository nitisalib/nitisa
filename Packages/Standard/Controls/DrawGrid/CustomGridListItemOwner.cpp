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
		CCustomGrid::COwner::COwner(CCustomGrid *control) :
			CListItemOwner(),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CCustomGrid::COwner::getControl()
		{
			return m_pControl;
		}

		IRenderer *CCustomGrid::COwner::getRenderer()
		{
			if (m_pControl->getForm())
				return m_pControl->getForm()->getRenderer();
			return nullptr;
		}

		IFont *CCustomGrid::COwner::getFont(IListItem *item)
		{
			return m_pControl->getFont();
		}

		IStyle *CCustomGrid::COwner::getStyle(IListItem *item)
		{
			return m_pControl->getStyle();
		}
	#pragma endregion

	#pragma region Notifications
		void CCustomGrid::COwner::NotifyOnSizeChange(IListItem *item)
		{
			if (!m_pControl->m_bIgnoreItems)
			{
				Point coords{ m_pControl->FindItemCoords(item) };
				if (coords.X >= 0 && (m_pControl->m_aRows[coords.Y].Autosize || m_pControl->m_aColumns[coords.X].Autosize))
					m_pControl->Update();
				else
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
		}

		void CCustomGrid::COwner::NotifyOnRepaintRequired(IListItem *item)
		{
			if (!m_pControl->m_bIgnoreItems)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CCustomGrid::COwner::NotifyOnBeforeAddItem(IListItem *item, IListItem *parent)
		{
			// Hierarchy is not used
		}

		void CCustomGrid::COwner::NotifyOnAddItem(IListItem *item)
		{
			// Hierarchy is not used
		}

		void CCustomGrid::COwner::NotifyOnBeforeDeleteItem(IListItem *item)
		{
			// Hierarchy is not used
		}

		void CCustomGrid::COwner::NotifyOnDeleteItem(IListItem *item, IListItem *parent)
		{
			// Hierarchy is not used
		}

		void CCustomGrid::COwner::NotifyOnBeforeDeleteItems(IListItem *parent)
		{
			// Hierarchy is not used
		}

		void CCustomGrid::COwner::NotifyOnDeleteItems(IListItem *parent)
		{
			// Hierarchy is not used
		}

		void CCustomGrid::COwner::NotifyOnShow(IListItem *item)
		{
			// Not supported
		}

		void CCustomGrid::COwner::NotifyOnHide(IListItem *item)
		{
			// Not supported
		}

		void CCustomGrid::COwner::NotifyOnEnable(IListItem *item)
		{
			if (!m_pControl->m_bIgnoreItems)
			{
				m_pControl->m_bIgnoreItems = true;
				Point coords{ m_pControl->FindItemCoords(item) };
				m_pControl->EnableCell(coords.X, coords.Y, cast<ICustomGridService*>(m_pControl->QueryService()));
				m_pControl->m_bIgnoreItems = false;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CCustomGrid::COwner::NotifyOnDisable(IListItem *item)
		{
			if (!m_pControl->m_bIgnoreItems)
			{
				m_pControl->m_bIgnoreItems = true;
				ICustomGridService *service{ cast<ICustomGridService*>(m_pControl->QueryService()) };
				Point coords{ m_pControl->FindItemCoords(item) };
				m_pControl->DisableCell(coords.X, coords.Y, service);
				m_pControl->DeactivateCell(coords.X, coords.Y, service);
				m_pControl->m_sActiveCell = { -1, -1 };
				m_pControl->m_bIgnoreItems = false;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CCustomGrid::COwner::NotifyOnSelect(IListItem *item)
		{
			if (!m_pControl->m_bIgnoreItems)
			{
				m_pControl->m_bIgnoreItems = true;
				ICustomGridService *service{ cast<ICustomGridService*>(m_pControl->QueryService()) };
				if (!m_pControl->m_bMultiselect)
					for (int y = 0; y < (int)m_pControl->m_aRows.size(); y++)
						for (int x = 0; x < (int)m_pControl->m_aColumns.size(); x++)
							if (m_pControl->m_aCells[y][x].Selected && m_pControl->m_aCells[y][x].Item != item)
								m_pControl->DeselectCell(x, y, service);
				Point coords{ m_pControl->FindItemCoords(item) };
				m_pControl->SelectCell(coords.X, coords.Y, service);
				m_pControl->m_bIgnoreItems = false;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CCustomGrid::COwner::NotifyOnDeselect(IListItem *item)
		{
			if (!m_pControl->m_bIgnoreItems)
			{
				m_pControl->m_bIgnoreItems = true;
				Point coords{ m_pControl->FindItemCoords(item) };
				m_pControl->DeselectCell(coords.X, coords.Y, cast<ICustomGridService*>(m_pControl->QueryService()));
				m_pControl->m_bIgnoreItems = false;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CCustomGrid::COwner::NotifyOnActivate(IListItem *item)
		{
			if (!m_pControl->m_bIgnoreItems)
			{
				m_pControl->m_bIgnoreItems = true;
				ICustomGridService *service{ cast<ICustomGridService*>(m_pControl->QueryService()) };
				Point coords{ m_pControl->FindItemCoords(item) };
				if (m_pControl->m_sActiveCell.X >= 0)
					m_pControl->DeactivateCell(m_pControl->m_sActiveCell.X, m_pControl->m_sActiveCell.Y, service);
				m_pControl->ActivateCell(coords.X, coords.Y, service);
				m_pControl->m_sActiveCell = coords;
				m_pControl->m_sSelectTo = coords;
				m_pControl->m_bIgnoreItems = false;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CCustomGrid::COwner::NotifyOnDeactivate(IListItem *item)
		{
			if (!m_pControl->m_bIgnoreItems)
			{
				m_pControl->m_bIgnoreItems = true;
				Point coords{ m_pControl->FindItemCoords(item) };
				m_pControl->DeactivateCell(coords.X, coords.Y, cast<ICustomGridService*>(m_pControl->QueryService()));
				m_pControl->m_sActiveCell = { -1, -1 };
				m_pControl->m_sSelectTo = { -1, -1 };
				m_pControl->m_bIgnoreItems = false;
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion
	}
}