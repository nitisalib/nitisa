// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/BoolArray.h"
#include "../../Core/Strings.h"
#include "../../Core/Variant.h"
#include "../Core/ExportPrefixType.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyBoolArrayState.h"
#include <iostream>
#include <map>
#include <vector>

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyBoolArrayState :public virtual IPropertyBoolArrayState, public CPropertyState
	{
	public:
		using FGetter = BoolArray(*)(IClass *parent, const String &state);
		using FSetter = bool(*)(IClass *parent, const String &state, BoolArray value);
	private:
		std::map<String, BoolArray> m_aOld;
		std::map<String, BoolArray> m_aValue;
		FGetter m_fGetter;
		FSetter m_fSetter;
		bool m_bChanged;
		int m_iMinCount;
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

		// IPropertyBoolArrayState getters
		BoolArray getValue(const String &state) override;
		int getMinCount() override;

		// IPropertyBoolArrayState setters
		bool setValue(const String &state, const BoolArray value) override;
		IPropertyBoolArrayState *setMinCount(const int value) override;

		CPropertyBoolArrayState(
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