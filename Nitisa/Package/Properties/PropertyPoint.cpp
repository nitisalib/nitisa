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
	CPropertyPoint::CPropertyPoint(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerPoint, skip, read_only),
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
		AddHeaderFile(L"Nitisa/Math/Point.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyPoint::getPreview()
	{
		return ToString(getValue());
	}

	String CPropertyPoint::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyPoint::isChanged()
	{
		return m_bChanged || getValue() != m_tOld;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyPoint::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyPoint::Copy(IProperty *dest)
	{
		IPropertyPoint *d{ cast<IPropertyPoint*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyPoint::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyPoint::Load(const Variant &src)
	{
		Point v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyPoint::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyPoint getters
	Point CPropertyPoint::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	bool CPropertyPoint::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyPoint::hasMax() const
	{
		return m_bMax;
	}

	int CPropertyPoint::getMin() const
	{
		return m_iMin;
	}

	int CPropertyPoint::getMax() const
	{
		return m_iMax;
	}
#pragma endregion

#pragma region IPropertyPoint setters
	bool CPropertyPoint::setValue(const Point value)
	{
		Point v{ value };
		if (m_bMin)
		{
			v.X = ntl::Max<int>(m_iMin, v.X);
			v.Y = ntl::Max<int>(m_iMin, v.Y);
		}
		if (m_bMax)
		{
			v.X = ntl::Min<int>(m_iMax, v.X);
			v.Y = ntl::Min<int>(m_iMax, v.Y);
		}
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, v);
		if (v != m_tValue)
		{
			m_tValue = v;
			return true;
		}
		return false;
	}

	IPropertyPoint *CPropertyPoint::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyPoint *CPropertyPoint::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyPoint *CPropertyPoint::setMin(const int value)
	{
		m_iMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyPoint *CPropertyPoint::setMax(const int value)
	{
		m_iMax = value;
		m_bMax = true;
		return this;
	}
#pragma endregion
}