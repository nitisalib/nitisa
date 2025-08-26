// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Image/Gradient.h"

namespace nitisa
{
	namespace standard
	{
		class IFormGradient
		{
		protected:
			IFormGradient() = default;
			~IFormGradient() = default;
			IFormGradient(const IFormGradient &other) = delete;
			IFormGradient(IFormGradient &&other) = delete;
			IFormGradient &operator=(const IFormGradient &other) = delete;
			IFormGradient &operator=(IFormGradient &&other) = delete;
		public:
			virtual Gradient *getValue() = 0; // Return value

			virtual bool setValue(Gradient &value) = 0; // Set value
		};
	}
}