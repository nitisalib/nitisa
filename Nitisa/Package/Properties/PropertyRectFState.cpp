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
	CPropertyRectFState::CPropertyRectFState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerRectF, skip, read_only, states, state_prefix_type, state_prefix),
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
		AddHeaderFile(L"Nitisa/Math/RectF.h");
		for (int i = 0; i < getStateCount(); i++)
		{
			m_aOld[getState(i)] = m_fGetter(m_pParent, getState(i));
			m_aValue[getState(i)] = m_fGetter(m_pParent, getState(i));
		}
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyRectFState::getPreview()
	{
		return L"";
	}

	String CPropertyRectFState::getPreview(const String &state)
	{
		return ToString(getValue(state));
	}

	bool CPropertyRectFState::isChanged()
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
	IProperty *CPropertyRectFState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyRectFState::Copy(IProperty *dest)
	{
		IPropertyRectFState *d{ cast<IPropertyRectFState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyRectFState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
	}

	void CPropertyRectFState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			RectF v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyRectFState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyRectFState getters
	RectF CPropertyRectFState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_aValue[state];
	}

	bool CPropertyRectFState::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyRectFState::hasMax() const
	{
		return m_bMax;
	}

	float CPropertyRectFState::getMin() const
	{
		return m_fMin;
	}

	float CPropertyRectFState::getMax() const
	{
		return m_fMax;
	}

	bool CPropertyRectFState::isAllowInvalid() const
	{
		return m_bAllowInvalid;
	}

	bool CPropertyRectFState::isAllowEmpty() const
	{
		return m_bAllowEmpty;
	}
#pragma endregion

#pragma region IPropertyRectFState setters
	bool CPropertyRectFState::setValue(const String &state, const RectF value)
	{
		RectF v{ value };
		if (m_bMin)
		{
			v.Left = ntl::Max<float>(m_fMin, v.Left);
			v.Top = ntl::Max<float>(m_fMin, v.Top);
			v.Right = ntl::Max<float>(m_fMin, v.Right);
			v.Bottom = ntl::Max<float>(m_fMin, v.Bottom);
		}
		if (m_bMax)
		{
			v.Left = ntl::Min<float>(m_fMax, v.Left);
			v.Top = ntl::Min<float>(m_fMax, v.Top);
			v.Right = ntl::Min<float>(m_fMax, v.Right);
			v.Bottom = ntl::Min<float>(m_fMax, v.Bottom);
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

	IPropertyRectFState *CPropertyRectFState::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyRectFState *CPropertyRectFState::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyRectFState *CPropertyRectFState::setMin(const float value)
	{
		m_fMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyRectFState *CPropertyRectFState::setMax(const float value)
	{
		m_fMax = value;
		m_bMax = true;
		return this;
	}

	IPropertyRectFState *CPropertyRectFState::setAllowInvalid(const bool value)
	{
		m_bAllowInvalid = value;
		return this;
	}

	IPropertyRectFState *CPropertyRectFState::setAllowEmpty(const bool value)
	{
		m_bAllowEmpty = value;
		return this;
	}
#pragma endregion
}