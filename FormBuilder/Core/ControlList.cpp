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
		CControlList::CControlList() :
			m_bSorted{ true }
		{

		}

		CControlList::~CControlList()
		{
			Clear();
		}
	#pragma endregion

	#pragma region Getters
		int CControlList::getCount() const
		{
			return (int)m_aControls.size();
		}

		CONTROL_INFO *CControlList::getInfo(const int index)
		{
			if (index >= 0 && index < (int)m_aControls.size())
				return m_aControls[index];
			return nullptr;
		}

		CONTROL_INFO *CControlList::getInfo(IControl *control)
		{
			if (control)
			{
				Sort();
				m_sSearch.Control = control;
				auto p{ std::lower_bound(m_aSortedControls.begin(), m_aSortedControls.end(), &m_sSearch, [](const CONTROL_INFO *a, const CONTROL_INFO *b) { return a->Control < b->Control; }) };
				if (p != m_aSortedControls.end() && (*p)->Control == control)
					return *p;
			}
			return nullptr;
		}
	#pragma endregion

	#pragma region Helpers
		void CControlList::Sort()
		{
			if (!m_bSorted)
			{
				std::sort(m_aSortedControls.begin(), m_aSortedControls.end(), [](const CONTROL_INFO *a, const CONTROL_INFO *b) { return a->Control < b->Control; });
				m_bSorted = true;
			}
		}
	#pragma endregion

	#pragma region Methods
		bool CControlList::Add(IControl *control, IEventList *events, IPropertyList *properties, IPackageControl *package_control, const int index)
		{
			if (index >= 0 && control && events && properties && package_control)
			{
				m_aControls.push_back(new CONTROL_INFO{ control, events, properties, package_control, index });
				m_aSortedControls.push_back(new CONTROL_INFO{ control, events, properties, package_control, index });
				m_bSorted = false;
				return true;
			}
			return false;
		}

		bool CControlList::Delete(const int index)
		{
			if (index >= 0 && index < (int)m_aControls.size())
			{
				if (m_bSorted)
				{
					m_sSearch.Control = m_aControls[index]->Control;
					auto p{ std::lower_bound(m_aSortedControls.begin(), m_aSortedControls.end(), &m_sSearch, [](const CONTROL_INFO *a, const CONTROL_INFO *b) { return a->Control < b->Control; }) };
					m_aSortedControls.erase(p);
				}
				else
				{
					for (auto p = m_aSortedControls.begin(); p != m_aSortedControls.end(); p++)
						if ((*p)->Control == m_aControls[index]->Control)
						{
							m_aSortedControls.erase(p);
							break;
						}
				}
				Application->Editor->getControl(m_aControls[index]->Index)->getPackage()->QueryService()->NotifyOnDestroyControl(m_aControls[index]->Control);
				m_aControls[index]->Events->Release();
				m_aControls[index]->Properties->Release();
				delete m_aControls[index];
				m_aControls.erase(m_aControls.begin() + index);
				return true;
			}
			return false;
		}

		bool CControlList::Delete(IControl *control)
		{
			for (size_t i = 0; i < m_aControls.size(); i++)
				if (m_aControls[i]->Control == control)
					return Delete((int)i);
			return false;
		}

		bool CControlList::Clear()
		{
			if (m_aControls.size() > 0)
			{
				for (auto info : m_aControls)
				{
					Application->Editor->getControl(info->Index)->getPackage()->QueryService()->NotifyOnDestroyControl(info->Control);
					info->Events->Release();
					info->Properties->Release();
					delete info;
				}
				m_aControls.clear();
				m_aSortedControls.clear();
				m_bSorted = true;
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}