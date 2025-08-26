// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	namespace ide
	{
		class IViewControl
		{
		protected:
			IViewControl() = default;
			~IViewControl() = default;
			IViewControl(const IViewControl &other) = delete;
			IViewControl(IViewControl &&other) = delete;
			IViewControl &operator=(const IViewControl &other) = delete;
			IViewControl &operator=(IViewControl &&other) = delete;
		public:
			virtual bool ActivateView(const int index) = 0; // Activate view by index. Negative index deactivates view. Maximum index depends on specific view (usually 2..4)
		};
	}
}