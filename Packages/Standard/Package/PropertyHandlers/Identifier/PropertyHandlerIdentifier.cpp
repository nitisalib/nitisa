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
		CPropertyHandlerIdentifier::CPropertyHandlerIdentifier(IPackage *package) :
			CPropertyHandlerTextInput(package, PropertyHandlerIdentifier),
			m_pProperty{ nullptr }
		{

		}

		bool CPropertyHandlerIdentifier::isEditable(IProperty *property)
		{
			return cast<IPropertyIdentifier*>(property) || cast<IPropertyIdentifierState*>(property);
		}

		IProperty *CPropertyHandlerIdentifier::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerIdentifier::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerIdentifier::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyIdentifierState *p{ cast<IPropertyIdentifierState*>(m_pProperty) };
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
					IPropertyIdentifier *p{ cast<IPropertyIdentifier*>(m_pProperty) };
					IPropertyIdentifierState *ps{ cast<IPropertyIdentifierState*>(m_pProperty) };
					if (ps)
					{
						if (m_sState.empty())
						{
							setText(L"");
							setScroll(0);
						}
						else
						{
							if (setText(ps->getValue(m_sState)))
								setScroll(0);
						}
					}
					else
					{
						if (setText(p->getValue()))
							setScroll(0);
					}
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerIdentifier::setPropertyState(const String &value)
		{
			IPropertyIdentifierState *p{ cast<IPropertyIdentifierState*>(m_pProperty) };
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
					if (setText(p->getValue(m_sState)))
						setScroll(0);
					return true;
				}
			}
			return false;
		}

		void CPropertyHandlerIdentifier::UpdatePropertyFromText()
		{
			if (m_pProperty)
			{
				IPropertyIdentifierState *ps{ cast<IPropertyIdentifierState*>(m_pProperty) };
				if (ps)
				{
					if (ps->setValue(m_sState, getText()))
						if (getListener() && cast<IPropertyHandlerListener*>(getListener()))
							cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
					setText(ps->getValue(m_sState));
				}
				else
				{
					IPropertyIdentifier *p{ cast<IPropertyIdentifier*>(m_pProperty) };
					if (p->setValue(getText()))
						if (getListener() && cast<IPropertyHandlerListener*>(getListener()))
							cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
					setText(p->getValue());
				}
			}
		}

		void CPropertyHandlerIdentifier::UpdateTextFromProperty()
		{
			if (m_pProperty)
			{
				IPropertyIdentifierState *ps{ cast<IPropertyIdentifierState*>(m_pProperty) };
				if (ps)
					setText(ps->getValue(m_sState));
				else
				{
					IPropertyIdentifier *p{ cast<IPropertyIdentifier*>(m_pProperty) };
					setText(p->getValue());
				}
			}
		}
	}
}