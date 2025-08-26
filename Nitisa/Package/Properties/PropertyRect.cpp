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
	CPropertyRect::CPropertyRect(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerRect, skip, read_only),
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
		AddHeaderFile(L"Nitisa/Math/Rect.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyRect::getPreview()
	{
		return ToString(getValue());
	}

	String CPropertyRect::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyRect::isChanged()
	{
		return m_bChanged || getValue() != m_tOld;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyRect::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyRect::Copy(IProperty *dest)
	{
		IPropertyRect *d{ cast<IPropertyRect*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyRect::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyRect::Load(const Variant &src)
	{
		Rect v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyRect::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyRect getters
	Rect CPropertyRect::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	bool CPropertyRect::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyRect::hasMax() const
	{
		return m_bMax;
	}

	int CPropertyRect::getMin() const
	{
		return m_iMin;
	}

	int CPropertyRect::getMax() const
	{
		return m_iMax;
	}

	bool CPropertyRect::isAllowInvalid() const
	{
		return m_bAllowInvalid;
	}

	bool CPropertyRect::isAllowEmpty() const
	{
		return m_bAllowEmpty;
	}
#pragma endregion

#pragma region IPropertyRect setters
	bool CPropertyRect::setValue(const Rect value)
	{
		Rect v{ value };
		if (m_bMin)
		{
			v.Left = ntl::Max<int>(m_iMin, v.Left);
			v.Top = ntl::Max<int>(m_iMin, v.Top);
			v.Right = ntl::Max<int>(m_iMin, v.Right);
			v.Bottom = ntl::Max<int>(m_iMin, v.Bottom);
		}
		if (m_bMax)
		{
			v.Left = ntl::Min<int>(m_iMax, v.Left);
			v.Top = ntl::Min<int>(m_iMax, v.Top);
			v.Right = ntl::Min<int>(m_iMax, v.Right);
			v.Bottom = ntl::Min<int>(m_iMax, v.Bottom);
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

	IPropertyRect *CPropertyRect::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyRect *CPropertyRect::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyRect *CPropertyRect::setMin(const int value)
	{
		m_iMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyRect *CPropertyRect::setMax(const int value)
	{
		m_iMax = value;
		m_bMax = true;
		return this;
	}

	IPropertyRect *CPropertyRect::setAllowInvalid(const bool value)
	{
		m_bAllowInvalid = value;
		return this;
	}

	IPropertyRect *CPropertyRect::setAllowEmpty(const bool value)
	{
		m_bAllowEmpty = value;
		return this;
	}
#pragma endregion
}