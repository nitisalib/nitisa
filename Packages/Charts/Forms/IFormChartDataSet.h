// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	namespace charts
	{
		class IChartDataSet;
		class IUpdateListener;

		class IFormChartDataSet
		{
		protected:
			IFormChartDataSet() = default;
			~IFormChartDataSet() = default;
			IFormChartDataSet(const IFormChartDataSet &other) = delete;
			IFormChartDataSet(IFormChartDataSet &&other) = delete;
			IFormChartDataSet &operator=(const IFormChartDataSet &other) = delete;
			IFormChartDataSet &operator=(IFormChartDataSet &&other) = delete;
		public:
			virtual IChartDataSet *getValue() = 0; // Return value

			virtual bool setValue(IChartDataSet *value) = 0; // Set value

			virtual void setUpdateListener(IUpdateListener *listener) = 0; // Assign update listener
		};
	}
}