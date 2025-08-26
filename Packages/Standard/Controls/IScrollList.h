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
	class IBuiltInScroll;

	namespace standard
	{
		class IScrollList :public virtual IControl
		{
		public:
			enum class Orientation
			{
				LeftToRight,
				TopToBottom
			};
		protected:
			IScrollList() = default;
			~IScrollList() = default;
			IScrollList(const IScrollList &other) = delete;
			IScrollList(IScrollList &&other) = delete;
			IScrollList &operator=(const IScrollList &other) = delete;
			IScrollList &operator=(IScrollList &&other) = delete;
		public:
			virtual Orientation getOrientation() = 0; // Return child control alignment orientation
			virtual IBuiltInScroll *getScrollBar() = 0;
			virtual float getScroll() = 0;
			virtual float getScrollMax() = 0;

			virtual bool setOrientation(const Orientation value) = 0; // Set child control alignment orientation
			virtual bool setScrollBar(IBuiltInScroll *value) = 0;
			virtual bool setScroll(const float value) = 0;
		};
	}
}