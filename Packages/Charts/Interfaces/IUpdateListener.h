// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	namespace charts
	{
		class IUpdateListener
		{
		protected:
			IUpdateListener() = default;
			~IUpdateListener() = default;
			IUpdateListener(const IUpdateListener &other) = delete;
			IUpdateListener(IUpdateListener &&other) = delete;
			IUpdateListener &operator=(const IUpdateListener &other) = delete;
			IUpdateListener &operator=(IUpdateListener &&other) = delete;
		public:
			virtual void NotifyOnUpdate() = 0; // Notification called when data was updated
		};
	}
}