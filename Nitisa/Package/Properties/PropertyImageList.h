// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Core/Variant.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyImageList.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class Image;

	class CPropertyImageList :public virtual IPropertyImageList, public CProperty
	{
	public:
		using FGetCount = int(*)(IClass *parent);
		using FGetImage = Image * (*)(IClass *parent, const int index);
		using FAdd = int(*)(IClass *parent, Image *value);
		using FDelete = bool(*)(IClass *parent, const int index);
		using FClear = bool(*)(IClass *parent);
		using FUpdate = void(*)(IClass *parent);
	private:
		FGetCount m_fGetCount;
		FGetImage m_fGetImage;
		FAdd m_fAdd;
		FDelete m_fDelete;
		FClear m_fClear;
		FUpdate m_fUpdate;
		bool m_bChanged;
	public:
		// IProperty getters
		String getPreview() override;
		String getPreview(const String &state) override;
		bool isChanged() override;

		// IProperty setters
		IProperty *setChanged(const bool value) override;

		// IProperty methods
		bool Copy(IProperty *dest) override;
		void Save(Variant &dest) override;
		void Load(const Variant &src) override;
		void Export(std::wofstream &f, const String &shift, const String &control) override;

		// IPropertyImageList getters
		int getCount() override;
		Image *getImage(const int index) override;

		// IPropertyImageList methods
		int Add(Image *value) override;
		bool Delete(const int index) override;
		bool Clear() override;
		void Update() override;

		CPropertyImageList(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetCount get_count, FGetImage get_image, FAdd add, FDelete del, FClear clear, FUpdate update); // See parent class constructor for more information
	};
}