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
	CPropertyIdentifier::CPropertyIdentifier(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerIdentifier, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false }
	{

	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyIdentifier::getPreview()
	{
		return getValue();
	}

	String CPropertyIdentifier::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyIdentifier::isChanged()
	{
		return m_bChanged || getValue() != m_tOld;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyIdentifier::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyIdentifier::Copy(IProperty *dest)
	{
		IPropertyIdentifier *d{ cast<IPropertyIdentifier*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyIdentifier::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyIdentifier::Load(const Variant &src)
	{
		String v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyIdentifier::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(L\"" << getValue() << L"\");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(L\"" << getValue() << L"\");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyIdentifier getters
	String CPropertyIdentifier::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}
#pragma endregion

#pragma region IPropertyIdentifier setters
	bool CPropertyIdentifier::setValue(const String value)
	{
		if (!isCppIdentifier(ReplaceAll(value, StringKeyValue{ L"{type}", L"" })))
			return false;
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