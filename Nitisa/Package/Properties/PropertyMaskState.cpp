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
	CPropertyMaskState::CPropertyMaskState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerMask, skip, read_only, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false }
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			m_aOld[getState(i)] = m_fGetter(m_pParent, getState(i));
			m_aValue[getState(i)] = m_fGetter(m_pParent, getState(i));
		}
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyMaskState::getPreview()
	{
		return L"";
	}

	String CPropertyMaskState::getPreview(const String &state)
	{
		return AnsiToString(std::bitset<32>(getValue(state)).to_string());
	}

	bool CPropertyMaskState::isChanged()
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
	IProperty *CPropertyMaskState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyMaskState::Copy(IProperty *dest)
	{
		IPropertyMaskState *d{ cast<IPropertyMaskState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyMaskState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
	}

	void CPropertyMaskState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			unsigned int v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyMaskState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", 0b" << getPreview(getState(i)) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", 0b" << getPreview(getState(i)) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyMaskState getters
	unsigned int CPropertyMaskState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_aValue[state];
	}
#pragma endregion

#pragma region IPropertyMaskState setters
	bool CPropertyMaskState::setValue(const String &state, const unsigned int value)
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