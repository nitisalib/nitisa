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
	CPropertyDoubleState::CPropertyDoubleState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerDouble, skip, read_only, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_bMin{ false },
		m_bMax{ false },
		m_fMin{ 0 },
		m_fMax{ 0 }
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			m_aOld[getState(i)] = m_fGetter(m_pParent, getState(i));
			m_aValue[getState(i)] = m_fGetter(m_pParent, getState(i));
		}
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyDoubleState::getPreview()
	{
		return L"";
	}

	String CPropertyDoubleState::getPreview(const String &state)
	{
		return ToStringCompact(getValue(state));
	}

	bool CPropertyDoubleState::isChanged()
	{
		if (m_bChanged)
			return true;
		for (int i = 0; i < getStateCount(); i++)
			if (ntl::IsNotEqual<double>(getValue(getState(i)), m_aOld[getState(i)]))
				return true;
		return false;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyDoubleState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyDoubleState::Copy(IProperty *dest)
	{
		IPropertyDoubleState *d{ cast<IPropertyDoubleState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyDoubleState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
	}

	void CPropertyDoubleState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			double v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyDoubleState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyDoubleState getters
	double CPropertyDoubleState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_aValue[state];
	}

	bool CPropertyDoubleState::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyDoubleState::hasMax() const
	{
		return m_bMax;
	}

	double CPropertyDoubleState::getMin() const
	{
		return m_fMin;
	}

	double CPropertyDoubleState::getMax() const
	{
		return m_fMax;
	}
#pragma endregion

#pragma region IPropertyDoubleState setters
	bool CPropertyDoubleState::setValue(const String &state, const double value)
	{
		double v{ value };
		if (m_bMin)
			v = ntl::Max<double>(m_fMin, v);
		if (m_bMax)
			v = ntl::Min<double>(m_fMax, v);
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, state, v);
		if (ntl::IsNotEqual<double>(v, m_aValue[state]))
		{
			m_aValue[state] = v;
			return true;
		}
		return false;
	}

	IPropertyDoubleState *CPropertyDoubleState::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyDoubleState *CPropertyDoubleState::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyDoubleState *CPropertyDoubleState::setMin(const double value)
	{
		m_fMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyDoubleState *CPropertyDoubleState::setMax(const double value)
	{
		m_fMax = value;
		m_bMax = true;
		return this;
	}
#pragma endregion
}