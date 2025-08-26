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
	namespace fb
	{
	#pragma region Constructor & destructor
		CComponentList::CComponentList() :
			m_bSorted{ true }
		{

		}

		CComponentList::~CComponentList()
		{
			Clear();
		}
	#pragma endregion

	#pragma region Getters
		int CComponentList::getCount() const
		{
			return (int)m_aComponents.size();
		}

		COMPONENT_INFO *CComponentList::getInfo(const int index)
		{
			if (index >= 0 && index < (int)m_aComponents.size())
				return m_aComponents[index];
			return nullptr;
		}

		COMPONENT_INFO *CComponentList::getInfo(IComponent *component)
		{
			if (component)
			{
				Sort();
				m_sSearch.Component = component;
				auto p{ std::lower_bound(m_aSortedComponents.begin(), m_aSortedComponents.end(), &m_sSearch,
					[](const COMPONENT_INFO *a, const COMPONENT_INFO *b) { return a->Component < b->Component; }) };
				if (p != m_aSortedComponents.end() && (*p)->Component == component)
					return *p;
			}
			return nullptr;
		}
	#pragma endregion

	#pragma region Helpers
		void CComponentList::Sort()
		{
			if (!m_bSorted)
			{
				std::sort(m_aSortedComponents.begin(), m_aSortedComponents.end(), [](const COMPONENT_INFO *a, const COMPONENT_INFO *b) { return a->Component < b->Component; });
				m_bSorted = true;
			}
		}
	#pragma endregion

	#pragma region Methods
		bool CComponentList::Add(IComponent *component, IEventList *events, IPropertyList *properties, IPackageComponent *package_component, const int index)
		{
			if (index >= 0 && component && events && properties && package_component)
			{
				m_aComponents.push_back(new COMPONENT_INFO{ component, events, properties, package_component, index });
				m_aSortedComponents.push_back(new COMPONENT_INFO{ component, events, properties, package_component, index });
				m_bSorted = false;
				return true;
			}
			return false;
		}

		bool CComponentList::Delete(const int index)
		{
			if (index >= 0 && index < (int)m_aComponents.size())
			{
				if (m_bSorted)
				{
					m_sSearch.Component = m_aComponents[index]->Component;
					auto p{ std::lower_bound(m_aSortedComponents.begin(), m_aSortedComponents.end(), &m_sSearch,
						[](const COMPONENT_INFO *a, const COMPONENT_INFO *b) { return a->Component < b->Component; }) };
					m_aSortedComponents.erase(p);
				}
				else
				{
					for (auto p = m_aSortedComponents.begin(); p != m_aSortedComponents.end(); p++)
						if ((*p)->Component == m_aComponents[index]->Component)
						{
							m_aSortedComponents.erase(p);
							break;
						}
				}
				Application->Editor->getComponent(m_aComponents[index]->Index)->getPackage()->QueryService()->NotifyOnDestroyComponent(m_aComponents[index]->Component);
				m_aComponents[index]->Events->Release();
				m_aComponents[index]->Properties->Release();
				delete m_aComponents[index];
				m_aComponents.erase(m_aComponents.begin() + index);
				return true;
			}
			return false;
		}

		bool CComponentList::Delete(IComponent *component)
		{
			for (size_t i = 0; i < m_aComponents.size(); i++)
				if (m_aComponents[i]->Component == component)
					return Delete((int)i);
			return false;
		}

		bool CComponentList::Clear()
		{
			if (m_aComponents.size() > 0)
			{
				for (auto info : m_aComponents)
				{
					Application->Editor->getComponent(info->Index)->getPackage()->QueryService()->NotifyOnDestroyComponent(info->Component);
					info->Events->Release();
					info->Properties->Release();
					delete info;
				}
				m_aComponents.clear();
				m_aSortedComponents.clear();
				m_bSorted = true;
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}