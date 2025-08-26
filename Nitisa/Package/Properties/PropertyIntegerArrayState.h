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
#include "../../Math/IntegerArray.h"
#include "../Core/ExportPrefixType.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyIntegerArrayState.h"
#include <iostream>
#include <map>
#include <vector>

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyIntegerArrayState :public virtual IPropertyIntegerArrayState, public CPropertyState
	{
	public:
		using FGetter = IntegerArray(*)(IClass *parent, const String &state);
		using FSetter = bool(*)(IClass *parent, const String &state, IntegerArray value);
	private:
		std::map<String, IntegerArray> m_aOld;
		std::map<String, IntegerArray> m_aValue;
		FGetter m_fGetter;
		FSetter m_fSetter;
		bool m_bChanged;
		int m_iMinCount;
		bool m_bMin;
		bool m_bMax;
		int m_iMin;
		int m_iMax;
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

		// IPropertyIntegerArrayState getters
		IntegerArray getValue(const String &state) override;
		int getMinCount() override;
		bool hasMin() override;
		bool hasMax() override;
		int getMin() override;
		int getMax() override;

		// IPropertyIntegerArrayState setters
		bool setValue(const String &state, const IntegerArray value) override;
		IPropertyIntegerArrayState *setMinCount(const int value) override;
		IPropertyIntegerArrayState *setHasMin(const bool value) override;
		IPropertyIntegerArrayState *setHasMax(const bool value) override;
		IPropertyIntegerArrayState *setMin(const int value) override;
		IPropertyIntegerArrayState *setMax(const int value) override;

		CPropertyIntegerArrayState(
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