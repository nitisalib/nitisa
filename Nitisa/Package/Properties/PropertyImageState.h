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
#include "../../Image/Image.h"
#include "../Core/ExportPrefixType.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyImageState.h"
#include <iostream>
#include <map>

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyImageState :public virtual IPropertyImageState, public CPropertyState
	{
	public:
		using FGetter = Image * (*)(IClass *parent, const String &state);
		using FUpdate = void(*)(IClass *parent);
	private:
		std::map<String, Image> m_aOld;
		FGetter m_fGetter;
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

		// IPropertyImageState getters
		Image *getValue(const String &state) override;

		// IPropertyImageState methods
		void Update() override;

		CPropertyImageState(
			IPropertyList *list,
			IClass *parent,
			const String &name,
			const StringArray &states,
			const ExportPrefixType state_prefix_type,
			const String &state_prefix,
			FSkip skip,
			FGetter getter,
			FUpdate update); // See parent class constructor for more information
	};
}