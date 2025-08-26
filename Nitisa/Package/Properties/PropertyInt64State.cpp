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
	CPropertyInt64State::CPropertyInt64State(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerInt64, skip, read_only, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_bMin{ false },
		m_bMax{ false },
		m_iMin{ 0 },
		m_iMax{ 0 }
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			m_aOld[getState(i)] = m_fGetter(m_pParent, getState(i));
			m_aValue[getState(i)] = m_fGetter(m_pParent, getState(i));
		}
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyInt64State::getPreview()
	{
		return L"";
	}

	String CPropertyInt64State::getPreview(const String &state)
	{
		return ToString(getValue(state));
	}

	bool CPropertyInt64State::isChanged()
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
	IProperty *CPropertyInt64State::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyInt64State::Copy(IProperty *dest)
	{
		IPropertyInt64State *d{ cast<IPropertyInt64State*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyInt64State::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
	}

	void CPropertyInt64State::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			long long v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyInt64State::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", " << getValue(getState(i)) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", " << getValue(getState(i)) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyInt64State getters
	long long CPropertyInt64State::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_aValue[state];
	}

	bool CPropertyInt64State::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyInt64State::hasMax() const
	{
		return m_bMax;
	}

	long long CPropertyInt64State::getMin() const
	{
		return m_iMin;
	}

	long long CPropertyInt64State::getMax() const
	{
		return m_iMax;
	}
#pragma endregion

#pragma region IPropertyInt64State setters
	bool CPropertyInt64State::setValue(const String &state, const long long value)
	{
		long long v{ value };
		if (m_bMin)
			v = ntl::Max<long long>(m_iMin, v);
		if (m_bMax)
			v = ntl::Min<long long>(m_iMax, v);
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, state, v);
		if (v != m_aValue[state])
		{
			m_aValue[state] = v;
			return true;
		}
		return false;
	}

	IPropertyInt64State *CPropertyInt64State::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyInt64State *CPropertyInt64State::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyInt64State *CPropertyInt64State::setMin(const long long value)
	{
		m_iMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyInt64State *CPropertyInt64State::setMax(const long long value)
	{
		m_iMax = value;
		m_bMax = true;
		return this;
	}
#pragma endregion
}