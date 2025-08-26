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
	CPropertyIntegerState::CPropertyIntegerState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerInteger, skip, read_only, states, state_prefix_type, state_prefix),
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
	String CPropertyIntegerState::getPreview()
	{
		return L"";
	}

	String CPropertyIntegerState::getPreview(const String &state)
	{
		return ToString(getValue(state));
	}

	bool CPropertyIntegerState::isChanged()
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
	IProperty *CPropertyIntegerState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyIntegerState::Copy(IProperty *dest)
	{
		IPropertyIntegerState *d{ cast<IPropertyIntegerState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyIntegerState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
	}

	void CPropertyIntegerState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			int v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyIntegerState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", " << getValue(getState(i)) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", " << getValue(getState(i)) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyIntegerState getters
	int CPropertyIntegerState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_aValue[state];
	}

	bool CPropertyIntegerState::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyIntegerState::hasMax() const
	{
		return m_bMax;
	}

	int CPropertyIntegerState::getMin() const
	{
		return m_iMin;
	}

	int CPropertyIntegerState::getMax() const
	{
		return m_iMax;
	}
#pragma endregion

#pragma region IPropertyIntegerState setters
	bool CPropertyIntegerState::setValue(const String &state, const int value)
	{
		int v{ value };
		if (m_bMin)
			v = ntl::Max<int>(m_iMin, v);
		if (m_bMax)
			v = ntl::Min<int>(m_iMax, v);
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, state, v);
		if (v != m_aValue[state])
		{
			m_aValue[state] = v;
			return true;
		}
		return false;
	}

	IPropertyIntegerState *CPropertyIntegerState::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyIntegerState *CPropertyIntegerState::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyIntegerState *CPropertyIntegerState::setMin(const int value)
	{
		m_iMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyIntegerState *CPropertyIntegerState::setMax(const int value)
	{
		m_iMax = value;
		m_bMax = true;
		return this;
	}
#pragma endregion
}