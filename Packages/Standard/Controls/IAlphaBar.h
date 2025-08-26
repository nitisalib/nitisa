// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	namespace standard
	{
		class IAlphaBar :public virtual IControl
		{
		protected:
			IAlphaBar() = default;
			~IAlphaBar() = default;
			IAlphaBar(const IAlphaBar &other) = delete;
			IAlphaBar(IAlphaBar &&other) = delete;
			IAlphaBar &operator=(const IAlphaBar &other) = delete;
			IAlphaBar &operator=(IAlphaBar &&other) = delete;
		public:
			virtual int getAlpha() = 0; // Return alpha(0..255)

			virtual bool setAlpha(const int value) = 0; // Set alpha
		};
	}
}