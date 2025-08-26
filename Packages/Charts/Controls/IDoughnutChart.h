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
		class IDoughnutChart :public virtual IRadialChart
		{
		protected:
			IDoughnutChart() = default;
			~IDoughnutChart() = default;
			IDoughnutChart(const IDoughnutChart &other) = delete;
			IDoughnutChart(IDoughnutChart &&other) = delete;
			IDoughnutChart &operator=(const IDoughnutChart &other) = delete;
			IDoughnutChart &operator=(IDoughnutChart &&other) = delete;
		public:
			// No additional properties and methods
		};
	}
}