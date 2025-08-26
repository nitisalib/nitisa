// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Math/RectB.h"

namespace nitisa
{
	namespace standard
	{
		class IFormRectB
		{
		protected:
			IFormRectB() = default;
			~IFormRectB() = default;
			IFormRectB(const IFormRectB &other) = delete;
			IFormRectB(IFormRectB &&other) = delete;
			IFormRectB &operator=(const IFormRectB &other) = delete;
			IFormRectB &operator=(IFormRectB &&other) = delete;
		public:
			virtual RectB getValue() = 0; // Return value

			virtual bool setValue(const RectB &value) = 0; // Set value

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}