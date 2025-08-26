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
	CPropertyGradient::CPropertyGradient(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetter getter) :
		CProperty(list, parent, name, PropertyHandlerGradient, skip, false),
		m_fGetter{ getter },
		m_bChanged{ false }
	{
		AddHeaderFile(L"Nitisa/Image/Color.h");
		AddHeaderFile(L"Nitisa/Image/Color1D.h");
		AddHeaderFile(L"Nitisa/Image/Color1DArray.h");
		AddHeaderFile(L"Nitisa/Image/Gradient.h");
		AddHeaderFile(L"Nitisa/Image/GradientType.h");
		if (getter(m_pParent))
			m_tOld = *getter(m_pParent);
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyGradient::getPreview()
	{
		if (getValue())
			return L"[Gradient(" + ToString(getValue()->getPointCount()) + L" points)]";
		return L"";
	}

	String CPropertyGradient::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyGradient::isChanged()
	{
		return m_bChanged || (getValue() && getValue()->isNotEqual(m_tOld));
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyGradient::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyGradient::Copy(IProperty *dest)
	{
		IPropertyGradient *d{ cast<IPropertyGradient*>(dest) };
		if (d && d->getValue() && getValue())
		{
			*d->getValue() = *getValue();
			return true;
		}
		return false;
	}

	void CPropertyGradient::Save(Variant &dest)
	{
		if (getValue())
		{
			dest.Reset();
			GradientToVariant(*getValue(), dest);
		}
	}

	void CPropertyGradient::Load(const Variant &src)
	{
		if (getValue())
			VariantToGradient(*getValue(), src);
	}

	void CPropertyGradient::Export(std::wofstream &f, const String &shift, const String &control)
	{
		Gradient *g{ getValue() };
		if (g)
		{
			if (control.empty())
			{
				f << shift << L"get" << m_sName << L"()->setPoints(" << AsSourceCode(*g) << L");" << std::endl;
				f << shift << L"get" << m_sName << L"()->setType(" << GradientTypeToString(g->Type) << L");" << std::endl;
			}
			else
			{
				f << shift << control << L"->get" << m_sName << L"()->setPoints(" << AsSourceCode(*g) << L");" << std::endl;
				f << shift << control << L"->get" << m_sName << L"()->setType(" << GradientTypeToString(g->Type) << L");" << std::endl;
			}
		}
	}
#pragma endregion

#pragma region IPropertyGradient getters
	Gradient *CPropertyGradient::getValue()
	{
		return m_fGetter(m_pParent);
	}
#pragma endregion
}