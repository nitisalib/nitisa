// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	CPropertyPointD::CPropertyPointD(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerPointD, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_bMin{ false },
		m_bMax{ false },
		m_fMin{ 0 },
		m_fMax{ 0 }
	{
		AddHeaderFile(L"Nitisa/Math/PointD.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyPointD::getPreview()
	{
		return ToString(getValue());
	}

	String CPropertyPointD::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyPointD::isChanged()
	{
		return m_bChanged || IsNotEqual(getValue(), m_tOld);
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyPointD::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyPointD::Copy(IProperty *dest)
	{
		IPropertyPointD *d{ cast<IPropertyPointD*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyPointD::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyPointD::Load(const Variant &src)
	{
		PointD v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyPointD::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyPointD getters
	PointD CPropertyPointD::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	bool CPropertyPointD::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyPointD::hasMax() const
	{
		return m_bMax;
	}

	double CPropertyPointD::getMin() const
	{
		return m_fMin;
	}

	double CPropertyPointD::getMax() const
	{
		return m_fMax;
	}
#pragma endregion

#pragma region IPropertyPointD setters
	bool CPropertyPointD::setValue(const PointD value)
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
			return m_fSetter(m_pParent, v);
		if (IsNotEqual(v, m_tValue))
		{
			m_tValue = v;
			return true;
		}
		return false;
	}

	IPropertyPointD *CPropertyPointD::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyPointD *CPropertyPointD::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyPointD *CPropertyPointD::setMin(const double value)
	{
		m_fMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyPointD *CPropertyPointD::setMax(const double value)
	{
		m_fMax = value;
		m_bMax = true;
		return this;
	}
#pragma endregion
}