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
#include "../../Math/RectF.h"
#include "../Core/ExportPrefixType.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyRectFState.h"
#include <iostream>
#include <map>

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyRectFState :public virtual IPropertyRectFState, public CPropertyState
	{
	public:
		using FGetter = RectF(*)(IClass *parent, const String &state);
		using FSetter = bool(*)(IClass *parent, const String &state, RectF value);
	private:
		std::map<String, RectF> m_aOld;
		std::map<String, RectF> m_aValue;
		FGetter m_fGetter;
		FSetter m_fSetter;
		bool m_bChanged;
		bool m_bMin;
		bool m_bMax;
		float m_fMin;
		float m_fMax;
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

		// IPropertyRectFState getters
		RectF getValue(const String &state) override;
		bool hasMin() const override;
		bool hasMax() const override;
		float getMin() const override;
		float getMax() const override;
		bool isAllowInvalid() const override;
		bool isAllowEmpty() const override;

		// IPropertyRectFState setters
		bool setValue(const String &state, const RectF value) override;
		IPropertyRectFState *setHasMin(const bool value) override;
		IPropertyRectFState *setHasMax(const bool value) override;
		IPropertyRectFState *setMin(const float value) override;
		IPropertyRectFState *setMax(const float value) override;
		IPropertyRectFState *setAllowInvalid(const bool value) override;
		IPropertyRectFState *setAllowEmpty(const bool value) override;

		CPropertyRectFState(
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