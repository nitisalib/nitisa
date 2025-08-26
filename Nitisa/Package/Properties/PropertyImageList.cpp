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
	CPropertyImageList::CPropertyImageList(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetCount get_count, FGetImage get_image, FAdd add, FDelete del, FClear clear, FUpdate update) :
		CProperty(list, parent, name, PropertyHandlerImageList, skip, false),
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
	String CPropertyImageList::getPreview()
	{
		return L"[ImageList(" + ToString(getCount()) + L")]";
	}

	String CPropertyImageList::getPreview(const String &state)
	{
		return L"";
	}

	bool CPropertyImageList::isChanged()
	{
		return m_bChanged || getCount() > 0;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyImageList::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyImageList::Copy(IProperty *dest)
	{
		IPropertyImageList *d{ cast<IPropertyImageList*>(dest) };
		if (d)
		{
			d->Clear();
			for (int i = 0; i < getCount(); i++)
			{
				Image *img{ new Image() };
				*img = *getImage(i);
				d->Add(img);
			}
			return true;
		}
		return false;
	}

	void CPropertyImageList::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getCount(); i++)
		{
			Variant image;
			ImageToVariant(*getImage(i), image);
			dest.push_back(image);
		}
	}

	void CPropertyImageList::Load(const Variant &src)
	{
		Clear();
		for (int i = 0; i < (int)src.size(); i++)
		{
			Image *img{ new Image() };
			VariantToImage(*img, src.get(i));
			Add(img);
		}
	}

	void CPropertyImageList::Export(std::wofstream &f, const String &shift, const String &control)
	{
		for (int i = 0; i < getCount(); i++)
		{
			Image *img{ getImage(i) };
			f << shift << L"{" << std::endl;
			f << shift << L"\tImage *img{ new Image() };" << std::endl;
			if (!img->isEmpty())
			{
				f << shift << L"\tstatic const Color data[] " << (*img) << L";" << std::endl;
				f << shift << L"\timg->setData(" << img->Width << L", " << img->Height << L", data);" << std::endl;
			}
			if (control.empty())
				f << shift << L"\t" << L"AddImage(img);" << std::endl;
			else
				f << shift << L"\t" << control << L"->AddImage(img);" << std::endl;
			f << shift << L"}" << std::endl;
		}
	}
#pragma endregion

#pragma region IPropertyImageList getters
	int CPropertyImageList::getCount()
	{
		return m_fGetCount(m_pParent);
	}

	Image *CPropertyImageList::getImage(const int index)
	{
		return m_fGetImage(m_pParent, index);
	}
#pragma endregion

#pragma region IPropertyImageList methods
	int CPropertyImageList::Add(Image *value)
	{
		return m_fAdd(m_pParent, value);
	}

	bool CPropertyImageList::Delete(const int index)
	{
		return m_fDelete(m_pParent, index);
	}

	bool CPropertyImageList::Clear()
	{
		return m_fClear(m_pParent);
	}

	void CPropertyImageList::Update()
	{
		m_fUpdate(m_pParent);
	}
#pragma endregion
}