// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		class IScrollBarLite :public virtual IControl
		{
		protected:
			IScrollBarLite() = default;
			~IScrollBarLite() = default;
			IScrollBarLite(const IScrollBarLite &other) = delete;
			IScrollBarLite(IScrollBarLite &&other) = delete;
			IScrollBarLite &operator=(const IScrollBarLite &other) = delete;
			IScrollBarLite &operator=(IScrollBarLite &&other) = delete;
		public:
			virtual float getMin() = 0; // Return minimum allowed position value
			virtual float getMax() = 0; // Return maximum allowed position value
			virtual float getPosition() = 0; // Return position/scroll value
			virtual bool isVertical() = 0; // Return whether is vertical or horizontal

			virtual bool setMin(const float value) = 0; // Set minimum allowed position value
			virtual bool setMax(const float value) = 0; // Set maximum allowed position value
			virtual bool setPosition(const float value) = 0; // Set position/scroll value
			virtual bool setVertical(const bool value) = 0; // Set whether is vertical or horizontal
		};
	}
}