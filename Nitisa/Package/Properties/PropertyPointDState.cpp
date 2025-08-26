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
	CPropertyPointDState::CPropertyPointDState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerPointD, skip, read_only, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_bMin{ false },
		m_bMax{ false },
		m_fMin{ 0 },
		m_fMax{ 0 }
	{
		AddHeaderFile(L"Nitisa/Math/Point.h");
		for (int i = 0; i < getStateCount(); i++)
		{
			m_aOld[getState(i)] = m_fGetter(m_pParent, getState(i));
			m_aValue[getState(i)] = m_fGetter(m_pParent, getState(i));
		}
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyPointDState::getPreview()
	{
		return L"";
	}

	String CPropertyPointDState::getPreview(const String &state)
	{
		return ToString(getValue(state));
	}

	bool CPropertyPointDState::isChanged()
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
	IProperty *CPropertyPointDState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyPointDState::Copy(IProperty *dest)
	{
		IPropertyPointDState *d{ cast<IPropertyPointDState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyPointDState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
	}

	void CPropertyPointDState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			PointD v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyPointDState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyPointDState getters
	PointD CPropertyPointDState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_aValue[state];
	}

	bool CPropertyPointDState::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyPointDState::hasMax() const
	{
		return m_bMax;
	}

	double CPropertyPointDState::getMin() const
	{
		return m_fMin;
	}

	double CPropertyPointDState::getMax() const
	{
		return m_fMax;
	}
#pragma endregion

#pragma region IPropertyPointDState setters
	bool CPropertyPointDState::setValue(const String &state, const PointD value)
	{
		PointD v{ value };
		if (m_bMin)
		{
			v.X = ntl::Max<double>(m_fMin, v.X);
			v.Y = ntl::Max<double>(m_fMin, v.Y);
		}
		if (m_bMax)
		{
			v.X = ntl::Min<double>(m_fMax, v.X);
			v.Y = ntl::Min<double>(m_fMax, v.Y);
		}
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, state, v);
		if (IsNotEqual(v, m_aValue[state]))
		{
			m_aValue[state] = v;
			return true;
		}
		return false;
	}

	IPropertyPointDState *CPropertyPointDState::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyPointDState *CPropertyPointDState::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyPointDState *CPropertyPointDState::setMin(const double value)
	{
		m_fMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyPointDState *CPropertyPointDState::setMax(const double value)
	{
		m_fMax = value;
		m_bMax = true;
		return this;
	}
#pragma endregion
}