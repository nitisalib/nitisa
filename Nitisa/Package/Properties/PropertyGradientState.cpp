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
	CPropertyGradientState::CPropertyGradientState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter) : CPropertyState(list, parent, name, PropertyHandlerGradient, skip, false, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_bChanged{ false }
	{
		AddHeaderFile(L"Nitisa/Image/Color.h");
		AddHeaderFile(L"Nitisa/Image/Color1D.h");
		AddHeaderFile(L"Nitisa/Image/Color1DArray.h");
		AddHeaderFile(L"Nitisa/Image/Gradient.h");
		AddHeaderFile(L"Nitisa/Image/GradientType.h");
		for (int i = 0; i < getStateCount(); i++)
			if (getValue(getState(i)))
				m_aOld[getState(i)] = *getValue(getState(i));
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyGradientState::getPreview()
	{
		return L"";
	}

	String CPropertyGradientState::getPreview(const String &state)
	{
		if (getValue(state))
			return L"[Gradient(" + ToString(getValue(state)->getPointCount()) + L" points)]";
		return L"";
	}

	bool CPropertyGradientState::isChanged()
	{
		if (m_bChanged)
			return true;
		for (int i = 0; i < getStateCount(); i++)
			if (getValue(getState(i)) && getValue(getState(i))->isNotEqual(m_aOld[getState(i)]))
				return true;
		return false;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyGradientState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyGradientState::Copy(IProperty *dest)
	{
		IPropertyGradientState *d{ cast<IPropertyGradientState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				if (getValue(getState(i)) && d->getValue(getState(i)))
					*d->getValue(getState(i)) = *getValue(getState(i));
			return true;
		}
		return false;
	}

	void CPropertyGradientState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			if (getValue(getState(i)))
				GradientToVariant(*getValue(getState(i)), dest[getState(i).c_str()]);
	}

	void CPropertyGradientState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
			if (getValue(getState(i)))
				VariantToGradient(*getValue(getState(i)), src.get(getState(i).c_str()));
	}

	void CPropertyGradientState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int j = 0; j < getStateCount(); j++)
		{
			Gradient *g{ getValue(getState(j)) };
			if (g)
			{
				if (control.empty())
				{
					f << shift << L"get" << m_sName << L"(" << state_prefix << getState(j) << L")->setPoints(" << AsSourceCode(*g) << L");" << std::endl;
					f << shift << L"get" << m_sName << L"(" << state_prefix << getState(j) << L")->setType(" << GradientTypeToString(g->Type) << L");" << std::endl;
				}
				else
				{
					f << shift << control << L"->get" << m_sName << L"(" << state_prefix << getState(j) << L")->setPoints(" << AsSourceCode(*g) << L");" << std::endl;
					f << shift << control << L"->get" << m_sName << L"(" << state_prefix << getState(j) << L")->setType(" << GradientTypeToString(g->Type) << L");" << std::endl;
				}
			}
		}
	}
#pragma endregion

#pragma region IPropertyGradientState getters
	Gradient *CPropertyGradientState::getValue(const String &state)
	{
		return m_fGetter(m_pParent, state);
	}
#pragma endregion
}