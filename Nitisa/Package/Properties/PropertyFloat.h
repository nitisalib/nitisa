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
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyFloat.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyFloat :public virtual IPropertyFloat, public CProperty
	{
	public:
		using FGetter = float(*)(IClass *parent);
		using FSetter = bool(*)(IClass *parent, float value);
	private:
		bool m_bMin;
		bool m_bMax;
		float m_fMin;
		float m_fMax;
		float m_tOld;
		float m_tValue;
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

		// IPropertyFloat getters
		float getValue() override;
		bool hasMin() const override;
		bool hasMax() const override;
		float getMin() const override;
		float getMax() const override;

		// IPropertyFloat setters
		bool setValue(const float value) override;
		IPropertyFloat *setHasMin(const bool value) override;
		IPropertyFloat *setHasMax(const bool value) override;
		IPropertyFloat *setMin(const float value) override;
		IPropertyFloat *setMax(const float value) override;

		CPropertyFloat(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter); // See parent class constructor for more information
	};
}