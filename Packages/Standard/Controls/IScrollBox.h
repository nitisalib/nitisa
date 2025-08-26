// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ScrollVisibility.h"
#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	namespace standard
	{
		class IScrollBox :public virtual IControl
		{
		protected:
			IScrollBox() = default;
			~IScrollBox() = default;
			IScrollBox(const IScrollBox &other) = delete;
			IScrollBox(IScrollBox &&other) = delete;
			IScrollBox &operator=(const IScrollBox &other) = delete;
			IScrollBox &operator=(IScrollBox &&other) = delete;
		public:
			virtual ScrollVisibility getVerticalScrollVisibility() = 0; // Return vertical scroll visibility
			virtual bool isVerticalScrollEnabled() = 0; // Whether vertical scroll enabled
			virtual float getVerticalScrollMax() = 0; // Return vertical scroll maximum value
			virtual float getVerticalScrollPosition() = 0; // Return vertical scroll position
			virtual ScrollVisibility getHorizontalScrollVisibility() = 0; // Return horizontal scroll visibility
			virtual bool isHorizontalScrollEnabled() = 0; // Whether horizontal scroll enabled
			virtual float getHorizontalScrollMax() = 0; // Return horizontal scroll maximum value
			virtual float getHorizontalScrollPosition() = 0; // Return horizontal scroll position

			virtual bool setVerticalScrollVisibility(const ScrollVisibility value) = 0; // Set vertical scroll visibility
			virtual bool setVerticalScrollPosition(const float value) = 0; // Set vertical scroll position
			virtual bool setHorizontalScrollVisibility(const ScrollVisibility value) = 0; // Set horizontal scroll visibility
			virtual bool setHorizontalScrollPosition(const float value) = 0; // Set horizontal scroll position
		};
	}
}