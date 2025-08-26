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
		class IStackedBarChart :public virtual ICartesianChart
		{
		protected:
			IStackedBarChart() = default;
			~IStackedBarChart() = default;
			IStackedBarChart(const IStackedBarChart &other) = delete;
			IStackedBarChart(IStackedBarChart &&other) = delete;
			IStackedBarChart &operator=(const IStackedBarChart &other) = delete;
			IStackedBarChart &operator=(IStackedBarChart &&other) = delete;
		public:
			// No additional properties and methods
		};
	}
}