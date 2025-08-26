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
#include "../Interfaces/IPropertyStringState.h"
#include <iostream>
#include <map>

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyStringState :public virtual IPropertyStringState, public CPropertyState
	{
	public:
		using FGetter = String(*)(IClass *parent, const String &state);
		using FSetter = bool(*)(IClass *parent, const String &state, String value);
	private:
		std::map<String, String> m_aOld;
		std::map<String, String> m_aValue;
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

		// IPropertyStringState getters
		String getValue(const String &state) override;

		// IPropertyStringState setters
		bool setValue(const String &state, const String value) override;

		CPropertyStringState(
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