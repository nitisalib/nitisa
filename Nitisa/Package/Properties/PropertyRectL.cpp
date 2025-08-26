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
	CPropertyRectL::CPropertyRectL(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerRectL, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_bMin{ false },
		m_bMax{ false },
		m_iMin{ 0 },
		m_iMax{ 0 },
		m_bAllowEmpty{ true },
		m_bAllowInvalid{ true }
	{
		AddHeaderFile(L"Nitisa/Math/RectL.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyRectL::getPreview()
	{
		return ToString(getValue());
	}

	String CPropertyRectL::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyRectL::isChanged()
	{
		return m_bChanged || getValue() != m_tOld;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyRectL::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyRectL::Copy(IProperty *dest)
	{
		IPropertyRectL *d{ cast<IPropertyRectL*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyRectL::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyRectL::Load(const Variant &src)
	{
		RectL v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyRectL::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyRectL getters
	RectL CPropertyRectL::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	bool CPropertyRectL::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyRectL::hasMax() const
	{
		return m_bMax;
	}

	long long CPropertyRectL::getMin() const
	{
		return m_iMin;
	}

	long long CPropertyRectL::getMax() const
	{
		return m_iMax;
	}

	bool CPropertyRectL::isAllowInvalid() const
	{
		return m_bAllowInvalid;
	}

	bool CPropertyRectL::isAllowEmpty() const
	{
		return m_bAllowEmpty;
	}
#pragma endregion

#pragma region IPropertyRectL setters
	bool CPropertyRectL::setValue(const RectL value)
	{
		RectL v{ value };
		if (m_bMin)
		{
			v.Left = ntl::Max<long long>(m_iMin, v.Left);
			v.Top = ntl::Max<long long>(m_iMin, v.Top);
			v.Right = ntl::Max<long long>(m_iMin, v.Right);
			v.Bottom = ntl::Max<long long>(m_iMin, v.Bottom);
		}
		if (m_bMax)
		{
			v.Left = ntl::Min<long long>(m_iMax, v.Left);
			v.Top = ntl::Min<long long>(m_iMax, v.Top);
			v.Right = ntl::Min<long long>(m_iMax, v.Right);
			v.Bottom = ntl::Min<long long>(m_iMax, v.Bottom);
		}
		if (!m_bAllowInvalid && !v.is_valid())
			return false;
		if (!m_bAllowEmpty && v.is_empty())
			return false;
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, v);
		if (v != m_tValue)
		{
			m_tValue = v;
			return true;
		}
		return false;
	}

	IPropertyRectL *CPropertyRectL::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyRectL *CPropertyRectL::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyRectL *CPropertyRectL::setMin(const long long value)
	{
		m_iMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyRectL *CPropertyRectL::setMax(const long long value)
	{
		m_iMax = value;
		m_bMax = true;
		return this;
	}

	IPropertyRectL *CPropertyRectL::setAllowInvalid(const bool value)
	{
		m_bAllowInvalid = value;
		return this;
	}

	IPropertyRectL *CPropertyRectL::setAllowEmpty(const bool value)
	{
		m_bAllowEmpty = value;
		return this;
	}
#pragma endregion
}