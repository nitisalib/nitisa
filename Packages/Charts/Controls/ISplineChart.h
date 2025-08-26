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
		class ISplineChart :public virtual ICartesianChart
		{
		protected:
			ISplineChart() = default;
			~ISplineChart() = default;
			ISplineChart(const ISplineChart &other) = delete;
			ISplineChart(ISplineChart &&other) = delete;
			ISplineChart &operator=(const ISplineChart &other) = delete;
			ISplineChart &operator=(ISplineChart &&other) = delete;
		public:
			// No additional properties and methods
		};
	}
}