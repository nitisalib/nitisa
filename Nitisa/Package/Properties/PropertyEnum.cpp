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
	CPropertyEnum::CPropertyEnum(IPropertyList *list, IClass *parent, const String &name, const bool read_only, const StringArray &items, const ExportPrefixType prefix_type, const String &prefix, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerEnum, skip, read_only),
		m_tOld{ getter(parent) },
		m_tValue{ getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false },
		m_aItems{ items },
		m_ePrefixType{ prefix_type },
		m_sPrefix{ prefix }
	{

	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyEnum::getPreview()
	{
		StringArray parts{ Explode(getValue(), L"::") };
		if (parts.size() == 2)
			return parts[1];
		return parts[0];
	}

	String CPropertyEnum::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyEnum::isChanged()
	{
		return m_bChanged || getValue() != m_tOld;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyEnum::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyEnum::Copy(IProperty *dest)
	{
		IPropertyEnum *d{ cast<IPropertyEnum*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyEnum::Save(Variant &dest)
	{
		dest.Reset();
		dest = ToVariant(getValue());
	}

	void CPropertyEnum::Load(const Variant &src)
	{
		String v;
		FromVariant(src, v);
		setValue(v);
	}

	void CPropertyEnum::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (control.empty())
			f << shift << L"set" << m_sName << L"(" << Prefix(m_ePrefixType, m_sPrefix) << getValue() << L");" << std::endl;
		else
			f << shift << control << L"->set" << m_sName << L"(" << Prefix(m_ePrefixType, m_sPrefix) << getValue() << L");" << std::endl;
	}
#pragma endregion

#pragma region IPropertyEnum getters
	String CPropertyEnum::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return m_tValue;
	}

	int CPropertyEnum::getItemCount() const
	{
		return (int)m_aItems.size();
	}

	String CPropertyEnum::getItem(const int index) const
	{
		if (index >= 0 && index < (int)m_aItems.size())
			return m_aItems[index];
		return L"";
	}
#pragma endregion

#pragma region IPropertyEnum setters
	bool CPropertyEnum::setValue(const String value)
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