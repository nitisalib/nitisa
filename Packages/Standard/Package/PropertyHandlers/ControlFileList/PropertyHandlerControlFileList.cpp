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
		CPropertyHandlerControlFileList::CPropertyHandlerControlFileList(IPackage *package) :
			CPropertyHandlerDropDown(package, PropertyHandlerControlFileList),
			m_pProperty{ nullptr }
		{

		}

		bool CPropertyHandlerControlFileList::isEditable(IProperty *property)
		{
			return cast<IPropertyControlFileList*>(property) || cast<IPropertyControlFileListState*>(property);
		}

		IProperty *CPropertyHandlerControlFileList::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerControlFileList::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerControlFileList::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyControlFileListState *p{ cast<IPropertyControlFileListState*>(m_pProperty) };
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
					IPropertyControlFileList *p{ cast<IPropertyControlFileList*>(m_pProperty) };
					IPropertyControlFileListState *ps{ cast<IPropertyControlFileListState*>(m_pProperty) };
					DeleteItems();
					IEditor *editor{ Application->Editor };
					if (editor)
					{
						Add(L"(Empty)");
						int index{ 0 };
						for (int j = 0; j < editor->getPackageCount(); j++)
							for (int i = 0; i < editor->getPackage(j)->getCreatedControlCount(); i++)
							{
								IFileList *control{ cast<IFileList*>(editor->getPackage(j)->getCreatedControl(i)) };
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

		bool CPropertyHandlerControlFileList::setPropertyState(const String &value)
		{
			IPropertyControlFileListState *p{ cast<IPropertyControlFileListState*>(m_pProperty) };
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
							IFileList *control{ cast<IFileList*>(editor->getPackage(j)->getCreatedControl(i)) };
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

		void CPropertyHandlerControlFileList::NotifyOnSelect(const int index)
		{
			IEditor *editor{ Application->Editor };
			if (m_pProperty && editor)
			{
				IFileList *item{ nullptr };
				if (index > 0)
				{
					int idx{ 1 };
					for (int j = 0; j < editor->getPackageCount(); j++)
					{
						for (int i = 0; i < editor->getPackage(j)->getCreatedControlCount(); i++)
						{
							IFileList *control{ cast<IFileList*>(editor->getPackage(j)->getCreatedControl(i)) };
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
				IPropertyControlFileListState *ps{ cast<IPropertyControlFileListState*>(m_pProperty) };
				bool changed;
				if (ps)
					changed = ps->setValue(m_sState, item);
				else
					changed = cast<IPropertyControlFileList*>(m_pProperty)->setValue(item);
				if (changed && getListener() && cast<IPropertyHandlerListener*>(getListener()))
					cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
			}
		}
	}
}