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
#include "../../Math/PointF.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyPointF.h"
#include <iostream>
#include <map>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyPointF :public virtual IPropertyPointF, public CProperty
	{
	public:
		using FGetter = PointF(*)(IClass *parent);
		using FSetter = bool(*)(IClass *parent, PointF value);
	private:
		PointF m_tOld;
		PointF m_tValue;
		FGetter m_fGetter;
		FSetter m_fSetter;
		bool m_bChanged;
		bool m_bMin;
		bool m_bMax;
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

		// IPropertyPointF getters
		PointF getValue() override;
		bool hasMin() const override;
		bool hasMax() const override;
		float getMin() const override;
		float getMax() const override;

		// IPropertyPointF setters
		bool setValue(const PointF value) override;
		IPropertyPointF *setHasMin(const bool value) override;
		IPropertyPointF *setHasMax(const bool value) override;
		IPropertyPointF *setMin(const float value) override;
		IPropertyPointF *setMax(const float value) override;

		CPropertyPointF(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter); // See parent class constructor for more information
	};
}