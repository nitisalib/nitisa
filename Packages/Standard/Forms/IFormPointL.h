// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Math/PointL.h"

namespace nitisa
{
	namespace standard
	{
		class IFormPointL
		{
		protected:
			IFormPointL() = default;
			~IFormPointL() = default;
			IFormPointL(const IFormPointL &other) = delete;
			IFormPointL(IFormPointL &&other) = delete;
			IFormPointL &operator=(const IFormPointL &other) = delete;
			IFormPointL &operator=(IFormPointL &&other) = delete;
		public:
			virtual PointL getValue() = 0; // Return value
			// Whether has limits
			virtual bool hasMin() = 0;
			virtual bool hasMax() = 0;
			// Return limits
			virtual long long getMin() = 0;
			virtual long long getMax() = 0;

			virtual bool setValue(const PointL &value) = 0; // Set value
			// Set whether has limits
			virtual bool setHasMin(const bool value) = 0;
			virtual bool setHasMax(const bool value) = 0;
			// Set limits
			virtual bool setMin(const long long value) = 0;
			virtual bool setMax(const long long value) = 0;

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}