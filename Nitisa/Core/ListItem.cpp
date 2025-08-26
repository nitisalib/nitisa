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
	CListItem::CListItem(const String &class_name, const bool accept_items) :
		CClass(class_name),
		m_sSize{ 0, 0 },
		m_sPosition{ 0, 0 },
		m_bVisible{ true },
		m_bEnabled{ true },
		m_bHovered{ false },
		m_bSelected{ false },
		m_bActive{ false },
		m_pService{ nullptr },
		m_pOwner{ nullptr },
		m_pParent{ nullptr },
		m_bDestroying{ false },
		m_bAcceptItems{ accept_items }
	{

	}

	CListItem::~CListItem()
	{
		m_bDestroying = true;
		DeleteItems();
		if (m_pService)
			m_pService->Release();
	}

	void CListItem::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Getters
	IListItem *CListItem::getParent()
	{
		return m_pParent;
	}

	PointF CListItem::getSize()
	{
		return m_sSize;
	}

	PointF CListItem::getPosition()
	{
		return m_sPosition;
	}

	int CListItem::getItemCount(const bool total)
	{
		int result{ (int)m_aItems.size() };
		if (total)
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				result += (*pos)->getItemCount(true);
		return result;
	}

	IListItem *CListItem::getItem(const int index)
	{
		if (index >= 0 && index < (int)m_aItems.size())
			return m_aItems[index];
		return nullptr;
	}

	IListItem *CListItem::getItem(const String &name)
	{
		for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			if ((*pos)->Name == name)
				return *pos;
		return nullptr;
	}

	IListItem *CListItem::getItem(const PointF &position)
	{
		if (m_bVisible)
		{
			for (auto i : m_aItems)
			{
				IListItem *item{ i->getItem(PointF{position.X - i->getPosition().X, position.Y - i->getPosition().Y}) };
				if (item)
					return item;
			}
			if (position.X >= m_sPosition.X && position.X < m_sPosition.X + m_sSize.X && position.Y >= m_sPosition.Y && position.Y < m_sPosition.Y + m_sSize.Y)
				return this;
		}
		return nullptr;
	}

	int CListItem::getItemIndex(IListItem *item)
	{
		for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			if (*pos == item)
				return int(pos - m_aItems.begin());
		return -1;
	}

	IFont *CListItem::getFont()
	{
		return nullptr;
	}

	bool CListItem::isVisible()
	{
		return m_bVisible;
	}

	bool CListItem::isEnabled()
	{
		return m_bEnabled;
	}

	bool CListItem::isHovered()
	{
		return m_bHovered;
	}

	bool CListItem::isSelected()
	{
		return m_bSelected;
	}

	bool CListItem::isActive()
	{
		return m_bActive;
	}

	bool CListItem::hasItem(IListItem *item)
	{
		if (!item)
			return false;
		for (auto i : m_aItems)
			if (i == item || i->hasItem(item))
				return true;
		return false;
	}

	bool CListItem::isAcceptItems()
	{
		return m_bAcceptItems;
	}

	bool CListItem::isAcceptItem(IListItem *item)
	{
		return m_bAcceptItems;
	}

	IListItemService *CListItem::QueryService()
	{
		if (!m_pService)
			m_pService = new CListItemService(this);
		return m_pService;
	}
#pragma endregion

#pragma region Setters
	bool CListItem::setName(const String &value)
	{
		if (value != m_sName)
		{
			m_sName = value;
			return true;
		}
		return false;
	}

	bool CListItem::setVisible(const bool value)
	{
		if (value != m_bVisible)
		{
			m_bVisible = value;
			if (m_pOwner)
				m_bVisible ? m_pOwner->NotifyOnShow(this) : m_pOwner->NotifyOnHide(this);
			return true;
		}
		return false;
	}

	bool CListItem::setEnabled(const bool value)
	{
		if (value != m_bEnabled)
		{
			m_bEnabled = value;
			if (m_pOwner)
				m_bEnabled ? m_pOwner->NotifyOnEnable(this) : m_pOwner->NotifyOnDisable(this);
			return true;
		}
		return false;
	}

	bool CListItem::setSelected(const bool value)
	{
		if (value != m_bSelected)
		{
			m_bSelected = value;
			if (m_pOwner)
				m_bSelected ? m_pOwner->NotifyOnSelect(this) : m_pOwner->NotifyOnDeselect(this);
			return true;
		}
		return false;
	}

	bool CListItem::setActive(const bool value)
	{
		if (value != m_bActive)
		{
			m_bActive = value;
			if (m_pOwner)
				m_bActive ? m_pOwner->NotifyOnActivate(this) : m_pOwner->NotifyOnDeactivate(this);
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Items
	bool CListItem::AddItem(IListItem *item)
	{
		if (m_bAcceptItems && item && item != this && isAcceptItem(item) && !item->getParent() && !hasItem(item) && !item->hasItem(this))
		{
			if (m_pOwner)
				m_pOwner->NotifyOnBeforeAddItem(item, this);
			m_aItems.push_back(item);
			item->QueryService()->setParent(this);
			if (m_pOwner)
				m_pOwner->NotifyOnAddItem(item);
			return true;
		}
		return false;
	}

	bool CListItem::InsertItem(IListItem *item, const int before)
	{
		if (m_bAcceptItems && item && item != this && isAcceptItem(item) && before >= 0 && !item->getParent() && !hasItem(item) && !item->hasItem(this))
		{
			if (m_pOwner)
				m_pOwner->NotifyOnBeforeAddItem(item, this);
			if (before <= (int)m_aItems.size() - 1)
				m_aItems.insert(m_aItems.begin() + before, item);
			else
				m_aItems.push_back(item);
			item->QueryService()->setParent(this);
			if (m_pOwner)
				m_pOwner->NotifyOnAddItem(item);
			return true;
		}
		return false;
	}

	bool CListItem::DeleteItem(const int index)
	{
		if (index >= 0 && index < (int)m_aItems.size())
		{
			IListItem *item{ m_aItems[index] };
			if (m_pOwner)
				m_pOwner->NotifyOnBeforeDeleteItem(m_aItems[index]);
			m_aItems.erase(m_aItems.begin() + index);
			if (m_pOwner)
				m_pOwner->NotifyOnDeleteItem(item, this);
			item->Release();
			return true;
		}
		return false;
	}

	bool CListItem::DeleteItem(IListItem *item)
	{
		for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			if (*pos == item)
				return DeleteItem(int(pos - m_aItems.begin()));
		return false;
	}

	bool CListItem::DeleteItems()
	{
		if (m_aItems.size() > 0)
		{
			if (!m_bDestroying && m_pOwner)
				m_pOwner->NotifyOnBeforeDeleteItems(this);
			for (auto pos : m_aItems)
				pos->Release();
			m_aItems.clear();
			if (!m_bDestroying && m_pOwner)
				m_pOwner->NotifyOnDeleteItems(this);
			return true;
		}
		return false;
	}

	bool CListItem::DetachItem(IListItem *item)
	{
		for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			if (*pos == item)
			{
				if (m_pOwner)
					m_pOwner->NotifyOnBeforeDeleteItem(item);
				m_aItems.erase(pos);
				if (m_pOwner)
					m_pOwner->NotifyOnDeleteItem(item, this);
				item->QueryService()->setParent(nullptr);
				return true;
			}
		return false;
	}
#pragma endregion

#pragma region Helpers
	bool CListItem::Copy(IListItem *dest)
	{
		CListItem *d{ cast<CListItem*>(dest) };
		if (d)
		{
			d->m_sName = m_sName;
			d->m_sSize = m_sSize;
			d->m_sPosition = m_sPosition;
			d->m_bVisible = m_bVisible;
			d->m_bEnabled = m_bEnabled;
			d->m_bHovered = m_bHovered;
			d->m_bSelected= m_bSelected;
			d->m_bActive = m_bActive;
			d->DeleteItems();
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				d->AddItem((*pos)->Clone());
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Change position
	bool CListItem::BringToFront()
	{
		if (m_pParent)
			return m_pParent->QueryService()->MoveItem(this, m_pParent->getItemCount());
		if (m_pOwner && m_pOwner->getControl())
		{
			IComponentItemList *component{ cast<IComponentItemList *>(m_pOwner->getControl()) };
			IComponentItemListService *service{ cast<IComponentItemListService *>(m_pOwner->getControl()->QueryService()) };
			if (component && service)
				return service->MoveItem(this, component->getItemCount());
		}
		return false;
	}

	bool CListItem::BringUp()
	{
		if (m_pParent)
			return m_pParent->QueryService()->MoveItem(this, m_pParent->getItemIndex(this) + 2);
		if (m_pOwner && m_pOwner->getControl())
		{
			IComponentItemList *component{ cast<IComponentItemList *>(m_pOwner->getControl()) };
			IComponentItemListService *service{ cast<IComponentItemListService *>(m_pOwner->getControl()->QueryService()) };
			if (component && service)
				return service->MoveItem(this, component->getItemIndex(this) + 2);
		}
		return false;
	}

	bool CListItem::BringDown()
	{
		if (m_pParent)
			return m_pParent->QueryService()->MoveItem(this, m_pParent->getItemIndex(this) - 1);
		if (m_pOwner && m_pOwner->getControl())
		{
			IComponentItemList *component{ cast<IComponentItemList *>(m_pOwner->getControl()) };
			IComponentItemListService *service{ cast<IComponentItemListService *>(m_pOwner->getControl()->QueryService()) };
			if (component && service)
				return service->MoveItem(this, component->getItemIndex(this) - 1);
		}
		return false;
	}

	bool CListItem::BringBefore(IListItem *item)
	{
		if (m_pParent)
			return m_pParent->QueryService()->MoveItem(this, m_pParent->getItemIndex(item));
		if (m_pOwner && m_pOwner->getControl())
		{
			IComponentItemList *component{ cast<IComponentItemList *>(m_pOwner->getControl()) };
			IComponentItemListService *service{ cast<IComponentItemListService *>(m_pOwner->getControl()->QueryService()) };
			if (component && service)
				return service->MoveItem(this, component->getItemIndex(item));
		}
		return false;
	}

	bool CListItem::BringBefore(const int index)
	{
		if (m_pParent)
			return m_pParent->QueryService()->MoveItem(this, index);
		if (m_pOwner && m_pOwner->getControl())
		{
			IComponentItemListService *service{ cast<IComponentItemListService *>(m_pOwner->getControl()->QueryService()) };
			if (service)
				return service->MoveItem(this, index);
		}
		return false;
	}

	bool CListItem::BringAfter(IListItem *item)
	{
		if (m_pParent)
			return m_pParent->QueryService()->MoveItem(this, m_pParent->getItemIndex(item) + 1);
		if (m_pOwner && m_pOwner->getControl())
		{
			IComponentItemList *component{ cast<IComponentItemList *>(m_pOwner->getControl()) };
			IComponentItemListService *service{ cast<IComponentItemListService *>(m_pOwner->getControl()->QueryService()) };
			if (component && service)
				return service->MoveItem(this, component->getItemIndex(item) + 1);
		}
		return false;
	}

	bool CListItem::BringAfter(const int index)
	{
		if (m_pParent)
			return m_pParent->QueryService()->MoveItem(this, index + 1);
		if (m_pOwner && m_pOwner->getControl())
		{
			IComponentItemListService *service{ cast<IComponentItemListService *>(m_pOwner->getControl()->QueryService()) };
			if (service)
				return service->MoveItem(this, index + 1);
		}
		return false;
	}
#pragma endregion
}