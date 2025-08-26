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
	CPropertyRectB::CPropertyRectB(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerRectB, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false }
	{
		AddHeaderFile(L"Nitisa/Math/RectB.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyRectB::getPreview()
	{
		return ToString(getValue());
	}

	String CPropertyRectB::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyRectB::isChanged()
	{
		return m_bChanged || getValue() != m_tOld;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyRectB::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyRectB::Copy(IProperty *dest)
	{
		IPropertyRectB *d{ cast<IPropertyRectB*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyRectB::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyRectB::Load(const Variant &src)
	{
		RectB v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyRectB::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << AsSourceCode(getValue()) << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyRectB getters
	RectB CPropertyRectB::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}
#pragma endregion

#pragma region IPropertyRectB setters
	bool CPropertyRectB::setValue(const RectB value)
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