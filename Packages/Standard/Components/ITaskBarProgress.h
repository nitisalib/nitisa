// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IComponent.h"
#include "Nitisa/Interfaces/IWindow.h"

namespace nitisa
{
	namespace standard
	{
		class ITaskBarProgress :public virtual IComponent
		{
		protected:
			ITaskBarProgress() = default;
			~ITaskBarProgress() = default;
			ITaskBarProgress(const ITaskBarProgress &other) = delete;
			ITaskBarProgress(ITaskBarProgress &&other) = delete;
			ITaskBarProgress &operator=(const ITaskBarProgress &other) = delete;
			ITaskBarProgress &operator=(ITaskBarProgress &&other) = delete;
		public:
			virtual bool setType(const IWindow::ProgressType value) = 0; // Set progress bar type
			virtual bool setProgress(const float value) = 0; // Set progress bar value. Automatically change type to wptNormal if type is wptNone or wptIndeterminate
		};
	}
}