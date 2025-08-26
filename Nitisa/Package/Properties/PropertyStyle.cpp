// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	CPropertyStyle::CPropertyStyle(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerStyle, skip, false),
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false }
	{
		AddHeaderFile(L"Nitisa/Interfaces/IApplication.h");
		AddHeaderFile(L"Nitisa/Interfaces/IStyles.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyStyle::getPreview()
	{
		if (getValue())
			return getValue()->ClassName;
		return L"";
	}

	String CPropertyStyle::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyStyle::isChanged()
	{
		return m_bChanged || getValue();
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyStyle::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyStyle::Copy(IProperty *dest)
	{
		IPropertyStyle *d{ cast<IPropertyStyle*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyStyle::Save(Variant &dest)
	{
		if (getValue() && m_pPropertyList && m_pPropertyList->getPackage())
		{
			dest.Reset();
			dest[L"Package"] = m_pPropertyList->getPackage()->getName();
			dest[L"ClassName"] = getValue()->ClassName;
		}
	}

	void CPropertyStyle::Load(const Variant &src)
	{
		IPackageStyle *p;
		if (Application->Editor && src.isSet(L"Package") && src.isSet(L"ClassName") && (p = Application->Editor->getStyle((String)src.get(L"Package"), (String)src.get(L"ClassName"))))
			setValue(p->getStyle());
		else
			setValue(nullptr);
	}

	void CPropertyStyle::Export(std::wofstream &f, const String &shift, const String &control)
	{
		IPackageStyle *p;
		if (Application->Editor && getValue() && (p = Application->Editor->getStyle(getValue())))
		{
			f << shift << L"if (!Application->getStyles()->getStyle(L\"" << p->getPackage()->getName() << L"\", L\"" << p->getClassName() << L"\"))" << std::endl;
			f << shift << L"\tApplication->getStyles()->Add(L\"" << p->getPackage()->getName() << L"\", new " << p->getNamespace() << L"::C" << p->getClassName() << L"());" << std::endl;
			if (control.empty())
				f << shift << L"set" << m_sName << L"(Application->getStyles()->getStyle(L\"" << ReplaceAll(p->getPackage()->getName(), L"\"", L"\\\")") << L"\", L\""
				<< ReplaceAll(p->getClassName(), L"\"", L"\\\")") << L"\"));" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(Application->getStyles()->getStyle(L\"" << ReplaceAll(p->getPackage()->getName(), L"\"", L"\\\")") << L"\", L\""
				<< ReplaceAll(p->getClassName(), L"\"", L"\\\")") << L"\"));" << std::endl;
		}
		else
		{
			if (control.empty())
				f << shift << L"set" << m_sName << L"(nullptr);" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(nullptr);" << std::endl;
		}
	}
#pragma endregion

#pragma region IPropertyStyle getters
	IStyle *CPropertyStyle::getValue()
	{
		return m_fGetter(m_pParent);
	}
#pragma endregion

#pragma region IPropertyStyle setters
	bool CPropertyStyle::setValue(IStyle *value)
	{
		return m_fSetter(m_pParent, value);
	}
#pragma endregion
}