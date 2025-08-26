// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Math/IntegerArray.h"

namespace nitisa
{
	namespace standard
	{
		class IFormIntegerArray
		{
		protected:
			IFormIntegerArray() = default;
			~IFormIntegerArray() = default;
			IFormIntegerArray(const IFormIntegerArray &other) = delete;
			IFormIntegerArray(IFormIntegerArray &&other) = delete;
			IFormIntegerArray &operator=(const IFormIntegerArray &other) = delete;
			IFormIntegerArray &operator=(IFormIntegerArray &&other) = delete;
		public:
			virtual IntegerArray getValue() = 0; // Return value
			virtual int getMinCount() = 0; // Return minimum allowed count of items in array
			virtual bool hasMin() = 0; // Return whether there is low limit for item values
			virtual bool hasMax() = 0; // Return whether there is high limit for item values
			virtual int getMin() = 0; // Return values low limit
			virtual int getMax() = 0; // Return values high limit

			virtual bool setValue(const IntegerArray &value) = 0; // Set value
			virtual bool setMinCount(const int value) = 0; // Set minimum allowed count of items in array
			virtual bool setHasMin(const bool value) = 0; // Set whether there is low limit for item values
			virtual bool setHasMax(const bool value) = 0; // Set whether there is high limit for item values
			virtual bool setMin(const int value) = 0; // Set values low limit
			virtual bool setMax(const int value) = 0; // Set values high limit
		};
	}
}