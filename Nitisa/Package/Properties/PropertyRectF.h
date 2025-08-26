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
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyRectF.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyRectF :public virtual IPropertyRectF, public CProperty
	{
	public:
		using FGetter = RectF(*)(IClass *parent);
		using FSetter = bool(*)(IClass *parent, RectF value);
	private:
		RectF m_tOld;
		RectF m_tValue;
		FGetter m_fGetter;
		FSetter m_fSetter;
		bool m_bChanged;
		bool m_bMin;
		bool m_bMax;
		float m_fMin;
		float m_fMax;
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

		// IPropertyRectF getters
		RectF getValue() override;
		bool hasMin() const override;
		bool hasMax() const override;
		float getMin() const override;
		float getMax() const override;
		bool isAllowEmpty() const override;
		bool isAllowInvalid() const override;

		// IPropertyRectF setters
		bool setValue(const RectF value) override;
		IPropertyRectF *setHasMin(const bool value) override;
		IPropertyRectF *setHasMax(const bool value) override;
		IPropertyRectF *setMin(const float value) override;
		IPropertyRectF *setMax(const float value) override;
		IPropertyRectF *setAllowEmpty(const bool value) override;
		IPropertyRectF *setAllowInvalid(const bool value) override;

		CPropertyRectF(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter); // See parent class constructor for more information
	};
}