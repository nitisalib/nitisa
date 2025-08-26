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
		CPropertyHandlerComponentImageList::CPropertyHandlerComponentImageList(IPackage *package) :
			CPropertyHandlerDropDown(package, PropertyHandlerComponentImageList),
			m_pProperty{ nullptr }
		{

		}

		bool CPropertyHandlerComponentImageList::isEditable(IProperty *property)
		{
			return cast<IPropertyComponentImageList*>(property) || cast<IPropertyComponentImageListState*>(property);
		}

		IProperty *CPropertyHandlerComponentImageList::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerComponentImageList::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerComponentImageList::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyComponentImageListState *p{ cast<IPropertyComponentImageListState*>(m_pProperty) };
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
					IPropertyComponentImageList *p{ cast<IPropertyComponentImageList*>(m_pProperty) };
					IPropertyComponentImageListState *ps{ cast<IPropertyComponentImageListState*>(m_pProperty) };
					DeleteItems();
					IEditor *editor{ Application->Editor };
					if (editor)
					{
						Add(L"(Empty)");
						int index{ 0 };
						for (int j = 0; j < editor->getPackageCount(); j++)
							for (int i = 0; i < editor->getPackage(j)->getCreatedComponentCount(); i++)
							{
								IImageList *component{ cast<IImageList*>(editor->getPackage(j)->getCreatedComponent(i)) };
								if (component)
								{
									Add(component->Name + L"(" + editor->getPackage(j)->getName() + L")");
									if (ps)
									{
										if (!m_sState.empty() && ps->getValue(m_sState) == component)
											index = getItemCount() - 1;
									}
									else if (p->getValue() == component)
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

		bool CPropertyHandlerComponentImageList::setPropertyState(const String &value)
		{
			IPropertyComponentImageListState *p{ cast<IPropertyComponentImageListState*>(m_pProperty) };
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
						for (int i = 0; i < editor->getPackage(j)->getCreatedComponentCount(); i++)
						{
							IImageList *component{ cast<IImageList*>(editor->getPackage(j)->getCreatedComponent(i)) };
							if (component)
							{
								if (p->getValue(m_sState) == component)
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

		void CPropertyHandlerComponentImageList::NotifyOnSelect(const int index)
		{
			IEditor *editor{ Application->Editor };
			if (m_pProperty && editor)
			{
				IImageList *listitem{ nullptr };
				if (index > 0)
				{
					int idx{ 1 };
					for (int j = 0; j < editor->getPackageCount(); j++)
					{
						for (int i = 0; i < editor->getPackage(j)->getCreatedComponentCount(); i++)
						{
							IImageList *component{ cast<IImageList*>(editor->getPackage(j)->getCreatedComponent(i)) };
							if (component)
							{
								if (idx == index)
								{
									listitem = component;
									break;
								}
								idx++;
							}
						}
						if (listitem)
							break;
					}
				}
				IPropertyComponentImageListState *ps{ cast<IPropertyComponentImageListState*>(m_pProperty) };
				bool changed;
				if (ps)
					changed = ps->setValue(m_sState, listitem);
				else
					changed = cast<IPropertyComponentImageList*>(m_pProperty)->setValue(listitem);
				if (changed && getListener() && cast<IPropertyHandlerListener*>(getListener()))
					cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
			}
		}
	}
}