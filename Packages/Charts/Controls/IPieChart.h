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
		class IPieChart :public virtual IRadialChart
		{
		protected:
			IPieChart() = default;
			~IPieChart() = default;
			IPieChart(const IPieChart &other) = delete;
			IPieChart(IPieChart &&other) = delete;
			IPieChart &operator=(const IPieChart &other) = delete;
			IPieChart &operator=(IPieChart &&other) = delete;
		public:
			// No additional properties and methods
		};
	}
}