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
#pragma region Constructor & destructor
	CEventList::CEventList(IPackage *package, IClass *parent, IPackageEntity *entity) :
		m_pPackage{ package },
		m_pParent{ parent },
		m_pEntity{ entity }
	{

	}

	CEventList::~CEventList()
	{
		Clear();
	}

	void CEventList::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Getters
	IPackage *CEventList::getPackage()
	{
		return m_pPackage;
	}

	int CEventList::getCount()
	{
		return (int)m_aItems.size();
	}

	IEvent *CEventList::getEvent(const int index)
	{
		if (index >= 0 && index < (int)m_aItems.size())
			return m_aItems[index];
		return nullptr;
	}

	IEvent *CEventList::getEvent(const String &name)
	{
		for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			if ((*pos)->getName() == name)
				return *pos;
		return nullptr;
	}

	IClass *CEventList::getParent()
	{
		return m_pParent;
	}

	IPackageEntity *CEventList::getEntity()
	{
		return m_pEntity;
	}
#pragma endregion

#pragma region Items
	void CEventList::Delete(const int index)
	{
		if (index >= 0 && index < (int)m_aItems.size())
		{
			m_aItems[index]->Release();
			m_aItems.erase(m_aItems.begin() + index);
		}
	}

	void CEventList::Delete(IEvent *item)
	{
		if (item)
		{
			int index{ 0 };
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++, index++)
				if (*pos == item)
				{
					Delete(index);
					break;
				}
		}
	}

	void CEventList::Delete(const String &name)
	{
		for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			if ((*pos)->getName() == name)
			{
				(*pos)->Release();
				m_aItems.erase(pos);
				break;
			}
	}

	void CEventList::Clear()
	{
		for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			(*pos)->Release();
		m_aItems.clear();
	}
#pragma endregion

#pragma region Save/Load/Export
	void CEventList::Save(Variant &dest)
	{
		for (int i = 0; i < getCount(); i++)
			if (getEvent(i)->isChanged())
				dest[getEvent(i)->getName().c_str()] = getEvent(i)->getValue();
	}

	void CEventList::Load(const Variant &src)
	{
		for (int i = 0; i < getCount(); i++)
			if (src.isSet(getEvent(i)->getName()))
				getEvent(i)->setValue((String)src.get(getEvent(i)->getName().c_str()));
	}

	void CEventList::Export(std::wofstream &f, const String &shift, const String &owner, const String &form, const String &dialog_box)
	{
		for (int i = 0; i < getCount(); i++)
			if (getEvent(i)->isChanged())
				getEvent(i)->Export(f, shift, owner, form, dialog_box);
	}
#pragma endregion
}