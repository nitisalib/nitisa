// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Math/RectL.h"

namespace nitisa
{
	namespace standard
	{
		class IFormRectL
		{
		protected:
			IFormRectL() = default;
			~IFormRectL() = default;
			IFormRectL(const IFormRectL &other) = delete;
			IFormRectL(IFormRectL &&other) = delete;
			IFormRectL &operator=(const IFormRectL &other) = delete;
			IFormRectL &operator=(IFormRectL &&other) = delete;
		public:
			virtual RectL getValue() = 0; // Return value
			// Whether there are limits
			virtual bool hasMin() = 0;
			virtual bool hasMax() = 0;
			// Return limits
			virtual long long getMin() = 0;
			virtual long long getMax() = 0;

			virtual bool setValue(const RectL &value) = 0; // Set value
			// Set whether there are limits
			virtual bool setHasMin(const bool value) = 0;
			virtual bool setHasMax(const bool value) = 0;
			// Set limits
			virtual bool setMin(const long long value) = 0;
			virtual bool setMax(const long long value) = 0;

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}