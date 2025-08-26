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
	CPropertyDouble::CPropertyDouble(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerDouble, skip, read_only),
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
	String CPropertyDouble::getPreview()
	{
		return ToStringCompact(getValue());
	}

	String CPropertyDouble::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyDouble::isChanged()
	{
		return m_bChanged || ntl::IsNotEqual<double>(getValue(), m_tOld);
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyDouble::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyDouble::Copy(IProperty *dest)
	{
		IPropertyDouble *d{ cast<IPropertyDouble*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyDouble::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyDouble::Load(const Variant &src)
	{
		double v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyDouble::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyDouble getters
	double CPropertyDouble::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	bool CPropertyDouble::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyDouble::hasMax() const
	{
		return m_bMax;
	}

	double CPropertyDouble::getMin() const
	{
		return m_fMin;
	}

	double CPropertyDouble::getMax() const
	{
		return m_fMax;
	}
#pragma endregion

#pragma region IPropertyDouble setters
	bool CPropertyDouble::setValue(const double value)
	{
		double v{ value };
		if (m_bMin)
			v = ntl::Max<double>(m_fMin, v);
		if (m_bMax)
			v = ntl::Min<double>(m_fMax, v);
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, v);
		if (ntl::IsNotEqual<double>(v, m_tValue))
		{
			m_tValue = v;
			return true;
		}
		return false;
	}

	IPropertyDouble *CPropertyDouble::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyDouble *CPropertyDouble::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyDouble *CPropertyDouble::setMin(const double value)
	{
		m_fMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyDouble *CPropertyDouble::setMax(const double value)
	{
		m_fMax = value;
		m_bMax = true;
		return this;
	}
#pragma endregion
}