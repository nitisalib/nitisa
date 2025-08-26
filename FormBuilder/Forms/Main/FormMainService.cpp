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
		CFormMainService::CFormMainService(CFormMain *form) :
			CFormService(form),
			m_pForm{ form },
			m_bIgnoreDetach{ false }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CFormMainService::UpdateTabOrders(const int old_tab_order, const int new_tab_order)
		{
			if (m_pForm->m_pFormEditor)
			{
				IControl *control1{ FindControlByTabOrder(m_pForm->m_pFormEditor, old_tab_order) };
				if (control1)
				{
					IControl *control2{ FindControlByTabOrder(m_pForm->m_pFormEditor, new_tab_order) };
					control1->QueryService()->setTabOrder(new_tab_order);
					if (control2)
						control2->QueryService()->setTabOrder(old_tab_order);
					return;
				}
			}
			CFormService::UpdateTabOrders(old_tab_order, new_tab_order);
		}

		String CFormMainService::GenerateComponentName(IComponent *component)
		{
			if (m_pForm->m_pFormEditor)
			{
				bool allowed{ true };
				m_pForm->FormEditor_OnCheckComponentAllowed(m_pForm->m_pFormEditor, component, allowed);
				if (allowed)
				{
					StringArray names;
					for (int i = 0; i < m_pForm->getComponentCount(); i++)
					{
						allowed = true;
						m_pForm->FormEditor_OnCheckComponentAllowed(m_pForm->m_pFormEditor, m_pForm->getComponent(i), allowed);
						if (allowed && m_pForm->getComponent(i) != component)
							names.push_back(m_pForm->getComponent(i)->Name);
					}
					std::sort(names.begin(), names.end());
					String name{ component->Name };
					int index{ 0 };
					if (name.empty())
					{
						index++;
						name = component->ClassName + ToString(index);
					}
					while (true)
					{
						auto pos = std::lower_bound(names.begin(), names.end(), name);
						if (pos == names.end() || *pos != name)
							break;
						index++;
						name = component->ClassName + ToString(index);
					}
					return name;
				}
			}
			return CFormService::GenerateComponentName(component);
		}

		void CFormMainService::EnumControls(StringArray &names, IControl *control, IControl *exclude)
		{
			if (control != exclude)
				names.push_back(control->Name);
			for (int i = 0; i < control->getControlCount(); i++)
				EnumControls(names, control->getControl(i), exclude);
		}

		String CFormMainService::GenerateControlName(IControl *control)
		{
			if (m_pForm->m_pFormEditor && control != m_pForm->m_pFormEditor && m_pForm->m_pFormEditor->hasChild(control))
			{
				StringArray names;
				for (int i = 0; i < m_pForm->m_pFormEditor->getControlCount(); i++)
					EnumControls(names, m_pForm->m_pFormEditor->getControl(i), control);
				std::sort(names.begin(), names.end());
				String name{ control->Name };
				int index{ 0 };
				if (name.empty())
				{
					index++;
					name = control->ClassName + ToString(index);
				}
				while (true)
				{
					auto pos = std::lower_bound(names.begin(), names.end(), name);
					if (pos == names.end() || *pos != name)
						break;
					index++;
					name = control->ClassName + ToString(index);
				}
				return name;
			}
			return CFormService::GenerateControlName(control);
		}

		void CFormMainService::EnumTabOrders(IntegerArray &orders, IControl *control)
		{
			orders.push_back(control->getTabOrder());
			for (int i = 0; i < control->getControlCount(); i++)
				EnumTabOrders(orders, control->getControl(i));
		}

		int CFormMainService::GenerateTabOrder(IControl *control)
		{
			if (m_pForm->m_pFormEditor && control != m_pForm->m_pFormEditor && m_pForm->m_pFormEditor->hasChild(control))
			{
				IntegerArray orders;
				for (int i = 0; i < m_pForm->m_pFormEditor->getControlCount(); i++)
					EnumTabOrders(orders, m_pForm->m_pFormEditor->getControl(i));
				std::sort(orders.begin(), orders.end());
				int result{ ntl::Max<int>(0, control->getTabOrder()) };
				auto p{ std::lower_bound(orders.begin(), orders.end(), result) };
				if (p == orders.end() || (*p) != result)
					return result;
				result = -1;
				do
				{
					result++;
					p = std::find(orders.begin(), orders.end(), result);
				} while (p != orders.end() && (*p) == result);
				return result;
			}
			return CFormService::GenerateTabOrder(control);
		}

		bool CFormMainService::RegisterHotkey(IComponent *component, const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down)
		{
			bool allowed{ true };
			if (m_pForm->m_pFormEditor)
				m_pForm->FormEditor_OnCheckComponentAllowed(m_pForm->m_pFormEditor, component, allowed);
			if (allowed)
				return false;
			return CFormService::RegisterHotkey(component, key, ctrl, alt, shift, is_down);
		}

		bool CFormMainService::RegisterHotkey(IControl *control, const Key key, const bool ctrl, const bool alt, const bool shift, const bool is_down)
		{
			if (m_pForm->m_pFormEditor && control != m_pForm->m_pFormEditor && !m_pForm->m_pFormEditor->hasChild(control))
				return CFormService::RegisterHotkey(control, key, ctrl, alt, shift, is_down);
			return false;
		}

		bool CFormMainService::RegisterMessageListener(IComponent *component, IWindowListenerOnMessage *listener)
		{
			return false;
		}
	#pragma endregion

	#pragma region Component notifications
		void CFormMainService::NotifyOnComponentAttach(IComponent *component)
		{
			if (m_pForm->m_pFormEditor)
			{
				bool allowed{ true };
				m_pForm->FormEditor_OnCheckComponentAllowed(m_pForm->m_pFormEditor, component, allowed);
				if (allowed)
					m_pForm->NotifyOnComponentAttach(component);
			}
		}

		void CFormMainService::NotifyOnComponentDetach(IComponent *component)
		{
			if (!m_bIgnoreDetach)
			{
				if (m_pForm->m_pHierarchyEditor)
					m_pForm->m_pHierarchyEditor->DeleteEx(component, nullptr, nullptr);
				m_pForm->m_pComponents->Delete(component);
			}
		}
	#pragma endregion

	#pragma region Control notifications
		void CFormMainService::NotifyOnControlAttach(IControl *control)
		{
			if (m_pForm->m_pFormEditor && m_pForm->m_pFormEditor->hasChild(control))
				m_pForm->NotifyOnControlAttach(control);
		}

		void CFormMainService::NotifyOnControlDetach(IControl *control)
		{
			if (control == m_pForm->m_pHierarchyEditor/* || control->hasChild(m_pForm->m_pHierarchyEditor)*/)
				m_pForm->m_pHierarchyEditor = nullptr;
			if (!m_bIgnoreDetach)
			{
				if (m_pForm->m_pHierarchyEditor)
					m_pForm->m_pHierarchyEditor->DeleteEx(control, control, nullptr);
				m_pForm->m_pControls->Delete(control);
			}
		}
	#pragma endregion
	}
}