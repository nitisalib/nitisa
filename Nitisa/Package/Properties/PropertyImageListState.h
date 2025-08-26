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
#include "../Core/ExportPrefixType.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyImageListState.h"
#include <iostream>

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class Image;

	class CPropertyImageListState :public virtual IPropertyImageListState, public CPropertyState
	{
	public:
		using FGetCount = int(*)(IClass *parent, const String &state);
		using FGetImage = Image * (*)(IClass *parent, const String &state, const int index);
		using FAdd = bool(*)(IClass *parent, const String &state, Image *value);
		using FDelete = bool(*)(IClass *parent, const String &state, const int index);
		using FClear = bool(*)(IClass *parent, const String &state);
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

		// IPropertyBoolState getters
		int getCount(const String &state) override;
		Image *getImage(const String &state, const int index) override;

		// IPropertyBoolState setters
		bool Add(const String &state, Image *value) override;
		bool Delete(const String &state, const int index) override;
		bool Clear(const String &state) override;
		void Update() override;

		CPropertyImageListState(
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
			FUpdate update); // See parent class constructor for more information
	};
}