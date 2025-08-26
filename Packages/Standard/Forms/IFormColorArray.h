// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Image/ColorArray.h"

namespace nitisa
{
	namespace standard
	{
		class IFormColorArray
		{
		protected:
			IFormColorArray() = default;
			~IFormColorArray() = default;
			IFormColorArray(const IFormColorArray &other) = delete;
			IFormColorArray(IFormColorArray &&other) = delete;
			IFormColorArray &operator=(const IFormColorArray &other) = delete;
			IFormColorArray &operator=(IFormColorArray &&other) = delete;
		public:
			virtual ColorArray getValue() = 0; // Return value
			virtual int getMinCount() = 0; // Return minimum allowed count of items in array

			virtual bool setValue(const ColorArray &value) = 0; // Set value
			virtual bool setMinCount(const int value) = 0; // Set minimum allowed count of items in array
		};
	}
}