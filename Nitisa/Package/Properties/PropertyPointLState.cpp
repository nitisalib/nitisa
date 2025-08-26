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
	CPropertyPointLState::CPropertyPointLState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerPointL, skip, read_only, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_bMin{ false },
		m_bMax{ false },
		m_iMin{ 0 },
		m_iMax{ 0 }
	{
		AddHeaderFile(L"Nitisa/Math/PointL.h");
		for (int i = 0; i < getStateCount(); i++)
		{
			m_aOld[getState(i)] = m_fGetter(m_pParent, getState(i));
			m_aValue[getState(i)] = m_fGetter(m_pParent, getState(i));
		}
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyPointLState::getPreview()
	{
		return L"";
	}

	String CPropertyPointLState::getPreview(const String &state)
	{
		return ToString(getValue(state));
	}

	bool CPropertyPointLState::isChanged()
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
	IProperty *CPropertyPointLState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyPointLState::Copy(IProperty *dest)
	{
		IPropertyPointLState *d{ cast<IPropertyPointLState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyPointLState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
	}

	void CPropertyPointLState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			PointL v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyPointLState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyPointLState getters
	PointL CPropertyPointLState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_aValue[state];
	}

	bool CPropertyPointLState::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyPointLState::hasMax() const
	{
		return m_bMax;
	}

	long long CPropertyPointLState::getMin() const
	{
		return m_iMin;
	}

	long long CPropertyPointLState::getMax() const
	{
		return m_iMax;
	}
#pragma endregion

#pragma region IPropertyPointLState setters
	bool CPropertyPointLState::setValue(const String &state, const PointL value)
	{
		PointL v{ value };
		if (m_bMin)
		{
			v.X = ntl::Max<long long>(m_iMin, v.X);
			v.Y = ntl::Max<long long>(m_iMin, v.Y);
		}
		if (m_bMax)
		{
			v.X = ntl::Min<long long>(m_iMax, v.X);
			v.Y = ntl::Min<long long>(m_iMax, v.Y);
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

	IPropertyPointLState *CPropertyPointLState::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyPointLState *CPropertyPointLState::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyPointLState *CPropertyPointLState::setMin(const long long value)
	{
		m_iMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyPointLState *CPropertyPointLState::setMax(const long long value)
	{
		m_iMax = value;
		m_bMax = true;
		return this;
	}
#pragma endregion
}