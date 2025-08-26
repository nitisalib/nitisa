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
		CPropertyHandlerDouble::CPropertyHandlerDouble(IPackage *package) :
			CPropertyHandlerTextInput(package, PropertyHandlerDouble),
			m_pProperty{ nullptr }
		{

		}

		bool CPropertyHandlerDouble::isEditable(IProperty *property)
		{
			return cast<IPropertyDouble*>(property) || cast<IPropertyDoubleState*>(property);
		}

		IProperty *CPropertyHandlerDouble::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerDouble::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerDouble::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyDoubleState *p{ cast<IPropertyDoubleState*>(m_pProperty) };
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
					IPropertyDouble *p{ cast<IPropertyDouble*>(m_pProperty) };
					IPropertyDoubleState *ps{ cast<IPropertyDoubleState*>(m_pProperty) };
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

		bool CPropertyHandlerDouble::setPropertyState(const String &value)
		{
			IPropertyDoubleState *p{ cast<IPropertyDoubleState*>(m_pProperty) };
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

		void CPropertyHandlerDouble::UpdatePropertyFromText()
		{
			if (m_pProperty)
			{
				IPropertyDoubleState *ps{ cast<IPropertyDoubleState*>(m_pProperty) };
				double f;
				if (ps)
				{
					if (TryStringToDouble(getText(), f))
						if (ps->setValue(m_sState, f))
						{
							if (getListener() && cast<IPropertyHandlerListener*>(getListener()))
								cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
						}
					setText(ToStringCompact(ps->getValue(m_sState)));
				}
				else
				{
					IPropertyDouble *p{ cast<IPropertyDouble*>(m_pProperty) };
					if (TryStringToDouble(getText(), f))
						if (p->setValue(f))
						{
							if (getListener() && cast<IPropertyHandlerListener*>(getListener()))
								cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
						}
					setText(ToStringCompact(p->getValue()));
				}
			}
		}

		void CPropertyHandlerDouble::UpdateTextFromProperty()
		{
			if (m_pProperty)
			{
				IPropertyDoubleState *ps{ cast<IPropertyDoubleState*>(m_pProperty) };
				if (ps)
					setText(ToStringCompact(ps->getValue(m_sState)));
				else
				{
					IPropertyDouble *p{ cast<IPropertyDouble*>(m_pProperty) };
					setText(ToStringCompact(p->getValue()));
				}
			}
		}
	}
}