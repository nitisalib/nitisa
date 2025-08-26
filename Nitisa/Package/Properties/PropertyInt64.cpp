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
	CPropertyInt64::CPropertyInt64(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerInt64, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_bMin{ false },
		m_bMax{ false },
		m_iMin{ 0 },
		m_iMax{ 0 }
	{

	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyInt64::getPreview()
	{
		return ToString(getValue());
	}

	String CPropertyInt64::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyInt64::isChanged()
	{
		return m_bChanged || getValue() != m_tOld;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyInt64::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyInt64::Copy(IProperty *dest)
	{
		IPropertyInt64 *d{ cast<IPropertyInt64*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyInt64::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyInt64::Load(const Variant &src)
	{
		long long v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyInt64::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << getValue() << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << getValue() << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyInt64 getters
	long long CPropertyInt64::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	bool CPropertyInt64::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyInt64::hasMax() const
	{
		return m_bMax;
	}

	long long CPropertyInt64::getMin() const
	{
		return m_iMin;
	}

	long long CPropertyInt64::getMax() const
	{
		return m_iMax;
	}
#pragma endregion

#pragma region IPropertyInt64 setters
	bool CPropertyInt64::setValue(const long long value)
	{
		long long v{ value };
		if (m_bMin)
			v = ntl::Max<long long>(m_iMin, v);
		if (m_bMax)
			v = ntl::Min<long long>(m_iMax, v);
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, v);
		if (v != m_tValue)
		{
			m_tValue = v;
			return true;
		}
		return false;
	}

	IPropertyInt64 *CPropertyInt64::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyInt64 *CPropertyInt64::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyInt64 *CPropertyInt64::setMin(const long long value)
	{
		m_iMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyInt64 *CPropertyInt64::setMax(const long long value)
	{
		m_iMax = value;
		m_bMax = true;
		return this;
	}
#pragma endregion
}