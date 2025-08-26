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
	CPropertyImageState::CPropertyImageState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FUpdate update) : CPropertyState(list, parent, name, PropertyHandlerImage, skip, false, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_fUpdate{ update },
		m_bChanged{ false }
	{
		AddHeaderFile(L"Nitisa/Image/Color.h");
		AddHeaderFile(L"Nitisa/Image/Image.h");
		for (int i = 0; i < getStateCount(); i++)
			if (getValue(getState(i)))
				m_aOld[getState(i)] = *getValue(getState(i));
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyImageState::getPreview()
	{
		return L"";
	}

	String CPropertyImageState::getPreview(const String &state)
	{
		if (getValue(state))
			return L"[Image(" + ToString(getValue(state)->Width) + L"x" + ToString(getValue(state)->Height) + L")]";
		return L"";
	}

	bool CPropertyImageState::isChanged()
	{
		if (m_bChanged)
			return true;
		for (int i = 0; i < getStateCount(); i++)
			if (getValue(getState(i)) && *getValue(getState(i)) != m_aOld[getState(i)])
				return true;
		return false;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyImageState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyImageState::Copy(IProperty *dest)
	{
		IPropertyImageState *d{ cast<IPropertyImageState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				if (getValue(getState(i)) && d->getValue(getState(i)))
					*d->getValue(getState(i)) = *getValue(getState(i));
			return true;
		}
		return false;
	}

	void CPropertyImageState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			if (getValue(getState(i)))
				ImageToVariant(*getValue(getState(i)), dest[getState(i).c_str()]);
	}

	void CPropertyImageState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
			if (getValue(getState(i)))
				VariantToImage(*getValue(getState(i)), src.get(getState(i).c_str()));
	}

	void CPropertyImageState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
			if (getValue(getState(i)))
			{
				Image *img{ getValue(getState(i)) };
				f << shift << L"{" << std::endl;
				if (control.empty())
					f << shift << L"\tImage *img{ " << L"get" << m_sName << L"(" << state_prefix << getState(i) << L") };" << std::endl;
				else
					f << shift << L"\tImage *img{ " << control << L"->get" << m_sName << L"(" << state_prefix << getState(i) + L") };" << std::endl;
				if (!img->isEmpty())
				{
					f << shift << L"\tstatic const Color data[] " << (*img) << L";" << std::endl;
					f << shift << L"\timg->setData(" << img->Width << L", " << img->Height << L", data);" << std::endl;
				}
				else
					f << shift << L"\timg->setSize(0, 0);" << std::endl;
				f << shift << L"}" << std::endl;
			}
	}
#pragma endregion

#pragma region IPropertyImageState getters
	Image *CPropertyImageState::getValue(const String &state)
	{
		return m_fGetter(m_pParent, state);
	}
#pragma endregion

#pragma region IPropertyImageState methods
	void CPropertyImageState::Update()
	{
		m_fUpdate(m_pParent);
	}
#pragma endregion
}