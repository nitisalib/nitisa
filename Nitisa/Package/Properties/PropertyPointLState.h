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
#include "../../Math/PointL.h"
#include "../Core/ExportPrefixType.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyPointLState.h"
#include <iostream>
#include <map>

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyPointLState :public virtual IPropertyPointLState, public CPropertyState
	{
	public:
		using FGetter = PointL(*)(IClass *parent, const String &state);
		using FSetter = bool(*)(IClass *parent, const String &state, PointL value);
	private:
		std::map<String, PointL> m_aOld;
		std::map<String, PointL> m_aValue;
		FGetter m_fGetter;
		FSetter m_fSetter;
		bool m_bChanged;
		bool m_bMin;
		bool m_bMax;
		long long m_iMin;
		long long m_iMax;
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

		// IPropertyPointLState getters
		PointL getValue(const String &state) override;
		bool hasMin() const override;
		bool hasMax() const override;
		long long getMin() const override;
		long long getMax() const override;

		// IPropertyPointLState setters
		bool setValue(const String &state, const PointL value) override;
		IPropertyPointLState *setHasMin(const bool value) override;
		IPropertyPointLState *setHasMax(const bool value) override;
		IPropertyPointLState *setMin(const long long value) override;
		IPropertyPointLState *setMax(const long long value) override;

		CPropertyPointLState(
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