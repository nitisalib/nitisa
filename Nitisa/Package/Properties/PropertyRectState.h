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
#include "../../Math/Rect.h"
#include "../Core/ExportPrefixType.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyRectState.h"
#include <iostream>
#include <map>

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyRectState :public virtual IPropertyRectState, public CPropertyState
	{
	public:
		using FGetter = Rect(*)(IClass *parent, const String &state);
		using FSetter = bool(*)(IClass *parent, const String &state, Rect value);
	private:
		std::map<String, Rect> m_aOld;
		std::map<String, Rect> m_aValue;
		FGetter m_fGetter;
		FSetter m_fSetter;
		bool m_bChanged;
		bool m_bMin;
		bool m_bMax;
		int m_iMin;
		int m_iMax;
		bool m_bAllowInvalid;
		bool m_bAllowEmpty;
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

		// IPropertyRectState getters
		Rect getValue(const String &state) override;
		bool hasMin() const override;
		bool hasMax() const override;
		int getMin() const override;
		int getMax() const override;
		bool isAllowInvalid() const override;
		bool isAllowEmpty() const override;

		// IPropertyRectState setters
		bool setValue(const String &state, const Rect value) override;
		IPropertyRectState *setHasMin(const bool value) override;
		IPropertyRectState *setHasMax(const bool value) override;
		IPropertyRectState *setMin(const int value) override;
		IPropertyRectState *setMax(const int value) override;
		IPropertyRectState *setAllowInvalid(const bool value) override;
		IPropertyRectState *setAllowEmpty(const bool value) override;

		CPropertyRectState(
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