// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	namespace charts
	{
		class IChartData;
		class IChartDataSet;

		class IRadialChart :public virtual IControl
		{
		protected:
			IRadialChart() = default;
			~IRadialChart() = default;
			IRadialChart(const IRadialChart &other) = delete;
			IRadialChart(IRadialChart &&other) = delete;
			IRadialChart &operator=(const IRadialChart &other) = delete;
			IRadialChart &operator=(IRadialChart &&other) = delete;
		public:
			void(*OnHoverPoint)(IRadialChart *sender, IChartData *data, const int index); // Event called when point appears under mouse pointer
			void(*OnLeavePoint)(IRadialChart *sender); // Event called when there were point below mouse point and now no new point is below mouse pointer. Do not called when one point becomes unhovered and another becomes hovered. In the last case only OnHoverPoint will be called

			virtual IChartDataSet *getDataSet() = 0; // Return assigned data set

			virtual bool setDataSet(IChartDataSet *value, const bool release_old) = 0; // Assign new data set. If release_old is set to true then existing data set will be destroyed first

			virtual void Update() = 0; // Update widget. Should be called after updating data set to refresh a widget
		};
	}
}