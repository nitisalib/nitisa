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
	CPropertyRectDState::CPropertyRectDState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerRectD, skip, read_only, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_bMin{ false },
		m_bMax{ false },
		m_fMin{ 0 },
		m_fMax{ 0 },
		m_bAllowInvalid{ true },
		m_bAllowEmpty{ true }
	{
		AddHeaderFile(L"Nitisa/Math/RectD.h");
		for (int i = 0; i < getStateCount(); i++)
		{
			m_aOld[getState(i)] = m_fGetter(m_pParent, getState(i));
			m_aValue[getState(i)] = m_fGetter(m_pParent, getState(i));
		}
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyRectDState::getPreview()
	{
		return L"";
	}

	String CPropertyRectDState::getPreview(const String &state)
	{
		return ToString(getValue(state));
	}

	bool CPropertyRectDState::isChanged()
	{
		if (m_bChanged)
			return true;
		for (int i = 0; i < getStateCount(); i++)
			if (IsNotEqual(getValue(getState(i)), m_aOld[getState(i)]))
				return true;
		return false;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyRectDState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyRectDState::Copy(IProperty *dest)
	{
		IPropertyRectDState *d{ cast<IPropertyRectDState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyRectDState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
	}

	void CPropertyRectDState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			RectD v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyRectDState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyRectDState getters
	RectD CPropertyRectDState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_aValue[state];
	}

	bool CPropertyRectDState::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyRectDState::hasMax() const
	{
		return m_bMax;
	}

	double CPropertyRectDState::getMin() const
	{
		return m_fMin;
	}

	double CPropertyRectDState::getMax() const
	{
		return m_fMax;
	}

	bool CPropertyRectDState::isAllowInvalid() const
	{
		return m_bAllowInvalid;
	}

	bool CPropertyRectDState::isAllowEmpty() const
	{
		return m_bAllowEmpty;
	}
#pragma endregion

#pragma region IPropertyRectDState setters
	bool CPropertyRectDState::setValue(const String &state, const RectD value)
	{
		RectD v{ value };
		if (m_bMin)
		{
			v.Left = ntl::Max<double>(m_fMin, v.Left);
			v.Top = ntl::Max<double>(m_fMin, v.Top);
			v.Right = ntl::Max<double>(m_fMin, v.Right);
			v.Bottom = ntl::Max<double>(m_fMin, v.Bottom);
		}
		if (m_bMax)
		{
			v.Left = ntl::Min<double>(m_fMax, v.Left);
			v.Top = ntl::Min<double>(m_fMax, v.Top);
			v.Right = ntl::Min<double>(m_fMax, v.Right);
			v.Bottom = ntl::Min<double>(m_fMax, v.Bottom);
		}
		if (!m_bAllowInvalid && !v.is_valid())
			return false;
		if (!m_bAllowEmpty && v.is_empty())
			return false;
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, state, v);
		if (IsNotEqual(v, m_aValue[state]))
		{
			m_aValue[state] = v;
			return true;
		}
		return false;
	}

	IPropertyRectDState *CPropertyRectDState::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyRectDState *CPropertyRectDState::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyRectDState *CPropertyRectDState::setMin(const double value)
	{
		m_fMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyRectDState *CPropertyRectDState::setMax(const double value)
	{
		m_fMax = value;
		m_bMax = true;
		return this;
	}

	IPropertyRectDState *CPropertyRectDState::setAllowInvalid(const bool value)
	{
		m_bAllowInvalid = value;
		return this;
	}

	IPropertyRectDState *CPropertyRectDState::setAllowEmpty(const bool value)
	{
		m_bAllowEmpty = value;
		return this;
	}
#pragma endregion
}