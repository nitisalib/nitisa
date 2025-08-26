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
		class IToggle :public virtual IControl
		{
		protected:
			IToggle() = default;
			~IToggle() = default;
			IToggle(const IToggle &other) = delete;
			IToggle(IToggle &&other) = delete;
			IToggle &operator=(const IToggle &other) = delete;
			IToggle &operator=(IToggle &&other) = delete;
		public:
			virtual bool isOn() = 0; // Return whether the widget is in "on" or "off" state

			virtual bool setOn(const bool value) = 0; // Set whether the widget is in "on" or "off" state

			virtual void Toggle() = 0; // Toggle state
		};
	}
}