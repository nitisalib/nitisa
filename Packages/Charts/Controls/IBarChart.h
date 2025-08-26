// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/ICartesianChart.h"

namespace nitisa
{
	namespace charts
	{
		class IBarChart :public virtual ICartesianChart
		{
		protected:
			IBarChart() = default;
			~IBarChart() = default;
			IBarChart(const IBarChart &other) = delete;
			IBarChart(IBarChart &&other) = delete;
			IBarChart &operator=(const IBarChart &other) = delete;
			IBarChart &operator=(IBarChart &&other) = delete;
		public:
			// No additional properties and methods
		};
	}
}