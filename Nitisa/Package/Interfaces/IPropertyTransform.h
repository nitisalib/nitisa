// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Math/Transform.h"
#include "IProperty.h"

namespace nitisa
{
	class IPropertyTransform :public virtual IProperty
	{
	protected:
		IPropertyTransform() = default;
		~IPropertyTransform() = default;
		IPropertyTransform(const IPropertyTransform &other) = delete;
		IPropertyTransform(IPropertyTransform &&other) = delete;
		IPropertyTransform &operator=(const IPropertyTransform &other) = delete;
		IPropertyTransform &operator=(IPropertyTransform &&other) = delete;
	public:
		virtual Transform getValue() = 0; // Return value

		virtual bool setValue(const Transform value) = 0; // Set value

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

		// Whether there are minimum limits
		virtual bool hasMinTx() const = 0;
		virtual bool hasMinTy() const = 0;
		virtual bool hasMinTz() const = 0;
		virtual bool hasMinRx() const = 0;
		virtual bool hasMinRy() const = 0;
		virtual bool hasMinRz() const = 0;
		virtual bool hasMinSx() const = 0;
		virtual bool hasMinSy() const = 0;
		virtual bool hasMinSz() const = 0;

		// Whether there are maximum limits
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
		virtual IPropertyTransform *setAllowedTx(const bool value) = 0;
		virtual IPropertyTransform *setAllowedTy(const bool value) = 0;
		virtual IPropertyTransform *setAllowedTz(const bool value) = 0;
		virtual IPropertyTransform *setAllowedRx(const bool value) = 0;
		virtual IPropertyTransform *setAllowedRy(const bool value) = 0;
		virtual IPropertyTransform *setAllowedRz(const bool value) = 0;
		virtual IPropertyTransform *setAllowedSx(const bool value) = 0;
		virtual IPropertyTransform *setAllowedSy(const bool value) = 0;
		virtual IPropertyTransform *setAllowedSz(const bool value) = 0;
		virtual IPropertyTransform *setAllowedRotateOrder(const bool value) = 0;
		virtual IPropertyTransform *setAllowedTransformOrder(const bool value) = 0;

		// Set whether have minimum limits
		virtual IPropertyTransform *setHasMinTx(const bool value) = 0;
		virtual IPropertyTransform *setHasMinTy(const bool value) = 0;
		virtual IPropertyTransform *setHasMinTz(const bool value) = 0;
		virtual IPropertyTransform *setHasMinRx(const bool value) = 0;
		virtual IPropertyTransform *setHasMinRy(const bool value) = 0;
		virtual IPropertyTransform *setHasMinRz(const bool value) = 0;
		virtual IPropertyTransform *setHasMinSx(const bool value) = 0;
		virtual IPropertyTransform *setHasMinSy(const bool value) = 0;
		virtual IPropertyTransform *setHasMinSz(const bool value) = 0;

		// Set whether have maximum limits
		virtual IPropertyTransform *setHasMaxTx(const bool value) = 0;
		virtual IPropertyTransform *setHasMaxTy(const bool value) = 0;
		virtual IPropertyTransform *setHasMaxTz(const bool value) = 0;
		virtual IPropertyTransform *setHasMaxRx(const bool value) = 0;
		virtual IPropertyTransform *setHasMaxRy(const bool value) = 0;
		virtual IPropertyTransform *setHasMaxRz(const bool value) = 0;
		virtual IPropertyTransform *setHasMaxSx(const bool value) = 0;
		virtual IPropertyTransform *setHasMaxSy(const bool value) = 0;
		virtual IPropertyTransform *setHasMaxSz(const bool value) = 0;

		// Set minimum limits
		virtual IPropertyTransform *setMinTx(const float value) = 0;
		virtual IPropertyTransform *setMinTy(const float value) = 0;
		virtual IPropertyTransform *setMinTz(const float value) = 0;
		virtual IPropertyTransform *setMinRx(const float value) = 0;
		virtual IPropertyTransform *setMinRy(const float value) = 0;
		virtual IPropertyTransform *setMinRz(const float value) = 0;
		virtual IPropertyTransform *setMinSx(const float value) = 0;
		virtual IPropertyTransform *setMinSy(const float value) = 0;
		virtual IPropertyTransform *setMinSz(const float value) = 0;

		// Set maximum limits
		virtual IPropertyTransform *setMaxTx(const float value) = 0;
		virtual IPropertyTransform *setMaxTy(const float value) = 0;
		virtual IPropertyTransform *setMaxTz(const float value) = 0;
		virtual IPropertyTransform *setMaxRx(const float value) = 0;
		virtual IPropertyTransform *setMaxRy(const float value) = 0;
		virtual IPropertyTransform *setMaxRz(const float value) = 0;
		virtual IPropertyTransform *setMaxSx(const float value) = 0;
		virtual IPropertyTransform *setMaxSy(const float value) = 0;
		virtual IPropertyTransform *setMaxSz(const float value) = 0;
	};
}