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
		class IMultiBarChart :public virtual ICartesianChart
		{
		protected:
			IMultiBarChart() = default;
			~IMultiBarChart() = default;
			IMultiBarChart(const IMultiBarChart &other) = delete;
			IMultiBarChart(IMultiBarChart &&other) = delete;
			IMultiBarChart &operator=(const IMultiBarChart &other) = delete;
			IMultiBarChart &operator=(IMultiBarChart &&other) = delete;
		public:
			// No additional properties and methods
		};
	}
}