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
#include "../../Math/RectL.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyRectL.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyRectL :public virtual IPropertyRectL, public CProperty
	{
	public:
		using FGetter = RectL(*)(IClass *parent);
		using FSetter = bool(*)(IClass *parent, RectL value);
	private:
		RectL m_tOld;
		RectL m_tValue;
		FGetter m_fGetter;
		FSetter m_fSetter;
		bool m_bChanged;
		bool m_bMin;
		bool m_bMax;
		long long m_iMin;
		long long m_iMax;
		bool m_bAllowEmpty;
		bool m_bAllowInvalid;
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

		// IPropertyRectL getters
		RectL getValue() override;
		bool hasMin() const override;
		bool hasMax() const override;
		long long getMin() const override;
		long long getMax() const override;
		bool isAllowEmpty() const override;
		bool isAllowInvalid() const override;

		// IPropertyRectL setters
		bool setValue(const RectL value) override;
		IPropertyRectL *setHasMin(const bool value) override;
		IPropertyRectL *setHasMax(const bool value) override;
		IPropertyRectL *setMin(const long long value) override;
		IPropertyRectL *setMax(const long long value) override;
		IPropertyRectL *setAllowEmpty(const bool value) override;
		IPropertyRectL *setAllowInvalid(const bool value) override;

		CPropertyRectL(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter); // See parent class constructor for more information
	};
}