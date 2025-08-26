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
		class ILineChart :public virtual ICartesianChart
		{
		protected:
			ILineChart() = default;
			~ILineChart() = default;
			ILineChart(const ILineChart &other) = delete;
			ILineChart(ILineChart &&other) = delete;
			ILineChart &operator=(const ILineChart &other) = delete;
			ILineChart &operator=(ILineChart &&other) = delete;
		public:
			// No additional properties and methods
		};
	}
}