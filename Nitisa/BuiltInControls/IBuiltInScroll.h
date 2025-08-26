// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IBuiltInControl.h"

namespace nitisa
{
	class IBuiltInScroll :public virtual IBuiltInControl
	{
	protected:
		IBuiltInScroll() = default;
		~IBuiltInScroll() = default;
		IBuiltInScroll(const IBuiltInScroll &other) = delete;
		IBuiltInScroll(IBuiltInScroll &&other) = delete;
		IBuiltInScroll &operator=(const IBuiltInScroll &other) = delete;
		IBuiltInScroll &operator=(IBuiltInScroll &&other) = delete;
	public:
		virtual float getMin() = 0; // Return minimum value
		virtual float getMax() = 0; // Return maximum value. Should be at least 1 greater then minimum value
		virtual float getScroll() = 0; // Return current value
		virtual float getScrollerSize() = 0; // Return size of part which can be dragged for scrolling
		virtual float getDeltaSmall() = 0; // Return scroll value by clicking on arrow
		virtual float getDeltaMedium() = 0; // Return scroll value by mouse wheel scrolling
		virtual float getDeltaLarge() = 0; // Return scroll value by clicking on area between scroller and arrow
		virtual bool isVertical() = 0; // Whether vertical or horizontal
		virtual bool isArrowsVisible() = 0; // Return whether arrows are visible

		virtual bool setMin(const float value) = 0; // Set minimum value
		virtual bool setMax(const float value) = 0; // Set maximum value
		virtual bool setScroll(const float value) = 0; // Set current value
		virtual bool setScrollerSize(const float value) = 0; // Set scroller size. Set to 0 to use automatically calculated size
		virtual bool setDeltaSmall(const float value) = 0; // Set scrolling value by clicking on scroll arrows
		virtual bool setDeltaMedium(const float value) = 0; // Set scrolling value by mouse wheel
		virtual bool setDeltaLarge(const float value) = 0; // Set scrolling value by clicking on area between scroller and scrolling arrow. Set to 0 to use automatically calculated delta
		virtual bool setVertical(const bool value) = 0; // Set whether scroll is vertical or horizontal
		virtual bool setArrowsVisible(const bool value) = 0; // Set whether arrows are visible
	};
}