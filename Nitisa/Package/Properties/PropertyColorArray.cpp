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
	CPropertyColorArray::CPropertyColorArray(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerColorArray, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_iMinCount{ 0 }
	{
		AddHeaderFile(L"Nitisa/Image/ColorArray.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyColorArray::getPreview()
	{
		if (getValue().size() > 1)
			return L"{ " + ToString(getValue()[0]) + L" }, ...";
		if (getValue().size() == 1)
			return L"{ " + ToString(getValue()[0]) + L" }";
		return L"";
	}

	String CPropertyColorArray::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyColorArray::isChanged()
	{
		return m_bChanged || getValue() != m_tOld;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyColorArray::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyColorArray::Copy(IProperty *dest)
	{
		IPropertyColorArray *d{ cast<IPropertyColorArray*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyColorArray::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyColorArray::Load(const Variant &src)
	{
		ColorArray v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyColorArray::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyColorArray getters
	ColorArray CPropertyColorArray::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	int CPropertyColorArray::getMinCount()
	{
		return m_iMinCount;
	}
#pragma endregion

#pragma region IPropertyColorArray setters
	bool CPropertyColorArray::setValue(const ColorArray value)
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

	IPropertyColorArray *CPropertyColorArray::setMinCount(const int value)
	{
		m_iMinCount = ntl::Max<int>(0, value);
		return this;
	}
#pragma endregion
}