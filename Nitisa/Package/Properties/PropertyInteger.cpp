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
	CPropertyInteger::CPropertyInteger(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerInteger, skip, read_only),
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
	String CPropertyInteger::getPreview()
	{
		return ToString(getValue());
	}

	String CPropertyInteger::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyInteger::isChanged()
	{
		return m_bChanged || getValue() != m_tOld;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyInteger::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyInteger::Copy(IProperty *dest)
	{
		IPropertyInteger *d{ cast<IPropertyInteger*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyInteger::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyInteger::Load(const Variant &src)
	{
		int v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyInteger::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << getValue() << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << getValue() << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyInteger getters
	int CPropertyInteger::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	bool CPropertyInteger::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyInteger::hasMax() const
	{
		return m_bMax;
	}

	int CPropertyInteger::getMin() const
	{
		return m_iMin;
	}

	int CPropertyInteger::getMax() const
	{
		return m_iMax;
	}
#pragma endregion

#pragma region IPropertyInteger setters
	bool CPropertyInteger::setValue(const int value)
	{
		int v{ value };
		if (m_bMin)
			v = ntl::Max<int>(m_iMin, v);
		if (m_bMax)
			v = ntl::Min<int>(m_iMax, v);
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, v);
		if (v != m_tValue)
		{
			m_tValue = v;
			return true;
		}
		return false;
	}

	IPropertyInteger *CPropertyInteger::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyInteger *CPropertyInteger::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyInteger *CPropertyInteger::setMin(const int value)
	{
		m_iMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyInteger *CPropertyInteger::setMax(const int value)
	{
		m_iMax = value;
		m_bMax = true;
		return this;
	}
#pragma endregion
}