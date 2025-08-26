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
		CPropertyHandlerEnum::CPropertyHandlerEnum(IPackage *package) :
			CPropertyHandlerDropDown(package, PropertyHandlerEnum),
			m_pProperty{ nullptr }
		{

		}

		bool CPropertyHandlerEnum::isEditable(IProperty *property)
		{
			return cast<IPropertyEnum*>(property) || cast<IPropertyEnumState*>(property);
		}

		IProperty *CPropertyHandlerEnum::getProperty()
		{
			return m_pProperty;
		}

		String CPropertyHandlerEnum::getPropertyState()
		{
			return m_sState;
		}

		bool CPropertyHandlerEnum::setProperty(IProperty *value)
		{
			if (!value || isEditable(value))
			{
				m_pProperty = value;
				if (!m_sState.empty())
				{
					IPropertyEnumState *p{ cast<IPropertyEnumState*>(m_pProperty) };
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
					IPropertyEnum *p{ cast<IPropertyEnum*>(m_pProperty) };
					IPropertyEnumState *ps{ cast<IPropertyEnumState*>(m_pProperty) };
					DeleteItems();
					if (ps)
					{
						if (RemovePrefixes(ps))
						{
							for (auto v : m_sValues)
								Add(v);
						}
						else
						{
							for (int i = 0; i < ps->getItemCount(); i++)
								Add(ps->getItem(i));
						}
					}
					else
					{
						if (RemovePrefixes(p))
						{
							for (auto v : m_sValues)
								Add(v);
						}
						else
						{
							for (int i = 0; i < p->getItemCount(); i++)
								Add(p->getItem(i));
						}
					}
					if (ps)
					{
						if (m_sState.empty())
							setActiveIndex(-1);
						else
							for (int i = 0; i < ps->getItemCount(); i++)
								if (ps->getItem(i) == ps->getValue(m_sState))
								{
									setActiveIndex(i);
									break;
								}
					}
					else
					{
						for (int i = 0; i < p->getItemCount(); i++)
							if (p->getItem(i) == p->getValue())
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

		bool CPropertyHandlerEnum::setPropertyState(const String &value)
		{
			IPropertyEnumState *p{ cast<IPropertyEnumState*>(m_pProperty) };
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
					for (int i = 0; i < p->getItemCount(); i++)
						if (p->getItem(i) == p->getValue(m_sState))
						{
							setActiveIndex(i);
							break;
						}
					return true;
				}
			}
			return false;
		}

		void CPropertyHandlerEnum::NotifyOnSelect(const int index)
		{
			if (m_pProperty)
			{
				IPropertyEnum *p{ cast<IPropertyEnum*>(m_pProperty) };
				IPropertyEnumState *ps{ cast<IPropertyEnumState*>(m_pProperty) };
				bool changed;
				if (ps)
					changed = ps->setValue(m_sState, ps->getItem(index));
				else
					changed = p->setValue(p->getItem(index));
				if (changed && getListener() && cast<IPropertyHandlerListener*>(getListener()))
					cast<IPropertyHandlerListener*>(getListener())->NotifyOnPropertyChange(this, m_pProperty);
			}
		}

		bool CPropertyHandlerEnum::RemovePrefixes(IPropertyEnum *p)
		{
			m_sValues.clear();
			m_sPrefix.clear();
			String prefix;
			StringArray values;
			for (int i = 0; i < p->getItemCount(); i++)
			{
				StringArray parts{ Explode(p->getItem(i), L"::") };
				if (parts.size() != 2)
					return false;
				if (i == 0)
					prefix = parts[0];
				else if (parts[0] != prefix)
					return false;
				values.push_back(parts[1]);
			}
			m_sValues = values;
			m_sPrefix = prefix;
			return true;
		}

		bool CPropertyHandlerEnum::RemovePrefixes(IPropertyEnumState *p)
		{
			m_sValues.clear();
			m_sPrefix.clear();
			String prefix;
			StringArray values;
			for (int i = 0; i < p->getItemCount(); i++)
			{
				StringArray parts{ Explode(p->getItem(i), L"::") };
				if (parts.size() != 2)
					return false;
				if (i == 0)
					prefix = parts[0];
				else if (parts[0] != prefix)
					return false;
				values.push_back(parts[1]);
			}
			m_sValues = values;
			m_sPrefix = prefix;
			return true;
		}
	}
}