// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	CPropertyString::CPropertyString(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerString, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false }
	{

	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyString::getPreview()
	{
		return getValue();
	}

	String CPropertyString::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyString::isChanged()
	{
		return m_bChanged || getValue() != m_tOld;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyString::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyString::Copy(IProperty *dest)
	{
		IPropertyString *d{ cast<IPropertyString*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyString::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyString::Load(const Variant &src)
	{
		String v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyString::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(UTF8ToString(\"" << ReplaceAll(getValue(), EncodeEscape) << L"\"));" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(UTF8ToString(\"" << ReplaceAll(getValue(), EncodeEscape) << L"\"));" << std::endl;
	}
#pragma endregion

#pragma region IPropertyString getters
	String CPropertyString::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}
#pragma endregion

#pragma region IPropertyString setters
	bool CPropertyString::setValue(const String value)
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