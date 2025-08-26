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
		class ITrackBar :public virtual IControl
		{
		protected:
			ITrackBar() = default;
			~ITrackBar() = default;
			ITrackBar(const ITrackBar &other) = delete;
			ITrackBar(ITrackBar &&other) = delete;
			ITrackBar &operator=(const ITrackBar &other) = delete;
			ITrackBar &operator=(ITrackBar &&other) = delete;
		public:
			void(*OnChange)(ITrackBar *sender); // Event called when control's value is changed

			virtual int getMin() = 0; // Return minimum
			virtual int getMax() = 0; // Return maximum
			virtual int getValue() = 0; // Return current value

			virtual bool setMin(const int value) = 0; // Set minimum
			virtual bool setMax(const int value) = 0; // Set maximum
			virtual bool setValue(const int value) = 0; // Set current value
		};
	}
}