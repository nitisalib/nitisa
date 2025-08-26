// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Math/Transform.h"
#include "IPropertyState.h"

namespace nitisa
{
	class IPropertyTransformState :public virtual IPropertyState
	{
	protected:
		IPropertyTransformState() = default;
		~IPropertyTransformState() = default;
		IPropertyTransformState(const IPropertyTransformState &other) = delete;
		IPropertyTransformState(IPropertyTransformState &&other) = delete;
		IPropertyTransformState &operator=(const IPropertyTransformState &other) = delete;
		IPropertyTransformState &operator=(IPropertyTransformState &&other) = delete;
	public:
		virtual Transform getValue(const String &state) = 0; // Return value depending on state

		virtual bool setValue(const String &state, const Transform value) = 0; // Set value of state

		// Whether transformations allowed
		virtual bool isAllowedTx() const = 0;
		virtual bool isAllowedTy() const = 0;
		virtual bool isAllowedTz() const = 0;
		virtual bool isAllowedRx() const = 0;
		virtual bool isAllowedRy() const = 0;
		virtual bool isAllowedRz() const = 0;
		virtual bool isAllowedSx() const = 0;
		virtual bool isAllowedSy() const = 0;
		virtual bool isAllowedSz() const = 0;
		virtual bool isAllowedRotateOrder() const = 0;
		virtual bool isAllowedTransformOrder() const = 0;

		// Whether minimum limits exist
		virtual bool hasMinTx() const = 0;
		virtual bool hasMinTy() const = 0;
		virtual bool hasMinTz() const = 0;
		virtual bool hasMinRx() const = 0;
		virtual bool hasMinRy() const = 0;
		virtual bool hasMinRz() const = 0;
		virtual bool hasMinSx() const = 0;
		virtual bool hasMinSy() const = 0;
		virtual bool hasMinSz() const = 0;

		// Whether maximum limits exist
		virtual bool hasMaxTx() const = 0;
		virtual bool hasMaxTy() const = 0;
		virtual bool hasMaxTz() const = 0;
		virtual bool hasMaxRx() const = 0;
		virtual bool hasMaxRy() const = 0;
		virtual bool hasMaxRz() const = 0;
		virtual bool hasMaxSx() const = 0;
		virtual bool hasMaxSy() const = 0;
		virtual bool hasMaxSz() const = 0;

		// Return minimum limits
		virtual float getMinTx() const = 0;
		virtual float getMinTy() const = 0;
		virtual float getMinTz() const = 0;
		virtual float getMinRx() const = 0;
		virtual float getMinRy() const = 0;
		virtual float getMinRz() const = 0;
		virtual float getMinSx() const = 0;
		virtual float getMinSy() const = 0;
		virtual float getMinSz() const = 0;

		// Return maximum limits
		virtual float getMaxTx() const = 0;
		virtual float getMaxTy() const = 0;
		virtual float getMaxTz() const = 0;
		virtual float getMaxRx() const = 0;
		virtual float getMaxRy() const = 0;
		virtual float getMaxRz() const = 0;
		virtual float getMaxSx() const = 0;
		virtual float getMaxSy() const = 0;
		virtual float getMaxSz() const = 0;

		// Set whether transformations allowed
		virtual IPropertyTransformState *setAllowedTx(const bool value) = 0;
		virtual IPropertyTransformState *setAllowedTy(const bool value) = 0;
		virtual IPropertyTransformState *setAllowedTz(const bool value) = 0;
		virtual IPropertyTransformState *setAllowedRx(const bool value) = 0;
		virtual IPropertyTransformState *setAllowedRy(const bool value) = 0;
		virtual IPropertyTransformState *setAllowedRz(const bool value) = 0;
		virtual IPropertyTransformState *setAllowedSx(const bool value) = 0;
		virtual IPropertyTransformState *setAllowedSy(const bool value) = 0;
		virtual IPropertyTransformState *setAllowedSz(const bool value) = 0;
		virtual IPropertyTransformState *setAllowedRotateOrder(const bool value) = 0;
		virtual IPropertyTransformState *setAllowedTransformOrder(const bool value) = 0;

		// Set whether minimum limits exist
		virtual IPropertyTransformState *setHasMinTx(const bool value) = 0;
		virtual IPropertyTransformState *setHasMinTy(const bool value) = 0;
		virtual IPropertyTransformState *setHasMinTz(const bool value) = 0;
		virtual IPropertyTransformState *setHasMinRx(const bool value) = 0;
		virtual IPropertyTransformState *setHasMinRy(const bool value) = 0;
		virtual IPropertyTransformState *setHasMinRz(const bool value) = 0;
		virtual IPropertyTransformState *setHasMinSx(const bool value) = 0;
		virtual IPropertyTransformState *setHasMinSy(const bool value) = 0;
		virtual IPropertyTransformState *setHasMinSz(const bool value) = 0;

		// Set whether maximum limits exist
		virtual IPropertyTransformState *setHasMaxTx(const bool value) = 0;
		virtual IPropertyTransformState *setHasMaxTy(const bool value) = 0;
		virtual IPropertyTransformState *setHasMaxTz(const bool value) = 0;
		virtual IPropertyTransformState *setHasMaxRx(const bool value) = 0;
		virtual IPropertyTransformState *setHasMaxRy(const bool value) = 0;
		virtual IPropertyTransformState *setHasMaxRz(const bool value) = 0;
		virtual IPropertyTransformState *setHasMaxSx(const bool value) = 0;
		virtual IPropertyTransformState *setHasMaxSy(const bool value) = 0;
		virtual IPropertyTransformState *setHasMaxSz(const bool value) = 0;

		// Set minimum limits
		virtual IPropertyTransformState *setMinTx(const float value) = 0;
		virtual IPropertyTransformState *setMinTy(const float value) = 0;
		virtual IPropertyTransformState *setMinTz(const float value) = 0;
		virtual IPropertyTransformState *setMinRx(const float value) = 0;
		virtual IPropertyTransformState *setMinRy(const float value) = 0;
		virtual IPropertyTransformState *setMinRz(const float value) = 0;
		virtual IPropertyTransformState *setMinSx(const float value) = 0;
		virtual IPropertyTransformState *setMinSy(const float value) = 0;
		virtual IPropertyTransformState *setMinSz(const float value) = 0;

		// Set maximum limits
		virtual IPropertyTransformState *setMaxTx(const float value) = 0;
		virtual IPropertyTransformState *setMaxTy(const float value) = 0;
		virtual IPropertyTransformState *setMaxTz(const float value) = 0;
		virtual IPropertyTransformState *setMaxRx(const float value) = 0;
		virtual IPropertyTransformState *setMaxRy(const float value) = 0;
		virtual IPropertyTransformState *setMaxRz(const float value) = 0;
		virtual IPropertyTransformState *setMaxSx(const float value) = 0;
		virtual IPropertyTransformState *setMaxSy(const float value) = 0;
		virtual IPropertyTransformState *setMaxSz(const float value) = 0;
	};
}