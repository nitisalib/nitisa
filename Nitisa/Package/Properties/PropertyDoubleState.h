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
#include "../Interfaces/IPropertyDoubleState.h"
#include <iostream>
#include <map>

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyDoubleState :public virtual IPropertyDoubleState, public CPropertyState
	{
	public:
		using FGetter = double(*)(IClass *parent, const String &state);
		using FSetter = bool(*)(IClass *parent, const String &state, double value);
	private:
		std::map<String, double> m_aOld;
		std::map<String, double> m_aValue;
		FGetter m_fGetter;
		FSetter m_fSetter;
		bool m_bChanged;
		bool m_bMin;
		bool m_bMax;
		double m_fMin;
		double m_fMax;
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

		// IPropertyDoubleState getters
		double getValue(const String &state) override;
		bool hasMin() const override;
		bool hasMax() const override;
		double getMin() const override;
		double getMax() const override;

		// IPropertyDoubleState setters
		bool setValue(const String &state, const double value) override;
		IPropertyDoubleState *setHasMin(const bool value) override;
		IPropertyDoubleState *setHasMax(const bool value) override;
		IPropertyDoubleState *setMin(const double value) override;
		IPropertyDoubleState *setMax(const double value) override;

		CPropertyDoubleState(
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