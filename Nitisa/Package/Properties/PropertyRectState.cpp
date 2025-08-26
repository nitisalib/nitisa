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
	CPropertyRectState::CPropertyRectState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerRect, skip, read_only, states, state_prefix_type, state_prefix),
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
		AddHeaderFile(L"Nitisa/Math/Rect.h");
		for (int i = 0; i < getStateCount(); i++)
		{
			m_aOld[getState(i)] = m_fGetter(m_pParent, getState(i));
			m_aValue[getState(i)] = m_fGetter(m_pParent, getState(i));
		}
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyRectState::getPreview()
	{
		return L"";
	}

	String CPropertyRectState::getPreview(const String &state)
	{
		return ToString(getValue(state));
	}

	bool CPropertyRectState::isChanged()
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
	IProperty *CPropertyRectState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyRectState::Copy(IProperty *dest)
	{
		IPropertyRectState *d{ cast<IPropertyRectState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyRectState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
	}

	void CPropertyRectState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			Rect v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyRectState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyRectState getters
	Rect CPropertyRectState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_aValue[state];
	}

	bool CPropertyRectState::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyRectState::hasMax() const
	{
		return m_bMax;
	}

	int CPropertyRectState::getMin() const
	{
		return m_iMin;
	}

	int CPropertyRectState::getMax() const
	{
		return m_iMax;
	}

	bool CPropertyRectState::isAllowInvalid() const
	{
		return m_bAllowInvalid;
	}

	bool CPropertyRectState::isAllowEmpty() const
	{
		return m_bAllowEmpty;
	}
#pragma endregion

#pragma region IPropertyRectState setters
	bool CPropertyRectState::setValue(const String &state, const Rect value)
	{
		Rect v{ value };
		if (m_bMin)
		{
			v.Left = ntl::Max<int>(m_iMin, v.Left);
			v.Top = ntl::Max<int>(m_iMin, v.Top);
			v.Right = ntl::Max<int>(m_iMin, v.Right);
			v.Bottom = ntl::Max<int>(m_iMin, v.Bottom);
		}
		if (m_bMax)
		{
			v.Left = ntl::Min<int>(m_iMax, v.Left);
			v.Top = ntl::Min<int>(m_iMax, v.Top);
			v.Right = ntl::Min<int>(m_iMax, v.Right);
			v.Bottom = ntl::Min<int>(m_iMax, v.Bottom);
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

	IPropertyRectState *CPropertyRectState::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyRectState *CPropertyRectState::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyRectState *CPropertyRectState::setMin(const int value)
	{
		m_iMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyRectState *CPropertyRectState::setMax(const int value)
	{
		m_iMax = value;
		m_bMax = true;
		return this;
	}

	IPropertyRectState *CPropertyRectState::setAllowInvalid(const bool value)
	{
		m_bAllowInvalid = value;
		return this;
	}

	IPropertyRectState *CPropertyRectState::setAllowEmpty(const bool value)
	{
		m_bAllowEmpty = value;
		return this;
	}
#pragma endregion
}