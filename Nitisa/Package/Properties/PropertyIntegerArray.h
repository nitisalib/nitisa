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
#include "../../Math/IntegerArray.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyIntegerArray.h"
#include <iostream>
#include <vector>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyIntegerArray :public virtual IPropertyIntegerArray, public CProperty
	{
	public:
		using FGetter = IntegerArray(*)(IClass *parent);
		using FSetter = bool(*)(IClass *parent, IntegerArray value);
	private:
		IntegerArray m_tOld;
		IntegerArray m_tValue;
		FGetter m_fGetter;
		FSetter m_fSetter;
		bool m_bChanged;
		int m_iMinCount;
		bool m_bMin;
		bool m_bMax;
		int m_iMin;
		int m_iMax;
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

		// IPropertyIntegerArray getters
		IntegerArray getValue() override;
		int getMinCount() override;
		bool hasMin() override;
		bool hasMax() override;
		int getMin() override;
		int getMax() override;

		// IPropertyIntegerArray setters
		bool setValue(const IntegerArray value) override;
		IPropertyIntegerArray *setMinCount(const int value) override;
		IPropertyIntegerArray *setHasMin(const bool value) override;
		IPropertyIntegerArray *setHasMax(const bool value) override;
		IPropertyIntegerArray *setMin(const int value) override;
		IPropertyIntegerArray *setMax(const int value) override;

		CPropertyIntegerArray(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter); // See parent class constructor for more information
	};
}