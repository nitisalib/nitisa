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
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyRect.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyRect :public virtual IPropertyRect, public CProperty
	{
	public:
		using FGetter = Rect(*)(IClass *parent);
		using FSetter = bool(*)(IClass *parent, Rect value);
	private:
		Rect m_tOld;
		Rect m_tValue;
		FGetter m_fGetter;
		FSetter m_fSetter;
		bool m_bChanged;
		bool m_bMin;
		bool m_bMax;
		int m_iMin;
		int m_iMax;
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

		// IPropertyRect getters
		Rect getValue() override;
		bool hasMin() const override;
		bool hasMax() const override;
		int getMin() const override;
		int getMax() const override;
		bool isAllowEmpty() const override;
		bool isAllowInvalid() const override;

		// IPropertyRect setters
		bool setValue(const Rect value) override;
		IPropertyRect *setHasMin(const bool value) override;
		IPropertyRect *setHasMax(const bool value) override;
		IPropertyRect *setMin(const int value) override;
		IPropertyRect *setMax(const int value) override;
		IPropertyRect *setAllowEmpty(const bool value) override;
		IPropertyRect *setAllowInvalid(const bool value) override;

		CPropertyRect(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter); // See parent class constructor for more information
	};
}