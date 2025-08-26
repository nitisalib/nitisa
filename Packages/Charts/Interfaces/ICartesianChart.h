// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"
#include "Nitisa/Math/PointB.h"
#include "Nitisa/Math/PointF.h"

namespace nitisa
{
	namespace charts
	{
		class IChartData;
		class IChartDataSet;

		class ICartesianChart :public virtual IControl
		{
		protected:
			ICartesianChart() = default;
			~ICartesianChart() = default;
			ICartesianChart(const ICartesianChart &other) = delete;
			ICartesianChart(ICartesianChart &&other) = delete;
			ICartesianChart &operator=(const ICartesianChart &other) = delete;
			ICartesianChart &operator=(ICartesianChart &&other) = delete;
		public:
			void(*OnHoverPoint)(ICartesianChart *sender, IChartData *data, const int index); // Event called when point appears under mouse pointer
			void(*OnLeavePoint)(ICartesianChart *sender); // Event called when there were point below mouse point and now no new point is below mouse pointer. Do not called when one point becomes unhovered and another becomes hovered. In the last case only OnHoverPoint will be called

			virtual PointF getXRange() = 0; // Return range in X-direction in global coordinate space represented on client area of control
			virtual PointF getYRange() = 0; // Return range in Y-direction in global coordinate space represented on client area of control
			virtual PointB getAutoRange() = 0; // Return whether ranges in X and Y directions should be calculated automatically to represent entire data of the dataset assigned to a widget
			virtual IChartDataSet *getDataSet() = 0; // Return assigned data set

			virtual bool setXRange(const PointF &value) = 0; // Set range in X-direction in global coordinate space represented on client area of control. It also cancels automatic range calculation in X direction
			virtual bool setYRange(const PointF &value) = 0; // Set range in Y-direction in global coordinate space represented on client area of control. It also cancels automatic range calculation in Y direction
			virtual bool setAutoRange(const PointB &value) = 0; // Set whether ranges in X and Y directions should be calculated automatically(to represent entire data of the dataset assigned to a widget)
			virtual bool setDataSet(IChartDataSet *value, const bool release_old) = 0; // Assign new data set. If release_old is set to true then existing data set will be destroyed first

			virtual void Update() = 0; // Update widget. Should be called after updating data set to refresh a widget
		};
	}
}