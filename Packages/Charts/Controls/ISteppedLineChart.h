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
		class ISteppedLineChart :public virtual ICartesianChart
		{
		protected:
			ISteppedLineChart() = default;
			~ISteppedLineChart() = default;
			ISteppedLineChart(const ISteppedLineChart &other) = delete;
			ISteppedLineChart(ISteppedLineChart &&other) = delete;
			ISteppedLineChart &operator=(const ISteppedLineChart &other) = delete;
			ISteppedLineChart &operator=(ISteppedLineChart &&other) = delete;
		public:
			// No additional properties and methods
		};
	}
}