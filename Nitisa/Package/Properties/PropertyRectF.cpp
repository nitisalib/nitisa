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
	CPropertyRectF::CPropertyRectF(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerRectF, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_bMin{ false },
		m_bMax{ false },
		m_fMin{ 0 },
		m_fMax{ 0 },
		m_bAllowEmpty{ true },
		m_bAllowInvalid{ true }
	{
		AddHeaderFile(L"Nitisa/Math/RectF.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyRectF::getPreview()
	{
		return ToString(getValue());
	}

	String CPropertyRectF::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyRectF::isChanged()
	{
		return m_bChanged || IsNotEqual(getValue(), m_tOld);
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyRectF::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyRectF::Copy(IProperty *dest)
	{
		IPropertyRectF *d{ cast<IPropertyRectF*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyRectF::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyRectF::Load(const Variant &src)
	{
		RectF v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyRectF::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyRectF getters
	RectF CPropertyRectF::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	bool CPropertyRectF::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyRectF::hasMax() const
	{
		return m_bMax;
	}

	float CPropertyRectF::getMin() const
	{
		return m_fMin;
	}

	float CPropertyRectF::getMax() const
	{
		return m_fMax;
	}

	bool CPropertyRectF::isAllowInvalid() const
	{
		return m_bAllowInvalid;
	}

	bool CPropertyRectF::isAllowEmpty() const
	{
		return m_bAllowEmpty;
	}
#pragma endregion

#pragma region IPropertyRectF setters
	bool CPropertyRectF::setValue(const RectF value)
	{
		RectF v{ value };
		if (m_bMin)
		{
			v.Left = ntl::Max<float>(m_fMin, v.Left);
			v.Top = ntl::Max<float>(m_fMin, v.Top);
			v.Right = ntl::Max<float>(m_fMin, v.Right);
			v.Bottom = ntl::Max<float>(m_fMin, v.Bottom);
		}
		if (m_bMax)
		{
			v.Left = ntl::Min<float>(m_fMax, v.Left);
			v.Top = ntl::Min<float>(m_fMax, v.Top);
			v.Right = ntl::Min<float>(m_fMax, v.Right);
			v.Bottom = ntl::Min<float>(m_fMax, v.Bottom);
		}
		if (!m_bAllowInvalid && !v.is_valid())
			return false;
		if (!m_bAllowEmpty && v.is_empty())
			return false;
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, v);
		if (IsNotEqual(v, m_tValue))
		{
			m_tValue = v;
			return true;
		}
		return false;
	}

	IPropertyRectF *CPropertyRectF::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyRectF *CPropertyRectF::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyRectF *CPropertyRectF::setMin(const float value)
	{
		m_fMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyRectF *CPropertyRectF::setMax(const float value)
	{
		m_fMax = value;
		m_bMax = true;
		return this;
	}

	IPropertyRectF *CPropertyRectF::setAllowInvalid(const bool value)
	{
		m_bAllowInvalid = value;
		return this;
	}

	IPropertyRectF *CPropertyRectF::setAllowEmpty(const bool value)
	{
		m_bAllowEmpty = value;
		return this;
	}
#pragma endregion
}