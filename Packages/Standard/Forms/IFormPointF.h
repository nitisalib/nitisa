// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Math/PointF.h"

namespace nitisa
{
	namespace standard
	{
		class IFormPointF
		{
		protected:
			IFormPointF() = default;
			~IFormPointF() = default;
			IFormPointF(const IFormPointF &other) = delete;
			IFormPointF(IFormPointF &&other) = delete;
			IFormPointF &operator=(const IFormPointF &other) = delete;
			IFormPointF &operator=(IFormPointF &&other) = delete;
		public:
			virtual PointF getValue() = 0; // Return value
			// Whether there are limits
			virtual bool hasMin() = 0;
			virtual bool hasMax() = 0;
			// Return limits
			virtual float getMin() = 0;
			virtual float getMax() = 0;

			virtual bool setValue(const PointF &value) = 0; // Set value
			// Set whether there are limits
			virtual bool setHasMin(const bool value) = 0;
			virtual bool setHasMax(const bool value) = 0;
			// Set limits
			virtual bool setMin(const float value) = 0;
			virtual bool setMax(const float value) = 0;

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}