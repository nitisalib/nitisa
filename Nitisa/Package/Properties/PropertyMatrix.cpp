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
	CPropertyMatrix::CPropertyMatrix(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerMatrix, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false }
	{
		AddHeaderFile(L"Nitisa/Math/Mat4f.h");
		AddHeaderFile(L"Nitisa/Math/Vec4f.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyMatrix::getPreview()
	{
		return ToString(getValue());
	}

	String CPropertyMatrix::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyMatrix::isChanged()
	{
		return m_bChanged || ntl::IsNotEqual<float>(getValue(), m_tOld);
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyMatrix::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyMatrix::Copy(IProperty *dest)
	{
		IPropertyMatrix *d{ cast<IPropertyMatrix*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyMatrix::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyMatrix::Load(const Variant &src)
	{
		Mat4f v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyMatrix::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyMatrix getters
	Mat4f CPropertyMatrix::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}
#pragma endregion

#pragma region IPropertyMatrix setters
	bool CPropertyMatrix::setValue(const Mat4f value)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, value);
		if (ntl::IsNotEqual<float>(value, m_tValue))
		{
			m_tValue = value;
			return true;
		}
		return false;
	}
#pragma endregion
}