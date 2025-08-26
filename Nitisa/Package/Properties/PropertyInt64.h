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
#include "../Interfaces/IPropertyInt64.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyInt64 :public virtual IPropertyInt64, public CProperty
	{
	public:
		using FGetter = long long(*)(IClass *parent);
		using FSetter = bool(*)(IClass *parent, long long value);
	private:
		long long m_tOld;
		long long m_tValue;
		FGetter m_fGetter;
		FSetter m_fSetter;
		bool m_bChanged;
		bool m_bMin;
		bool m_bMax;
		long long m_iMin;
		long long m_iMax;
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

		// IPropertyInt64 getters
		long long getValue() override;
		bool hasMin() const override;
		bool hasMax() const override;
		long long getMin() const override;
		long long getMax() const override;

		// IPropertyInt64 setters
		bool setValue(const long long value) override;
		IPropertyInt64 *setHasMin(const bool value) override;
		IPropertyInt64 *setHasMax(const bool value) override;
		IPropertyInt64 *setMin(const long long value) override;
		IPropertyInt64 *setMax(const long long value) override;

		CPropertyInt64(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter); // See parent class constructor for more information
	};
}