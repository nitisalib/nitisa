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
	CPropertyFloat::CPropertyFloat(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerFloat, skip, read_only),
		m_bMin{ false },
		m_bMax{ false },
		m_fMin{ 0 },
		m_fMax{ 0 },
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false }
	{

	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyFloat::getPreview()
	{
		return ToStringCompact(getValue());
	}

	String CPropertyFloat::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyFloat::isChanged()
	{
		return m_bChanged || ntl::IsNotEqual<float>(getValue(), m_tOld);
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyFloat::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyFloat::Copy(IProperty *dest)
	{
		IPropertyFloat *d{ cast<IPropertyFloat*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyFloat::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyFloat::Load(const Variant &src)
	{
		float v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyFloat::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyFloat getters
	float CPropertyFloat::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	bool CPropertyFloat::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyFloat::hasMax() const
	{
		return m_bMax;
	}

	float CPropertyFloat::getMin() const
	{
		return m_fMin;
	}

	float CPropertyFloat::getMax() const
	{
		return m_fMax;
	}
#pragma endregion

#pragma region IPropertyFloat setters
	bool CPropertyFloat::setValue(const float value)
	{
		float v{ value };
		if (m_bMin)
			v = ntl::Max<float>(m_fMin, v);
		if (m_bMax)
			v = ntl::Min<float>(m_fMax, v);
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, v);
		if (ntl::IsNotEqual<float>(v, m_tValue))
		{
			m_tValue = v;
			return true;
		}
		return false;
	}

	IPropertyFloat *CPropertyFloat::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyFloat *CPropertyFloat::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyFloat *CPropertyFloat::setMin(const float value)
	{
		m_fMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyFloat *CPropertyFloat::setMax(const float value)
	{
		m_fMax = value;
		m_bMax = true;
		return this;
	}
#pragma endregion
}