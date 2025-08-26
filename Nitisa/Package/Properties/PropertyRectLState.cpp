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
	CPropertyRectLState::CPropertyRectLState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerRectL, skip, read_only, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_bMin{ false },
		m_bMax{ false },
		m_iMin{ 0 },
		m_iMax{ 0 },
		m_bAllowInvalid{ true },
		m_bAllowEmpty{ true }
	{
		AddHeaderFile(L"Nitisa/Math/RectL.h");
		for (int i = 0; i < getStateCount(); i++)
		{
			m_aOld[getState(i)] = m_fGetter(m_pParent, getState(i));
			m_aValue[getState(i)] = m_fGetter(m_pParent, getState(i));
		}
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyRectLState::getPreview()
	{
		return L"";
	}

	String CPropertyRectLState::getPreview(const String &state)
	{
		return ToString(getValue(state));
	}

	bool CPropertyRectLState::isChanged()
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
	IProperty *CPropertyRectLState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyRectLState::Copy(IProperty *dest)
	{
		IPropertyRectLState *d{ cast<IPropertyRectLState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyRectLState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
	}

	void CPropertyRectLState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			RectL v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyRectLState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyRectLState getters
	RectL CPropertyRectLState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_aValue[state];
	}

	bool CPropertyRectLState::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyRectLState::hasMax() const
	{
		return m_bMax;
	}

	long long CPropertyRectLState::getMin() const
	{
		return m_iMin;
	}

	long long CPropertyRectLState::getMax() const
	{
		return m_iMax;
	}

	bool CPropertyRectLState::isAllowInvalid() const
	{
		return m_bAllowInvalid;
	}

	bool CPropertyRectLState::isAllowEmpty() const
	{
		return m_bAllowEmpty;
	}
#pragma endregion

#pragma region IPropertyRectLState setters
	bool CPropertyRectLState::setValue(const String &state, const RectL value)
	{
		RectL v{ value };
		if (m_bMin)
		{
			v.Left = ntl::Max<long long>(m_iMin, v.Left);
			v.Top = ntl::Max<long long>(m_iMin, v.Top);
			v.Right = ntl::Max<long long>(m_iMin, v.Right);
			v.Bottom = ntl::Max<long long>(m_iMin, v.Bottom);
		}
		if (m_bMax)
		{
			v.Left = ntl::Min<long long>(m_iMax, v.Left);
			v.Top = ntl::Min<long long>(m_iMax, v.Top);
			v.Right = ntl::Min<long long>(m_iMax, v.Right);
			v.Bottom = ntl::Min<long long>(m_iMax, v.Bottom);
		}
		if (!m_bAllowInvalid && !v.is_valid())
			return false;
		if (!m_bAllowEmpty && v.is_empty())
			return false;
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, state, v);
		if (v != m_aValue[state])
		{
			m_aValue[state] = v;
			return true;
		}
		return false;
	}

	IPropertyRectLState *CPropertyRectLState::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyRectLState *CPropertyRectLState::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyRectLState *CPropertyRectLState::setMin(const long long value)
	{
		m_iMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyRectLState *CPropertyRectLState::setMax(const long long value)
	{
		m_iMax = value;
		m_bMax = true;
		return this;
	}

	IPropertyRectLState *CPropertyRectLState::setAllowInvalid(const bool value)
	{
		m_bAllowInvalid = value;
		return this;
	}

	IPropertyRectLState *CPropertyRectLState::setAllowEmpty(const bool value)
	{
		m_bAllowEmpty = value;
		return this;
	}
#pragma endregion
}