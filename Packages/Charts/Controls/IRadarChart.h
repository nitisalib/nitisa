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
		class IRadarChart :public virtual IRadialChart
		{
		protected:
			IRadarChart() = default;
			~IRadarChart() = default;
			IRadarChart(const IRadarChart &other) = delete;
			IRadarChart(IRadarChart &&other) = delete;
			IRadarChart &operator=(const IRadarChart &other) = delete;
			IRadarChart &operator=(IRadarChart &&other) = delete;
		public:
			virtual bool isAutoRange() = 0; // Return whether range should be calculated automatically to represent entire data of the dataset assigned to a widget
			virtual float getRange() = 0; // Return range in global coordinate space represented on client area of control

			virtual bool setAutoRange(const bool value) = 0; // Set whether range should be calculated automatically to represent entire data of the dataset assigned to a widget
			virtual bool setRange(const float value) = 0; // Set range in global coordinate space represented on client area of control
		};
	}
}