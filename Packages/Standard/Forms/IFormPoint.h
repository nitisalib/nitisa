// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Math/Point.h"

namespace nitisa
{
	namespace standard
	{
		class IFormPoint
		{
		protected:
			IFormPoint() = default;
			~IFormPoint() = default;
			IFormPoint(const IFormPoint &other) = delete;
			IFormPoint(IFormPoint &&other) = delete;
			IFormPoint &operator=(const IFormPoint &other) = delete;
			IFormPoint &operator=(IFormPoint &&other) = delete;
		public:
			virtual Point getValue() = 0; // Return value
			// Whether has limits
			virtual bool hasMin() = 0;
			virtual bool hasMax() = 0;
			// Return limits
			virtual int getMin() = 0;
			virtual int getMax() = 0;

			virtual bool setValue(const Point &value) = 0; // Set value
			// Set whether has limits
			virtual bool setHasMin(const bool value) = 0;
			virtual bool setHasMax(const bool value) = 0;
			// Set limits
			virtual bool setMin(const int value) = 0;
			virtual bool setMax(const int value) = 0;

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}