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
	CControlItemList::CControlItemList(const String &class_name, const bool accept_form, const bool accept_control, const bool accept_controls, const bool accept_focus, const bool accept_modal,
		const bool tab_stop, const Point &design_dpi) :
		CControl(class_name, accept_form, accept_control, accept_controls, accept_focus, accept_modal, tab_stop, design_dpi)
	{

	}

	void CControlItemList::BeforeRelease()
	{
		DeleteItems();
		CControl::BeforeRelease();
	}
#pragma endregion

#pragma region Getters
	int CControlItemList::getItemCount()
	{
		return (int)m_aItems.size();
	}

	IListItem *CControlItemList::getItem(const int index)
	{
		if (index >= 0 && index < (int)m_aItems.size())
		{
			SortItems();
			return m_aItems[index];
		}
		return nullptr;
	}

	int CControlItemList::getItemIndex(IListItem *item)
	{
		SortItems();
		for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			if (*pos == item)
				return int(pos - m_aItems.begin());
		return -1;
	}

	bool CControlItemList::isAcceptItem(IListItem *item)
	{
		return true;
	}
#pragma endregion

#pragma region Items
	void CControlItemList::SortItems()
	{
		// Do nothing. Derived class should manage sorting if supports and requires
	}

	bool CControlItemList::AddItem(IListItem *item)
	{
		return InsertItem(item, (int)m_aItems.size());
	}

	bool CControlItemList::InsertItem(IListItem *item, const int before)
	{
		if (item && isAcceptItem(item) && !item->getParent() && !item->QueryService()->getOwner())
		{
			SortItems();
			item->setActive(false);
			item->setSelected(false);
			item->QueryService()->setHovered(false);
			if (before <= 0)
				m_aItems.insert(m_aItems.begin(), item);
			else if (before >= (int)m_aItems.size())
				m_aItems.push_back(item);
			else
				m_aItems.insert(m_aItems.begin() + before, item);
			return true;
		}
		return false;
	}

	bool CControlItemList::DeleteItem(const int index)
	{
		if (index >= 0 && index < (int)m_aItems.size())
		{
			SortItems();
			m_aItems[index]->Release();
			m_aItems.erase(m_aItems.begin() + index);
			return true;
		}
		return false;
	}

	bool CControlItemList::DeleteItem(IListItem *item)
	{
		if (item)
			for (size_t i = 0; i < m_aItems.size(); i++)
				if (m_aItems[i] == item)
					return DeleteItem((int)i);
		return false;
	}

	bool CControlItemList::DeleteItems()
	{
		if (m_aItems.size() > 0)
		{
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				(*pos)->Release();
			m_aItems.clear();
			return true;
		}
		return false;
	}
#pragma endregion
}