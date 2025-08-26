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
	CPropertyFontState::CPropertyFontState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerFont, skip, read_only, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false }
	{
		AddHeaderFile(L"Nitisa/Core/Font.h");
		AddHeaderFile(L"Nitisa/Core/FontWeight.h");
		AddHeaderFile(L"Nitisa/Image/Color.h");
		AddHeaderFile(L"Nitisa/Math/PointF.h");
		for (int i = 0; i < getStateCount(); i++)
			if (getValue(getState(i)))
				m_aOld[getState(i)].Copy(getValue(getState(i)));
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyFontState::getPreview()
	{
		return L"";
	}

	String CPropertyFontState::getPreview(const String &state)
	{
		if (getValue(state))
			return L"[IFont(" + getValue(state)->FontName + L", " + ToString(getValue(state)->Height) + L")]";
		return L"";
	}

	bool CPropertyFontState::isChanged()
	{
		if (m_bChanged)
			return true;
		for (int i = 0; i < getStateCount(); i++)
			if (!m_aOld[getState(i)].isEqual(getValue(getState(i))))
				return true;
		return false;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyFontState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyFontState::Copy(IProperty *dest)
	{
		IPropertyFontState *d{ cast<IPropertyFontState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyFontState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			FontToVariant(getValue(getState(i)), dest[getState(i).c_str()]);
	}

	void CPropertyFontState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			CFont font;
			VariantToFont(&font, src.get(getState(i).c_str()));
			setValue(getState(i), &font);
		}
	}

	void CPropertyFontState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
			if (getValue(getState(i)))
			{
				f << shift << L"{" << std::endl;
				f << shift << L"\tCFont font;" << std::endl;
				f << shift << L"\tfont.setFontName(L\"" << getValue(getState(i))->FontName << L"\");" << std::endl;
				f << shift << L"\tfont.setHeight(" << getValue(getState(i))->Height << L");" << std::endl;
				f << shift << L"\tfont.setWeight(" << FontWeightToString(getValue(getState(i))->Weight) << L");" << std::endl;
				f << shift << L"\tfont.setDistance(" << AsSourceCode(getValue(getState(i))->Distance) << L");" << std::endl;
				f << shift << L"\tfont.setColor(" << AsSourceCode(getValue(getState(i))->Color) << L");" << std::endl;
				f << shift << L"\tfont.setShadowShift(" << AsSourceCode(getValue(getState(i))->ShadowShift) << L");" << std::endl;
				f << shift << L"\tfont.setShadowRadius(" << getValue(getState(i))->ShadowRadius << L");" << std::endl;
				f << shift << L"\tfont.setShadowColor(" << AsSourceCode(getValue(getState(i))->ShadowColor) << L");" << std::endl;
				f << shift << L"\tfont.setItalic(" << ToString(getValue(getState(i))->Italic) << L");" << std::endl;
				f << shift << L"\tfont.setUnderline(" << ToString(getValue(getState(i))->Underline) << L");" << std::endl;
				f << shift << L"\tfont.setStrikeOut(" << ToString(getValue(getState(i))->StrikeOut) << L");" << std::endl;
				f << shift << L"\tfont.setMonospace(" << ToString(getValue(getState(i))->Monospace) << L");" << std::endl;
				if (control.empty())
					f << shift << L"\t" << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", &font);" << std::endl;
				else
					f << shift << L"\t" << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", &font);" << std::endl;
				f << shift << L"}" << std::endl;
			}
	}
#pragma endregion

#pragma region IPropertyFontState getters
	IFont *CPropertyFontState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		if (m_aValue.find(state) == m_aValue.end())
			m_aValue[state].Copy(m_fGetter(m_pParent, state));
		return &m_aValue[state];
	}
#pragma endregion

#pragma region IPropertyFontState setters
	bool CPropertyFontState::setValue(const String &state, IFont *value)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, state, value);
		m_aValue[state].Copy(value);
		return true;
	}
#pragma endregion
}