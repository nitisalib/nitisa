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
	CPropertyIntegerArray::CPropertyIntegerArray(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerIntegerArray, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_iMinCount{ 0 },
		m_bMin{ false },
		m_bMax{ false },
		m_iMin{ 0 },
		m_iMax{ 0 }
	{
		AddHeaderFile(L"Nitisa/Math/IntegerArray.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyIntegerArray::getPreview()
	{
		if (getValue().size() > 1)
			return ToString(getValue()[0]) + L", ...";
		if (getValue().size() == 1)
			return ToString(getValue()[0]);
		return L"";
	}

	String CPropertyIntegerArray::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyIntegerArray::isChanged()
	{
		return m_bChanged || getValue() != m_tOld;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyIntegerArray::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyIntegerArray::Copy(IProperty *dest)
	{
		IPropertyIntegerArray *d{ cast<IPropertyIntegerArray*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyIntegerArray::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyIntegerArray::Load(const Variant &src)
	{
		IntegerArray v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyIntegerArray::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyIntegerArray getters
	IntegerArray CPropertyIntegerArray::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	int CPropertyIntegerArray::getMinCount()
	{
		return m_iMinCount;
	}

	bool CPropertyIntegerArray::hasMin()
	{
		return m_bMin;
	}

	bool CPropertyIntegerArray::hasMax()
	{
		return m_bMax;
	}

	int CPropertyIntegerArray::getMin()
	{
		return m_iMin;
	}

	int CPropertyIntegerArray::getMax()
	{
		return m_iMax;
	}
#pragma endregion

#pragma region IPropertyIntegerArray setters
	bool CPropertyIntegerArray::setValue(const IntegerArray value)
	{
		auto v{ value };
		if (m_bMin || m_bMax)
			for (auto &i : v)
			{
				if (m_bMin)
					i = ntl::Max<int>(m_iMin, i);
				if (m_bMax)
					i = ntl::Min<int>(m_iMax, i);
			}
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, v);
		if (v != m_tValue)
		{
			m_tValue = v;
			return true;
		}
		return false;
	}

	IPropertyIntegerArray *CPropertyIntegerArray::setMinCount(const int value)
	{
		m_iMinCount = ntl::Max<int>(0, value);
		return this;
	}

	IPropertyIntegerArray *CPropertyIntegerArray::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyIntegerArray *CPropertyIntegerArray::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyIntegerArray *CPropertyIntegerArray::setMin(const int value)
	{
		m_iMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyIntegerArray *CPropertyIntegerArray::setMax(const int value)
	{
		m_iMax = value;
		m_bMax = true;
		return this;
	}
#pragma endregion
}