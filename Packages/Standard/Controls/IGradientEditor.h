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
	class Gradient;

	namespace standard
	{
		class IGradientEditor :public virtual IControl
		{
		protected:
			IGradientEditor() = default;
			~IGradientEditor() = default;
			IGradientEditor(const IGradientEditor &other) = delete;
			IGradientEditor(IGradientEditor &&other) = delete;
			IGradientEditor &operator=(const IGradientEditor &other) = delete;
			IGradientEditor &operator=(IGradientEditor &&other) = delete;
		public:
			virtual Gradient *getGradient() = 0; // Return gradient
			virtual int getActivePoint() = 0; // Return active point index. -1 - no active point

			virtual bool setActivePoint(const int value) = 0; // Set active point index
		};
	}
}