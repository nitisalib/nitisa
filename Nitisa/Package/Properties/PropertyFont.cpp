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
	CPropertyFont::CPropertyFont(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter) :
		CProperty(list, parent, name, PropertyHandlerFont, skip, read_only),
		m_tOld{ nullptr, getter(parent) },
		m_tValue{ nullptr, getter(parent) },
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false }
	{
		AddHeaderFile(L"Nitisa/Core/Font.h");
		AddHeaderFile(L"Nitisa/Core/FontWeight.h");
		AddHeaderFile(L"Nitisa/Image/Color.h");
		AddHeaderFile(L"Nitisa/Math/PointF.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyFont::getPreview()
	{
		if (getValue())
			return L"[IFont(" + getValue()->FontName + L", " + ToString(getValue()->Height) + L")]";
		return L"";
	}

	String CPropertyFont::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyFont::isChanged()
	{
		return m_bChanged || !m_tOld.isEqual(getValue());
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyFont::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyFont::Copy(IProperty *dest)
	{
		IPropertyFont *d{ cast<IPropertyFont*>(dest) };
		if (d)
		{
			d->setValue(getValue());
			return true;
		}
		return false;
	}

	void CPropertyFont::Save(Variant &dest)
	{
		dest.Reset();
		FontToVariant(getValue(), dest);
	}

	void CPropertyFont::Load(const Variant &src)
	{
		CFont font;
		VariantToFont(&font, src);
		setValue(&font);
	}

	void CPropertyFont::Export(std::wofstream &f, const String &shift, const String &control)
	{
		if (getValue())
		{
			f << shift << L"{" << std::endl;
			f << shift << L"\tCFont font;" << std::endl;
			f << shift << L"\tfont.setFontName(L\"" << getValue()->FontName << L"\");" << std::endl;
			f << shift << L"\tfont.setHeight(" << getValue()->Height << L");" << std::endl;
			f << shift << L"\tfont.setWeight(" << FontWeightToString(getValue()->Weight) << L");" << std::endl;
			f << shift << L"\tfont.setDistance(" << AsSourceCode(getValue()->Distance) << L");" << std::endl;
			f << shift << L"\tfont.setColor(" << AsSourceCode(getValue()->Color) << L");" << std::endl;
			f << shift << L"\tfont.setShadowShift(" << AsSourceCode(getValue()->ShadowShift) << L");" << std::endl;
			f << shift << L"\tfont.setShadowRadius(" << getValue()->ShadowRadius << L");" << std::endl;
			f << shift << L"\tfont.setShadowColor(" << AsSourceCode(getValue()->ShadowColor) << L");" << std::endl;
			f << shift << L"\tfont.setItalic(" << ToString(getValue()->Italic) << L");" << std::endl;
			f << shift << L"\tfont.setUnderline(" << ToString(getValue()->Underline) << L");" << std::endl;
			f << shift << L"\tfont.setStrikeOut(" << ToString(getValue()->StrikeOut) << L");" << std::endl;
			f << shift << L"\tfont.setMonospace(" << ToString(getValue()->Monospace) << L");" << std::endl;
			if (control.empty())
				f << shift << L"\t" << L"set" << m_sName << L"(&font);" << std::endl;
			else
				f << shift << L"\t" << control << L"->set" << m_sName << L"(&font);" << std::endl;
			f << shift << L"}" << std::endl;
		}
	}
#pragma endregion

#pragma region IPropertyFont getters
	IFont *CPropertyFont::getValue()
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent);
		return &m_tValue;
	}
#pragma endregion

#pragma region IPropertyFont setters
	bool CPropertyFont::setValue(IFont *value)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, value);
		if (!value->isEqual(&m_tValue))
			return m_tValue.Copy(value);
		return false;
	}
#pragma endregion
}