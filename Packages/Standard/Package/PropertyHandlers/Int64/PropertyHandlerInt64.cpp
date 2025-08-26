// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
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
		CPropertyHandlerInt64::CPropertyHandlerInt64(IPackage *package) :
			CPropertyHandlerTextInput(package, PropertyHandlerInt64),
			m_pProperty{ nullptr }
		{

		}

		bool CPropertyHandlerInt64::isEditable(IProperty *property)
		{
			return cast<IPropertyInt64*>(property) || cast<IPropertyInt64State*>(property);
		}

		IProperty *CPropertyHandlerInt64::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerInt64::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerInt64::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyInt64State *p{ cast<IPropertyInt64State*>(m_pProperty) };
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
					IPropertyInt64 *p{ cast<IPropertyInt64*>(m_pProperty) };
					IPropertyInt64State *ps{ cast<IPropertyInt64State*>(m_pProperty) };
					if (ps)
					{
						if (m_sState.empty())
							setText(L"");
						else
							setText(ToString(ps->getValue(m_sState)));
					}
					else
						setText(ToString(p->getValue()));
					setScroll(0);
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerInt64::setPropertyState(const String &value)
		{
			IPropertyInt64State *p{ cast<IPropertyInt64State*>(m_pProperty) };
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
					setText(ToString(p->getValue(m_sState)));
					setScroll(0);
					return true;
				}
			}
			return false;
		}

		void CPropertyHandlerInt64::UpdatePropertyFromText()
		{
			if (m_pProperty)
			{
				IPropertyInt64State *ps{ cast<IPropertyInt64State*>(m_pProperty) };
				long long i;
				if (ps)
				{
					if (TryStringToInt64(getText(), i))
						if (ps->setValue(m_sState, i))
						{
							if (getListener() && cast<IPropertyHandlerListener*>(getListener()))
								cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
						}
					setText(ToString(ps->getValue(m_sState)));
				}
				else
				{
					IPropertyInt64 *p{ cast<IPropertyInt64*>(m_pProperty) };
					if (TryStringToInt64(getText(), i))
						if (p->setValue(i))
						{
							if (getListener() && cast<IPropertyHandlerListener*>(getListener()))
								cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
						}
					setText(ToString(p->getValue()));
				}
			}
		}

		void CPropertyHandlerInt64::UpdateTextFromProperty()
		{
			if (m_pProperty)
			{
				IPropertyInt64State *ps{ cast<IPropertyInt64State*>(m_pProperty) };
				if (ps)
					setText(ToString(ps->getValue(m_sState)));
				else
				{
					IPropertyInt64 *p{ cast<IPropertyInt64*>(m_pProperty) };
					setText(ToString(p->getValue()));
				}
			}
		}
	}
}