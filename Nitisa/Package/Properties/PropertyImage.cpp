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
	CPropertyImage::CPropertyImage(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetter getter, FUpdate update) :
		CProperty(list, parent, name, PropertyHandlerImage, skip, false),
		m_fGetter{ getter },
		m_fUpdate{ update },
		m_bChanged{ false }
	{
		AddHeaderFile(L"Nitisa/Image/Color.h");
		AddHeaderFile(L"Nitisa/Image/Image.h");
		if (m_fGetter)
			m_tOld = *m_fGetter(m_pParent);
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyImage::getPreview()
	{
		if (getValue())
			return L"[Image(" + ToString(getValue()->Width) + L"x" + ToString(getValue()->Height) + L")]";
		return L"";
	}

	String CPropertyImage::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyImage::isChanged()
	{
		return m_bChanged || (getValue() && m_tOld != *getValue());
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyImage::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyImage::Copy(IProperty *dest)
	{
		IPropertyImage *d{ cast<IPropertyImage*>(dest) };
		if (d)
		{
			if (getValue() && d->getValue())
				*d->getValue() = *getValue();
			return true;
		}
		return false;
	}

	void CPropertyImage::Save(Variant &dest)
	{
		if (getValue())
		{
			dest.Reset();
			ImageToVariant(*getValue(), dest);
		}
	}

	void CPropertyImage::Load(const Variant &src)
	{
		if (getValue())
			VariantToImage(*getValue(), src);
	}

	void CPropertyImage::Export(std::wofstream &f, const String &shift, const String &control)
	{
		Image *img{ getValue() };
		f << shift << L"{" << std::endl;
		if (control.empty())
			f << shift << L"\tImage *img{ " << L"get" << m_sName << L"() };" << std::endl;
		else
			f << shift << L"\tImage *img{ " << control << L"->get" << m_sName << L"() };" << std::endl;
		if (!img->isEmpty())
		{
			f << shift << L"\tstatic const Color data[] " << (*img) << L";" << std::endl;
			f << shift << L"\timg->setData(" << img->Width << L", " << img->Height << L", data);" << std::endl;
		}
		else
			f << shift << L"\timg->setSize(0, 0);" << std::endl;
		f << shift << L"}" << std::endl;
	}
#pragma endregion

#pragma region IPropertyImage getters
	Image *CPropertyImage::getValue()
	{
		return m_fGetter(m_pParent);
	}
#pragma endregion

#pragma region IPropertyImage methods
	void CPropertyImage::Update()
	{
		m_fUpdate(m_pParent);
	}
#pragma endregion
}