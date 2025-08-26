// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Package/Interfaces/IProperty.h"

namespace nitisa
{
	namespace charts
	{
		class IChartDataSet;

		class IPropertyChartDataSet :public virtual IProperty
		{
		protected:
			IPropertyChartDataSet() = default;
			~IPropertyChartDataSet() = default;
			IPropertyChartDataSet(const IPropertyChartDataSet &other) = delete;
			IPropertyChartDataSet(IPropertyChartDataSet &&other) = delete;
			IPropertyChartDataSet &operator=(const IPropertyChartDataSet &other) = delete;
			IPropertyChartDataSet &operator=(IPropertyChartDataSet &&other) = delete;
		public:
			virtual IChartDataSet *getValue() = 0; // Return value

			virtual bool setValue(IChartDataSet *value) = 0; // Set value

			virtual void Update() = 0; // Call update on assigned widget
		};
	}
}