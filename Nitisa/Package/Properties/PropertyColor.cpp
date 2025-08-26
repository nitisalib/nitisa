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
	CPropertyColor::CPropertyColor(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerColor, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false }
	{
		AddHeaderFile(L"Nitisa/Image/Color.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyColor::getPreview()
	{
		return ToString(getValue());
	}

	String CPropertyColor::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyColor::isChanged()
	{
		return m_bChanged || getValue() != m_tOld;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyColor::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyColor::Copy(IProperty *dest)
	{
		IPropertyColor *d{ cast<IPropertyColor*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyColor::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyColor::Load(const Variant &src)
	{
		Color v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyColor::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyColor getters
	Color CPropertyColor::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}
#pragma endregion

#pragma region IPropertyColor setters
	bool CPropertyColor::setValue(const Color value)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, value);
		if (value != m_tValue)
		{
			m_tValue = value;
			return true;
		}
		return false;
	}
#pragma endregion
}