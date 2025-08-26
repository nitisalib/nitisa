// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Math/PointB.h"

namespace nitisa
{
	namespace standard
	{
		class IFormPointB
		{
		protected:
			IFormPointB() = default;
			~IFormPointB() = default;
			IFormPointB(const IFormPointB &other) = delete;
			IFormPointB(IFormPointB &&other) = delete;
			IFormPointB &operator=(const IFormPointB &other) = delete;
			IFormPointB &operator=(IFormPointB &&other) = delete;
		public:
			virtual PointB getValue() = 0; // Return value

			virtual bool setValue(const PointB &value) = 0; // Set value

			virtual void ActivateFirstEnabledInput() = 0;
		};
	}
}