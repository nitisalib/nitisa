// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Font.h"
#include "../../Core/Strings.h"
#include "../../Core/Variant.h"
#include "../Core/ExportPrefixType.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyFontState.h"
#include <iostream>
#include <map>

namespace nitisa
{
	class IClass;
	class IFont;
	class IProperty;
	class IPropertyList;

	class CPropertyFontState :public virtual IPropertyFontState, public CPropertyState
	{
	public:
		using FGetter = IFont*(*)(IClass *parent, const String &state);
		using FSetter = bool(*)(IClass *parent, const String &state, IFont *value);
	private:
		std::map<String, CFont> m_aOld;
		std::map<String, CFont> m_aValue;
		FGetter m_fGetter;
		FSetter m_fSetter;
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

		// IPropertyFontState getters
		IFont *getValue(const String &state) override;

		// IPropertyFontState setters
		bool setValue(const String &state, IFont *value) override;

		CPropertyFontState(
			IPropertyList *list,
			IClass *parent,
			const String &name,
			const bool read_only,
			const StringArray &states,
			const ExportPrefixType state_prefix_type,
			const String &state_prefix,
			FSkip skip,
			FGetter getter,
			FSetter setter); // See parent class constructor for more information
	};
}