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
	CPropertyBorderColor::CPropertyBorderColor(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerBorderColor, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false }
	{
		AddHeaderFile(L"Nitisa/Image/BorderColor.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyBorderColor::getPreview()
	{
		return ToString(getValue());
	}

	String CPropertyBorderColor::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyBorderColor::isChanged()
	{
		return m_bChanged || getValue() != m_tOld;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyBorderColor::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyBorderColor::Copy(IProperty *dest)
	{
		IPropertyBorderColor *d{ cast<IPropertyBorderColor*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyBorderColor::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyBorderColor::Load(const Variant &src)
	{
		BorderColor v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyBorderColor::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyBorderColor getters
	BorderColor CPropertyBorderColor::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}
#pragma endregion

#pragma region IPropertyBorderColor setters
	bool CPropertyBorderColor::setValue(const BorderColor value)
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