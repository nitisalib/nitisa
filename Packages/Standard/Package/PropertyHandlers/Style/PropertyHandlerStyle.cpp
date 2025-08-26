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
		CPropertyHandlerStyle::CPropertyHandlerStyle(IPackage *package) :
			CPropertyHandlerDropDown(package, PropertyHandlerStyle),
			m_pProperty{ nullptr }
		{

		}

		bool CPropertyHandlerStyle::isEditable(IProperty *property)
		{
			return cast<IPropertyStyle*>(property) || cast<IPropertyStyleState*>(property);
		}

		IProperty *CPropertyHandlerStyle::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerStyle::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerStyle::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyStyleState *p{ cast<IPropertyStyleState*>(m_pProperty) };
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
					IPropertyStyle *p{ cast<IPropertyStyle*>(m_pProperty) };
					IPropertyStyleState *ps{ cast<IPropertyStyleState*>(m_pProperty) };
					DeleteItems();
					IEditor *editor{ Application->Editor };
					if (editor)
					{
						for (int i = 0; i < editor->getStyleCount(); i++)
							Add(editor->getStyle(i)->getTitle() + L"(" + editor->getStyle(i)->getPackage()->getName() + L")");
						if (ps)
						{
							if (m_sState.empty())
								setActiveIndex(-1);
							else
								for (int i = 0; i < editor->getStyleCount(); i++)
									if (ps->getValue(m_sState) == editor->getStyle(i)->getStyle())
									{
										setActiveIndex(i);
										break;
									}
						}
						else
							for (int i = 0; i < editor->getStyleCount(); i++)
								if (p->getValue() == editor->getStyle(i)->getStyle())
								{
									setActiveIndex(i);
									break;
								}
					}
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerStyle::setPropertyState(const String &value)
		{
			IPropertyStyleState *p{ cast<IPropertyStyleState*>(m_pProperty) };
			if (p)
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
					IEditor *editor{ Application->Editor };
					if (editor)
						for (int i = 0; i < editor->getStyleCount(); i++)
							if (p->getValue(m_sState) == editor->getStyle(i)->getStyle())
							{
								setActiveIndex(i);
								break;
							}
					return true;
				}
			}
			return false;
		}

		void CPropertyHandlerStyle::NotifyOnSelect(const int index)
		{
			if (m_pProperty)
			{
				IPropertyStyleState *ps{ cast<IPropertyStyleState*>(m_pProperty) };
				IEditor *editor{ Application->Editor };
				bool changed{ false };
				if (editor)
				{
					if (ps)
						changed = ps->setValue(m_sState, editor->getStyle(index)->getStyle());
					else
						changed = cast<IPropertyStyle*>(m_pProperty)->setValue(editor->getStyle(index)->getStyle());
				}
				if (changed && getListener() && cast<IPropertyHandlerListener*>(getListener()))
					cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
			}
		}
	}
}