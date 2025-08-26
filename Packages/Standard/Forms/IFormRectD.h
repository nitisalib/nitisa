// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Math/RectD.h"

namespace nitisa
{
	namespace standard
	{
		class IFormRectD
		{
		protected:
			IFormRectD() = default;
			~IFormRectD() = default;
			IFormRectD(const IFormRectD &other) = delete;
			IFormRectD(IFormRectD &&other) = delete;
			IFormRectD &operator=(const IFormRectD &other) = delete;
			IFormRectD &operator=(IFormRectD &&other) = delete;
		public:
			virtual RectD getValue() = 0; // Return value
			// Whether there are limits
			virtual bool hasMin() = 0;
			virtual bool hasMax() = 0;
			// Return limits
			virtual double getMin() = 0;
			virtual double getMax() = 0;

			virtual bool setValue(const RectD &value) = 0; // Set value
			// Set whether there are limits
			virtual bool setHasMin(const bool value) = 0;
			virtual bool setHasMax(const bool value) = 0;
			// Set limits
			virtual bool setMin(const double value) = 0;
			virtual bool setMax(const double value) = 0;

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}