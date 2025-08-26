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
	CPropertyPointF::CPropertyPointF(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerPointF, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_bMin{ false },
		m_bMax{ false },
		m_fMin{ 0 },
		m_fMax{ 0 }
	{
		AddHeaderFile(L"Nitisa/Math/PointF.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyPointF::getPreview()
	{
		return ToString(getValue());
	}

	String CPropertyPointF::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyPointF::isChanged()
	{
		return m_bChanged || IsNotEqual(getValue(), m_tOld);
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyPointF::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyPointF::Copy(IProperty *dest)
	{
		IPropertyPointF *d{ cast<IPropertyPointF*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyPointF::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyPointF::Load(const Variant &src)
	{
		PointF v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyPointF::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyPointF getters
	PointF CPropertyPointF::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	bool CPropertyPointF::hasMin() const
	{
		return m_bMin;
	}

	bool CPropertyPointF::hasMax() const
	{
		return m_bMax;
	}

	float CPropertyPointF::getMin() const
	{
		return m_fMin;
	}

	float CPropertyPointF::getMax() const
	{
		return m_fMax;
	}
#pragma endregion

#pragma region IPropertyPointF setters
	bool CPropertyPointF::setValue(const PointF value)
	{
		PointF v{ value };
		if (m_bMin)
		{
			v.X = ntl::Max<float>(m_fMin, v.X);
			v.Y = ntl::Max<float>(m_fMin, v.Y);
		}
		if (m_bMax)
		{
			v.X = ntl::Min<float>(m_fMax, v.X);
			v.Y = ntl::Min<float>(m_fMax, v.Y);
		}
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, v);
		if (IsNotEqual(v, m_tValue))
		{
			m_tValue = v;
			return true;
		}
		return false;
	}

	IPropertyPointF *CPropertyPointF::setHasMin(const bool value)
	{
		m_bMin = value;
		return this;
	}

	IPropertyPointF *CPropertyPointF::setHasMax(const bool value)
	{
		m_bMax = value;
		return this;
	}

	IPropertyPointF *CPropertyPointF::setMin(const float value)
	{
		m_fMin = value;
		m_bMin = true;
		return this;
	}

	IPropertyPointF *CPropertyPointF::setMax(const float value)
	{
		m_fMax = value;
		m_bMax = true;
		return this;
	}
#pragma endregion
}