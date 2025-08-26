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
		CPropertyHandlerInteger::CPropertyHandlerInteger(IPackage *package) :
			CPropertyHandlerTextInput(package, PropertyHandlerInteger),
			m_pProperty{ nullptr }
		{

		}

		bool CPropertyHandlerInteger::isEditable(IProperty *property)
		{
			return cast<IPropertyInteger*>(property) || cast<IPropertyIntegerState*>(property);
		}

		IProperty *CPropertyHandlerInteger::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerInteger::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerInteger::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyIntegerState *p{ cast<IPropertyIntegerState*>(m_pProperty) };
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
					IPropertyInteger *p{ cast<IPropertyInteger*>(m_pProperty) };
					IPropertyIntegerState *ps{ cast<IPropertyIntegerState*>(m_pProperty) };
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

		bool CPropertyHandlerInteger::setPropertyState(const String &value)
		{
			IPropertyIntegerState *p{ cast<IPropertyIntegerState*>(m_pProperty) };
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

		void CPropertyHandlerInteger::UpdatePropertyFromText()
		{
			if (m_pProperty)
			{
				IPropertyIntegerState *ps{ cast<IPropertyIntegerState*>(m_pProperty) };
				int i;
				if (ps)
				{
					if (TryStringToInt(getText(), i))
						if (ps->setValue(m_sState, i))
						{
							if (getListener() && cast<IPropertyHandlerListener*>(getListener()))
								cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
						}
					setText(ToString(ps->getValue(m_sState)));
				}
				else
				{
					IPropertyInteger *p{ cast<IPropertyInteger*>(m_pProperty) };
					if (TryStringToInt(getText(), i))
						if (p->setValue((int)i))
						{
							if (getListener() && cast<IPropertyHandlerListener*>(getListener()))
								cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
						}
					setText(ToString(p->getValue()));
				}
			}
		}

		void CPropertyHandlerInteger::UpdateTextFromProperty()
		{
			if (m_pProperty)
			{
				IPropertyIntegerState *ps{ cast<IPropertyIntegerState*>(m_pProperty) };
				if (ps)
					setText(ToString(ps->getValue(m_sState)));
				else
				{
					IPropertyInteger *p{ cast<IPropertyInteger*>(m_pProperty) };
					setText(ToString(p->getValue()));
				}
			}
		}
	}
}