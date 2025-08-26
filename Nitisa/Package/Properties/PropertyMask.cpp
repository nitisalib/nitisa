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
	CPropertyMask::CPropertyMask(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerMask, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false }
	{

	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyMask::getPreview()
	{
		return AnsiToString(std::bitset<32>(getValue()).to_string());
	}

	String CPropertyMask::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyMask::isChanged()
	{
		return m_bChanged || getValue() != m_tOld;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyMask::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyMask::Copy(IProperty *dest)
	{
		IPropertyMask *d{ cast<IPropertyMask*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyMask::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyMask::Load(const Variant &src)
	{
		unsigned int v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyMask::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(0b" << getPreview() << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(0b" << getPreview() << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyMask getters
	unsigned int CPropertyMask::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}
#pragma endregion

#pragma region IPropertyMask setters
	bool CPropertyMask::setValue(const unsigned int value)
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