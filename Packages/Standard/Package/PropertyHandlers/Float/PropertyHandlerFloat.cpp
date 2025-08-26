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
		CPropertyHandlerFloat::CPropertyHandlerFloat(IPackage *package) :
			CPropertyHandlerTextInput(package, PropertyHandlerFloat),
			m_pProperty{ nullptr }
		{

		}

		bool CPropertyHandlerFloat::isEditable(IProperty *property)
		{
			return cast<IPropertyFloat*>(property) || cast<IPropertyFloatState*>(property);
		}

		IProperty *CPropertyHandlerFloat::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerFloat::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerFloat::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyFloatState *p{ cast<IPropertyFloatState*>(m_pProperty) };
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
					IPropertyFloat *p{ cast<IPropertyFloat*>(m_pProperty) };
					IPropertyFloatState *ps{ cast<IPropertyFloatState*>(m_pProperty) };
					if (ps)
					{
						if (m_sState.empty())
							setText(L"");
						else
							setText(ToStringCompact(ps->getValue(m_sState)));
					}
					else
						setText(ToStringCompact(p->getValue()));
					setScroll(0);
				}
				return true;
			}
			return false;
		}

		bool CPropertyHandlerFloat::setPropertyState(const String &value)
		{
			IPropertyFloatState *p{ cast<IPropertyFloatState*>(m_pProperty) };
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
					setText(ToStringCompact(p->getValue(m_sState)));
					setScroll(0);
					return true;
				}
			}
			return false;
		}

		void CPropertyHandlerFloat::UpdatePropertyFromText()
		{
			if (m_pProperty)
			{
				IPropertyFloatState *ps{ cast<IPropertyFloatState*>(m_pProperty) };
				float f;
				if (ps)
				{
					if (TryStringToFloat(getText(), f))
						if (ps->setValue(m_sState, f))
						{
							if (getListener() && cast<IPropertyHandlerListener*>(getListener()))
								cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
						}
					setText(ToStringCompact(ps->getValue(m_sState)));
				}
				else
				{
					IPropertyFloat *p{ cast<IPropertyFloat*>(m_pProperty) };
					if (TryStringToFloat(getText(), f))
						if (p->setValue(f))
						{
							if (getListener() && cast<IPropertyHandlerListener*>(getListener()))
								cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
						}
					setText(ToStringCompact(p->getValue()));
				}
			}
		}

		void CPropertyHandlerFloat::UpdateTextFromProperty()
		{
			if (m_pProperty)
			{
				IPropertyFloatState *ps{ cast<IPropertyFloatState*>(m_pProperty) };
				if (ps)
					setText(ToStringCompact(ps->getValue(m_sState)));
				else
				{
					IPropertyFloat *p{ cast<IPropertyFloat*>(m_pProperty) };
					setText(ToStringCompact(p->getValue()));
				}
			}
		}
	}
}