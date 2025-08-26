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
#include "../Interfaces/IPropertyDouble.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyDouble :public virtual IPropertyDouble, public CProperty
	{
	public:
		using FGetter = double(*)(IClass *parent);
		using FSetter = bool(*)(IClass *parent, double value);
	private:
		bool m_bMin;
		bool m_bMax;
		double m_fMin;
		double m_fMax;
		double m_tOld;
		double m_tValue;
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

		// IPropertyDouble getters
		double getValue() override;
		bool hasMin() const override;
		bool hasMax() const override;
		double getMin() const override;
		double getMax() const override;

		// IPropertyDouble setters
		bool setValue(const double value) override;
		IPropertyDouble *setHasMin(const bool value) override;
		IPropertyDouble *setHasMax(const bool value) override;
		IPropertyDouble *setMin(const double value) override;
		IPropertyDouble *setMax(const double value) override;

		CPropertyDouble(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter); // See parent class constructor for more information
	};
}