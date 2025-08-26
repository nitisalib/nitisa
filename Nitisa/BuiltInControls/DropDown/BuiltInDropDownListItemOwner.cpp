// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	CBuiltInDropDownListItemOwner::CBuiltInDropDownListItemOwner(CBuiltInDropDown *dropdown) :
		CListItemOwner(),
		m_pDropDown{ dropdown }
	{

	}
#pragma endregion

#pragma region Getters
	IControl *CBuiltInDropDownListItemOwner::getControl()
	{
		return m_pDropDown->getControl();
	}

	IRenderer *CBuiltInDropDownListItemOwner::getRenderer()
	{
		if (m_pDropDown->getControl() && m_pDropDown->getControl()->getForm())
			return m_pDropDown->getControl()->getForm()->getRenderer();
		return nullptr;
	}

	IFont *CBuiltInDropDownListItemOwner::getFont(IListItem *item)
	{
		IFont *result{ item->getFont() };
		if (!result && m_pDropDown->getControl())
			result = m_pDropDown->getControl()->getFont();
		return result;
	}

	IStyle *CBuiltInDropDownListItemOwner::getStyle(IListItem *item)
	{
		if (m_pDropDown->getControl())
			return m_pDropDown->getControl()->getStyle();
		return nullptr;
	}
#pragma endregion

#pragma region Notifications
	void CBuiltInDropDownListItemOwner::NotifyOnSizeChange(IListItem *item)
	{
		if (!isIgnoreSizeChange() && m_pDropDown->m_bOpened && !item->getParent())
		{
			m_pDropDown->m_bSorted = false;
			RectF r{ m_pDropDown->getListRenderRect() };
			m_pDropDown->UpdateList();
			m_pDropDown->UpdateHoveredItem();
			if (m_pDropDown->m_pListener)
			{
				if (m_pDropDown->m_pCanvasList)
					m_pDropDown->m_pCanvasList->setValid(false);
				m_pDropDown->m_pListener->NotifyOnRepaint(m_pDropDown, r + m_pDropDown->getListRenderRect());
			}
		}
	}

	void CBuiltInDropDownListItemOwner::NotifyOnRepaintRequired(IListItem *item)
	{
		if (m_pDropDown->m_bOpened && !item->getParent() && m_pDropDown->m_pListener)
		{
			if (m_pDropDown->m_pCanvasList)
				m_pDropDown->m_pCanvasList->setValid(false);
			m_pDropDown->m_pListener->NotifyOnRepaint(m_pDropDown, m_pDropDown->getListRenderRect());
		}
	}

	void CBuiltInDropDownListItemOwner::NotifyOnBeforeAddItem(IListItem *item, IListItem *parent)
	{
		// Nothing. Children are not supported
	}

	void CBuiltInDropDownListItemOwner::NotifyOnAddItem(IListItem *item)
	{
		item->QueryService()->setOwner(m_pDropDown->QueryListItemOwner());
		item->QueryService()->setDPI(m_pDropDown->getDPI());
	}

	void CBuiltInDropDownListItemOwner::NotifyOnBeforeDeleteItem(IListItem *item)
	{
		// Nothing. Children are not supported
	}

	void CBuiltInDropDownListItemOwner::NotifyOnDeleteItem(IListItem *item, IListItem *parent)
	{
		// Nothing. Children are not supported
	}

	void CBuiltInDropDownListItemOwner::NotifyOnBeforeDeleteItems(IListItem *parent)
	{
		// Nothing. Children are not supported
	}

	void CBuiltInDropDownListItemOwner::NotifyOnDeleteItems(IListItem *parent)
	{
		// Nothing. Children are not supported
	}

	void CBuiltInDropDownListItemOwner::NotifyOnShow(IListItem *item)
	{
		// Nothing. All items are visible independent of visibility state
	}

	void CBuiltInDropDownListItemOwner::NotifyOnHide(IListItem *item)
	{
		// Nothing. All items are visible independent of visibility state
	}

	void CBuiltInDropDownListItemOwner::NotifyOnEnable(IListItem *item)
	{
		if (!isIgnoreEnable() && m_pDropDown->m_bOpened && !item->getParent() && m_pDropDown->m_pListener)
		{
			if (m_pDropDown->m_pCanvasList)
				m_pDropDown->m_pCanvasList->setValid(false);
			m_pDropDown->m_pListener->NotifyOnRepaint(m_pDropDown, m_pDropDown->getListRenderRect());
		}
	}

	void CBuiltInDropDownListItemOwner::NotifyOnDisable(IListItem *item)
	{
		if (!isIgnoreDisable() && m_pDropDown->m_bOpened && !item->getParent())
		{
			RectF r{ m_pDropDown->getListRenderRect() };
			if (m_pDropDown->m_iActiveIndex >= 0 && m_pDropDown->getItemIndex(item) == m_pDropDown->m_iActiveIndex)
			{
				setIgnoreDeactivate(true);
				m_pDropDown->m_iActiveIndex = -1;
				item->setActive(false);
				setIgnoreDeactivate(false);
				if (!m_pDropDown->m_bEditable)
				{
					r += m_pDropDown->getControlRenderRect();
					if (m_pDropDown->m_pCanvasControl)
						m_pDropDown->m_pCanvasControl->setValid(false);
				}
			}
			if (m_pDropDown->m_pCanvasList)
				m_pDropDown->m_pCanvasList->setValid(false);
			if (m_pDropDown->m_pListener)
				m_pDropDown->m_pListener->NotifyOnRepaint(m_pDropDown, r);
		}
	}

	void CBuiltInDropDownListItemOwner::NotifyOnSelect(IListItem *item)
	{
		if (!isIgnoreSelect() && item->isVisible() && m_pDropDown->m_bOpened && m_pDropDown->m_pListener)
		{
			if (m_pDropDown->m_pCanvasList)
				m_pDropDown->m_pCanvasList->setValid(false);
			m_pDropDown->m_pListener->NotifyOnRepaint(m_pDropDown, m_pDropDown->getListRenderRect());
		}
	}

	void CBuiltInDropDownListItemOwner::NotifyOnDeselect(IListItem *item)
	{
		if (!isIgnoreDeselect() && item->isVisible() && m_pDropDown->m_bOpened && m_pDropDown->m_pListener)
		{
			if (m_pDropDown->m_pCanvasList)
				m_pDropDown->m_pCanvasList->setValid(false);
			m_pDropDown->m_pListener->NotifyOnRepaint(m_pDropDown, m_pDropDown->getListRenderRect());
		}
	}

	void CBuiltInDropDownListItemOwner::NotifyOnActivate(IListItem *item)
	{
		if (!isIgnoreActivate() && !item->getParent())
		{
			int index{ 0 };
			setIgnoreDeactivate(true);
			for (auto pos = m_pDropDown->m_aItems.begin(); pos != m_pDropDown->m_aItems.end(); pos++, index++)
				if (*pos != item && (*pos)->isActive())
					(*pos)->setActive(false);
				else if (*pos == item)
					m_pDropDown->m_iActiveIndex = index;
			setIgnoreDeactivate(false);
			IBuiltInDropDownListener *listener{ cast<IBuiltInDropDownListener*>(m_pDropDown->m_pListener) };
			if (listener)
				listener->NotifyOnSelect(m_pDropDown, m_pDropDown->m_iActiveIndex);
			if (m_pDropDown->m_pCanvasControl)
				m_pDropDown->m_pCanvasControl->setValid(false);
			if (m_pDropDown->m_pCanvasList)
				m_pDropDown->m_pCanvasList->setValid(false);
			if (m_pDropDown->m_bOpened && m_pDropDown->m_pListener)
				m_pDropDown->m_pListener->NotifyOnRepaint(m_pDropDown, m_pDropDown->getListRenderRect());
		}
	}

	void CBuiltInDropDownListItemOwner::NotifyOnDeactivate(IListItem *item)
	{
		if (!isIgnoreDeactivate() && !item->getParent())
		{
			if (m_pDropDown->m_iActiveIndex >= 0 && m_pDropDown->getItemIndex(item) == m_pDropDown->m_iActiveIndex)
			{
				m_pDropDown->m_iActiveIndex = -1;
				if (!m_pDropDown->m_bEditable)
				{
					if (m_pDropDown->m_pCanvasControl)
						m_pDropDown->m_pCanvasControl->setValid(false);
				}
			}
			if (m_pDropDown->m_pCanvasList)
				m_pDropDown->m_pCanvasList->setValid(false);
			if (m_pDropDown->m_pListener)
				m_pDropDown->m_pListener->NotifyOnRepaint(m_pDropDown, m_pDropDown->getListRenderRect());
		}
	}
#pragma endregion
}