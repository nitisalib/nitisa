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
	CPropertyRectD::CPropertyRectD(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerRectD, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_bMin{ false },
		m_bMax{ false },
		m_fMin{ 0 },
		m_fMax{ 0 },
		m_bAllowEmpty{ true },
		m_bAllowInvalid{ true }
	{
		AddHeaderFile(L"Nitisa/Math/RectD.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyRectD::getPreview()
	{
		return ToString(getValue());
	}

	String CPropertyRectD::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyRectD::isChanged()
	{
		return m_bChanged || IsNotEqual(getValue(), m_tOld);
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyRectD::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyRectD::Copy(IProperty *dest)
	{
		IPropertyRectD *d{ cast<IPropertyRectD*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyRectD::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyRectD::Load(const Variant &src)
	{
		RectD v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyRectD::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyRectD getters
	RectD CPropertyRectD::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	bool CPropertyRectD::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyRectD::hasMax() const
	{
		return m_bMax;
	}

	double CPropertyRectD::getMin() const
	{
		return m_fMin;
	}

	double CPropertyRectD::getMax() const
	{
		return m_fMax;
	}

	bool CPropertyRectD::isAllowInvalid() const
	{
		return m_bAllowInvalid;
	}

	bool CPropertyRectD::isAllowEmpty() const
	{
		return m_bAllowEmpty;
	}
#pragma endregion

#pragma region IPropertyRectD setters
	bool CPropertyRectD::setValue(const RectD value)
	{
		RectD v{ value };
		if (m_bMin)
		{
			v.Left = ntl::Max<double>(m_fMin, v.Left);
			v.Top = ntl::Max<double>(m_fMin, v.Top);
			v.Right = ntl::Max<double>(m_fMin, v.Right);
			v.Bottom = ntl::Max<double>(m_fMin, v.Bottom);
		}
		if (m_bMax)
		{
			v.Left = ntl::Min<double>(m_fMax, v.Left);
			v.Top = ntl::Min<double>(m_fMax, v.Top);
			v.Right = ntl::Min<double>(m_fMax, v.Right);
			v.Bottom = ntl::Min<double>(m_fMax, v.Bottom);
		}
		if (!m_bAllowInvalid && !v.is_valid())
			return false;
		if (!m_bAllowEmpty && v.is_empty())
			return false;
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, v);
		if (IsNotEqual(v, m_tValue))
		{
			m_tValue = v;
			return true;
		}
		return false;
	}

	IPropertyRectD *CPropertyRectD::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyRectD *CPropertyRectD::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyRectD *CPropertyRectD::setMin(const double value)
	{
		m_fMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyRectD *CPropertyRectD::setMax(const double value)
	{
		m_fMax = value;
		m_bMax = true;
		return this;
	}

	IPropertyRectD *CPropertyRectD::setAllowInvalid(const bool value)
	{
		m_bAllowInvalid = value;
		return this;
	}

	IPropertyRectD *CPropertyRectD::setAllowEmpty(const bool value)
	{
		m_bAllowEmpty = value;
		return this;
	}
#pragma endregion
}