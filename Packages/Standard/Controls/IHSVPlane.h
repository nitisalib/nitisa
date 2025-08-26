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
		class IHSVPlane :public virtual IControl
		{
		protected:
			IHSVPlane() = default;
			~IHSVPlane() = default;
			IHSVPlane(const IHSVPlane &other) = delete;
			IHSVPlane(IHSVPlane &&other) = delete;
			IHSVPlane &operator=(const IHSVPlane &other) = delete;
			IHSVPlane &operator=(IHSVPlane &&other) = delete;
		public:
			virtual int getHue() = 0; // Return hue(0..360)
			virtual float getSaturation() = 0; // Return saturation(0..1)
			virtual float getValue() = 0; // Return value(0..1)

			virtual bool setHue(const int value) = 0; // Set hue
			virtual bool setSaturation(const float value) = 0; // Set saturation
			virtual bool setValue(const float value) = 0; // Set value
		};
	}
}