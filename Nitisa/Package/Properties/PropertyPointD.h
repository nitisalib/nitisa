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
#include "../../Math/PointD.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyPointD.h"
#include <iostream>
#include <map>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyPointD :public virtual IPropertyPointD, public CProperty
	{
	public:
		using FGetter = PointD(*)(IClass *parent);
		using FSetter = bool(*)(IClass *parent, PointD value);
	private:
		PointD m_tOld;
		PointD m_tValue;
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

		// IPropertyPointD getters
		PointD getValue() override;
		bool hasMin() const override;
		bool hasMax() const override;
		double getMin() const override;
		double getMax() const override;

		// IPropertyPointD setters
		bool setValue(const PointD value) override;
		IPropertyPointD *setHasMin(const bool value) override;
		IPropertyPointD *setHasMax(const bool value) override;
		IPropertyPointD *setMin(const double value) override;
		IPropertyPointD *setMax(const double value) override;

		CPropertyPointD(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter); // See parent class constructor for more information
	};
}