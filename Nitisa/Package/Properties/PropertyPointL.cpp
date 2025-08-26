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
	CPropertyPointL::CPropertyPointL(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerPointL, skip, read_only),
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
		AddHeaderFile(L"Nitisa/Math/PointL.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyPointL::getPreview()
	{
		return ToString(getValue());
	}

	String CPropertyPointL::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyPointL::isChanged()
	{
		return m_bChanged || getValue() != m_tOld;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyPointL::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyPointL::Copy(IProperty *dest)
	{
		IPropertyPointL *d{ cast<IPropertyPointL*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyPointL::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyPointL::Load(const Variant &src)
	{
		PointL v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyPointL::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyPointL getters
	PointL CPropertyPointL::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	bool CPropertyPointL::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyPointL::hasMax() const
	{
		return m_bMax;
	}

	long long CPropertyPointL::getMin() const
	{
		return m_iMin;
	}

	long long CPropertyPointL::getMax() const
	{
		return m_iMax;
	}
#pragma endregion

#pragma region IPropertyPointL setters
	bool CPropertyPointL::setValue(const PointL value)
	{
		PointL v{ value };
		if (m_bMin)
		{
			v.X = ntl::Max<long long>(m_iMin, v.X);
			v.Y = ntl::Max<long long>(m_iMin, v.Y);
		}
		if (m_bMax)
		{
			v.X = ntl::Min<long long>(m_iMax, v.X);
			v.Y = ntl::Min<long long>(m_iMax, v.Y);
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

	IPropertyPointL *CPropertyPointL::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyPointL *CPropertyPointL::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyPointL *CPropertyPointL::setMin(const long long value)
	{
		m_iMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyPointL *CPropertyPointL::setMax(const long long value)
	{
		m_iMax = value;
		m_bMax = true;
		return this;
	}
#pragma endregion
}