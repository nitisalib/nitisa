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
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyFloatArray.h"
#include <iostream>
#include <vector>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyFloatArray :public virtual IPropertyFloatArray, public CProperty
	{
	public:
		using FGetter = FloatArray(*)(IClass *parent);
		using FSetter = bool(*)(IClass *parent, FloatArray value);
	private:
		FloatArray m_tOld;
		FloatArray m_tValue;
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

		// IPropertyFloatArray getters
		FloatArray getValue() override;
		int getMinCount() override;
		bool hasMin() override;
		bool hasMax() override;
		float getMin() override;
		float getMax() override;

		// IPropertyFloatArray setters
		bool setValue(const FloatArray value) override;
		IPropertyFloatArray *setMinCount(const int value) override;
		IPropertyFloatArray *setHasMin(const bool value) override;
		IPropertyFloatArray *setHasMax(const bool value) override;
		IPropertyFloatArray *setMin(const float value) override;
		IPropertyFloatArray *setMax(const float value) override;

		CPropertyFloatArray(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter); // See parent class constructor for more information
	};
}