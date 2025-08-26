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
	CPropertyImageListState::CPropertyImageListState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetCount get_count,
		FGetImage get_image,
		FAdd add,
		FDelete del,
		FClear clear,
		FUpdate update) : CPropertyState(list, parent, name, PropertyHandlerImageList, skip, false, states, state_prefix_type, state_prefix),
		m_fGetCount{ get_count },
		m_fGetImage{ get_image },
		m_fAdd{ add },
		m_fDelete{ del },
		m_fClear{ clear },
		m_fUpdate{ update },
		m_bChanged{ false }
	{
		AddHeaderFile(L"Nitisa/Image/Color.h");
		AddHeaderFile(L"Nitisa/Image/Image.h");
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyImageListState::getPreview()
	{
		return L"";
	}

	String CPropertyImageListState::getPreview(const String &state)
	{
		return L"[ImageList(" + ToString(getCount(state)) + L")]";
	}

	bool CPropertyImageListState::isChanged()
	{
		if (m_bChanged)
			return true;
		for (int i = 0; i < getStateCount(); i++)
			if (getCount(getState(i)) > 0)
				return true;
		return false;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyImageListState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyImageListState::Copy(IProperty *dest)
	{
		IPropertyImageListState *d{ cast<IPropertyImageListState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
			{
				d->Clear(getState(i));
				for (int j = 0; j < getCount(getState(i)); j++)
				{
					Image *img{ new Image() };
					*img = *getImage(getState(i), j);
					d->Add(getState(i), img);
				}
			}
			return true;
		}
		return false;
	}

	void CPropertyImageListState::Save(Variant &dest)
	{
		dest.Reset();
		for (int j = 0; j < getStateCount(); j++)
			for (int i = 0; i < getCount(getState(j)); i++)
			{
				Variant image;
				ImageToVariant(*getImage(getState(j), i), image);
				dest[getState(j).c_str()].push_back(image);
			}
	}

	void CPropertyImageListState::Load(const Variant &src)
	{
		for (int j = 0; j < getStateCount(); j++)
		{
			Clear(getState(j));
			for (int i = 0; i < (int)src.get(getState(j).c_str()).size(); i++)
			{
				Image *img{ new Image() };
				VariantToImage(*img, src.get(getState(j).c_str()).get(i));
				Add(getState(j), img);
			}
		}
	}

	void CPropertyImageListState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int j = 0; j < getStateCount(); j++)
			for (int i = 0; i < getCount(getState(j)); i++)
			{
				Image *img{ getImage(getState(j), i) };
				f << shift << L"{" << std::endl;
				f << shift << L"\tImage *img{ new Image() };" << std::endl;
				if (!img->isEmpty())
				{
					f << shift << L"\tstatic const Color data[] " << (*img) << L";" << std::endl;
					f << shift << L"\timg->setData(" << img->Width << L", " << img->Height << L", data);" << std::endl;
				}
				if (control.empty())
					f << shift << L"\t" << L"AddImage(" << state_prefix << getState(j) << L", img);" << std::endl;
				else
					f << shift << L"\t" << control << L"->AddImage(" << state_prefix << getState(j) << L", img);" << std::endl;
				f << shift << L"}" << std::endl;
			}
	}
#pragma endregion

#pragma region IPropertyImageListState getters
	int CPropertyImageListState::getCount(const String &state)
	{
		return m_fGetCount(m_pParent, state);
	}

	Image *CPropertyImageListState::getImage(const String &state, const int index)
	{
		return m_fGetImage(m_pParent, state, index);
	}
#pragma endregion

#pragma region IPropertyImageListState methods
	bool CPropertyImageListState::Add(const String &state, Image *value)
	{
		return m_fAdd(m_pParent, state, value);
	}

	bool CPropertyImageListState::Delete(const String &state, const int index)
	{
		return m_fDelete(m_pParent, state, index);
	}

	bool CPropertyImageListState::Clear(const String &state)
	{
		return m_fClear(m_pParent, state);
	}

	void CPropertyImageListState::Update()
	{
		m_fUpdate(m_pParent);
	}
#pragma endregion
}