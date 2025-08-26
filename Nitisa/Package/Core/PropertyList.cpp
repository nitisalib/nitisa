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
#pragma region Constructor & destructor
	CPropertyList::CPropertyList(IPackage *package, IClass *parent, IPackageEntity *entity) :
		m_pPackage{ package },
		m_pParent{ parent },
		m_pEntity{ entity }
	{

	}

	CPropertyList::~CPropertyList()
	{
		Clear();
	}

	void CPropertyList::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Getters
	IPackage *CPropertyList::getPackage()
	{
		return m_pPackage;
	}

	int CPropertyList::getCount()
	{
		return (int)m_aItems.size();
	}

	IProperty *CPropertyList::getProperty(const int index)
	{
		if (index >= 0 && index < (int)m_aItems.size())
			return m_aItems[index];
		return nullptr;
	}

	IProperty *CPropertyList::getProperty(const String &name)
	{
		for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			if ((*pos)->Name == name)
				return *pos;
		return nullptr;
	}

	IClass *CPropertyList::getParent()
	{
		return m_pParent;
	}

	IPackageEntity *CPropertyList::getEntity()
	{
		return m_pEntity;
	}
#pragma endregion

#pragma region Setters
	void CPropertyList::setParent(IClass *parent, IPackageEntity *entity)
	{
		m_pParent = parent;
		m_pEntity = entity;
		for (auto pos : m_aItems)
			pos->setParent(parent);
	}
#pragma endregion

#pragma region Items
	void CPropertyList::Delete(const int index)
	{
		if (index >= 0 && index < (int)m_aItems.size())
		{
			m_aItems[index]->Release();
			m_aItems.erase(m_aItems.begin() + index);
		}
	}

	void CPropertyList::Delete(IProperty *item)
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

	void CPropertyList::Delete(const String &name)
	{
		for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			if ((*pos)->Name == name)
			{
				(*pos)->Release();
				m_aItems.erase(pos);
				break;
			}
	}

	void CPropertyList::Clear()
	{
		for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			(*pos)->Release();
		m_aItems.clear();
	}
#pragma endregion

#pragma region Save/Load/Export
	void CPropertyList::Save(Variant &dest)
	{
		for (int i = 0; i < getCount(); i++)
			if (getProperty(i)->isChanged() && !getProperty(i)->isSkip())
				getProperty(i)->Save(dest[getProperty(i)->Name.c_str()]);
	}

	void CPropertyList::Load(const Variant &src)
	{
		for (int i = 0; i < getCount(); i++)
			if (src.isSet(getProperty(i)->Name))
				getProperty(i)->Load(src.get(getProperty(i)->Name.c_str()));
	}

	void CPropertyList::Export(std::wofstream &f, const String &shift, const String &owner)
	{
		for (int i = 0; i < getCount(); i++)
		{
			auto p{ getProperty(i) };
			if (p->isChanged() && !p->isSkip())
				p->Export(f, shift, owner);
		}
	}
#pragma endregion
}