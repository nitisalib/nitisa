// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Image/Color.h"

namespace nitisa
{
	namespace standard
	{
		class IFormColor
		{
		protected:
			IFormColor() = default;
			~IFormColor() = default;
			IFormColor(const IFormColor &other) = delete;
			IFormColor(IFormColor &&other) = delete;
			IFormColor &operator=(const IFormColor &other) = delete;
			IFormColor &operator=(IFormColor &&other) = delete;
		public:
			virtual Color getValue() = 0; // Return value

			virtual bool setValue(const Color &value) = 0; // Set value

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}