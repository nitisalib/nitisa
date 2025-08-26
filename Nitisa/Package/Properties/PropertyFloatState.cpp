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
	CPropertyFloatState::CPropertyFloatState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerFloat, skip, read_only, states, state_prefix_type, state_prefix),
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
	String CPropertyFloatState::getPreview()
	{
		return L"";
	}

	String CPropertyFloatState::getPreview(const String &state)
	{
		return ToStringCompact(getValue(state));
	}

	bool CPropertyFloatState::isChanged()
	{
		if (m_bChanged)
			return true;
		for (int i = 0; i < getStateCount(); i++)
			if (ntl::IsNotEqual<float>(getValue(getState(i)), m_aOld[getState(i)]))
				return true;
		return false;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyFloatState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyFloatState::Copy(IProperty *dest)
	{
		IPropertyFloatState *d{ cast<IPropertyFloatState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyFloatState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
	}

	void CPropertyFloatState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			float v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyFloatState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyFloatState getters
	float CPropertyFloatState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_aValue[state];
	}

	bool CPropertyFloatState::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyFloatState::hasMax() const
	{
		return m_bMax;
	}

	float CPropertyFloatState::getMin() const
	{
		return m_fMin;
	}

	float CPropertyFloatState::getMax() const
	{
		return m_fMax;
	}
#pragma endregion

#pragma region IPropertyFloatState setters
	bool CPropertyFloatState::setValue(const String &state, const float value)
	{
		float v{ value };
		if (m_bMin)
			v = ntl::Max<float>(m_fMin, v);
		if (m_bMax)
			v = ntl::Min<float>(m_fMax, v);
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, state, v);
		if (ntl::IsNotEqual<float>(v, m_aValue[state]))
		{
			m_aValue[state] = v;
			return true;
		}
		return false;
	}

	IPropertyFloatState *CPropertyFloatState::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyFloatState *CPropertyFloatState::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyFloatState *CPropertyFloatState::setMin(const float value)
	{
		m_fMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyFloatState *CPropertyFloatState::setMax(const float value)
	{
		m_fMax = value;
		m_bMax = true;
		return this;
	}
#pragma endregion
}