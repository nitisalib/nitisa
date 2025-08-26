// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/BoolArray.h"

namespace nitisa
{
	namespace standard
	{
		class IFormBoolArray
		{
		protected:
			IFormBoolArray() = default;
			~IFormBoolArray() = default;
			IFormBoolArray(const IFormBoolArray &other) = delete;
			IFormBoolArray(IFormBoolArray &&other) = delete;
			IFormBoolArray &operator=(const IFormBoolArray &other) = delete;
			IFormBoolArray &operator=(IFormBoolArray &&other) = delete;
		public:
			virtual BoolArray getValue() = 0; // Return value
			virtual int getMinCount() = 0; // Return minimum allowed count of items in array

			virtual bool setValue(const BoolArray &value) = 0; // Set value
			virtual bool setMinCount(const int value) = 0; // Set minimum allowed count of items in array
		};
	}
}