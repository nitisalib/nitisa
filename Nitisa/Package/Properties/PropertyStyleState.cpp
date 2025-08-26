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
	CPropertyStyleState::CPropertyStyleState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerStyle, skip, false, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false }
	{
		AddHeaderFile(L"Nitisa/Interfaces/IApplication.h");
		AddHeaderFile(L"Nitisa/Interfaces/IStyles.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyStyleState::getPreview()
	{
		return L"";
	}

	String CPropertyStyleState::getPreview(const String &state)
	{
		if (getValue(state))
			return getValue(state)->ClassName;
		return L"";
	}

	bool CPropertyStyleState::isChanged()
	{
		if (m_bChanged)
			return true;
		for (int i = 0; i < getStateCount(); i++)
			if (getValue(getState(i)))
				return true;
		return false;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyStyleState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyStyleState::Copy(IProperty *dest)
	{
		IPropertyStyleState *d{ cast<IPropertyStyleState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyStyleState::Save(Variant &dest)
	{
		if (Application->Editor && m_pPropertyList && m_pPropertyList->getPackage())
		{
			dest.Reset();
			for (int j = 0; j < getStateCount(); j++)
			{
				IStyle *style{ getValue(getState(j)) };
				if (style)
				{
					dest[getState(j).c_str()][L"Package"] = m_pPropertyList->getPackage()->getName();
					dest[getState(j).c_str()][L"ClassName"] = style->ClassName;
				}
			}
		}
	}

	void CPropertyStyleState::Load(const Variant &src)
	{
		if (Application->Editor)
		{
			IPackageStyle *p;
			for (int i = 0; i < getStateCount(); i++)
				if (src.isSet(getState(i)) && src.get(getState(i).c_str()).get(L"Package"), src.get(getState(i).c_str()).get(L"ClassName") &&
					(p = Application->Editor->getStyle((String)src.get(getState(i).c_str()).get(L"Package"), (String)src.get(getState(i).c_str()).get(L"ClassName"))))
					setValue(getState(i), p->getStyle());
				else
					setValue(getState(i), nullptr);
		}
	}

	void CPropertyStyleState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (Application->Editor)
		{
			String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
			IPackageStyle *p;
			for (int j = 0; j < getStateCount(); j++)
				if (getValue(getState(j)) && (p = Application->Editor->getStyle(getValue(getState(j)))))
				{
					f << shift << L"if (!Application->getStyles()->getStyle(L\"" << p->getPackage()->getName() << L"\", L\"" << p->getClassName() << L"\"))" << std::endl;
					f << shift << L"\tApplication->getStyles()->Add(L\"" << p->getPackage()->getName() << L"\", new " << p->getNamespace() << L"::C" << p->getClassName() << L"());" << std::endl;
					if (control.empty())
						f << shift << L"set" << m_sName << L"(" << state_prefix << getState(j) << L", Application->getStyles()->getStyle(L\"" <<
						ReplaceAll(p->getPackage()->getName(), L"\"", L"\\\")") << L"\", L\"" << ReplaceAll(p->getClassName(), L"\"", L"\\\")") << L"\"));" << std::endl;
					else
						f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(j) << L", Application->getStyles()->getStyle(L\"" <<
						ReplaceAll(p->getPackage()->getName(), L"\"", L"\\\")") << L"\", L\"" << ReplaceAll(p->getClassName(), L"\"", L"\\\")") << L"\"));" << std::endl;
				}
				else
				{
					if (control.empty())
						f << shift << L"set" << m_sName << L"(" << state_prefix << getState(j) << L", nullptr);" << std::endl;
					else
						f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(j) << L", nullptr);" << std::endl;
				}
		}
	}
#pragma endregion

#pragma region IPropertyStyleState getters
	IStyle *CPropertyStyleState::getValue(const String &state)
	{
		return m_fGetter(m_pParent, state);
	}
#pragma endregion

#pragma region IPropertyStyleState setters
	bool CPropertyStyleState::setValue(const String &state, IStyle *value)
	{
		return m_fSetter(m_pParent, state, value);
	}
#pragma endregion
}