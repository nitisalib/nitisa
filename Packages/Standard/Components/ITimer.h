// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IComponent.h"

namespace nitisa
{
	namespace standard
	{
		class ITimer :public virtual IComponent
		{
		protected:
			ITimer() = default;
			~ITimer() = default;
			ITimer(const ITimer &other) = delete;
			ITimer(ITimer &&other) = delete;
			ITimer &operator=(const ITimer &other) = delete;
			ITimer &operator=(ITimer &&other) = delete;
		public:
			virtual float getInterval() = 0; // Return interval
			virtual bool isEnabled() = 0; // Return whether is enabled

			virtual bool setInterval(const float value) = 0; // Set interval(in seconds)
			virtual bool setEnabled(const bool value) = 0; // Enable/disable
		};
	}
}