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
		class IProgressBar :public virtual IControl
		{
		protected:
			IProgressBar() = default;
			~IProgressBar() = default;
			IProgressBar(const IProgressBar &other) = delete;
			IProgressBar(IProgressBar &&other) = delete;
			IProgressBar &operator=(const IProgressBar &other) = delete;
			IProgressBar &operator=(IProgressBar &&other) = delete;
		public:
			virtual float getMin() = 0; // Return minimum allowed progress value
			virtual float getMax() = 0; // Return maximum allowed progress value
			virtual float getProgress() = 0; // Return progress value

			virtual bool setMin(const float value) = 0; // Set minimum allowed progress value
			virtual bool setMax(const float value) = 0; // Set maximum allowed progress value
			virtual bool setProgress(const float value) = 0; // Set progress value
		};
	}
}