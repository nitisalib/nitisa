// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Package/Interfaces/IProperty.h"
#include "../../Controls/IForexChart.h"

namespace nitisa
{
	namespace charts
	{
		class IPropertyForexChartData :public virtual IProperty
		{
		protected:
			IPropertyForexChartData() = default;
			~IPropertyForexChartData() = default;
			IPropertyForexChartData(const IPropertyForexChartData &other) = delete;
			IPropertyForexChartData(IPropertyForexChartData &&other) = delete;
			IPropertyForexChartData &operator=(const IPropertyForexChartData &other) = delete;
			IPropertyForexChartData &operator=(IPropertyForexChartData &&other) = delete;
		public:
			virtual IForexChart::IForexChartData *getValue() = 0; // Return value

			virtual bool setValue(IForexChart::IForexChartData *value) = 0; // Set value

			virtual void Update() = 0; // Call update on assigned widget
		};
	}
}