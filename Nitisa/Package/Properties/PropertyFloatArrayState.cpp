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
	CPropertyFloatArrayState::CPropertyFloatArrayState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerFloatArray, skip, read_only, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_iMinCount{ 0 },
		m_bHasMin{ false },
		m_bHasMax{ false },
		m_fMin{ 0 },
		m_fMax{ 0 }
	{
		AddHeaderFile(L"Nitisa/Math/FloatArray.h");
		for (int i = 0; i < getStateCount(); i++)
		{
			m_tOld[getState(i)] = m_fGetter(m_pParent, getState(i));
			m_tValue[getState(i)] = m_fGetter(m_pParent, getState(i));
		}
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyFloatArrayState::getPreview()
	{
		return L"";
	}

	String CPropertyFloatArrayState::getPreview(const String &state)
	{
		if (getValue(state).size() > 1)
			return ToStringCompact(getValue(state)[0]) + L", ...";
		if (getValue(state).size() == 1)
			return ToStringCompact(getValue(state)[0]);
		return L"";
	}

	bool CPropertyFloatArrayState::isChanged()
	{
		if (m_bChanged)
			return true;
		for (int i = 0; i < getStateCount(); i++)
		{
			auto value{ getValue(getState(i)) };
			if (value.size() != m_tOld[getState(i)].size())
				return true;
			for (size_t index = 0; index < value.size(); index++)
				if (ntl::IsNotEqual<float>(value[index], m_tOld[getState(i)][index]))
					return true;
		}
		return false;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyFloatArrayState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyFloatArrayState::Copy(IProperty *dest)
	{
		IPropertyFloatArrayState *d{ cast<IPropertyFloatArrayState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyFloatArrayState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
	}

	void CPropertyFloatArrayState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			FloatArray v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyFloatArrayState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyFloatArrayState getters
	FloatArray CPropertyFloatArrayState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_tValue[state];
	}

	int CPropertyFloatArrayState::getMinCount()
	{
		return m_iMinCount;
	}

	bool CPropertyFloatArrayState::hasMin()
	{
		return m_bHasMin;
	}

	bool CPropertyFloatArrayState::hasMax()
	{
		return m_bHasMax;
	}

	float CPropertyFloatArrayState::getMin()
	{
		return m_fMin;
	}

	float CPropertyFloatArrayState::getMax()
	{
		return m_fMax;
	}
#pragma endregion

#pragma region IPropertyFloatArrayState setters
	bool CPropertyFloatArrayState::setValue(const String &state, const FloatArray value)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, state, value);
		if (IsNotEqual(value, m_tValue[state]))
		{
			m_tValue [state]= value;
			return true;
		}
		return false;
	}

	IPropertyFloatArrayState *CPropertyFloatArrayState::setMinCount(const int value)
	{
		m_iMinCount = ntl::Max<int>(0, value);
		return this;
	}

	IPropertyFloatArrayState *CPropertyFloatArrayState::setHasMin(const bool value)
	{
		m_bHasMin = value;
		return this;
	}

	IPropertyFloatArrayState *CPropertyFloatArrayState::setHasMax(const bool value)
	{
		m_bHasMax = value;
		return this;
	}

	IPropertyFloatArrayState *CPropertyFloatArrayState::setMin(const float value)
	{
		m_fMin = value;
		m_bHasMin = true;
		return this;
	}

	IPropertyFloatArrayState *CPropertyFloatArrayState::setMax(const float value)
	{
		m_fMax = value;
		m_bHasMax = true;
		return this;
	}
#pragma endregion
}