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
		class IHSVPlane;

		class IHSVBar :public virtual IControl
		{
		protected:
			IHSVBar() = default;
			~IHSVBar() = default;
			IHSVBar(const IHSVBar &other) = delete;
			IHSVBar(IHSVBar &&other) = delete;
			IHSVBar &operator=(const IHSVBar &other) = delete;
			IHSVBar &operator=(IHSVBar &&other) = delete;
		public:
			virtual int getHue() = 0; // Return hue(0..360)
			virtual IHSVPlane *getHSVPlane() = 0; // Return assigned HSVPlane widget

			virtual bool setHue(const int value) = 0; // Set hue
			virtual bool setHSVPlane(IHSVPlane *value) = 0; // Assign HSVPlane widget
		};
	}
}