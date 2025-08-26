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
#pragma region Constructor & destructor
	CPropertyEnumState::CPropertyEnumState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		const StringArray &items,
		const ExportPrefixType prefix_type,
		const String &prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerEnum, skip, read_only, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_aItems{ items },
		m_ePrefixType{ prefix_type },
		m_sPrefix{ prefix }
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			m_aOld[getState(i)] = m_fGetter(m_pParent, getState(i));
			m_aValue[getState(i)] = m_fGetter(m_pParent, getState(i));
		}
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyEnumState::getPreview()
	{
		return L"";
	}

	String CPropertyEnumState::getPreview(const String &state)
	{
		StringArray parts{ Explode(getValue(state), L"::") };
		if (parts.size() == 2)
			return parts[1];
		return parts[0];
	}

	bool CPropertyEnumState::isChanged()
	{
		if (m_bChanged)
			return true;
		for (int i = 0; i < getStateCount(); i++)
			if (getValue(getState(i)) != m_aOld[getState(i)])
				return true;
		return false;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyEnumState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyEnumState::Copy(IProperty *dest)
	{
		IPropertyEnumState *d{ cast<IPropertyEnumState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyEnumState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = getValue(getState(i));
	}

	void CPropertyEnumState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			String v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyEnumState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", " << Prefix(m_ePrefixType, m_sPrefix) << getValue(getState(i)) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", " << Prefix(m_ePrefixType, m_sPrefix) << getValue(getState(i)) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyEnumState getters
	String CPropertyEnumState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_aValue[state];
	}

	int CPropertyEnumState::getItemCount() const
	{
		return (int)m_aItems.size();
	}

	String CPropertyEnumState::getItem(const int index) const
	{
		if (index >= 0 && index < (int)m_aItems.size())
			return m_aItems[index];
		return L"";
	}
#pragma endregion

#pragma region IPropertyEnumState setters
	bool CPropertyEnumState::setValue(const String &state, const String value)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, state, value);
		if (value != m_aValue[state])
		{
			m_aValue[state] = value;
			return true;
		}
		return false;
	}
#pragma endregion
}