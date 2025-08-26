// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Math/Rect.h"

namespace nitisa
{
	namespace standard
	{
		class IFormRect
		{
		protected:
			IFormRect() = default;
			~IFormRect() = default;
			IFormRect(const IFormRect &other) = delete;
			IFormRect(IFormRect &&other) = delete;
			IFormRect &operator=(const IFormRect &other) = delete;
			IFormRect &operator=(IFormRect &&other) = delete;
		public:
			virtual Rect getValue() = 0; // Return value
			// Whether there are limits
			virtual bool hasMin() = 0;
			virtual bool hasMax() = 0;
			// Return limits
			virtual int getMin() = 0;
			virtual int getMax() = 0;

			virtual bool setValue(const Rect &value) = 0; // Set value
			// Set whether there are limits
			virtual bool setHasMin(const bool value) = 0;
			virtual bool setHasMax(const bool value) = 0;
			// Set limits
			virtual bool setMin(const int value) = 0;
			virtual bool setMax(const int value) = 0;

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}