// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Image/BorderColor.h"

namespace nitisa
{
	namespace standard
	{
		class IFormBorderColor
		{
		protected:
			IFormBorderColor() = default;
			~IFormBorderColor() = default;
			IFormBorderColor(const IFormBorderColor &other) = delete;
			IFormBorderColor(IFormBorderColor &&other) = delete;
			IFormBorderColor &operator=(const IFormBorderColor &other) = delete;
			IFormBorderColor &operator=(IFormBorderColor &&other) = delete;
		public:
			virtual BorderColor getValue() = 0; // Return value

			virtual bool setValue(const BorderColor &value) = 0; // Set value

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}