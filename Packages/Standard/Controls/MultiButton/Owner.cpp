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
	#pragma region Constructor & destrictor
		CMultiButton::COwner::COwner(CMultiButton *control):
			CListItemOwner(),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CMultiButton::COwner::getControl()
		{
			return m_pControl;
		}

		IRenderer *CMultiButton::COwner::getRenderer()
		{
			if (m_pControl->getForm())
				return m_pControl->getForm()->getRenderer();
			return nullptr;
		}

		IFont *CMultiButton::COwner::getFont(IListItem *item)
		{
			return m_pControl->getFont();
		}

		IStyle *CMultiButton::COwner::getStyle(IListItem *item)
		{
			return m_pControl->getStyle();
		}
	#pragma endregion

	#pragma region Notifications
		void CMultiButton::COwner::NotifyOnSizeChange(IListItem *item)
		{
			// Do nothing
		}

		void CMultiButton::COwner::NotifyOnRepaintRequired(IListItem *item)
		{
			if (m_pControl->m_bHasExtra || item == m_pControl->getActiveButton())
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CMultiButton::COwner::NotifyOnBeforeAddItem(IListItem *item, IListItem *parent)
		{
			// Do nothing
		}

		void CMultiButton::COwner::NotifyOnAddItem(IListItem *item)
		{
			// Do nothing
		}

		void CMultiButton::COwner::NotifyOnBeforeDeleteItem(IListItem *item)
		{
			// Do nothing
		}

		void CMultiButton::COwner::NotifyOnDeleteItem(IListItem *item, IListItem *parent)
		{
			// Do nothing
		}

		void CMultiButton::COwner::NotifyOnBeforeDeleteItems(IListItem *parent)
		{
			// Do nothing
		}

		void CMultiButton::COwner::NotifyOnDeleteItems(IListItem *parent)
		{
			// Do nothing
		}

		void CMultiButton::COwner::NotifyOnShow(IListItem *item)
		{
			// Do nothing
		}

		void CMultiButton::COwner::NotifyOnHide(IListItem *item)
		{
			// Do nothing
		}

		void CMultiButton::COwner::NotifyOnEnable(IListItem *item)
		{
			// Do nothing
		}

		void CMultiButton::COwner::NotifyOnDisable(IListItem *item)
		{
			// Do nothing
		}

		void CMultiButton::COwner::NotifyOnSelect(IListItem *item)
		{
			// Do nothing
		}

		void CMultiButton::COwner::NotifyOnDeselect(IListItem *item)
		{
			// Do nothing
		}

		void CMultiButton::COwner::NotifyOnActivate(IListItem *item)
		{
			// Do nothing
		}

		void CMultiButton::COwner::NotifyOnDeactivate(IListItem *item)
		{
			// Do nothing
		}
	#pragma endregion
	}
}