// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Controls/IForexChart.h"

namespace nitisa
{
	namespace charts
	{
		class IUpdateListener;

		class IFormForexChartData
		{
		protected:
			IFormForexChartData() = default;
			~IFormForexChartData() = default;
			IFormForexChartData(const IFormForexChartData &other) = delete;
			IFormForexChartData(IFormForexChartData &&other) = delete;
			IFormForexChartData &operator=(const IFormForexChartData &other) = delete;
			IFormForexChartData &operator=(IFormForexChartData &&other) = delete;
		public:
			virtual IForexChart::IForexChartData *getValue() = 0; // Return value

			virtual bool setValue(IForexChart::IForexChartData *value) = 0; // Set value

			virtual void setUpdateListener(IUpdateListener *listener) = 0; // Assign update listener
		};
	}
}