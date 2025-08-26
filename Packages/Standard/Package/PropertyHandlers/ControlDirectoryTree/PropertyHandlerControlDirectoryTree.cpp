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
		CPropertyHandlerControlDirectoryTree::CPropertyHandlerControlDirectoryTree(IPackage *package) :
			CPropertyHandlerDropDown(package, PropertyHandlerControlDirectoryTree),
			m_pProperty{ nullptr }
		{

		}

		bool CPropertyHandlerControlDirectoryTree::isEditable(IProperty *property)
		{
			return cast<IPropertyControlDirectoryTree*>(property) || cast<IPropertyControlDirectoryTreeState*>(property);
		}

		IProperty *CPropertyHandlerControlDirectoryTree::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerControlDirectoryTree::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerControlDirectoryTree::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyControlDirectoryTreeState *p{ cast<IPropertyControlDirectoryTreeState*>(m_pProperty) };
					bool found{ false };
					if (p)
					{
						for (int i = 0; i < p->getStateCount(); i++)
							if (p->getState(i) == m_sState)
							{
								found = true;
								break;
							}
					}
					if (!found)
						m_sState.clear();
				}
				if (m_pProperty)
				{
					IPropertyControlDirectoryTree *p{ cast<IPropertyControlDirectoryTree*>(m_pProperty) };
					IPropertyControlDirectoryTreeState *ps{ cast<IPropertyControlDirectoryTreeState*>(m_pProperty) };
					DeleteItems();
					IEditor *editor{ Application->Editor };
					if (editor)
					{
						Add(L"(Empty)");
						int index{ 0 };
						for (int j = 0; j < editor->getPackageCount(); j++)
							for (int i = 0; i < editor->getPackage(j)->getCreatedControlCount(); i++)
							{
								IDirectoryTree *control{ cast<IDirectoryTree*>(editor->getPackage(j)->getCreatedControl(i)) };
								if (control)
								{
									Add(control->Name + L"(" + editor->getPackage(j)->getName() + L")");
									if (ps)
									{
										if (!m_sState.empty() && ps->getValue(m_sState) == control)
											index = getItemCount() - 1;
									}
									else if (p->getValue() == control)
										index = getItemCount() - 1;
								}
							}
						setActiveIndex(index);
					}
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerControlDirectoryTree::setPropertyState(const String &value)
		{
			IPropertyControlDirectoryTreeState *p{ cast<IPropertyControlDirectoryTreeState*>(m_pProperty) };
			IEditor *editor{ Application->Editor };
			if (p && editor)
			{
				bool found{ false };
				for (int i = 0; i < p->getStateCount(); i++)
					if (p->getState(i) == value)
					{
						found = true;
						break;
					}
				if (found && value != m_sState)
				{
					m_sState = value;
					int index{ 0 }, idx{ 1 };
					bool found{ false };
					for (int j = 0; j < editor->getPackageCount(); j++)
					{
						for (int i = 0; i < editor->getPackage(j)->getCreatedControlCount(); i++)
						{
							IDirectoryTree *control{ cast<IDirectoryTree*>(editor->getPackage(j)->getCreatedControl(i)) };
							if (control)
							{
								if (p->getValue(m_sState) == control)
								{
									found = true;
									index = idx;
									break;
								}
								idx++;
							}
						}
						if (found)
							break;
					}
					setActiveIndex(index);
					return true;
				}
			}
			return false;
		}

		void CPropertyHandlerControlDirectoryTree::NotifyOnSelect(const int index)
		{
			IEditor *editor{ Application->Editor };
			if (m_pProperty && editor)
			{
				IDirectoryTree *item{ nullptr };
				if (index > 0)
				{
					int idx{ 1 };
					for (int j = 0; j < editor->getPackageCount(); j++)
					{
						for (int i = 0; i < editor->getPackage(j)->getCreatedControlCount(); i++)
						{
							IDirectoryTree *control{ cast<IDirectoryTree*>(editor->getPackage(j)->getCreatedControl(i)) };
							if (control)
							{
								if (idx == index)
								{
									item = control;
									break;
								}
								idx++;
							}
						}
						if (item)
							break;
					}
				}
				IPropertyControlDirectoryTreeState *ps{ cast<IPropertyControlDirectoryTreeState*>(m_pProperty) };
				bool changed;
				if (ps)
					changed = ps->setValue(m_sState, item);
				else
					changed = cast<IPropertyControlDirectoryTree*>(m_pProperty)->setValue(item);
				if (changed && getListener() && cast<IPropertyHandlerListener*>(getListener()))
					cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
			}
		}
	}
}