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
	CPropertyIntegerArrayState::CPropertyIntegerArrayState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerIntegerArray, skip, read_only, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_iMinCount{ 0 },
		m_bMin{ false },
		m_bMax{ false },
		m_iMin{ 0 },
		m_iMax{ 0 }
	{
		AddHeaderFile(L"Nitisa/Math/IntegerArray.h");
		for (int i = 0; i < getStateCount(); i++)
		{
			m_aOld[getState(i)] = m_fGetter(m_pParent, getState(i));
			m_aValue[getState(i)] = m_fGetter(m_pParent, getState(i));
		}
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyIntegerArrayState::getPreview()
	{
		return L"";
	}

	String CPropertyIntegerArrayState::getPreview(const String &state)
	{
		if (getValue(state).size() > 1)
			return ToString(getValue(state)[0]) + L", ...";
		if (getValue(state).size() == 1)
			return ToString(getValue(state)[0]);
		return L"";
	}

	bool CPropertyIntegerArrayState::isChanged()
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
	IProperty *CPropertyIntegerArrayState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyIntegerArrayState::Copy(IProperty *dest)
	{
		IPropertyIntegerArrayState *d{ cast<IPropertyIntegerArrayState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyIntegerArrayState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
	}

	void CPropertyIntegerArrayState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			IntegerArray v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyIntegerArrayState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyIntegerArrayState getters
	IntegerArray CPropertyIntegerArrayState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_aValue[state];
	}

	int CPropertyIntegerArrayState::getMinCount()
	{
		return m_iMinCount;
	}

	bool CPropertyIntegerArrayState::hasMin()
	{
		return m_bMin;
	}

	bool CPropertyIntegerArrayState::hasMax()
	{
		return m_bMax;
	}

	int CPropertyIntegerArrayState::getMin()
	{
		return m_iMin;
	}

	int CPropertyIntegerArrayState::getMax()
	{
		return m_iMax;
	}
#pragma endregion

#pragma region IPropertyIntegerArrayState setters
	bool CPropertyIntegerArrayState::setValue(const String &state, const IntegerArray value)
	{
		auto v{ value };
		if (m_bMin || m_bMax)
			for (auto &i : v)
			{
				if (m_bMin)
					i = ntl::Max<int>(m_iMin, i);
				if (m_bMax)
					i = ntl::Min<int>(m_iMax, i);
			}
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, state, v);
		if (v != m_aValue[state])
		{
			m_aValue[state] = v;
			return true;
		}
		return false;
	}

	IPropertyIntegerArrayState *CPropertyIntegerArrayState::setMinCount(const int value)
	{
		m_iMinCount = ntl::Max<int>(0, value);
		return this;
	}

	IPropertyIntegerArrayState *CPropertyIntegerArrayState::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyIntegerArrayState *CPropertyIntegerArrayState::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyIntegerArrayState *CPropertyIntegerArrayState::setMin(const int value)
	{
		m_iMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyIntegerArrayState *CPropertyIntegerArrayState::setMax(const int value)
	{
		m_iMax = value;
		m_bMax = true;
		return this;
	}
#pragma endregion
}