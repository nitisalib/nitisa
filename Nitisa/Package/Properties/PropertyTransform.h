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
#include "../../Math/Transform.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyTransform.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyTransform :public virtual IPropertyTransform, public CProperty
	{
	public:
		using FGetter = Transform(*)(IClass *parent);
		using FSetter = bool(*)(IClass *parent, Transform value);
	private:
		Transform m_tOld;
		Transform m_tValue;
		FGetter m_fGetter;
		FSetter m_fSetter;
		bool m_bChanged;
		
		bool m_bTx;
		bool m_bTy;
		bool m_bTz;
		bool m_bRx;
		bool m_bRy;
		bool m_bRz;
		bool m_bSx;
		bool m_bSy;
		bool m_bSz;
		bool m_bRotateOrder;
		bool m_bTransformOrder;

		bool m_bMinTx;
		bool m_bMinTy;
		bool m_bMinTz;
		bool m_bMinRx;
		bool m_bMinRy;
		bool m_bMinRz;
		bool m_bMinSx;
		bool m_bMinSy;
		bool m_bMinSz;

		bool m_bMaxTx;
		bool m_bMaxTy;
		bool m_bMaxTz;
		bool m_bMaxRx;
		bool m_bMaxRy;
		bool m_bMaxRz;
		bool m_bMaxSx;
		bool m_bMaxSy;
		bool m_bMaxSz;

		float m_fMinTx;
		float m_fMinTy;
		float m_fMinTz;
		float m_fMinRx;
		float m_fMinRy;
		float m_fMinRz;
		float m_fMinSx;
		float m_fMinSy;
		float m_fMinSz;

		float m_fMaxTx;
		float m_fMaxTy;
		float m_fMaxTz;
		float m_fMaxRx;
		float m_fMaxRy;
		float m_fMaxRz;
		float m_fMaxSx;
		float m_fMaxSy;
		float m_fMaxSz;
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

		// IPropertyTransform getters
		Transform getValue() override;

		bool isAllowedTx() const override;
		bool isAllowedTy() const override;
		bool isAllowedTz() const override;
		bool isAllowedRx() const override;
		bool isAllowedRy() const override;
		bool isAllowedRz() const override;
		bool isAllowedSx() const override;
		bool isAllowedSy() const override;
		bool isAllowedSz() const override;
		bool isAllowedRotateOrder() const override;
		bool isAllowedTransformOrder() const override;

		bool hasMinTx() const override;
		bool hasMinTy() const override;
		bool hasMinTz() const override;
		bool hasMinRx() const override;
		bool hasMinRy() const override;
		bool hasMinRz() const override;
		bool hasMinSx() const override;
		bool hasMinSy() const override;
		bool hasMinSz() const override;

		bool hasMaxTx() const override;
		bool hasMaxTy() const override;
		bool hasMaxTz() const override;
		bool hasMaxRx() const override;
		bool hasMaxRy() const override;
		bool hasMaxRz() const override;
		bool hasMaxSx() const override;
		bool hasMaxSy() const override;
		bool hasMaxSz() const override;

		float getMinTx() const override;
		float getMinTy() const override;
		float getMinTz() const override;
		float getMinRx() const override;
		float getMinRy() const override;
		float getMinRz() const override;
		float getMinSx() const override;
		float getMinSy() const override;
		float getMinSz() const override;

		float getMaxTx() const override;
		float getMaxTy() const override;
		float getMaxTz() const override;
		float getMaxRx() const override;
		float getMaxRy() const override;
		float getMaxRz() const override;
		float getMaxSx() const override;
		float getMaxSy() const override;
		float getMaxSz() const override;

		// IPropertyTransform setters
		bool setValue(const Transform value) override;

		IPropertyTransform *setAllowedTx(const bool value) override;
		IPropertyTransform *setAllowedTy(const bool value) override;
		IPropertyTransform *setAllowedTz(const bool value) override;
		IPropertyTransform *setAllowedRx(const bool value) override;
		IPropertyTransform *setAllowedRy(const bool value) override;
		IPropertyTransform *setAllowedRz(const bool value) override;
		IPropertyTransform *setAllowedSx(const bool value) override;
		IPropertyTransform *setAllowedSy(const bool value) override;
		IPropertyTransform *setAllowedSz(const bool value) override;
		IPropertyTransform *setAllowedRotateOrder(const bool value) override;
		IPropertyTransform *setAllowedTransformOrder(const bool value) override;

		IPropertyTransform *setHasMinTx(const bool value) override;
		IPropertyTransform *setHasMinTy(const bool value) override;
		IPropertyTransform *setHasMinTz(const bool value) override;
		IPropertyTransform *setHasMinRx(const bool value) override;
		IPropertyTransform *setHasMinRy(const bool value) override;
		IPropertyTransform *setHasMinRz(const bool value) override;
		IPropertyTransform *setHasMinSx(const bool value) override;
		IPropertyTransform *setHasMinSy(const bool value) override;
		IPropertyTransform *setHasMinSz(const bool value) override;

		IPropertyTransform *setHasMaxTx(const bool value) override;
		IPropertyTransform *setHasMaxTy(const bool value) override;
		IPropertyTransform *setHasMaxTz(const bool value) override;
		IPropertyTransform *setHasMaxRx(const bool value) override;
		IPropertyTransform *setHasMaxRy(const bool value) override;
		IPropertyTransform *setHasMaxRz(const bool value) override;
		IPropertyTransform *setHasMaxSx(const bool value) override;
		IPropertyTransform *setHasMaxSy(const bool value) override;
		IPropertyTransform *setHasMaxSz(const bool value) override;

		IPropertyTransform *setMinTx(const float value) override;
		IPropertyTransform *setMinTy(const float value) override;
		IPropertyTransform *setMinTz(const float value) override;
		IPropertyTransform *setMinRx(const float value) override;
		IPropertyTransform *setMinRy(const float value) override;
		IPropertyTransform *setMinRz(const float value) override;
		IPropertyTransform *setMinSx(const float value) override;
		IPropertyTransform *setMinSy(const float value) override;
		IPropertyTransform *setMinSz(const float value) override;

		IPropertyTransform *setMaxTx(const float value) override;
		IPropertyTransform *setMaxTy(const float value) override;
		IPropertyTransform *setMaxTz(const float value) override;
		IPropertyTransform *setMaxRx(const float value) override;
		IPropertyTransform *setMaxRy(const float value) override;
		IPropertyTransform *setMaxRz(const float value) override;
		IPropertyTransform *setMaxSx(const float value) override;
		IPropertyTransform *setMaxSy(const float value) override;
		IPropertyTransform *setMaxSz(const float value) override;

		CPropertyTransform(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter); // See parent class constructor for more information
	};
}