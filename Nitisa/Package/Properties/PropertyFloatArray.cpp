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
	CPropertyFloatArray::CPropertyFloatArray(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerFloatArray, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_iMinCount{ 0 },
		m_bHasMin{ false },
		m_bHasMax{ false },
		m_fMin{ 0 },
		m_fMax{ 0 }
	{
		AddHeaderFile(L"Nitisa/Math/FloatArray.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyFloatArray::getPreview()
	{
		if (getValue().size() > 1)
			return ToStringCompact(getValue()[0]) + L", ...";
		if (getValue().size() == 1)
			return ToStringCompact(getValue()[0]);
		return L"";
	}

	String CPropertyFloatArray::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyFloatArray::isChanged()
	{
		if (m_bChanged || getValue().size() != m_tOld.size())
			return true;
		auto value{ getValue() };
		for (size_t i = 0; i < value.size(); i++)
			if (ntl::IsNotEqual<float>(value[i], m_tOld[i]))
				return true;
		return false;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyFloatArray::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyFloatArray::Copy(IProperty *dest)
	{
		IPropertyFloatArray *d{ cast<IPropertyFloatArray*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyFloatArray::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyFloatArray::Load(const Variant &src)
	{
		FloatArray v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyFloatArray::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyFloatArray getters
	FloatArray CPropertyFloatArray::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	int CPropertyFloatArray::getMinCount()
	{
		return m_iMinCount;
	}

	bool CPropertyFloatArray::hasMin()
	{
		return m_bHasMin;
	}

	bool CPropertyFloatArray::hasMax()
	{
		return m_bHasMax;
	}

	float CPropertyFloatArray::getMin()
	{
		return m_fMin;
	}

	float CPropertyFloatArray::getMax()
	{
		return m_fMax;
	}
#pragma endregion

#pragma region IPropertyFloatArray setters
	bool CPropertyFloatArray::setValue(const FloatArray value)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, value);
		if (IsNotEqual(value, m_tValue))
		{
			m_tValue = value;
			return true;
		}
		return false;
	}

	IPropertyFloatArray *CPropertyFloatArray::setMinCount(const int value)
	{
		m_iMinCount = ntl::Max<int>(0, value);
		return this;
	}

	IPropertyFloatArray *CPropertyFloatArray::setHasMin(const bool value)
	{
		m_bHasMin = value;
		return this;
	}

	IPropertyFloatArray *CPropertyFloatArray::setHasMax(const bool value)
	{
		m_bHasMax = value;
		return this;
	}

	IPropertyFloatArray *CPropertyFloatArray::setMin(const float value)
	{
		m_fMin = value;
		m_bHasMin = true;
		return this;
	}

	IPropertyFloatArray *CPropertyFloatArray::setMax(const float value)
	{
		m_fMax = value;
		m_bHasMax = true;
		return this;
	}
#pragma endregion
}