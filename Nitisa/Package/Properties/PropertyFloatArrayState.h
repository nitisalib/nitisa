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
#include "../../Math/FloatArray.h"
#include "../Core/ExportPrefixType.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyFloatArrayState.h"
#include <iostream>
#include <map>
#include <vector>

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyFloatArrayState :public virtual IPropertyFloatArrayState, public CPropertyState
	{
	public:
		using FGetter = FloatArray(*)(IClass *parent, const String &state);
		using FSetter = bool(*)(IClass *parent, const String &state, FloatArray value);
	private:
		std::map<String, FloatArray> m_tOld;
		std::map<String, FloatArray> m_tValue;
		FGetter m_fGetter;
		FSetter m_fSetter;
		bool m_bChanged;
		int m_iMinCount;
		bool m_bHasMin;
		bool m_bHasMax;
		float m_fMin;
		float m_fMax;
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

		// IPropertyFloatArrayState getters
		FloatArray getValue(const String &state) override;
		int getMinCount() override;
		bool hasMin() override;
		bool hasMax() override;
		float getMin() override;
		float getMax() override;

		// IPropertyFloatArrayState setters
		bool setValue(const String &state, const FloatArray value) override;
		IPropertyFloatArrayState *setMinCount(const int value) override;
		IPropertyFloatArrayState *setHasMin(const bool value) override;
		IPropertyFloatArrayState *setHasMax(const bool value) override;
		IPropertyFloatArrayState *setMin(const float value) override;
		IPropertyFloatArrayState *setMax(const float value) override;

		CPropertyFloatArrayState(
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