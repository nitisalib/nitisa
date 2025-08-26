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
	namespace standard
	{
		CPropertyHandlerBool::CPropertyHandlerBool(IPackage *package) :
			CPropertyHandlerDropDown(package, PropertyHandlerBool),
			m_pProperty{ nullptr }
		{
			Add(L"false");
			Add(L"true");
			setLoopActiveItemOnDoubleClick(true);
		}

		bool CPropertyHandlerBool::isEditable(IProperty *property)
		{
			return cast<IPropertyBool*>(property) || cast<IPropertyBoolState*>(property);
		}

		IProperty *CPropertyHandlerBool::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerBool::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerBool::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyBoolState *p{ cast<IPropertyBoolState*>(m_pProperty) };
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
					IPropertyBool *p{ cast<IPropertyBool*>(m_pProperty) };
					IPropertyBoolState *ps{ cast<IPropertyBoolState*>(m_pProperty) };
					if (ps)
					{
						if (m_sState.empty())
							setActiveIndex(-1);
						else
							setActiveIndex(ps->getValue(m_sState) ? 1 : 0);
					}
					else
						setActiveIndex(p->getValue() ? 1 : 0);
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerBool::setPropertyState(const String &value)
		{
			IPropertyBoolState *p{ cast<IPropertyBoolState*>(m_pProperty) };
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
					setActiveIndex(p->getValue(m_sState) ? 1 : 0);
					return true;
				}
			}
			return false;
		}

		void CPropertyHandlerBool::NotifyOnSelect(const int index)
		{
			if (m_pProperty && (index == 0 || index == 1))
			{
				IPropertyBoolState *ps{ cast<IPropertyBoolState*>(m_pProperty) };
				bool changed;
				if (ps)
					changed = ps->setValue(m_sState, index == 1);
				else
					changed = cast<IPropertyBool*>(m_pProperty)->setValue(index == 1);
				if (changed && getListener() && cast<IPropertyHandlerListener*>(getListener()))
					cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
			}
		}
	}
}