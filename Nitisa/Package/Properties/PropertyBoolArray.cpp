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
	CPropertyBoolArray::CPropertyBoolArray(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerBoolArray, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_iMinCount{ 0 }
	{
		AddHeaderFile(L"Nitisa/Core/BoolArray.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyBoolArray::getPreview()
	{
		if (getValue().size() > 1)
			return ToString(getValue()[0]) + L", ...";
		if (getValue().size() == 1)
			return ToString(getValue()[0]);
		return L"";
	}

	String CPropertyBoolArray::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyBoolArray::isChanged()
	{
		return m_bChanged || getValue() != m_tOld;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyBoolArray::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyBoolArray::Copy(IProperty *dest)
	{
		IPropertyBoolArray *d{ cast<IPropertyBoolArray*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyBoolArray::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyBoolArray::Load(const Variant &src)
	{
		BoolArray v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyBoolArray::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyBoolArray getters
	BoolArray CPropertyBoolArray::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	int CPropertyBoolArray::getMinCount()
	{
		return m_iMinCount;
	}
#pragma endregion

#pragma region IPropertyBoolArray setters
	bool CPropertyBoolArray::setValue(const BoolArray value)
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

	IPropertyBoolArray *CPropertyBoolArray::setMinCount(const int value)
	{
		m_iMinCount = ntl::Max<int>(0, value);
		return this;
	}
#pragma endregion
}