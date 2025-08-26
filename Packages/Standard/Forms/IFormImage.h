// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Image/Image.h"

namespace nitisa
{
	namespace standard
	{
		class IFormImage
		{
		protected:
			IFormImage() = default;
			~IFormImage() = default;
			IFormImage(const IFormImage &other) = delete;
			IFormImage(IFormImage &&other) = delete;
			IFormImage &operator=(const IFormImage &other) = delete;
			IFormImage &operator=(IFormImage &&other) = delete;
		public:
			virtual Image *getValue() = 0; // Return value

			virtual bool setValue(const Image &value) = 0; // Set value
		};
	}
}