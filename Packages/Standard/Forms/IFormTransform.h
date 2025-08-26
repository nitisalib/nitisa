// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Math/Transform.h"

namespace nitisa
{
	namespace standard
	{
		class IFormTransform
		{
		protected:
			IFormTransform() = default;
			~IFormTransform() = default;
			IFormTransform(const IFormTransform &other) = delete;
			IFormTransform(IFormTransform &&other) = delete;
			IFormTransform &operator=(const IFormTransform &other) = delete;
			IFormTransform &operator=(IFormTransform &&other) = delete;
		public:
			virtual Transform getValue() = 0; // Return value
			// Whether transformations are allowed
			virtual bool isAllowedTx() const = 0;
			virtual bool isAllowedTy() const = 0;
			virtual bool isAllowedTz() const = 0;
			virtual bool isAllowedSx() const = 0;
			virtual bool isAllowedSy() const = 0;
			virtual bool isAllowedSz() const = 0;
			virtual bool isAllowedRx() const = 0;
			virtual bool isAllowedRy() const = 0;
			virtual bool isAllowedRz() const = 0;
			virtual bool isAllowedRotateOrder() const = 0;
			virtual bool isAllowedTransformOrder() const = 0;
			// Whether there are minimum limits
			virtual bool hasMinTx() const = 0;
			virtual bool hasMinTy() const = 0;
			virtual bool hasMinTz() const = 0;
			virtual bool hasMinSx() const = 0;
			virtual bool hasMinSy() const = 0;
			virtual bool hasMinSz() const = 0;
			virtual bool hasMinRx() const = 0;
			virtual bool hasMinRy() const = 0;
			virtual bool hasMinRz() const = 0;
			// Whether there are maximum limits
			virtual bool hasMaxTx() const = 0;
			virtual bool hasMaxTy() const = 0;
			virtual bool hasMaxTz() const = 0;
			virtual bool hasMaxSx() const = 0;
			virtual bool hasMaxSy() const = 0;
			virtual bool hasMaxSz() const = 0;
			virtual bool hasMaxRx() const = 0;
			virtual bool hasMaxRy() const = 0;
			virtual bool hasMaxRz() const = 0;
			// Return minimum limits
			virtual float getMinTx() const = 0;
			virtual float getMinTy() const = 0;
			virtual float getMinTz() const = 0;
			virtual float getMinSx() const = 0;
			virtual float getMinSy() const = 0;
			virtual float getMinSz() const = 0;
			virtual float getMinRx() const = 0;
			virtual float getMinRy() const = 0;
			virtual float getMinRz() const = 0;
			// Return maximum limits
			virtual float getMaxTx() const = 0;
			virtual float getMaxTy() const = 0;
			virtual float getMaxTz() const = 0;
			virtual float getMaxSx() const = 0;
			virtual float getMaxSy() const = 0;
			virtual float getMaxSz() const = 0;
			virtual float getMaxRx() const = 0;
			virtual float getMaxRy() const = 0;
			virtual float getMaxRz() const = 0;

			virtual bool setValue(const Transform &value) = 0; // Set value
			// Set whether transformations are allowed
			virtual bool setAllowedTx(const bool value) = 0;
			virtual bool setAllowedTy(const bool value) = 0;
			virtual bool setAllowedTz(const bool value) = 0;
			virtual bool setAllowedSx(const bool value) = 0;
			virtual bool setAllowedSy(const bool value) = 0;
			virtual bool setAllowedSz(const bool value) = 0;
			virtual bool setAllowedRx(const bool value) = 0;
			virtual bool setAllowedRy(const bool value) = 0;
			virtual bool setAllowedRz(const bool value) = 0;
			virtual bool setAllowedRotateOrder(const bool value) = 0;
			virtual bool setAllowedTransformOrder(const bool value) = 0;
			// Set whether there are minimum limits
			virtual bool setHasMinTx(const bool value) = 0;
			virtual bool setHasMinTy(const bool value) = 0;
			virtual bool setHasMinTz(const bool value) = 0;
			virtual bool setHasMinSx(const bool value) = 0;
			virtual bool setHasMinSy(const bool value) = 0;
			virtual bool setHasMinSz(const bool value) = 0;
			virtual bool setHasMinRx(const bool value) = 0;
			virtual bool setHasMinRy(const bool value) = 0;
			virtual bool setHasMinRz(const bool value) = 0;
			// Set whether there are maximum limits
			virtual bool setHasMaxTx(const bool value) = 0;
			virtual bool setHasMaxTy(const bool value) = 0;
			virtual bool setHasMaxTz(const bool value) = 0;
			virtual bool setHasMaxSx(const bool value) = 0;
			virtual bool setHasMaxSy(const bool value) = 0;
			virtual bool setHasMaxSz(const bool value) = 0;
			virtual bool setHasMaxRx(const bool value) = 0;
			virtual bool setHasMaxRy(const bool value) = 0;
			virtual bool setHasMaxRz(const bool value) = 0;
			// Set minimum limits
			virtual bool setMinTx(const float value) = 0;
			virtual bool setMinTy(const float value) = 0;
			virtual bool setMinTz(const float value) = 0;
			virtual bool setMinSx(const float value) = 0;
			virtual bool setMinSy(const float value) = 0;
			virtual bool setMinSz(const float value) = 0;
			virtual bool setMinRx(const float value) = 0;
			virtual bool setMinRy(const float value) = 0;
			virtual bool setMinRz(const float value) = 0;
			// Set maximum limits
			virtual bool setMaxTx(const float value) = 0;
			virtual bool setMaxTy(const float value) = 0;
			virtual bool setMaxTz(const float value) = 0;
			virtual bool setMaxSx(const float value) = 0;
			virtual bool setMaxSy(const float value) = 0;
			virtual bool setMaxSz(const float value) = 0;
			virtual bool setMaxRx(const float value) = 0;
			virtual bool setMaxRy(const float value) = 0;
			virtual bool setMaxRz(const float value) = 0;

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}