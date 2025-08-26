// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IRadialChart.h"

namespace nitisa
{
	namespace charts
	{
		class ISemiDoughnutChart :public virtual IRadialChart
		{
		protected:
			ISemiDoughnutChart() = default;
			~ISemiDoughnutChart() = default;
			ISemiDoughnutChart(const ISemiDoughnutChart &other) = delete;
			ISemiDoughnutChart(ISemiDoughnutChart &&other) = delete;
			ISemiDoughnutChart &operator=(const ISemiDoughnutChart &other) = delete;
			ISemiDoughnutChart &operator=(ISemiDoughnutChart &&other) = delete;
		public:
			// No additional properties and methods
		};
	}
}