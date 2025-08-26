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
#include "../Core/ExportPrefixType.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyTransformState.h"
#include <iostream>
#include <map>

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyTransformState :public virtual IPropertyTransformState, public CPropertyState
	{
	public:
		using FGetter = Transform(*)(IClass *parent, const String &state);
		using FSetter = bool(*)(IClass *parent, const String &state, Transform value);
	private:
		std::map<String, Transform> m_aOld;
		std::map<String, Transform> m_aValue;
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

		// IPropertyTransformState getters
		Transform getValue(const String &state) override;

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

		// IPropertyTransformState setters
		bool setValue(const String &state, const Transform value) override;

		IPropertyTransformState *setAllowedTx(const bool value) override;
		IPropertyTransformState *setAllowedTy(const bool value) override;
		IPropertyTransformState *setAllowedTz(const bool value) override;
		IPropertyTransformState *setAllowedRx(const bool value) override;
		IPropertyTransformState *setAllowedRy(const bool value) override;
		IPropertyTransformState *setAllowedRz(const bool value) override;
		IPropertyTransformState *setAllowedSx(const bool value) override;
		IPropertyTransformState *setAllowedSy(const bool value) override;
		IPropertyTransformState *setAllowedSz(const bool value) override;
		IPropertyTransformState *setAllowedRotateOrder(const bool value) override;
		IPropertyTransformState *setAllowedTransformOrder(const bool value) override;

		IPropertyTransformState *setHasMinTx(const bool value) override;
		IPropertyTransformState *setHasMinTy(const bool value) override;
		IPropertyTransformState *setHasMinTz(const bool value) override;
		IPropertyTransformState *setHasMinRx(const bool value) override;
		IPropertyTransformState *setHasMinRy(const bool value) override;
		IPropertyTransformState *setHasMinRz(const bool value) override;
		IPropertyTransformState *setHasMinSx(const bool value) override;
		IPropertyTransformState *setHasMinSy(const bool value) override;
		IPropertyTransformState *setHasMinSz(const bool value) override;

		IPropertyTransformState *setHasMaxTx(const bool value) override;
		IPropertyTransformState *setHasMaxTy(const bool value) override;
		IPropertyTransformState *setHasMaxTz(const bool value) override;
		IPropertyTransformState *setHasMaxRx(const bool value) override;
		IPropertyTransformState *setHasMaxRy(const bool value) override;
		IPropertyTransformState *setHasMaxRz(const bool value) override;
		IPropertyTransformState *setHasMaxSx(const bool value) override;
		IPropertyTransformState *setHasMaxSy(const bool value) override;
		IPropertyTransformState *setHasMaxSz(const bool value) override;

		IPropertyTransformState *setMinTx(const float value) override;
		IPropertyTransformState *setMinTy(const float value) override;
		IPropertyTransformState *setMinTz(const float value) override;
		IPropertyTransformState *setMinRx(const float value) override;
		IPropertyTransformState *setMinRy(const float value) override;
		IPropertyTransformState *setMinRz(const float value) override;
		IPropertyTransformState *setMinSx(const float value) override;
		IPropertyTransformState *setMinSy(const float value) override;
		IPropertyTransformState *setMinSz(const float value) override;

		IPropertyTransformState *setMaxTx(const float value) override;
		IPropertyTransformState *setMaxTy(const float value) override;
		IPropertyTransformState *setMaxTz(const float value) override;
		IPropertyTransformState *setMaxRx(const float value) override;
		IPropertyTransformState *setMaxRy(const float value) override;
		IPropertyTransformState *setMaxRz(const float value) override;
		IPropertyTransformState *setMaxSx(const float value) override;
		IPropertyTransformState *setMaxSy(const float value) override;
		IPropertyTransformState *setMaxSz(const float value) override;

		CPropertyTransformState(
			IPropertyList *list,
			IClass *parent,
			const String &name,
			const bool read_only,
			const StringArray &states,
			const ExportPrefixType state_prefix_type,
			const String &state_prefix,
			FSkip skip,
			FGetter getter,
			FSetter setter); // See parent class constructor for more information
	};
}